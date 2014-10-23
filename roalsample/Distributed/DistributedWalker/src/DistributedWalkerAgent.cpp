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

#include "DistributedWalkerAgent.h"

using namespace std;
namespace Roal
{

//------------------------------------------------------------------------------
DistributedWalkerAgent::DistributedWalkerAgent(const string name,
                     DistributedWorld* world, 
                     int bodyPopulationSize, int generationCycle, 
                     Position* newOriginPosition)
    : DistributedAgent(name, world, bodyPopulationSize, generationCycle)
{  
    geno = new LeggedCreatureGenotype();
    geno->setMinMaxValue("legCount",6,6);
    
    this->factory = new LeggedCreatureFactory(name+"_factory",geno);
    this->originPosition = newOriginPosition;
    this->brainPopulationSize = bodyPopulationSize;
    
    //start the simualtion
    initPopulation();
}


//------------------------------------------------------------------------------
void DistributedWalkerAgent::initPopulation()
{
    // Create and register LeggedCreature's and LeggedCreatureBrain's.
    long genCnt = this->getGenerationCount();   
    
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
    Agent::initPopulation();
}


//------------------------------------------------------------------------------
void DistributedWalkerAgent::handleMutation()
{
    // Reproduce...
    // The worst four creatures die. The best two creatures create two childs
    // which replace two of the four that died. The other two of the four that
    // died are replaced by two new random creatures. All other creatures stay
    // the same.
    
    long genCnt = this->getGenerationCount();
    
    // Sort the creatures by the distances they travelled (with quicksort)
    LeggedCreatureBrain* brainsArray[this->populationSize];
    BrainsMap::iterator it;
    int i = 0;
    for (it=brains.begin(); it!=brains.end(); it++) {
        brainsArray[i] = (LeggedCreatureBrain*)it->second;
        i++;
    }
    distancesSort(brainsArray, 0, (int)brains.size()-1);
    
    
    // Get results of the actual generation for statistics
    string msgStat = toStdStr(this->getGenerationCount()) + " ";
    for (int i = brains.size()-1; i >= 0; i--) {
        msgStat += toStdStr(brainsArray[i]->getDistanceTravelled()) + " ";
    }
    
    
    // Get mother and father for reproduction (the two best creatures)
    LeggedCreaturePhenotype* mother =
            (LeggedCreaturePhenotype*)brainsArray[0]->getPhenotype();
    LeggedCreaturePhenotype* father =
            (LeggedCreaturePhenotype*)brainsArray[1]->getPhenotype();
    
    // Prepare two "emtpy phenotype halfes" for the childs
    vector<string> first;
    vector<string> second;
    
    first.push_back("armHeight");
    first.push_back("armLength");
    first.push_back("armWidth");
    first.push_back("force");

    second.push_back("bodyHeight");
    second.push_back("bodyLength");
    second.push_back("bodyWidth");
    second.push_back("constValue");
    second.push_back("legCount");

    float legCount = mother->getValue("legCount");
    
    for (int i = 1; i <= legCount ; i++) {
        if (i%2 == 0) {
            first.push_back("axle"+toStdStr(i)+"_Comp1");
            first.push_back("axle"+toStdStr(i)+"_Comp2");
            first.push_back("elbow"+toStdStr(i)+"_Comp1");
            first.push_back("elbow"+toStdStr(i)+"_Comp2");
            
        } else {
            second.push_back("axle"+toStdStr(i)+"_Comp1");
            second.push_back("axle"+toStdStr(i)+"_Comp2");
            second.push_back("elbow"+toStdStr(i)+"_Comp1");
            second.push_back("elbow"+toStdStr(i)+"_Comp2");
        }
    }
    
    // Create Childs by crossing mother and father one way and another
    LeggedCreaturePhenotype* child1 =
            (LeggedCreaturePhenotype*)mother->crossWith(father, first, second);
    LeggedCreaturePhenotype* child2 =
            (LeggedCreaturePhenotype*)mother->crossWith(father, second, first); 
    
    
    // Graphviz bloodline statistics:
    // Mother Blooline node
    LeggedCreatureBrain* motherBrain = brainsArray[0];
    float motherDist = motherBrain->getDistanceTravelled();
    string msgBloodline = motherBrain->getName() 
        + " [label = \"" + motherBrain->getName() 
        + " | Info: " + motherBrain->toString(": "," | ") + "\","
        + "style=filled, fillcolor="+getHexColor(motherDist, 0, 90)+" ]\n";

    // Father blooline node
    LeggedCreatureBrain* fatherBrain = brainsArray[1];
    float fatherDist = fatherBrain->getDistanceTravelled();
    msgBloodline += fatherBrain->getName() 
        + " [label = \"" + fatherBrain->getName() 
        + " | Info: " + fatherBrain->toString(": "," | ") + "\","
        + "style=filled, fillcolor="+getHexColor(fatherDist, 0, 90)+" ]\n";
    
    // Bloodline links
    msgBloodline += motherBrain->getName() + " -> "
            + "walker_"+toStdStr(genCnt)+"_"+toStdStr(this->populationSize-4)+"\n" 
       + fatherBrain->getName() + " -> "
            + "walker_"+toStdStr(genCnt)+"_"+toStdStr(this->populationSize-4)+"\n"
       + motherBrain->getName() + " -> "
            + "walker_"+toStdStr(genCnt)+"_"+toStdStr(this->populationSize-3)+"\n" 
       + fatherBrain->getName() + " -> "
            + "walker_"+toStdStr(genCnt)+"_"+toStdStr(this->populationSize-3)+"\n";
    
    // Send message with statistics to master
    ConnectorMessage* message = new ConnectorMessage(DIST_STAT_FROM_AGENT);
    message->setValue(DIST_STAT_GENCOUNT, toStdStr(this->getGenerationCount()));
    message->setValue(DIST_LINE_STAT_LINE, msgStat);
    message->setValue(DIST_LINE_STAT_VALUECOUNT, toStdStr((int)(brains.size())));
    message->setValue(DIST_BLOODLINE_STAT_LINES, msgBloodline);
    
    this->sendCommandToMaster(message);
    
    
    // Put the brains into an array
    LeggedCreaturePhenotype* phenotypeArray[this->populationSize];
    
    for (int i = 0; i < (this->populationSize-4); i++) {
        phenotypeArray[i] = new LeggedCreaturePhenotype(geno);
        phenotypeArray[i]->copyFrom(brainsArray[i]->getPhenotype());
    }
    
    phenotypeArray[this->populationSize-4] = child1;
    phenotypeArray[this->populationSize-3] = child2;
    phenotypeArray[this->populationSize-2] =
            (LeggedCreaturePhenotype*)geno->getRandomPhenotype();
    phenotypeArray[this->populationSize-1] =
            (LeggedCreaturePhenotype*)geno->getRandomPhenotype();
    
    this->killAllBrains();
    this->killAllBodies(); 
    
    // Instanciate creatures for the next generation
    for (int i = 0; i < this->populationSize; i++) {
            //create a random position for the body around of the agent origin   
            Brain* walker = this->factory->generateCreature(
                        "walker_"+toStdStr(genCnt)+"_"+toStdStr(i), 
                        getRandomPosFromOrigin(originPosition, 
                        500.0 + this->populationSize*10), phenotypeArray[i]);
            walker->getBody()->setCheckEmergency(true);  
            this->registerBody(walker->getBody());
            this->registerBrain(walker);
    } 
}


//------------------------------------------------------------------------------
void DistributedWalkerAgent::distancesSort(LeggedCreatureBrain** brainsArray,
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

