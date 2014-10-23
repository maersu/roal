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

#include "PlantAgent.h"

using namespace std;
namespace Roal
{

//------------------------------------------------------------------------------
 PlantAgent:: PlantAgent(const string name, World* world, Position* newOriginPosition)
: Agent(name, world)
{
    this->originPosition = newOriginPosition;
    initPopulation();

}
//------------------------------------------------------------------------------
 PlantAgent:: PlantAgent(const string name, World* world, int populationSize, 
int generationCycle, Position* newOriginPosition)
: Agent(name, world, populationSize, generationCycle)
{  
    this->originPosition = newOriginPosition;
    initPopulation();

}

//------------------------------------------------------------------------------
void  PlantAgent::initPopulation()
{
    // Create and register Braitenberg's and BraitenbergBrain's.
    long genCnt = this->getGenerationCount();       
    for (int i=0; i< this->populationSize ; i++) {
        Roal::Plant* p = new Plant(this->getName()+toStdStr(i),getRandomPosFromOrigin(originPosition, 100+this->populationSize), "mat025.mesh");
        p->setCheckEmergency(false);
        this->registerBody(p);	
    }
    
    // Call super method
    Agent::initPopulation();
}

//------------------------------------------------------------------------------
void  PlantAgent::handleMutation()
{
   //  this->killAllBrains();
   // this->killAllBodies();
    /*
    for(BodiesMap::iterator it = bodies.begin(); it != bodies.end(); it++) {
        p = ((Plant*)it->second);
        cout<<"--- Check Age:"<<it->first <<endl;        
        age = p->getAge();
        
        if (age>40.0)
        {
           this->unregisterAndDeleteBody(it->second);  
           cout<<"--- unregisterAndDeleteBody<<endl:"<<it->first <<endl;; 
        }
        
       // p->setPosition(p->getPosition()->getX()+2,p->getPosition()->getY()+10*age,p->getPosition()->getZ()+2);
       // p->setScale(0.1*age,0.5,0.5);
    }*/
    
    
}

};
