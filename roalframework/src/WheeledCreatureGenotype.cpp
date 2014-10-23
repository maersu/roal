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

#include "WheeledCreatureGenotype.h"

namespace Roal
{

//-----------------------------------------------------------------------------
WheeledCreatureGenotype::WheeledCreatureGenotype()
{
    //At the moment only 4 legged Creature are suported
    setMinMaxValue("wheelCount", 4, 4);    
}

//------------------------------------------------------------------------------
WheeledCreatureGenotype::~WheeledCreatureGenotype()
{

}

//------------------------------------------------------------------------------
Phenotype* WheeledCreatureGenotype::getRandomPhenotype()
{
    Phenotype* result = new Phenotype(this);
    this->setRequiredMinMaxValues();
    
     // Generate random data for the WheeledCreatureBrain
    float tmp;
    
    tmp = getRandomValue("bodyWidth");
    result->setValue("bodyWidth", tmp);
     
    tmp  = getRandomValue("bodyHeight");
    result->setValue("bodyHeight", tmp);

    tmp  = getRandomValue("bodyLength");
    result->setValue("bodyLength", tmp);
    
    tmp  = getRandomValue("wheelCount");
    result->setValue("wheelCount", tmp);
    
    tmp  = getRandomValue("hasFrontNbrSensors");
    if (tmp>0.5) {tmp = 1.0;} else {tmp = 0.0;}
    result->setValue("hasFrontNbrSensors", tmp);
    
    tmp  = getRandomValue("hasBackNbrSensors");
    if (tmp>0.5) {tmp = 1.0;} else {tmp = 0.0;}
    result->setValue("hasBackNbrSensors", tmp);

    tmp  = getRandomValue("hasCollisionCage");
    if (tmp>0.5) {tmp = 1.0;} else {tmp = 0.0;}
    result->setValue("hasCollisionCage", tmp);
    
    tmp  = getRandomValue("frontNbrSensorsRadius");
    result->setValue("frontNbrSensorsRadius", tmp);
    
    tmp  = getRandomValue("backNbrSensorsRadius");
    result->setValue("backNbrSensorsRadius", tmp);
    
    tmp  = getRandomValue("texture");
    result->setValue("texture", tmp);

    tmp  = getRandomValue("corpusMass");
    result->setValue("corpusMass", tmp);
    
    tmp  = getRandomValue("wheelMass");
    result->setValue("wheelMass", tmp);
    
    return result;
}
//---------------------------------------------------------------------
void WheeledCreatureGenotype::setRequiredMinMaxValues()
{
    //default Values
    if (! (this->hasMinMaxValue("bodyWidth"))) {setMinMaxValue("bodyWidth", 0.6, 5.0);}       
    if (! (this->hasMinMaxValue("bodyHeight"))) {setMinMaxValue("bodyHeight", 1.0, 2.0);}
    if (! (this->hasMinMaxValue("bodyLength"))) {setMinMaxValue("bodyLength", 0.6, 8.0);}
    if (! (this->hasMinMaxValue("wheelCount"))) {setMinMaxValue("wheelCount", 2, 6);}      
    if (! (this->hasMinMaxValue("hasFrontNbrSensors"))) {setMinMaxValue("hasFrontNbrSensors", 0, 1);}         
    if (! (this->hasMinMaxValue("hasBackNbrSensors"))) {setMinMaxValue("hasBackNbrSensors", 0, 1);}    
    if (! (this->hasMinMaxValue("hasCollisionCage"))) {setMinMaxValue("hasCollisionCage", 0, 1);}    
    if (! (this->hasMinMaxValue("frontNbrSensorsRadius"))) {setMinMaxValue("frontNbrSensorsRadius", 2, 400);}         
    if (! (this->hasMinMaxValue("backNbrSensorsRadius"))) {setMinMaxValue("backNbrSensorsRadius", 2, 400);}   
    if (! (this->hasMinMaxValue("texture"))) {setMinMaxValue("texture", 0, 27);}  
    if (! (this->hasMinMaxValue("corpusMass"))) {setMinMaxValue("corpusMass", 0.2, 4);}  
    if (! (this->hasMinMaxValue("wheelMass"))) {setMinMaxValue("wheelMass", 0.2, 1.2);}      
}

};
