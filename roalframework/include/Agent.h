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
#ifndef _AGENT_H_
#define _AGENT_H_

#include <string>
#include "Brain.h"
#include "World.h"
#include "Body.h"
#include "RoalCore.h"
#include "KeySensor.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
class World; // Forward declaration for World class
class KeySensor;
    
/**
 * Creates the creatures and controls the evolutionary process.
 *
 * An Agent creates creatures (Body and a Brain) and decides which creatures
 * will survive and which will die. It surveys the learning progress of each
 * creature and manages the evolutionary process by using genetic algorithms
 * for example.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class Agent
{
public:
    /**
     * Constructor.
     * 
     * @param name The name of the Agent.
     * @param world The world, the agent lives in.
     */
	Agent(const string name, World* world);
    
    /**
     * Constructor with additional parameters.
     * 
     * @param name The name of the Agent.
     * @param world The world, the agent lives in.
     * @param populationSize The amount of creatures of a population.
     * @param generationCycle The duration of one generation cycle in seconds.
     */
	Agent(const string name, World* world, int populationSize, int generationCycle);
    
    /**
     * Destructor
     */
	virtual ~Agent();
    
    /**
     * Sets the name of the Agent.
     * 
     * @param name A name for the Agent.
     */   
    void setName(const string name);
    
    /**
     * Returns the name of the Agent.
     * 
     * @return The name of the Agent.
     */
    string getName();
    
    /**
     * Returns true if the Body is already registered.
     * 
     * @param name The name of a Body.
     * @return true if the Body is already registered.
     */
    bool isBodyRegistered(string name);
    
    /**
     * Returns true if the Brain is already registered.
     * 
     * @param name The name of a Brain.
     * @return true if the Brain is already registered.
     */    
    bool isBrainRegistered(string name);
 
    /**
     * Adds a Body to the World.
     * 
     * @param body A Body to register within the Agent/World.
     * 
     * @exception RoalException if a Body with the same name exists already.
     */
	void registerBody(Body* body);
    
    /**
     * Adds a Brain to the World.
     * 
     * Hint: The Brain should hold a Body.
     * 
     * @param brain A Brain to register within the Agent/World.
     * 
     * @exception RoalException if a Brain with the same name exists already.
     */
    void registerBrain(Brain* brain);
    
    /**
     * Kills a Brain.
     * 
     * After killing, the Brain and its Body are still available in the World
     * but they are dead, since the Brain will no more be handled by the Agent.
     * 
     * @param brain A Brain to kill.
     * 
     * @exception RoalException if a Brain with the given name does not exist.
     */
    void killBrain(Brain* brain);

    /**
     * Removes a Body from the Agent and the World.
     * 
     * @param body A Body to unregister from the Agent and the World.
     * 
     * @exception RoalException if a Brain with the given name does not exist.
     */
	void unregisterAndDeleteBody(Body* body);
    
    /**
     * Kills all registered Brain objects.
     * 
     * Kills all the Brain objects from the Brain map and the dead Brain map.
     * After killing, the Brain objects and their corresponding Body objects
     * are still available in the World but they are dead, since the Brain will
     * no more be handled by the Agent.
     */
    virtual void killAllBrains();

    /**
     * Kills all the registered Body objects.
     */    
    virtual void killAllBodies();
    
    /**
     * Create and register the creatures.
     * 
     * The initPopulation method is called once in a simulation. It contains the
     * initial creation of the creatures (Brain and Body objects), either
     * manually or by a CreatureFactory.
     */
    virtual void initPopulation();

    /**
     * The simulation's iteration method for each frame.
     * 
     * This method is called from the World::frameStarted method every time a frame
     * is rendered. It calls the Brain object's iterate method which allows
     * them to control their Body objects (e.g. read sensors, apply force).
     * 
     * @param elapsedTime The time since last frame in seconds.
     */ 
    virtual void iterate(float elapsedTime);
    
    /**
     * The simulation's post-iteration method for each frame.
     * 
     * This method is called from the World::frameEnded method every time a frame
     * is rendered. Here you typically remove or add objects from or to the world.
     */
    virtual void prepareNextStep();
    
    /**
     * Returns the number of generations that already passed.
     * 
     * @return the number of generations.
     */    
    long getGenerationCount();
    
    /**
     * Returns the age of the currently running population in seconds.
     * 
     * @return The age of the generation in seconds.
     */
    double getGenerationAge();
    
    /**
     * Returns the closest Body from given Position.
     *
     * @param pos The position from which the distances starts.
     * @param maxRadius The maximum radius (discribes a sphere).
     * @param ignoreName A Body with this name will be not considered.
     * 
     * @return the closest Body (NULL if no Body is in the maxRadius)
     */
    Body* getClosestBody(Position* pos, float maxRadius, string ignoreName);
    
    /**
     * Returns the distance to the closest body from a given Position.
     *
     * @param pos the position from which the distances starts.
     * @param maxRadius the maximum radius (discribes a sphere).
     * @param ignoreName a Body with this name will be not considered.
     * 
     * @return the distance to closest Body (maxRadius if no Body is in the maxRadius)
     */
    float getClosestBodyDistance(Position* pos, float maxRadius, string ignoreName);
    
    /**
     * Returns the distance to the closest body from given Position.
     *
     * @param pos the position from which the distances starts.
     * @param maxRadius the maximum radius (discribes a sphere).
     * @param ignoreName a Body with this name will be not considered.
     * 
     * @return the distance to closest Body (maxRadius if no Body is in the maxRadius)
     */
    float getClosestBodyDistanceWorldWide(Position* pos, float maxRadius,
                        string ignoreName, vector<string> ignoreAgent);
    
protected:
    /**
     * Default constructor, may not be used.
     */
    Agent()
    {
        throw(RoalException(typeid( this ).name(),
              "Default constructor of Agent, may not be used."));
    }
    
    /**
     * The name of the Agent
     */ 
    string name;
    
    /**
     * The world, the agent lives in.
     *
     * This pointer is needed to register the generated creatures (Body and Brain
     * objects in the world).
     */ 
    World* world;
    
    typedef map<string, Body*> BodiesMap;
    /**
     * The Body objects of the creatures the agent controls.
     */
	BodiesMap bodies;

    typedef map<string, Brain*> BrainsMap;
    /**
     * The Body objects of the creatures the agent controls.
     */
	BrainsMap brains;
    
    /**
     * The brains of the creatures that were killed by the emergency function.
     * 
     * Can be used for further investigations ;-)
     */
	BrainsMap deadBrains;
    
    /**
     * The amount of creatures to create initially and after each generation cycle.
     */ 
    int populationSize;
    
    /**
     * The duration of one generation cycle in seconds.
     *
     * The number of seconds until the active generation dies and new children
     * will become active.
     */ 
    int generationCycle;
    
    /**
     * Calculate a random position around the Agent's origin.
     *
     * @return The calculated random Position.
     */
    Position* getRandomPosFromOrigin(Position* origin, float radius);
     
    /**
     * Processes and generates the a new generation.
     *
     * This method will be called if a generation cycle is over. You will have
     * to implement it. Here you can do crossing, reproduction, mutations,
     * killing etc. and finally create the a new generation of creatures (Brain
     * and Body objects).
     */
    virtual void handleMutation() = 0;
    
    /**
     * Creates a KeySensor to use keystrokes in the simulation.
     */
    KeySensor* createKeySensor();
    
    /**
     * A counter that is used to not check every frame if the is key is pressed.
     * 
     * @see Agent::iterate where this counter is used.
     */
    int toggleMovableTextCounter;

private:
    /**
     * The start time of this Agent (is set in Agent::initPopulation).
     */
    time_t generationStartTime;
     
    /**
     * The amount of generations that passed.
     */
    long generationCount;
};

}

#endif //_AGENT_H_
