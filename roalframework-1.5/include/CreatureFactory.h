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
#ifndef _CREATUREFACTORY_H_
#define _CREATUREFACTORY_H_

#include "RoalCore.h"
#include "WheeledCreatureGenotype.h"
#include "NeighborDistanceSensor.h"


namespace Roal
{

/**
 * The CreatureFactory is an abstract class which serves some method to create Creatures.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class CreatureFactory
{
public:
    /**
     * Constructor
     * 
     */
	CreatureFactory(string name);

    /**
     * Destructor
     */
	virtual ~CreatureFactory();

    /**
     * Builds a random creature (Body and Brain).
     * 
     * The Body is already registered in the Brain, use Brain::getBody() to get it.
     */
   virtual Brain* generateRandomCreature(string name, Position* pos) = 0;
    
    /**
     * Builds a creature (Body and Brain) from the given phenotype.
     * 
     * The Body is already registered in the Brain, use Brain::getBody to get it.
     */
    virtual Brain* generateCreature(string name, Position* pos, Phenotype* phenotype) = 0;
    
    /**
     * Builds a random Body from the LeggedCreatureGenotype.
     */
    virtual Body* generateRandomBody(string name, Position* pos) = 0;
    
    /**
     * Builds a body from the given Phenotype.
     */
    virtual Body* generateBody(string name, Position* pos, Phenotype* phenotype) = 0;
    
    /**
     * The name of the factory.
     */
    string getName();

protected:
            
    /**
     * Returns a mesh file name from the given index for CubeSegment objects.
     */
    string getCubeTextureFileName(int indexName);

    /**
     * Returns a random mesh file name for CubeSegment objects.
     */
    string getRandomCubeTextureFileName();

    /**
     * the name of the facctory.
     */
    string name;
    
private:
    /**  
     * Default Constructor.
     * 
     * Do Not Use!
     */   
    CreatureFactory() {};   

};

}

#endif //_CREATUREFACTORY_H_
