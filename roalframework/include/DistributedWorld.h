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
#ifndef _DISTRIBUTEDWORLD_H_
#define _DISTRIBUTEDWORLD_H_

#include <OGRE/Ogre.h>
#include <OGRE/OgreConfigFile.h>
#include <OgreOde_Core/OgreOde_Core.h>
#include <OgreOde_Prefab/OgreOde_Prefab.h>

#include "Body.h"
#include "Brain.h"
#include "Agent.h"
#include "WorldFrameListener.h"
#include "RoalException.h"
#include "DistributedAgent.h"
#include "Joint.h"
#include "Slave.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * A World implementation for the distributed environment.
 * 
 * Manages registering and unregistering at the Master and handsover incoming
 * ConnectorMessage to a DistributedAgent.
 * 
 * @see World
 *
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class DistributedWorld: public World, public Slave
{
public:
    /**
     * Constructor.
     * 
     * @param terrainConfigFile The name of the config file to load.
     * @param resourcesConfigFile The Path to resource config file
     * @param ipAddress The Slave's IP address.
     * @param port The Slave's server port.
     * @param masterIPAddress The Master's IP address.
     * @param masterPort The Master's server port.
     */
	DistributedWorld(string terrainConfigFile, string resourcesConfigFile,
                    string ipAddress, int port,
                    string masterIPAddress, int masterPort);
    
    /**
     * Destructor.
     */
	virtual ~DistributedWorld();
	
    /**
     * The iteration method before each frame.
     * 
     * Calls Agent::iteration of every Agent registered in the World.
     * 
     * @see WorldFrameListener::frameStarted
     */
    void frameStarted(const FrameEvent& evt);
};

}

#endif //_DISTRIBUTEDWORLD_H_
