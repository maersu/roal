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
#ifndef _WHEELEDCREATUREFACTORY_H_
#define _WHEELEDCREATUREFACTORY_H_

#include "RoalCore.h"
#include "CreatureFactory.h"
#include "WheeledCreatureGenotype.h"
#include "NeighborDistanceSensor.h"


namespace Roal
{

/**
 * The LeggedCreatureFactory creates Body generated from the given 
 * LeggedCreatureGenotype or a random created LeggedCreatureGenotype. 
 * @see CreatureFactory
 *
 * @image html wheeledcreature1.png 
 * @image latex wheeledcreature1.ps 
 *   
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class WheeledCreatureFactory: public CreatureFactory
{
public:
    /**
     * Constructor
     *
     * @param name The name of the factory 
     * @param genotype The Genotype used to create random Body and Brain objects
     * @param agent The agnets which owns this factory
     */
	WheeledCreatureFactory(string name, WheeledCreatureGenotype* genotype, 
            Agent* agent);

    /**
     * Constructor
     * 
     * @param name The name of the factory
     * @param agent The agnets which owns this factory 
     */
	WheeledCreatureFactory(string name, Agent* agent);
    
    /**
     * Destructor
     */
	virtual ~WheeledCreatureFactory();

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

protected:
    
    /**
     * The Genotype used to create random Phenotype objects
     */
    WheeledCreatureGenotype* m_genotype;

    /**
     * the number of created bodies 
     */
    int bodyCnt;

    /**
     * The agent which owns this Factory
     */
    Agent* agent;
};

}

#endif //_WHEELEDCREATUREFACTORY_H_
