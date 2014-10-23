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
#ifndef _DISTRIBUTEDAGENT_H_
#define _DISTRIBUTEDAGENT_H_

#include <string>
#include "Agent.h"
#include "Brain.h"
#include "World.h"
#include "Body.h"
#include "Util.h"
#include "DistributedWorld.h"
#include "Connector.h"
#include "ConnectorMessage.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
class DistributedWorld; // Forward declaration for World class

/**
 * Controls the evolutionary process in a distributed environment.
 *
 * Is able to send and receive ConnectorMessage object to and from a Master.
 * @see Agent
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class DistributedAgent : public Agent
{
public:
    /**
     * Constructor.
     * 
     * @param name The name of the Agent.
     * @param world see Agent::world
     */
	DistributedAgent(const string name, DistributedWorld* world);
    
    /**
     * Constructor with additional parameters.
     * 
     * @param name The name of the Agent.
     * @param world see Agent::world
     * @param populationSize The amount of creatures of a population.
     * @param generationCycle The duration of one generation cycle in seconds.
     */
	DistributedAgent(const string name, DistributedWorld* world,
                     int populationSize, int generationCycle);

    /**
     * The simulation's iteration method for each frame, with a ConnectorMessage.
     * 
     * The DistributedWorld calls this method to handover a ConnectorMessage
     * to the Agent. If no message is available, the usual Agent::iterate
     * method is called.
     * 
     * @see Agent::iterate
     *
     * @warning the ConnectorMessage pointer is only valid in the scope of the 
     * iterate method. 
     *
     * @param elapsedTime The time since last frame in seconds.
     * @param message A message sent from the Master.
     *
     */ 
    virtual void iterate(float elapsedTime, ConnectorMessage* message);
    
    /**
     * Sends a ConnectorMessage to the Master.
     * 
     * @param message A ConnectorMessage to send to the Master.
     *
     * @exception RoalException if an error occurs when sending the message.
     * @todo should be protected
     */ 
    string sendCommandToMaster(ConnectorMessage* message);

    /**
     * Set a DistributedWorld for this Agent.
     * 
     * @param distWorld The DistributedWorld to set.
     **/
    void setDistWorld(DistributedWorld* distWorld); 

private:
    /**
     * Default constructor, may not be used.
     */
    DistributedAgent()
    {
        throw(RoalException(typeid( this ).name(),
              "Default constructor of DistributedAgent, may not be used."));
    }
    
    /**
     * The DistributedWorld, the agent lives in.
     *
     * This pointer is needed to register the generated creatures (Body and Brain
     * objects in the world) and to use basic distributed functions.
     */
    DistributedWorld* distWorld;
    
};

}

#endif //_DISTRIBUTEDAGENT_H_
