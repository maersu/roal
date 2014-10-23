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

#include "DistributedWorld.h"

namespace Roal
{

//------------------------------------------------------------------------------
DistributedWorld::DistributedWorld(string terrainConfigFile, string resourcesConfigFile,
    string ipAddress, int port,
    string masterIPAddress, int masterPort)
    : World(terrainConfigFile,resourcesConfigFile), Slave(ipAddress, port)
{
    this->sendRegisterCommandToMaster(masterIPAddress, masterPort);
}


//------------------------------------------------------------------------------
DistributedWorld::~DistributedWorld()
{
    ConnectorMessage* message = new  ConnectorMessage(DIST_COM_UNREGISTERSLAVE);
    this->sendCommandToMaster(message);
    delete message;
}

//------------------------------------------------------------------------------
void DistributedWorld::frameStarted(const FrameEvent& evt)
{
    float time = evt.timeSinceLastFrame;
    
    //check if there is a new Message
    if (this->connector->hasMessage()) {
    
        ConnectorMessage* message = this->connector->getNextMessage();
        string tmp = "-_-";
        if (message->hasValue(DIST_AGENT_NAME))
        {
          tmp = message->getValue(DIST_AGENT_NAME);
        }
        
        // Call the Agent's iterate method
        for(AgentsMap::iterator it = agents.begin(); it != agents.end(); it++) {
            
            if (dynamic_cast<DistributedAgent*>((DistributedAgent*)(it->second))!=NULL
                            && it->second->getName().compare(tmp) == 0) 
            {
                ((DistributedAgent*)(it->second))->iterate(time,message);
            } else {
                it->second->iterate(time);
            }   
        }
        delete message;
    } else {
        
        // Call the Agent's iterate method
        for(AgentsMap::iterator it = agents.begin(); it != agents.end(); it++) {
            it->second->iterate(time);    
        }
    }
}

};
