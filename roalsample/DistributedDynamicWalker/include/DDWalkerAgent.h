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
#ifndef _DDWALKERAGENT_H_
#define _DDWALKERAGENT_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <RoalFramework/DistributedAgent.h>
#include <RoalFramework/Util.h>
#include <RoalFramework/Box.h>
#include <RoalFramework/LeggedCreatureFactory.h>
#include <RoalFramework/LeggedCreatureBrain.h>
#include <RoalFramework/LeggedCreaturePhenotype.h>
#include <RoalFramework/LeggedCreatureGenotype.h>
#include <RoalFramework/KeySensor.h>

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The Agent implementation for the distributed dynamic walker example.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class DDWalkerAgent : public DistributedAgent
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
     */
    DDWalkerAgent(const string name, DistributedWorld* world,
                           int bodyPopulationSize, int generationCycle, 
                           Position* newOriginPosition);
    /**
     * Create and register the creatures from the given Message.
     */
    void initPopulation(ConnectorMessage* message);
    
    /**
     * @see Agent::handleMutate
     */
    void handleMutation();

    void iterate(float elapsedTime, ConnectorMessage* message);

protected:

    /**
     * this is the origin position of the agents
     */    
    Position* originPosition;
    
    /**
     * The number of brains to manage (may be bigger than the number of bodies).
     */
    int brainPopulationSize;
    
    /**
     * Sorts an array of Brain objects by their fitness.
     * 
     * @param brainsArray An array of Brain objects.
     * @param left The index of the left border (0 if from beginning).
     * @param right The index of the right border (size of brainsArray if until end).
     */
    void distancesSort(LeggedCreatureBrain** brainsArray, int left, int right);
    
private:
    /**
     * A Genotype for the creatures of this Agent.
     */
    LeggedCreatureGenotype* geno; 
    
    /**
     * An instance of the LeggedCreatureFactory, used to generate random phenotypes.
     */
    LeggedCreatureFactory* factory;
    
    /**
     * A reference to the KeySensor.
     */
    KeySensor* key;

};


}

#endif //_DDWALKERAGENT_H_
