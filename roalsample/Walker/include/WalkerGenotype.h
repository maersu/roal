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
#ifndef _WALKERGENOTYPE_H_
#define _WALKERGENOTYPE_H_

#include <RoalFramework/Genotype.h>
#include <RoalFramework/RoalException.h>

namespace Roal
{

/**
 * WalkerGenotype is the Genotype implementation for the Walker creature.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class WalkerGenotype
{
public:
    /**
     * Constructor
     * 
     * The constructor generates random brain data.
     */
	WalkerGenotype();
    
    /**
     * Destructor
     */
	virtual ~WalkerGenotype();
    
    /**
     * Sets a certain parameter of the Brain data.
     * 
     * @see WalkerGenotype::brainData
     * 
     * @param index The index of the data.
     * @param value The value of the data.
     */
    void setBrainDataAtIndex(int index, float value);
    
    /**
     * Get a certain parameter of the Brain data.
     * 
     * @see WalkerGenotype::brainData
     * 
     * @param index The index of the data.
     */
    float getBrainDataAtIndex(int index);
    
    /**
     * @see Genotype::crossWith
     * 
     * @exception Throws a RoalException if the Genotype is not a WalkerGenotype.
     */
    WalkerGenotype* crossWith(WalkerGenotype* partnerGenotype);

private:
    /**
     * The Brain data consists of several parameters that affect the brain.
     */
    float brainData[9];
};

};

#endif //_WALKERGENOTYPE_H_
