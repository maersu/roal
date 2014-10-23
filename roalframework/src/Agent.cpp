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

#include "Agent.h"

namespace Roal
{

//------------------------------------------------------------------------------
Agent::Agent(const string name, World* world)
{    
    // Set default values
    this->populationSize = 1;
    this->generationCycle = 600;
    
    this->setName(name);
    this->world = world;
    this->generationCount = 0;
    
    this->toggleMovableTextCounter = 0;
}


//------------------------------------------------------------------------------
Agent::Agent(const string name, World* world, int populationSize, int generationCycle)
{
    this->populationSize = populationSize;
    this->generationCycle = generationCycle;
    
    this->setName(name);
    this->world = world;
    this->generationCount = 0;
    
    this->toggleMovableTextCounter = 0;
}


//------------------------------------------------------------------------------
Agent::~Agent()
{
    this->killAllBrains();
    this->killAllBodies();
}


//------------------------------------------------------------------------------
void Agent::setName(const string name)
{
    this->name = name;
}


//------------------------------------------------------------------------------
string Agent::getName()
{
    return this->name;
}


//------------------------------------------------------------------------------
bool Agent::isBodyRegistered(string name)
{    
    // Try to find the bodies
    BodiesMap::iterator it = bodies.find(name);   
    return (it != bodies.end());
}


//------------------------------------------------------------------------------
bool Agent::isBrainRegistered(string name)
{
    // Try to find the brain
    BrainsMap::iterator it = brains.find(name);
    
    return (it != brains.end());
}


//------------------------------------------------------------------------------
void Agent::registerBody(Body* body)
{
    
    if (!this->isBodyRegistered(body->getName())) {
        // Add the body to the map 
        bodies[body->getName()] = body;
        this->world->registerBody(body);
                
    } else {
        throw(RoalException(typeid( this ).name(),
            "A Body with the name "+body->getName()+" is "+"already registered!"));
    }
   
}


//------------------------------------------------------------------------------
void Agent::registerBrain(Brain* brain)
{
    if (!this->isBrainRegistered(brain->getName())) {
        // Add the brain to the map
        brains[brain->getName()] = brain;
    } else {
        throw(RoalException(typeid( this ).name(),
            "A Brain with the name "+brain->getName()+" is "+"already registered"));
    }
}


//------------------------------------------------------------------------------
void Agent::unregisterAndDeleteBody(Body* body)
{
    world->unregisterBody(body);
    bodies.erase(body->getName()); 
    delete body;
}


//------------------------------------------------------------------------------
void Agent::killBrain(Brain* brain)
{
    if (this->isBrainRegistered(brain->getName())) {
        // Add the brain to the map
        brains.erase(brain->getName());
    } else {
        throw(RoalException(typeid( this ).name(),
            "An Brain with the name "+brain->getName()+" is "+"not registered"));
    }
}


//------------------------------------------------------------------------------
void Agent::killAllBrains()
{
    for(BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) {
        delete it->second;
    }
    brains.clear();
    
    for(BrainsMap::iterator it = deadBrains.begin(); it != deadBrains.end(); it++) {
        delete it->second;
    }
    deadBrains.clear();
}


//------------------------------------------------------------------------------    
void Agent::killAllBodies()
{    
    for(BodiesMap::iterator it = bodies.begin(); it != bodies.end(); it++) {
        this->unregisterAndDeleteBody(it->second);
    }    
}


//------------------------------------------------------------------------------
void Agent::initPopulation()
{
    generationStartTime = time(NULL);
}


//------------------------------------------------------------------------------
void Agent::iterate(float elapsedTime)
{     
    if (toggleMovableTextCounter<10) {
        toggleMovableTextCounter++;
    } else {
        toggleMovableTextCounter = 0;
    }
    
    // Call the Brain's iterate method
    for(BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) {
        it->second->iterate(elapsedTime);
        
        InputReader* mInputDevice = this->world->getFrameListener()->getInputReader();
        if (mInputDevice->isKeyDown(KC_T) && toggleMovableTextCounter == 0) {
            if (it->second->getBody()->isMovableTextVisible() == true) {
                it->second->getBody()->setMovableTextVisible(false);
            } else {
                it->second->getBody()->setMovableTextVisible(true);
            }
        }
        it->second->getBody()->resetCollisionCounter();
    }
}


//------------------------------------------------------------------------------
void Agent::prepareNextStep()
{
   //check if there is a Body which needs an emergency handling 
   for(BodiesMap::iterator it = bodies.begin(); it != bodies.end(); it++) {
        if (it->second->getCheckEmergency() 
                && it->second->getCollisionCount() >= KILL_COLLISION_TRESHOLD) {
            cerr << "Handle Emergency: Remove Body: "  
                << it->second->getName() 
                << " Collision count:" 
                << it->second->getCollisionCount() << endl;
            
            unregisterAndDeleteBody(it->second); 
            
            for(BrainsMap::iterator itb = brains.begin(); itb != brains.end(); itb++) {
                if (itb->second->getBody() == it->second) {   
                    cerr << "Handle Emergency: Remove Brain: "  
                         << itb->second->getName() << endl;
                    
                    // Preserve the brain for potential uses - they will be
                    // killed in killAllBrains()
                    deadBrains[itb->second->getName()] = itb->second;
                    
                    // Delete brain from brains map
                    brains.erase(itb->second->getName());
                    
                    break;
                }
            } 
        }/* else {
            it->second->resetCollisionCounter();
        }*/
   }       
   
    //call the handleMutation methods of the derivated Agents
    if (this->getGenerationAge() >= generationCycle) {
      generationCount ++;
      this->handleMutation();
      
      generationStartTime = time(NULL);
    }
}


//-----------------------------------------------------------------------------
long Agent::getGenerationCount()
{
    return this->generationCount;
}


//-----------------------------------------------------------------------------
double Agent::getGenerationAge()
{
    return difftime(time(NULL),generationStartTime);
}


//------------------------------------------------------------------------------
Body* Agent::getClosestBody(Position* pos, float maxRadius, string ignoreName)
{
    float dist = maxRadius;
    float tmpDist = 0.0;
    Body* result = 0;
    
    //find the Bodies
    for(BodiesMap::iterator it = bodies.begin(); it != bodies.end(); it++) {
        tmpDist = pos->getPlanarDistanceTo(it->second->getPosition()->getX(),
                                           it->second->getPosition()->getZ()); 
        if (tmpDist<dist && it->second->getName() != ignoreName) {
            result = it->second;
        }
    }
    
    return result;
}


//------------------------------------------------------------------------------
float Agent::getClosestBodyDistance(Position* pos, float maxRadius, string ignoreName)
{
    float dist = maxRadius;
    float tmpDist = 0.0;
    
    //find the Bodies
    for(BodiesMap::iterator it = bodies.begin(); it != bodies.end(); it++) {
        tmpDist = pos->getPlanarDistanceTo(it->second->getPosition()); 

        if (tmpDist<dist && it->second->getName() != ignoreName) {
            dist = tmpDist;
        }
    }

    return dist;
}


//------------------------------------------------------------------------------
float Agent::getClosestBodyDistanceWorldWide(Position* pos, float maxRadius, 
                            string ignoreName, vector<string> ignoreAgent)
{
    return this->world->getClosestBodyDistance(pos, maxRadius,
                                               ignoreName, ignoreAgent);
}


//------------------------------------------------------------------------------
Position* Agent::getRandomPosFromOrigin(Position* origin, float radius)
{
    float x = (((float)rand()/RAND_MAX) * radius) 
                + origin->getX();
    float z = (((float)rand()/RAND_MAX) * radius) 
                 + origin->getZ();
    
    /**@todo use world->heightAt(Vector3(x,10000,z)) for dynamic hight detection*/
    
    float y = origin->getY()+1;
   
    return new Position(x,y,z);
}


//------------------------------------------------------------------------------
KeySensor* Agent::createKeySensor()
{
    return world->createKeySensor();   
}

}
