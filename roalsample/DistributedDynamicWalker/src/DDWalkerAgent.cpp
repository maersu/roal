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

#include "DDWalkerAgent.h"

using namespace std;
namespace Roal
{

//------------------------------------------------------------------------------
DDWalkerAgent::DDWalkerAgent(const string name,
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
    
    //scream for init data
    ConnectorMessage* msg = new ConnectorMessage(NEED_POPULATION); 
    this->sendCommandToMaster(msg);
    delete msg;
}


//------------------------------------------------------------------------------
void DDWalkerAgent::initPopulation(ConnectorMessage* message)
{
    int idx=0;
    int loc ;
    
    string names = message->getValue("PhenotypeNames"); 
    int count = atoi(message->getValue("PhenotypeValueCount").c_str());
    string tmp  = "";
       
    loc = names.find( ":", idx);
    while (loc != string::npos)
    {
        tmp = names.substr(idx, loc-idx); 
        Phenotype* p = new Phenotype(NULL);
        
        p->setValues(message->getValue(tmp)+":",count);
        Brain* b = factory->generateCreature(tmp, getRandomPosFromOrigin(originPosition,
                                       500),p);
        b->setName(tmp);
        //b->getBody()->setCheckEmergency(false);
        this->registerBody(b->getBody());
        this->registerBrain(b);
        
        //Next Round
        idx = loc+1;
        loc = names.find( ":", idx );
    }
    
    Agent::initPopulation();
}

//------------------------------------------------------------------------------
void DDWalkerAgent::iterate(float elapsedTime, ConnectorMessage* message)
{    
    
    // Call the Brain's iterate method
    for(BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) {
        it->second->iterate(elapsedTime);
    }
    
    // Init a population
    if (message->getCommand().compare(INIT_POPULATION) == 0 
            && message->hasValue("PhenotypeNames") 
            && message->hasValue("PhenotypeValueCount")) 
    {
        this->initPopulation(message);
        
    // Unknown message
    } else {
        cerr << this->getName()<< ": Unknown message from Master: " << *message << endl;
    }
}

//------------------------------------------------------------------------------
void DDWalkerAgent::handleMutation()
{
    string names = "";
    
    ConnectorMessage* msg = new ConnectorMessage(POPULATION_EVAL); 
    // Call the Brain's iterate method
    for(BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) {
        LeggedCreatureBrain* b = ((LeggedCreatureBrain*)(it->second)); 
        
        msg->setValue(b->getName(), toStdStr(b->getDistanceTravelled()));
        names = names + b->getName()+":";
    }
    msg->setValue("PhenotypeNames",names);
    
    this->killAllBodies();
    this->killAllBrains();
  
    this->sendCommandToMaster(msg);
    delete msg;
}
};

