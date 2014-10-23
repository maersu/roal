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
#ifndef _WALKERAGENT_H_
#define _WALKERAGENT_H_

#include <iostream>
#include <stdio.h>

#include <RoalFramework/Agent.h>
#include <RoalFramework/World.h>
#include <RoalFramework/Position.h>
#include <RoalFramework/Body.h>
#include <RoalFramework/Brain.h>
#include <RoalFramework/Util.h>
#include <RoalFramework/File.h>

#include "Walker.h"
#include "WalkerBrain.h"

using namespace std;

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
class WalkerAgent : public Agent
{
public:
    /**
     * Constructor
     * 
     * @see Agent::Agent
     * 
     * @name The name of the agent
     * @param newOriginPosition The origin position where to place the creatures around
     * @param world The World which holds this Agent
     */
    WalkerAgent(const string name, World* world, Position* newOriginPosition);
    
    /**
     * Constructor with additional parameters.
     * 
     * @see Agent::Agent
     * 
     * @name The name of the agent
     * @param world The World which holds this Agent
     * @param populationSize The number of creatures in one generation
     * @param generationCycle The lif time of a generation in seconds
     * @param newOriginPosition The origin position where to place the creatures around
     * @param newSurviverRate The Rate of the survivers
     */
    WalkerAgent(const string name, World* world, int populationSize, 
            int generationCycle, Position* newOriginPosition, float newSurviverRate);
    
    /**
     * @see Agent::killAllBrains
     */
    virtual void killAllBrains();
    
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
    

    typedef map<string, Brain*> SurviverBrainsMap;
    /**
     * The Brain objects that survive a generation.
     * 
     * In this map, the method WalkerAgent::handleMutation stores the brains that 
     * survive (it calculates the successors and stores them).
     */
	SurviverBrainsMap surviverBrains;
    
    float surviverRate;
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

#endif //_WALKERAGENT_H_
