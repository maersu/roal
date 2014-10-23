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
#ifndef _HUNTERBRAITENBERGBRAIN_H_
#define _HUNTERBRAITENBERGBRAIN_H_

#include <RoalFramework/Brain.h>
#include <RoalFramework/IEffector.h>
#include <RoalFramework/Phenotype.h>
#include <RoalFramework/Util.h>
/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
/**
 * HunterBraitenbergBrain is the Brain implementation for the Braitenberg creature.
 * @see Brain
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class HunterBraitenbergBrain : public Brain
{
public:
    /**
     * Constructor
     * 
     * @param name see Brain::name
     */
	HunterBraitenbergBrain(const std::string name);
    
    /**
     * Destructor  
     */
	virtual ~HunterBraitenbergBrain();
    
    /**
     * @see Brain::iterate
     */
    virtual void iterate(float elapsedTime);
    
    /**
     * @see Brain::registerBody
     */
    virtual void registerBody(Body* body);

    /**
     * Returns the current energy of the Brain
     */
    float getEnergy();

    /**
     * Adds a value to the  internale enregy count
     */
    void addEnergy(float energy);
    
protected:

    /**
     * The age of the agent
     */
    float age;

    /**
     * The energy of the agent
     */
    float energy;
};

}

#endif //_HUNTERBRAITENBERGBRAIN_H_
