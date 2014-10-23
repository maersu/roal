/**     
    This file is part of Roal, a framework for simulations in the field
    of Artificial Intelligence and Aritificial Life.
    See http://roal.sourceforge.net/ for more informations.

    Copyright (c) 2005 Project Roal

    Roal is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free SBraitenbergVehicleoftware Foundation; either version 2 of the License, or
    (at your option) any later version.

    Roal is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Roal; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <RoalFramework/Box.h>
#include <RoalFramework/RoalCore.h>
#include <RoalFramework/Body.h>
#include <RoalFramework/Cage.h>

#include "HunterBraitenbergAgent.h"
#include "VictimBraitenbergAgent.h"
#include "PlantAgent.h"

int main(int argc, char *argv[])
{
    using namespace Roal;
    using Roal::World;
    
    //create and configure the new roal world
    World* world = new World("landscape.cfg", "resources.cfg");
    try
    {
       
        world->setGravity(Vector3(0,-9.80665,0)); 
        world->setBackgroundColor(ColourValue(0.0, 0.0, 0.76));  
        world->setCameraPosition(Vector3(1000,200,1000)); 
        world->setCameraLookAt(Vector3(750,1,750));
       
        world->setMainLightPosition(Vector3(20,800,50));
        world->setMainLightColor(ColourValue(0.2,0.2,0.2));  
        world->setIsUseShadow(false);
        world->setShowDebugObjects(false);
        world->setTheme("marshigh");
        
        VictimBraitenbergAgent* victimAgent = new VictimBraitenbergAgent("Victim", world, 4, 20,
                                            new Position(750,4,750));
        world->registerAgent(victimAgent);

        
        Roal::Cage* cage = new Roal::Cage("cage",new Position(750,2,750),"mat011.mesh",300,8,3.5);
        world->registerBody(cage);	
    
            
        HunterBraitenbergAgent* hunterAgent = new HunterBraitenbergAgent("Hunter", world, 2, 20,
                                            new Position(700,4,700));
        world->registerAgent(hunterAgent);
    
        /* Add some obstacle
        PlantAgent* plantAgent = new PlantAgent("Plant", world, 10, 20,
                                            new Position(750,2.5,750));
        world->registerAgent(plantAgent);
        */          
        //Start the simulation   
        world->run();
    
    } catch (Roal::RoalException& e) {
        e.print();
    }
        //Killing the world is important, otherwise the mousepointer is no more accessible
        delete world;
    return 0;
}
