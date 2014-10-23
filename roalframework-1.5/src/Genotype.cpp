/**     
    This file is part of Roal, a framework for simulations in the field
    of Artificial Intelligence and Aritificial Life.
    See http://roal.sourceforge.net/ for more informations.

    Copyright (c) 2005 Project Roal

    Roal is free software; you can redistribute it and/or modify
    it under the terms of the GNU Genweehleral Public License as published by
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

#include <math.h>
#include "Genotype.h"

namespace Roal
{

//------------------------------------------------------------------------------
Genotype::Genotype()
{

}


//------------------------------------------------------------------------------
Genotype::~Genotype()
{
}


//------------------------------------------------------------------------------
bool Genotype::hasMinMaxValue(string key)
{
    return  ( this->hasValue(MIN_PREFIX+key) && this->hasValue(MAX_PREFIX+key) );
}


//------------------------------------------------------------------------------
void Genotype::setMinMaxValue(string key, float minValue, float maxValue)
{ 
    if (maxValue < minValue)
    {
        throw(RoalException(typeid( this ).name(), "Could not setValue min: "
                    +toStdStr(minValue)+" max: "+toStdStr(maxValue)));
    }
    this->setValue(MIN_PREFIX+key,minValue);
    this->setValue(MAX_PREFIX+key,maxValue);
    
}


//------------------------------------------------------------------------------
float Genotype::getMinValue(string key)
{ 
    return this->getValue(MIN_PREFIX + key);
}


//------------------------------------------------------------------------------
float Genotype::getMaxValue(string key)
{ 
    return this->getValue(MAX_PREFIX + key);
}


//------------------------------------------------------------------------------
int Genotype::getValuesCount()
{
    // different from Value Handler because the Genotype stores two informatin 
    // per key
    return ValueHandler::getValuesCount()/2;
}


//------------------------------------------------------------------------------
float Genotype::getRandomValue(string key)
{
    
    float result = getRandomValue(MIN_PREFIX+key,MAX_PREFIX+key);
    return result;
}


//------------------------------------------------------------------------------
float Genotype::getRandomValue(float min, float max)
{
    if (max < min)
    {
        throw(RoalException(typeid( this ).name(), "Could not create Random Value between min: "
                    +toStdStr(min)+"and max: "+toStdStr(max)));
    }
    
    float summ = max + (-1 * min);
    
    float result = ((float)rand()/(float)RAND_MAX) * summ + (min);
    return result;
    
}


//------------------------------------------------------------------------------
float Genotype::getRandomValue(string minKey, string maxKey)
{
    if ( this->hasValue(minKey) && this->hasValue(maxKey) )
    {
        return this->getRandomValue(this->getValue(minKey), this->getValue(maxKey));
    } else {
      throw(RoalException(typeid( this ).name(), 
         "Could not create Random Value because Key(s) does not exists: minKey:"
                    +minKey+" maxKey: "+maxKey));  
    }
}

}
