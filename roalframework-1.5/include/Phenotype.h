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
#ifndef _PHENOTYPE_H_
#define _PHENOTYPE_H_

#include "ValueHandler.h"
#include "Genotype.h"

namespace Roal
{

class Genotype;
/**
 * The Phenotype class represents the genetic material of a creature.
 * 
 * The Phenotype object contains absolut genetic informations about a creature. 
 * That can be intellectual information (used in the Brain) or information about the
 * physical nature of the creature (used in the Body). The Phenotype defines 
 * exactly one creature. It same like DNS
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class Phenotype: public ValueHandler
{
public:
    /**
     * Constructor
     */
	Phenotype(Genotype* creator);
    
    /**
     * Destructor
     */
	virtual ~Phenotype();

    Genotype* getCreatorGenotype();

protected:
    Genotype* creator;

    /**
     * calculates the currentValue normalized under the aspects of min and max.
     *
     * @param currentValue The Value to normalize.
     * @param min The min value taken as 0 % 
     * @param min The min value taken as 100 %.
     */
    float getNormalizedValue(float currentValue, float min, float  max);

};

}

#endif //_PHENOTYPE_H_
