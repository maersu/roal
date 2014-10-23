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
#ifndef _PLANTAGENT_H_
#define _PLANTAGENT_H_

#include <RoalFramework/Agent.h>
#include <RoalFramework/World.h>
#include <RoalFramework/Position.h>
#include <RoalFramework/Body.h>
#include <RoalFramework/Util.h>
#include <RoalFramework/File.h>
#include "Plant.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
class World; // Forward declaration for World class

/**
 * PlantAgent is the Plant implementation of the Agent.
 * @see Agent
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class PlantAgent: public Agent
{
public:
    /**
     * Constructor
     * 
     * @see RoalFramework::Agent::Agent
     * 
     * @name The name of the agent
     * @param newOriginPosition The origin position where to place the creatures around
     * @param world The World which holds this Agent
     */
    PlantAgent(const string name, World* world, Position* newOriginPosition);
    
    /**
     * Constructor with additional parameters.
     * 
     * @see RoalFramework::Agent::Agent
     * 
     * @name The name of the agent
     * @param world The World which holds this Agent
     * @param population Size The number of creatures in one generation
     * @param generation Cycle The lif time of a generation in seconds
     * @param newOriginPosition The origin position where to place the creatures around
     */
    PlantAgent(const string name, World* world, int populationSize, 
            int generationCycle, Position* newOriginPosition);

protected:
    
    /**
     * Create and register the creatures.
     *
     * This method is only use from the constructor.
     */
    void initPopulation();
    
    /**
     * @see RoalFramework::Agent::handleMutate
     */
    void handleMutation();
    
    /**
     * this is the origin position of the agents
     */    
    Position* originPosition;
    
};
}

#endif //_PLANTAGENT_H_
