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

#include "WalkerSuperAgent.h"
#include <iostream>
#include <stdio.h>

namespace Roal
{

//------------------------------------------------------------------------------
WalkerSuperAgent::WalkerSuperAgent(const std::string name, World* world, int brainPopulationSize, 
                     int bodyPopulationSize, int generationCycle, 
                     Position* newOriginPosition, float newbreedRate)
: Agent(name, world, bodyPopulationSize, generationCycle)
{  
    //more done 100% is impossible and less than 0% too
    if (newbreedRate > 1.0){
      this->newbreedRate = 1.0;
    } else if (newbreedRate < 0.0) {
      this->newbreedRate = 0.0;
    } else {
      this->newbreedRate =newbreedRate;
    }
    this->originPosition = newOriginPosition;
    this->brainPopulationSize = brainPopulationSize;
    
    // we don't need dead bodies
    if (this->brainPopulationSize <= bodyPopulationSize) {
        this->brainPopulationSize = (bodyPopulationSize/2);
    }
    
    //start the simualtion
    initPopulation();
}

//------------------------------------------------------------------------------
void WalkerSuperAgent::initPopulation()
{
    // Create and register Walker's and WalkerBrain's.
    long genCnt = this->getGenerationCount();   
    
    std::string walkerName;
    std::string brainName;
    
    
    for (int i=1; i < this->brainPopulationSize; i++) {
        
        brainName = this->getName()+"_Brain_"+toStdStr(genCnt) +"_"+toStdStr(i);
             
        // Create the Brain
        WalkerBrain* walkerBrain = new WalkerBrain(brainName);
        
        brainsCon[i] = walkerBrain;
    }
   
    
    
    for (int k=1; k <= this->populationSize; k++) {
        
        // Create the Body
        walkerName = this->getName()+"_Body_"+ toStdStr(genCnt) +"_"+toStdStr(k);
        
        //create a random position for the body around of the agent origin   
        Walker* walker = new Walker(walkerName, 
                        this->getRandomPosFromOrigin(originPosition, 
                                            50.0+this->populationSize*20));
         this->registerBody(walker);
         bodiesCon[k] = walker;
    }

         pickNetxBrains();

         // Call super method
         Agent::initPopulation();
}


//------------------------------------------------------------------------------
void WalkerSuperAgent::pickNetxBrains()
{
    
    int hits = 0;
    brains.clear();
    // try a possible key
    while (hits < populationSize){
       
        
       int m = (rand()%brainsCon.size()+1);
       
       
       WalkerBrain* aWalkerBrain = (WalkerBrain*)(brainsCon[m]);
       
        
       if (!isBrainRegistered(aWalkerBrain->getName())) {
        
          this->registerBrain(aWalkerBrain);
          hits++;
          ((Walker*)bodiesCon[hits])->resetDistanceTravelled();
           aWalkerBrain->registerBody(bodiesCon[hits]);
       }
    }
}

//------------------------------------------------------------------------------
void WalkerSuperAgent::handleMutation()
{
    // Put the brains into an array
    Brain* brainsArray[(int)brains.size()];
    int i = 0; 
    BrainsMap::iterator it;
    for (it=brains.begin(); it!=brains.end(); it++) {
        brainsArray[i] = it->second;
        i++;
    }
    
    // Sort the array by the distances the Walker's traveled (with quicksort)
    distancesSort(brainsArray, 0, (int)brains.size()-1);
    
    // Write generation data to file
    string dataFilename = "/tmp/" + this->getName() + "_lineStat.data";
    string configFilename = "/tmp/" + this->getName() + "_lineStat.plot";
    
    File* gnuplotData = new File(dataFilename);
    
    if (this->getGenerationCount()==1) {
        // Create GnuPlot config file
        string cfg = "set title 'Roal Agent: "+ this->getName()
            + "'\nset xlabel 'Generation'\nset ylabel 'Covered distance [m]'\n"
            + "set autoscale\nplot ";
        for (int i=0; i<brains.size(); i++) {
            if (i>0) {
                cfg += ", ";
            }
            cfg += "'" + dataFilename + "' using 1:" + toStdStr(i+2)
                + " with lines title 'Creature " + toStdStr(i+1) + "'";
        }
        cfg += "\npause 30\nreread\n";
        
        File* gnuplotConfig = new File(configFilename);
        gnuplotConfig->reset();
        gnuplotConfig->writeln(cfg);
        delete gnuplotConfig;
        
        // Empty data file
        gnuplotData->reset();
    }
    
    // Generate stats record and write to file
    string statLine = toStdStr(this->getGenerationCount()) + " ";
    for (int i = brains.size()-1; i >= 0; i--) {
        statLine += toStdStr(((Walker*)(brainsArray[i]->getBody()))->getDistanceTravelled()) + " ";
    }
    gnuplotData->writeln(statLine);
    delete gnuplotData;
    
    
    // Calculate successor generation
    int m = 0; 
    for (int i = (int)(brains.size()-1); i > (int)(brains.size())/2; i=i-2) {
        WalkerBrain* mother = (WalkerBrain*)brainsArray[i];
        WalkerBrain* father = (WalkerBrain*)brainsArray[i-1];
        
        WalkerBrain* child = new WalkerBrain(this->getName() + "_Brain_" +
                toStdStr(this->getGenerationCount()) + "_" + toStdStr(i));
        WalkerBrain* child2 = new WalkerBrain(this->getName() + "_Brain_" +
                toStdStr(this->getGenerationCount()) + "_" + toStdStr(i-1));
      
        // Cross mother's and father's genotype and get the child's genotype
        WalkerGenotype* childGenotype = mother->getGenotype()
                                        ->crossWith(father->getGenotype());
        child->setGenotype(childGenotype);
        
        // Cross mother's and father's genotype and get the child's genotype
        WalkerGenotype* childGenotype2 = father->getGenotype()
                                        ->crossWith(mother->getGenotype());
        child2->setGenotype(childGenotype);
        
        for (int k = 1; k < this->brainPopulationSize; k++) {
           if (brainsCon[k]->getName() == brainsArray[m]->getName()){
                  brainsCon.erase(k);
                  brainsCon[k] = child;
           }
           if (brainsCon[k]->getName() == brainsArray[m+1]->getName()){
                  brainsCon.erase(k);
                  brainsCon[k] = child2;
           }    
        } 
        m = m + 2; 
    }
    
    pickNetxBrains();
}


//------------------------------------------------------------------------------
void WalkerSuperAgent::distancesSort(Brain** brainsArray, int left, int right)
{
    if (left >= right) { return; }
    int l = left-1;
    int r = right;
    while (true)
    {
        while (((Walker*)(brainsArray[++l]->getBody()))->getDistanceTravelled()
                    < ((Walker*)(brainsArray[right]->getBody()))->getDistanceTravelled())
        {
            if (l>=r) { break; }
        }
        while (((Walker*)(brainsArray[--r]->getBody()))->getDistanceTravelled()
                    > ((Walker*)(brainsArray[right]->getBody()))->getDistanceTravelled())
        {
            if (l>=r) { break; }
        }
        if (l>=r) { break; }
        
        Brain* temp = brainsArray[l];
        brainsArray[l] = brainsArray[r];
        brainsArray[r] = temp;
    }
    Brain* temp = brainsArray[l];
    brainsArray[l] = brainsArray[right];
    brainsArray[right] = temp;
    
    distancesSort(brainsArray, left, l-1);
    distancesSort(brainsArray, l+1, right);
}

};

