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
#ifndef _LEGGEDCREATUREFACTORY_H_
#define _LEGGEDCREATUREFACTORY_H_

#include "RoalCore.h"
#include "CreatureFactory.h"
#include "LeggedCreatureGenotype.h"
#include "LeggedCreatureBrain.h"

namespace Roal
{

/**
 * The LeggedCreatureFactory creates Body generated from the given 
 * LeggedCreaturGenotype or a random created LeggedCreatureGenotype. 
 * @see CreatureFactory
 *
 * @image html leggedcreature1.png 
 * @image latex leggedcreature1.ps 
 *
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class LeggedCreatureFactory: public CreatureFactory
{
public:
    /**
     * Constructor
     *
     * @param name The name of the factory 
     * @param genotype The Genotype used to create random Body and Brain objects
     */
	LeggedCreatureFactory(string name, LeggedCreatureGenotype* genotype);

    /**
     * Constructor
     * 
     * @param name The name of the factory 
     */
	LeggedCreatureFactory(string name);
    
    /**
     * Destructor
     */
	virtual ~LeggedCreatureFactory();

    /**
     * @see CreatureFactory::generateRandomCreature().
     */
    Brain* generateRandomCreature(string name, Position* pos);
    
    /**
     * @see CreatureFactory::generateCreature().
     */
    Brain* generateCreature(string name, Position* pos, Phenotype* phenotype);
    
    /**
     * @see CreatureFactory::generateRandomBody().
     */
    Body* generateRandomBody(string name, Position* pos);
    
    /**
     * @see CreatureFactory::generateBody().
     */
    Body* generateBody(string name, Position* pos, Phenotype* phenotype);
        
private:

    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */   
    LeggedCreatureFactory(); 
        
    /**
     * The Genotype used to create random Phenotype objects
     */
    LeggedCreatureGenotype* m_genotype;

    /**
     * the number of created bodies 
     */
    int bodyCnt;
};

}

#endif //_LEGGEDCREATUREFACTORY_H_
