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
#ifndef _LEGGEDCREATUREPHENOTYPE_H_
#define _LEGGEDCREATUREPHENOTYPE_H_

#include <vector>
#include "Phenotype.h"
#include "LeggedCreatureGenotype.h"

using namespace std;

namespace Roal
{

/**
 * The LeggedCreaturePhenotype class represents the genetic material of a LeggedCreature.
 * @see Phenotype
 *
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class LeggedCreaturePhenotype: public Phenotype
{
public:
    /**
     * Constructor
     */
	LeggedCreaturePhenotype(LeggedCreatureGenotype* creator);
    
    /**
     * Destructor
     */
	virtual ~LeggedCreaturePhenotype();

    /**
     * Normalize every information under the aspects of the minima and maxima of 
     * the creator Genotype and returns the result as string
     *
     * @param separator A string used to seprate the values.
     */
    string toNormalizeValueString(string separator);

     /**
     * Normalize every information under the aspects of the minima and maxima of 
     * the creator Genotype and returns the result as a vector where every value
     * is avector item.
     */
    vector<float> toNormalizeVector();
};

}

#endif //_LEGGEDCREATUREPHENOTYPE_H_
