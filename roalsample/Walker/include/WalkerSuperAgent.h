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
#ifndef _WALKERSUPERAGENT_H_
#define _WALKERSUPERAGENT_H_

#include <RoalFramework/Agent.h>
#include "Walker.h"
#include "WalkerBrain.h"
#include <RoalFramework/World.h>
#include <RoalFramework/Position.h>
#include <RoalFramework/Body.h>
#include <RoalFramework/Brain.h>
#include <RoalFramework/Util.h>
#include <RoalFramework/File.h>

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
class World; // Forward declaration for World class

/**
 * WalkerAgent is the Agent implementation for the Walker creature.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class WalkerSuperAgent : public Agent
{
public:
  
    /**
     * Constructor with additional parameters.
     * 
     * @see Agent::Agent
     * 
     * @name The name of the agent
     * @param world The World which holds this Agent
     * @param brainPopulationSize The number of brains
     * @param bodynPopulationSize The number of simultan bodies
     * @param generationCycle The life time of a generation in seconds
     * @param newOriginPosition The origin position where to place the creatures around
     * @param newbreedRatee The Rate of the survivers
     */
    WalkerSuperAgent(const std::string name, World* world, int brainPopulationSize, 
                     int bodyPopulationSize, int generationCycle, 
                     Position* newOriginPosition, float newbreedRate);
    
protected:
    
    /**
     * Create and register the creatures.
     *
     * This method is only use from the constructor.
     */
    void initPopulation();
    
    /**
     * @see Agent::handleMutate
     */
    void handleMutation();
    
    /**
     * this is the origin position of the agents
     */    
    Position* originPosition;
    
    float newbreedRate;
    
    int brainPopulationSize;
    
    void distancesSort(Brain** brainsArray, int left, int right);
    
    void pickNetxBrains();

private:

    typedef std::map<int, Brain*> BrainsContainer;
    /**
     * The Brain objects
     */
    BrainsContainer brainsCon;
    
    
    typedef std::map<int, Body*> BodiesContainer;
    /**
     * The Body objects
     */
    BodiesContainer bodiesCon;
};

/**
 * Sorts an array of WalkerBrain objects by the distance they traveled.
 * 
 * This function uses a quicksort algorithm to sort an array of WalkerBrain objects
 * by the distance they traveled. The distance is saved in the Body (Walker in this
 * case), which is contained in the WalkerBrain.
 */
void distancesSort(Brain** brainsArray, int left, int right);

};

#endif //_WALKERSUPERAGENT_H_
