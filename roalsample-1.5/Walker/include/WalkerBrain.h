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
#ifndef _WALKERBRAIN_H_
#define _WALKERBRAIN_H_

#include <RoalFramework/Brain.h>
#include "Walker.h"
#include "WalkerGenotype.h"
#include <RoalFramework/Util.h>

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * WalkerBrain is the Brain implementation for the Walker creature.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class WalkerBrain : public Brain
{
public:
    /**
     * Constructor
     * 
     * @param name see Brain::name
     */
	WalkerBrain(const std::string name);
    
    /**
     * Destructor  
     */
	virtual ~WalkerBrain();
    
    /**
     * @see Brain::iterate
     */
    virtual void iterate(float elapsedTime);
    
    /**
     * @see Brain::registerBody
     * 
     * @exception Throws a RoalException if the Body is no a Walker.
     */
    virtual void registerBody(Body* body);
    
    /**
     * Get the Genotype of the Walker creature.
     */
    WalkerGenotype* getGenotype();
    
    /**
     * Set the Genotype for the Walker creature.
     */
    void setGenotype(WalkerGenotype* genotype);
    
    /**
     * Returns a String which represents a the current WalkerBrain in a human 
     * readable form.
     * 
     * @param sep  the Separator to divide the information  
     * @return The String which holds different parameters and other Informations
     */
    std::string toString(std::string sep);
    
protected:
    /**
     * The genetical informations of the Walker creature
     */
    WalkerGenotype* genotype;
    
    /**
     * The age of the Walker creature.
     */
    float age;
    int updateMovableTextCounter;
};

};

#endif //_WALKERBRAIN_H_
