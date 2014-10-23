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
#ifndef _NEIGHBORDISTANCESENSOR_H_
#define _NEIGHBORDISTANCESENSOR_H_

#include "IStandaloneSensor.h"
#include "CubeSegment.h"
#include "Agent.h"
#include <float.h>

using namespace std;
/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
/**
 * The NeighborDistanceSensor is both a IStandaloneSensor and a CubeSegment. It 
 * serves information about a the distance of the nearest body.
 * You can ignore races (handeld by an Agnet) from this process. Also you can define
 * a working radius.    
 *
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class NeighborDistanceSensor: public IStandaloneSensor, public CubeSegment
{
public:
    /**
     * Constructor
     *
     * @param ownerAgnet the owner agent.
     * @param owner the owner Body.
     * @param name of the sensor. this has to be unique in the Wolrd.
     * @param meshFile The name of the Mesh File the Sensor uses.
     * @param radius the maximum distance the sensor can "see". 
     */
     NeighborDistanceSensor(Agent* ownerAgent, Roal::Body* owner, 
                         string name, string meshFile, float radius);
    /**
     * Constructor
     *
     * @param ownerAgnet the owner agent.
     * @param owner the owner Body.
     * @param name of the sensor. this has to be unique in the Wolrd.
     * @param meshFile The name of the Mesh File the Sensor uses.
     */
     NeighborDistanceSensor(Agent* ownerAgent, Roal::Body* owner, 
                         string name, string meshFile);
    /**
     * Destructor 
     */
    virtual ~NeighborDistanceSensor();

    /**
     * @see IStandaloneSensor::update().
     *
     * @warning Do not call this method in a non runing simulation!
     */
    virtual void update();

    /**
     * Sets the radius of the sensor.
     *
     * @param radius the maximum distance the sensor can "see". 
     */
    void setRadius(float radius);

    /**
     * Returns the radius of the sensor.
     *
     * @return radius the maximum distance the sensor can "see". 
     */
    float getRadius();
    
    /**
     * Body objects controlled by this Agent are not take in account.
     *
     * @param agentName the name of the Agent to ignore 
     */
    void addIgnoreAgent(string agentName);

private:
    
    /**
     * the owner agnet
     */
    Agent* ownerAgent;

    /**
     * radius the maximum distance the sensor can "see". 
     */
    float radius;

    /**
     * Vector which holds all names of the agents to ignore.
     */
    std::vector<string> ignoreAgent;

};

}

#endif //_NEIGHBORDISTANCESENSOR_H_
