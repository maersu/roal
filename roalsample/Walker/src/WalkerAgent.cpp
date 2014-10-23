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

#include "WalkerAgent.h"

namespace Roal
{

//------------------------------------------------------------------------------
WalkerAgent::WalkerAgent(const string name, World* world, Position* newOriginPosition)
: Agent(name, world)
{
    initPopulation();
    this->originPosition = newOriginPosition;
    surviverRate = 2/3;
}


//------------------------------------------------------------------------------
WalkerAgent::WalkerAgent(const string name, World* world, int populationSize, 
int generationCycle, Position* newOriginPosition, float newSurviverRate)
: Agent(name, world, populationSize, generationCycle)
{  
    if (newSurviverRate > 1.0){
      this->surviverRate = 1.0;
    } else if (newSurviverRate < 0.0) {
      this->surviverRate = 0.0;
    } else {
      this->surviverRate = newSurviverRate;
    }
    this->originPosition = newOriginPosition;
    initPopulation();
}


//------------------------------------------------------------------------------
void WalkerAgent::killAllBrains()
{
    // Only kill those Brain objects that are not in the surviver map.
    for(BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) {
        SurviverBrainsMap::iterator sIt;
        bool survives = false;
        for (sIt=surviverBrains.begin(); sIt!=surviverBrains.end() && !survives; sIt++) {
            if ((it->second) == (sIt->second)) {
                survives = true;
            }
        }
        if (!survives) {
            delete it->second;
        }
    }
    brains.clear();
}


//------------------------------------------------------------------------------
void WalkerAgent::initPopulation()
{
    // Create and register Walker's and WalkerBrain's.
    int i = 0;
    long genCnt = this->getGenerationCount();   
     
    string walkerName;
    string brainName;
     
    if (surviverBrains.size() >0) {
        
        SurviverBrainsMap::iterator it;
        for (it=surviverBrains.begin(); it!=surviverBrains.end(); it++) {
          
            // Create the Body
            walkerName = this->getName()+"_Body_"+ toStdStr(genCnt) +"_"+toStdStr(i);
               
            //create a random position for the body around of the agent origin   
               
               
            Walker* walker = new Walker(walkerName, 
                    this->getRandomPosFromOrigin(originPosition, 
                        35.0 + this->populationSize));
            walker->setCheckEmergency(false);
            this->registerBody(walker);
               
            brainName = this->getName()+"_Brain_"+toStdStr(genCnt) +"_"+toStdStr(i);
             
            // Create the Brain
            WalkerBrain* walkerBrain = (WalkerBrain*)(*it).second;
            walkerBrain->registerBody(walker);
            this->registerBrain(walkerBrain);
            
            i++;
        }
        
    }
    
    int p;
    //are some places left???
    if (i > 0) {
      p = i;
    } else {
      p = 0;
    }
         
    
    if (surviverBrains.size() < this->populationSize) {
        
        for (int k=0; k< (this->populationSize - surviverBrains.size()) ; k++) {
            // Create the Body
            walkerName = this->getName()+"_Body_"+toStdStr(genCnt) +"_"+toStdStr(p);
               
            Walker* walker = new Walker(walkerName, 
                    this->getRandomPosFromOrigin(originPosition, 
                                35.0 + this->populationSize));
            walker->setCheckEmergency(false);
            this->registerBody(walker);
               
            brainName = this->getName()+"_Brain_"+toStdStr(genCnt) +"_"+toStdStr(p);
             
            // Create the Brain
            WalkerBrain* walkerBrain = new WalkerBrain(brainName);
            walkerBrain->registerBody(walker);
            this->registerBrain(walkerBrain);
            
            p++;
        }
        
    } 
    // Call super method
    Agent::initPopulation();
}

//------------------------------------------------------------------------------
void WalkerAgent::handleMutation()
{
    
    // Put the brains into an array
    Brain* brainsArray[(int)brains.size()];
    int i = 0;
    BrainsMap::iterator it;
    for (it=brains.begin(); it!=brains.end(); it++) {
        brainsArray[i] = (*it).second;
        i++;
    }
  
    // Sort the array by the distances the Walker's traveled (with quicksort)
    distancesSort(brainsArray, 0, (int)brains.size()-1);
    
    // Reproduce...
    // The lowest of all creatures dies. The best of all
    // creatures build the lowest by reproducing.
    int j=0;
    
    for (int i = (int)(brains.size()*this->surviverRate); i > 0; i=i-2)
    {
        WalkerBrain* mother = (WalkerBrain*)brainsArray[i];
        WalkerBrain* father = (WalkerBrain*)brainsArray[i-1];
        WalkerBrain* child = new WalkerBrain(this->getName() + "_Brain_" +
                toStdStr(this->getGenerationCount()) + "_" + toStdStr(i));
        
        // Cross mother's and father's genotype and get the child's genotype
        WalkerGenotype* childGenotype = mother->getGenotype()
                                        ->crossWith(father->getGenotype());
        child->setGenotype(childGenotype);
        
        surviverBrains["surviver"+(j++)] = mother;
        surviverBrains["surviver"+(j++)] = father;
        surviverBrains["surviver"+(j++)] = child;
    }
     
    this->killAllBrains();
    this->killAllBodies(); 
    
    initPopulation();
}


//------------------------------------------------------------------------------
void distancesSort(Brain** brainsArray, int left, int right)
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
