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

#include <unistd.h>
#include <RoalFramework/DistributedWorld.h>
#include <RoalFramework/Util.h>
#include <RoalFramework/RoalCore.h>
#include <RoalFramework/Slave.h>
#include <RoalFramework/LeggedCreatureFactory.h>
#include "DistributedWalkerAgent.h"

using namespace Roal;
using Roal::World;
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 5) {  
        cerr << "Usage: WalkerSlave [Slave IP Address] [Slave Listener Port] " <<
                     "[Master IP Address]\n                    [Master Listener Port]" << endl; 
        return -1;        
    }
    
    // Create and configure the Roal world
    DistributedWorld* world = new DistributedWorld("landscape.cfg",
                                                   "resources.cfg",
                                                   string(argv[1]),
                                                   atoi(argv[2]),
                                                   string(argv[3]),
                                                   atoi(argv[4]));
    
    try {
        world->setGravity(Vector3(0,-9.80665,0)); 
        world->setBackgroundColor(ColourValue(0.0, 0.0, 0.76));  
        world->setCameraPosition(Vector3(350,50,200)); 
        world->setCameraLookAt(Vector3(350,0,550)); 
        world->setMainLightPosition(Vector3(20,800,50));
        world->setMainLightColor(ColourValue(0,0.9,0.5));  
        world->setIsUseShadow(false);
        world->setShowDebugObjects(false);
        world->setTheme("marshigh");
       
        DistributedWalkerAgent* agent = new DistributedWalkerAgent("LeggedCreatureAgent", 
                                             world, 
                                             5, //populationSize
                                             35, //generationCycle
                                             new Position(350,3,550));
        world->registerAgent(agent);
        
        //Start the simulation  
        world->run();
        
    } catch (Roal::RoalException& e) {
        e.print();
    }
    
    //Killing the world is important, otherwise the mousepointer is no more accessible
    delete world; 
    
    return 0;
}
