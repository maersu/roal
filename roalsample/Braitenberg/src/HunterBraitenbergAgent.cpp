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


#include <RoalFramework/WheeledCreatureGenotype.h>
#include "HunterBraitenbergAgent.h"

using namespace std;
namespace Roal
{

//------------------------------------------------------------------------------
HunterBraitenbergAgent::HunterBraitenbergAgent(const string name, World* world, int populationSize, 
int generationCycle, Position* newOriginPosition)
: Agent(name, world, populationSize, generationCycle)
{  
    this->originPosition = newOriginPosition;
    
    WheeledCreatureGenotype* geno = new WheeledCreatureGenotype();
    geno->setMinMaxValue("hasFrontNbrSensors", 1, 1);    
    geno->setMinMaxValue("hasBackNbrSensors", 1, 1); 
    geno->setMinMaxValue("frontNbrSensorsRadius", 100,  150);
    geno->setMinMaxValue("backNbrSensorsRadius", 100,  150); 
    geno->setMinMaxValue("hasCollisionCage" , 1,  1); 
    geno->setMinMaxValue("bodyHeight", 0.8, 3.5);
   // geno->setMinMaxValue("bodyWidth", 3.0, 3.5);
   // geno->setMinMaxValue("bodyLength", 1.0, 3.5);
    //geno->setMinMaxValue("frontNbrSensorsRadius", 50, 100);
    geno->setMinMaxValue("texture", 17, 17);  
    
    this->factory = new  WheeledCreatureFactory(name+"_factory",geno,this);
    
    initPopulation();

}

//------------------------------------------------------------------------------
void HunterBraitenbergAgent::initPopulation()
{
    // Create and register Braitenberg's and BraitenbergBrain's.
    long genCnt = this->getGenerationCount();   
     
    string braitenbergName;
    string brainName;
    
    for (int i=0; i< this->populationSize ; i++) {
      
        //create a random Creature   
        Roal::Body* body 
                = this->factory->generateRandomBody("Hunter_"+toStdStr(genCnt)+"_"+toStdStr(i), 
                new Position(this->originPosition->getX()+30*i,this->originPosition->getY(),this->originPosition->getZ()));
        //set Ignore Agents
        NeighborDistanceSensor* senLF = (NeighborDistanceSensor*)body->getSensor("distSenFront_L");
        NeighborDistanceSensor* senRF = (NeighborDistanceSensor*)body->getSensor("distSenFront_R");
        NeighborDistanceSensor* senLB = (NeighborDistanceSensor*)body->getSensor("distSenBack_L");
        NeighborDistanceSensor* senRB = (NeighborDistanceSensor*)body->getSensor("distSenBack_R");
        
        senLF->addIgnoreAgent(this->getName());
        senRF->addIgnoreAgent(this->getName());
        senLB->addIgnoreAgent(this->getName());
        senRB->addIgnoreAgent(this->getName());
        
        
        this->registerBody(body);
        
        //create brain
        HunterBraitenbergBrain* brain =  new HunterBraitenbergBrain("HunterBrain_"+toStdStr(genCnt)+"_"+toStdStr(i));
        brain->registerBody(body);
        brain->setPhenotype(body->getPhenotype());
        this->registerBrain(brain);   
    }
    
    // Call super method
    Agent::initPopulation();
}


//------------------------------------------------------------------------------
void HunterBraitenbergAgent::prepareNextStep()
{
     //check if there is a Body which neeeds a Emergency handling 
   for(BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) 
   {
        if (((HunterBraitenbergBrain*)it->second)->getEnergy()<=0) 
        {    
            unregisterAndDeleteBody(it->second->getBody()); 
            cout << "Delete Body because the energy is over" <<endl;
            killBrain(it->second);
        }   
   }       
    Agent::prepareNextStep();
}

//------------------------------------------------------------------------------
void HunterBraitenbergAgent::handleMutation()
{
   //  this->killAllBrains();
   /// this->killAllBodies();    
}

};
