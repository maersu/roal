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

#include "WalkerGenotype.h"

namespace Roal
{

//-----------------------------------------------------------------------------
WalkerGenotype::WalkerGenotype()
{
    // Generate random data for the WalkerBrain
    this->setBrainDataAtIndex(8, ((float)rand()/RAND_MAX) * 5.0 - 2.5);
    this->setBrainDataAtIndex(0, ((float)rand()/RAND_MAX) * 2.0 - 1.0);
    this->setBrainDataAtIndex(1, ((float)rand()/RAND_MAX) * 2.0 - 1.0);
    this->setBrainDataAtIndex(2, ((float)rand()/RAND_MAX) * 2.0 - 1.0);
    this->setBrainDataAtIndex(3, ((float)rand()/RAND_MAX) * 2.0 - 1.0);
    this->setBrainDataAtIndex(4, ((float)rand()/RAND_MAX) * 6.3 - 3.15);
    this->setBrainDataAtIndex(5, ((float)rand()/RAND_MAX) * 6.3 - 3.15);
    this->setBrainDataAtIndex(6, ((float)rand()/RAND_MAX) * 6.3 - 3.15);
    this->setBrainDataAtIndex(7, ((float)rand()/RAND_MAX) * 6.3 - 3.15);
}


//------------------------------------------------------------------------------
WalkerGenotype::~WalkerGenotype()
{
}


//------------------------------------------------------------------------------
void WalkerGenotype::setBrainDataAtIndex(int index, float value)
{
    if ( (index>=0) && (index<9) ) {
       this->brainData[index] = value;
    } else {
        throw(RoalException(typeid( this ).name(),
            "Index is out of bound! Should be between 0 and 8"));
    }
}


//------------------------------------------------------------------------------
float WalkerGenotype::getBrainDataAtIndex(int index)
{
    if ( (index>=0) && (index<9) ) {
        return this->brainData[index];
    } else {
        throw(RoalException(typeid( this ).name(),
            "Index is out of bound! Should be between 0 and 8"));
    }
}


//------------------------------------------------------------------------------
WalkerGenotype* WalkerGenotype::crossWith(WalkerGenotype* partnerGenotype)
{
    WalkerGenotype* first;
    WalkerGenotype* second;
    
    // Generate the successor's Genotype
    WalkerGenotype* successorGenotype = new WalkerGenotype();
    
    //We don't always want to use the first half of the first argument passed.
    //We sometimes want to take the first half of the second argument...
    //The first argument has more influence on the child.
    
    if(rand() % 2){
      first = this;
      second = (WalkerGenotype*)partnerGenotype;
    } else {
      first = (WalkerGenotype*)partnerGenotype;
      second = this;
    }
    
    // Cross the indexes
    successorGenotype->setBrainDataAtIndex(0, first->getBrainDataAtIndex(0));
    successorGenotype->setBrainDataAtIndex(1, first->getBrainDataAtIndex(1));
                                            
    successorGenotype->setBrainDataAtIndex(2, first->getBrainDataAtIndex(2));
    successorGenotype->setBrainDataAtIndex(3, first->getBrainDataAtIndex(3));
    
    successorGenotype->setBrainDataAtIndex(4, first->getBrainDataAtIndex(4));
    successorGenotype->setBrainDataAtIndex(5, second->getBrainDataAtIndex(5));
                                                    
    successorGenotype->setBrainDataAtIndex(6, second->getBrainDataAtIndex(6));
    successorGenotype->setBrainDataAtIndex(7, second->getBrainDataAtIndex(7));
    
    // Let index 8 be random generated
    successorGenotype->setBrainDataAtIndex(8, second->getBrainDataAtIndex(8));
    
    
    return successorGenotype;
}

};
