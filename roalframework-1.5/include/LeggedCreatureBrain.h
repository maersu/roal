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
#ifndef _LEGGEDCREATUREBRAIN_H_
#define _LEGGEDCREATUREBRAIN_H_

#include <stdio.h>
#include <string>
#include <map>

#include "IEffector.h"
#include "Brain.h"
#include "Body.h"
#include "Phenotype.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * LeggedCreatureBrain is the Brain implementation for the LeggedCreature creature.
 * It supports some method to handle a Body created by the LeggedCreatureFactory.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class LeggedCreatureBrain: public Brain
{
public:
    /**
     * Constructor
     * 
     * @param name see Brain::name
     */
	LeggedCreatureBrain(const std::string name);
    
    /**
     * Destructor  
     */
	virtual ~LeggedCreatureBrain();
    
    /**
     * @see Brain::iterate
     */
    virtual void iterate(float elapsedTime);
    
    /**
     * @see Brain::registerBody
     * 
     * @exception Throws a RoalException if the Body is no a LeggedCreature.
     */
    virtual void registerBody(Body* body);
    
    /**
     * Returns a string which represents the current LeggedCreatureBrain in a human 
     * readable form.
     * 
     * @param sep  the Separator to divide the information  
     * @return The String which holds different parameters and other Informations
     */
    std::string toString(string valueDelimiter, string separator);
    
    /**
     * Returns the distance the body travelled sience last resetDistanceTravelled() call.
     */
    float getDistanceTravelled();    

    /**
     * Resets the distance the body travelled.
     */
    void resetDistanceTravelled();

protected:
    
    /**
     * The age of the LeggedCreature creature.
     */
    float age;

private:

    /**
     * the last position initalliezed by resetDistanceTravelled().
     */
    Position* lastPos;
};

}

#endif //_LEGGEDCREATUREBRAIN_H_
