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

#include "NeighborDistanceSensor.h"


/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

//------------------------------------------------------------------------------
NeighborDistanceSensor::NeighborDistanceSensor(Agent* ownerAgent, Roal::Body* owner, 
                        std::string name, std::string meshFile, float radius)
    :IStandaloneSensor(),
    CubeSegment(owner,name,meshFile)
{
    this->ownerAgent = ownerAgent;
    setRadius(radius);
}


//------------------------------------------------------------------------------
NeighborDistanceSensor::NeighborDistanceSensor(Agent* ownerAgent, Roal::Body* owner, 
                        std::string name, std::string meshFile)
    :IStandaloneSensor(),
    CubeSegment(owner,name,meshFile)
{
    this->ownerAgent = ownerAgent;
    setRadius(10000.0); /**@todo use a const value like FLOAT_MAX.*/
}

//------------------------------------------------------------------------------    
NeighborDistanceSensor::~NeighborDistanceSensor()
{
}

//------------------------------------------------------------------------------ 
void NeighborDistanceSensor::update()
{
    // ask every agent which body is the nearest to the given Position.
    float dist =  
        this->ownerAgent->getClosestBodyDistanceWorldWide(this->getPosition(), 
                                                this->radius,
                                                this->getOwner()->getName(), 
                                                ignoreAgent);
    
    //normalize the radius (create a value between 0 and 1)
    if (this->radius > 0 && this->radius > dist)
    {
       this->setValue((1.0-dist/this->radius));
    } else {
       this->setValue(0);
    }

}

//------------------------------------------------------------------------------ 
void NeighborDistanceSensor::setRadius(float radius)
{
    this->radius = radius;
}

//------------------------------------------------------------------------------ 
float NeighborDistanceSensor::getRadius()
{
    return this->radius;
}

//------------------------------------------------------------------------------
void NeighborDistanceSensor::addIgnoreAgent(string agentName)
{
     ignoreAgent.push_back(agentName);
}

};
