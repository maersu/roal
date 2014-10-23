/**     
    This file is part of Roal, a framework for simulations in the field
    of Artificial Intelligence and Aritificial Life.
    See http://roal.sourceforge.net/ for more informations.

    Copyright (c) 2005 Project Roal

    Roal is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Roal is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Roal; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "NNWalkerAgent.h"

namespace Roal
{

//------------------------------------------------------------------------------
NNWalkerAgent::NNWalkerAgent(const string name, DistributedWorld* world,
                             int populationSize, int generationCycle,
                             Position* newOriginPosition,
                             LeggedCreatureGenotype* genotype,
                             bool collectTrainingDataMode)
    : DistributedAgent(name, world, populationSize, generationCycle)
{
    this->genotype = genotype;
    this->factory = new LeggedCreatureFactory(name + "_factory", genotype);
    
    this->originPosition = newOriginPosition;
    this->populationSize = populationSize;
    
    this->collectTrainingDataMode = collectTrainingDataMode;
    
    this->phenotypesPoolSize = 5000;
    this->electedPhenotypes = 10;
    
    // Start the simulation
    initPopulation();
}


//------------------------------------------------------------------------------
void NNWalkerAgent::initPopulation()
{
    long genCnt = this->getGenerationCount();
    
    if (collectTrainingDataMode) {    
        
        // Generate random creatures
        for (int i = 0; i < this->populationSize; i++) {
            // Put the body at a random position around the agent's origin   
            Brain* walker = this->factory->generateRandomCreature(
                    "walker_"+toStdStr(genCnt)+"_"+toStdStr(i),
                    getRandomPosFromOrigin(originPosition,
                                           500.0 + this->populationSize*10));
            walker->getBody()->setCheckEmergency(true);  
            
            this->registerBody(walker->getBody());
            this->registerBrain(walker);
        }
        
    } else {
        
        // Train the neural network with a given data file
        cout << "Training neural network:" << endl;
        trainNeuralNetwork("/tmp/"+this->getName()+"_FANN.data", "/tmp/"+this->getName()+"_FANN.net");
        
        // Create a pool of phenotypes with predicted fitness values
        cout << endl << "Generating a pool of " << this->phenotypesPoolSize
             << " phenotypes and predicting a fitness for each..." << endl;
        list<PhenotypeFitness> phenotypes =
                generatePhenotypePool(this->phenotypesPoolSize,
                                      "/tmp/"+this->getName()+"_FANN.net");
    
        //phenotypes.reverse(); //use this to elect the worst phenotypes
        
        // Elect the best phenotypes in the pool
        cout << endl << "Predicted fitness (beween 0 and 1) of the elected "
             << this->electedPhenotypes << " phenotypes:" << endl;
        electAndRegisterPhenotypes(phenotypes, this->electedPhenotypes);
        
    }

    Agent::initPopulation();
}


//------------------------------------------------------------------------------
void NNWalkerAgent::handleMutation()
{
    long genCnt = this->getGenerationCount();
    
    if (!collectTrainingDataMode) {
        
        // Sort the creatures by the distances they travelled (with quicksort)
        LeggedCreatureBrain* brainsArray[this->populationSize];
        BrainsMap::iterator it;
        int i = 0;
        for (it=brains.begin(); it!=brains.end(); it++) {
            brainsArray[i] = (LeggedCreatureBrain*)it->second;
            i++;
        }
        i = 0;
        for (it=deadBrains.begin(); it!=deadBrains.end(); it++) {
            ((LeggedCreatureBrain*)it->second)->resetDistanceTravelled();
            brainsArray[i] = (LeggedCreatureBrain*)it->second;
            i++;
        }
        distancesSort(brainsArray, 0, (int)brains.size()-1);
        
        // Prepare and send message with statistics to master
        string msgLine = toStdStr(this->getGenerationCount()) + " ";
        for (int i = brains.size()-1; i >= 0; i--) {
            msgLine += toStdStr(brainsArray[i]->getDistanceTravelled()) + " ";
        }
        ConnectorMessage* messageLine = new ConnectorMessage(DIST_STAT_FROM_AGENT);
        messageLine->setValue(DIST_STAT_GENCOUNT,toStdStr(this->getGenerationCount()));
        messageLine->setValue(DIST_LINE_STAT_LINE,msgLine);
        messageLine->setValue(DIST_LINE_STAT_VALUECOUNT,toStdStr((int)(brains.size())));
        
        this->sendCommandToMaster(messageLine);
        
    }
    
    if (collectTrainingDataMode) {
        
        File* file = new File("/tmp/" + this->getName() + "_FANN.data");
        if (!file->exists()) {
            // Write header (#records, #input neurons, #output neurons)
            file->write("0 32 1");
        }
        delete file;
        
    }
    
    // Read existing training data from NN data file
    ifstream dataInputFile(("/tmp/" + this->getName() + "_FANN.data").c_str());
    string data = "";
    string line;
    int recordCounter;
    string inputOutputNeurons;
    if (dataInputFile.is_open()) {
        int i=0;
        while (!dataInputFile.eof()) {
            getline(dataInputFile, line);
            if (i==0) {
                recordCounter = atoi(line.substr(0, line.find(" ", 0)).c_str());
                inputOutputNeurons = line.substr(line.find(" ", 0)+1).c_str();
            } else {
                data += line + "\n";
            }
            i++;
        }
        dataInputFile.close();
    } else {
        cerr << "Unable to open file '" << "/tmp/" << this->getName() << "_FANN.data" << "' to read" << endl;
    }
    
    ofstream dataOutputFile(("/tmp/" + this->getName() + "_FANN.data").c_str());
    if (dataOutputFile.is_open()) {
        // Write header line with record counter and amount of input/output neurons
        recordCounter += brains.size();
        dataOutputFile << recordCounter << " " << inputOutputNeurons << endl;
        
        // Write existing results to NN data file
        dataOutputFile << data;
        
        // Write results from actual generation to NN data file
        for (BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) {
            LeggedCreatureBrain*  brain = (LeggedCreatureBrain*)it->second; 
            LeggedCreaturePhenotype* ft = (LeggedCreaturePhenotype*)brain->getPhenotype();
            dataOutputFile << ft->toNormalizeValueString(" ") << endl;
            float distance = (float)(1.0/100.0*brain->getDistanceTravelled());
            if (distance < 0.0001) { distance = 0.0; }
            dataOutputFile << toStdStr(distance) << endl;
        }
        for (BrainsMap::iterator it = deadBrains.begin(); it != deadBrains.end(); it++) {
            LeggedCreatureBrain*  brain = (LeggedCreatureBrain*)it->second; 
            LeggedCreaturePhenotype* ft = (LeggedCreaturePhenotype*)brain->getPhenotype();
            dataOutputFile << ft->toNormalizeValueString(" ") << endl;
            dataOutputFile << 0 << endl;
        }
        dataOutputFile.close();
    } else {
        cerr << "Unable to open file '" << "/tmp/" << this->getName()
             << "_FANN.data" << "' to write" << endl;
    }
    
    // Remove the brains and bodies
    this->killAllBrains();
    this->killAllBodies();
    
    if (collectTrainingDataMode) {
        
        this->initPopulation();
        
    } else {
        
        // Train the neural network with data file (that contains the new data)
        cout << "Training neural network:" << endl;
        trainNeuralNetwork("/tmp/" + this->getName()+"_FANN.data", this->getName()+"_FANN.net");
        
        // Create a new pool of phenotypes with predicted fitness values
        cout << endl << "Generating a pool of " << this->phenotypesPoolSize
             << " phenotypes and predicting a fitness for each..." << endl;
        list<PhenotypeFitness> phenotypes =
                generatePhenotypePool(this->phenotypesPoolSize,
                                      "/tmp/" + this->getName()+"_FANN.net");
        
        // Elect the best phenotypes in the pool
        cout << endl << "Predicted fitness (beween 0 and 1) of the elected "
             << this->electedPhenotypes << " phenotypes:" << endl;
        electAndRegisterPhenotypes(phenotypes, this->electedPhenotypes);
        
    }
}


//------------------------------------------------------------------------------
void NNWalkerAgent::trainNeuralNetwork(string dataFile, string netFile)
{
    const float connection_rate = 1;
    const float learning_rate = 0.7;
    const unsigned int num_input = 33;
    const unsigned int num_output = 1;
    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = 16;
    const float desired_error = 0.02;
    const unsigned int max_iterations = 5000;
    const unsigned int iterations_between_reports = 1000;

    struct fann *ann = fann_create(connection_rate, learning_rate, num_layers,
                                   num_input, num_neurons_hidden,
                                   num_output);
    
    fann_set_activation_function_hidden(ann, FANN_SIGMOID);
    fann_set_activation_function_output(ann, FANN_SIGMOID);
    
    // Train the neural network
    char data[dataFile.size()];
    strcpy(data, dataFile.c_str());
    fann_train_on_file(ann, data, max_iterations,
                       iterations_between_reports, desired_error);
    
    // Write trained NN to a file
    char net[netFile.size()];
    strcpy(net, netFile.c_str());
    fann_save(ann, net);
    
    fann_destroy(ann);
}


//------------------------------------------------------------------------------
list<PhenotypeFitness> NNWalkerAgent::generatePhenotypePool(int phenotypesPoolSize,
                                                            string netFile)
{
    list<PhenotypeFitness> phenotypes;
    
    for (int i=0; i<phenotypesPoolSize; i++) {
        // Create a random phenotype
        LeggedCreaturePhenotype* phenotype =
                (LeggedCreaturePhenotype*)genotype->getRandomPhenotype();
        
        // Create a trained NN from a file
        char net[netFile.size()];
        strcpy(net, netFile.c_str());
        struct fann *ann = fann_create_from_file(net);
        
        // Set the values of the input neurons
        fann_type input[phenotype->getValuesCount()];
        vector<float> inputVector;
        inputVector = phenotype->toNormalizeVector();
        int k=0;
        for(vector<float>::iterator it = inputVector.begin();
            it != inputVector.end(); it++) {
            input[k++] = *it;
        }
            
        // Let the NN calculate a prediction of the fitness of this phenotype
        fann_type* output = fann_run(ann, input);
        
        // Save the phenotype into the pool-list, ordered by fitness
        PhenotypeFitness pf;
        pf.phenotype = phenotype;
        pf.fitness = *output;
        list<PhenotypeFitness>::iterator it = phenotypes.begin();
        while (it != phenotypes.end() && it->fitness > pf.fitness) {
            it++;
        }
        // Insert new phenotype before the one with next bigger fitness value
        phenotypes.insert(it, pf);
        
        fann_destroy(ann);
    }
    
    return phenotypes;
}


//------------------------------------------------------------------------------
void NNWalkerAgent::electAndRegisterPhenotypes(list<PhenotypeFitness> phenotypes,
                                    int numberOfPhenotypes)
{
    int i=0;
    for(list<PhenotypeFitness>::iterator it = phenotypes.begin();
        it != phenotypes.end(); it++) {
        if (i<numberOfPhenotypes) {
            cout << it->fitness << endl;
            // Put the creature at a random position around the Agent's origin point
            Brain* walker = this->factory->generateCreature(
                "NNWalker_" + toStdStr(getGenerationCount()) + "_" + toStdStr(i),
                getRandomPosFromOrigin(originPosition, 300.0 + this->populationSize*10),
                it->phenotype // The phenotype
            );
            walker->getBody()->setCheckEmergency(false);
            this->registerBody(walker->getBody());
            this->registerBrain(walker);
            i++;
        } else {
            // Delete the unused phenotypes
            delete it->phenotype;
        }
    }
}

//------------------------------------------------------------------------------
void NNWalkerAgent::distancesSort(LeggedCreatureBrain** brainsArray,
                                  int left, int right)
{
    if (left >= right) { return; }
    int l = left-1;
    int r = right;
    while (true)
    {
        while ((brainsArray[++l]->getDistanceTravelled())
                    < ((brainsArray[right]->getDistanceTravelled())))
        {
            if (l>=r) { break; }
        }
        while ((brainsArray[--r]->getDistanceTravelled())
                    > ((brainsArray[right]->getDistanceTravelled())))
        {
            if (l>=r) { break; }
        }
        if (l>=r) { break; }
        
        LeggedCreatureBrain* temp = brainsArray[l];
        brainsArray[l] = brainsArray[r];
        brainsArray[r] = temp;
    }
    LeggedCreatureBrain* temp = brainsArray[l];
    brainsArray[l] = brainsArray[right];
    brainsArray[right] = temp;
    
    distancesSort(brainsArray, left, l-1);
    distancesSort(brainsArray, l+1, right);
}

};
