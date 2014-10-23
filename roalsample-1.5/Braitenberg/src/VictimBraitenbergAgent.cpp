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

#include "VictimBraitenbergAgent.h"
#include <RoalFramework/WheeledCreatureGenotype.h>
using namespace std;
namespace Roal
{

//------------------------------------------------------------------------------
VictimBraitenbergAgent::VictimBraitenbergAgent(const string name, World* world, int populationSize, 
int generationCycle, Position* newOriginPosition)
: Agent(name, world, populationSize, generationCycle)
{  
    this->originPosition = newOriginPosition;
    
    WheeledCreatureGenotype* geno = new WheeledCreatureGenotype();
    geno->setMinMaxValue("hasFrontNbrSensors", 1, 1);    
    geno->setMinMaxValue("hasBackNbrSensors", 1,1); 
    geno->setMinMaxValue("frontNbrSensorsRadius", 50,  150);
    geno->setMinMaxValue("backNbrSensorsRadius", 50,  150); 
    geno->setMinMaxValue("hasCollisionCage" , 1,  1); 
       geno->setMinMaxValue("bodyHeight", 0.8, 3.5);
   // geno->setMinMaxValue("bodyWidth", 3.0, 3.5);
   // geno->setMinMaxValue("bodyLength", 1.0, 3.5);
    //geno->setMinMaxValue("frontNbrSensorsRadius", 50, 100);
    geno->setMinMaxValue("texture", 27, 27);  
    this->factory = new  WheeledCreatureFactory(name+"_factory",geno,this);
 
    
    initPopulation();

}

//------------------------------------------------------------------------------
void VictimBraitenbergAgent::initPopulation()
{
    // Create and register Braitenberg's and BraitenbergBrain's.
    long genCnt = this->getGenerationCount();   
     
    for (int i=0; i< this->populationSize ; i++) {
      
        //create a random Creature   
        Roal::Body* body = 
                this->factory->generateRandomBody("Victim_"+toStdStr(genCnt)+"_"+toStdStr(i), 
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
        VictimBraitenbergBrain* brain =  new VictimBraitenbergBrain("VictimBrain_"+toStdStr(genCnt)+"_"+toStdStr(i));
        brain->registerBody(body);
        brain->setPhenotype(body->getPhenotype());
        this->registerBrain(brain);   
    }
    
    // Call super method
    Agent::initPopulation();
}

//------------------------------------------------------------------------------
void VictimBraitenbergAgent::prepareNextStep()
{
  //check if there is a Body which neeeds a Emergency handling 
   for(BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) 
   {
        if (((VictimBraitenbergBrain*)it->second)->getEnergy()<=0) 
        {    
            unregisterAndDeleteBody(it->second->getBody()); 
            killBrain(it->second);
            cout << "Delete Body because the energy is over" <<endl;
        }   
   }       
    Agent::prepareNextStep();
}

//------------------------------------------------------------------------------
void VictimBraitenbergAgent::handleMutation()
{
    /*
    long genCnt = this->getGenerationCount();   
    float firstFit;
    float secondFit;
    */

    /* 
    if (brains.size()>1)
    {
        Phenotype* secondP;
        Phenotype* firstP;
        Phenotype* child1;
           
        //check if there is a Body which neeeds a Emergency handling 
        for(BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) 
        {
            if (((VictimBraitenbergBrain*)it->second)->getEnergy()>firstFit){
                
                secondP = firstP;
                secondFit = firstFit;
                
                firstP = it->second->getPhenotype();
                firstFit = ((VictimBraitenbergBrain*)it->second)->getEnergy();
                
            } else if (((VictimBraitenbergBrain*)it->second)->getEnergy()>secondFit){
                
                secondP = it->second->getPhenotype();
                secondFit = ((VictimBraitenbergBrain*)it->second)->getEnergy();  
            
            }
               
        }
        
        // Prepare two "emtpy phenotype halfes" for the childs
        vector<string> first;
        vector<string> second;
        
        first.push_back("bodyWidth");
        first.push_back("bodyLength");
        first.push_back("hasFrontNbrSensors");
        first.push_back("hasCollisionCage");
        first.push_back("backNbrSensorsRadius");
        first.push_back("corpusMass");
    
        second.push_back("bodyHeight");
        second.push_back("wheelCount");
        second.push_back("hasBackNbrSensors");
        second.push_back("frontNbrSensorsRadius");
        second.push_back("texture");
        second.push_back("wheelMass");
        

        child1 = (Phenotype*)firstP->crossWith(secondP, first, second);        
                
        //create a random Creature   
        Roal::Body* body = this->factory->generateBody("Victim_"+toStdStr(genCnt)+"_"+toStdStr(0), 
                    getRandomPosFromOrigin(originPosition, 200+this->populationSize*15), child1);
        
        //set Ignore Agents
        NeighborDistanceSensor* senLF = (NeighborDistanceSensor*)body->getSensor("distSenFront_L");
        NeighborDistanceSensor* senRF = (NeighborDistanceSensor*)body->getSensor("distSenFront_R");
        NeighborDistanceSensor* senLB = (NeighborDistanceSensor*)body->getSensor("distSenBack_L");
        NeighborDistanceSensor* senRB = (NeighborDistanceSensor*)body->getSensor("distSenBack_R");
       
        
        senLF->addIgnoreAgent(this->getName());
        senRF->addIgnoreAgent(this->getName());
        senLB->addIgnoreAgent(this->getName());
        senRB->addIgnoreAgent(this->getName());
   
       
        senLF->addIgnoreAgent("Plant");
        senRF->addIgnoreAgent("Plant");
        senLB->addIgnoreAgent("Hunter");
        senRB->addIgnoreAgent("Hunter");
        
   
        this->registerBody(body);
        
        //create brain
        VictimBraitenbergBrain* brain =  new VictimBraitenbergBrain("VictimBrain_"+toStdStr(genCnt)+"_"+toStdStr(0));
        brain->registerBody(body);
        brain->setPhenotype(body->getPhenotype());
        this->registerBrain(brain);   
    }
    
    */
    /*
    this->killAllBrains();
    this->killAllBodies();   
    
    
    for (int i=0; i< this->populationSize ; i++) {
        
        
        Box* b =  new Box("Victim_"+toStdStr(genCnt)+"_"+toStdStr(i), getRandomPosFromOrigin(originPosition, 200+this->populationSize*15),"mat000.mesh");
        b->setCheckEmergency(false);
        this->registerBody(b);
        
        
        //create a random Creature   
        Roal::Body* body = this->factory->generateRandomBody("Victim_"+toStdStr(genCnt)+"_"+toStdStr(i), getRandomPosFromOrigin(originPosition, 200+this->populationSize*15));
        
        /*
        //set Ignore Agents
        NeighborDistanceSensor* senLF = (NeighborDistanceSensor*)body->getSensor("distSenFront_L");
        NeighborDistanceSensor* senRF = (NeighborDistanceSensor*)body->getSensor("distSenFront_R");
        NeighborDistanceSensor* senLB = (NeighborDistanceSensor*)body->getSensor("distSenBack_L");
        NeighborDistanceSensor* senRB = (NeighborDistanceSensor*)body->getSensor("distSenBack_R");
       
        
        senLF->addIgnoreAgent(this->getName());
        senRF->addIgnoreAgent(this->getName());
        senLB->addIgnoreAgent(this->getName());
        senRB->addIgnoreAgent(this->getName());
   
       
        senLF->addIgnoreAgent("Plant");
        senRF->addIgnoreAgent("Plant");
        senLB->addIgnoreAgent("Hunter");
        senRB->addIgnoreAgent("Hunter");
        
           
        //create brain
        VictimBraitenbergBrain* brain =  new VictimBraitenbergBrain("VictimBrain_"+toStdStr(genCnt)+"_"+toStdStr(i));
        */
       // brain->registerBody(body);
       // brain->setPhenotype(body->getPhenotype());
       // this->registerBody(body);   
       // this->registerBrain(brain); }  

}
};
