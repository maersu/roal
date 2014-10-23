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

#include <RoalFramework/RoalCore.h>
#include "WalkerAgent.h"
#include "Walker.h"
#include "WalkerBrain.h"
#include "WalkerSuperAgent.h"

int main(int argc, char *argv[])
{
    using namespace Roal;
    using Roal::World;
    
    //create and configure the new roal world
    World* world = new World("landscape.cfg", "resources.cfg");
    try
    {
        world->setGravity(Vector3(0,-9.80665,0)); 
        world->setBackgroundColor(ColourValue(1.0, 1.0, 1.0));  
        world->setCameraPosition(Vector3(680,15,500)); 
        world->setCameraLookAt(Vector3(750,1,550)); 
        world->setMainLightPosition(Vector3(20,800,50));
        world->setMainLightColor(ColourValue(0,0.9,0.5));  
        world->setIsUseShadow(false);
        world->setShowDebugObjects(false);
        world->setTheme("marshigh");
        
       
        /** These agent are not usefull
        
        WalkerAgent* walkerAgent = new WalkerAgent("PureInzest", world, 5, 100,
                                            new Position(1100,0,520), 0.67);
        world->registerAgent(walkerAgent);
       
        WalkerAgent* walkerAgent3 = new WalkerAgent("PureRandom", world, 6, 30,
                                            new Position(1100,1,550), 0);
        world->registerAgent(walkerAgent3);*/
        
        WalkerSuperAgent* walkerSuperAgent = new WalkerSuperAgent("SuperAgent", 
                                                        world, 
                                                        36, //brainPopulationSize 
                                                        8, //bodyPopulationSize 
                                                        20, //generationCycle 
                                                        new Position(750,1,550),
                                                        0);
        world->registerAgent(walkerSuperAgent);
       
    
        //Start the simulation   
        world->run();
    
    } catch (Roal::RoalException& e) {
        e.print();
    }
        //Killing the world is important, otherwise the mousepointer is no more accessible
        delete world;
    return 0;
}
