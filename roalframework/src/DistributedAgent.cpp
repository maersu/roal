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

#include "DistributedAgent.h"

namespace Roal
{

//------------------------------------------------------------------------------
DistributedAgent::DistributedAgent(const string name, DistributedWorld* world)
   : Agent(name,world)
{
    this->distWorld = world;
}


//------------------------------------------------------------------------------
DistributedAgent::DistributedAgent(const string name, DistributedWorld* world,
                                   int populationSize, int generationCycle)
   : Agent(name,world, populationSize, generationCycle)
{
    this->distWorld = world;
}


//------------------------------------------------------------------------------
void DistributedAgent::iterate(float elapsedTime, ConnectorMessage* message)
{    
    // Call the Brain's iterate method
    for(BrainsMap::iterator it = brains.begin(); it != brains.end(); it++) {
        it->second->iterate(elapsedTime);
    }
    
    cout << " DistributedAgent::iterate Message Received: "
         << this->getName() << ": " << *message << endl;
}


//------------------------------------------------------------------------------
string DistributedAgent::sendCommandToMaster(ConnectorMessage* message)
{
    message->setValue(DIST_AGENT_NAME,this->getName());
    return this->distWorld->sendCommandToMaster(message);
}


//------------------------------------------------------------------------------
void DistributedAgent::setDistWorld(DistributedWorld* distWorld)
{
    this->distWorld = distWorld;
}

}
