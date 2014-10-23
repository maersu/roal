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

#include "LeggedCreatureGenotype.h"

namespace Roal
{

//-----------------------------------------------------------------------------
LeggedCreatureGenotype::LeggedCreatureGenotype()
{
     
}

//------------------------------------------------------------------------------
LeggedCreatureGenotype::~LeggedCreatureGenotype()
{

}

//------------------------------------------------------------------------------
Phenotype* LeggedCreatureGenotype::getRandomPhenotype()
{
    Phenotype* result = new Phenotype(this);
    this->setRequiredMinMaxValues();
    
     // Generate random data for the LeggedCreatureBrain
    float tmp, bodyWidth, bodyLength, bodyHeight, armHeight, armWidth, armLength, 
    constValue, force;
    
    bodyWidth = getRandomValue("bodyWidth");
    result->setValue("bodyWidth", bodyWidth);
     
    bodyHeight  = getRandomValue("bodyHeight");
    result->setValue("bodyHeight", bodyHeight);

    bodyLength  = getRandomValue("bodyLength");
    result->setValue("bodyLength", bodyLength);   
    
    armHeight = ((float)rand()/(float)RAND_MAX) * bodyHeight;  //smaller than body Hight
    result->setValue("armHeight", armHeight);
    
    int legCount  = floor(getRandomValue("legCount"));
    while (legCount%2 != 0){
        legCount  = floor(getRandomValue("legCount"));
    }

    result->setValue("legCount", (float)legCount);
    
    armWidth  = getRandomValue("armWidth"); 
    result->setValue("armWidth", armWidth);
    
    armLength  = getRandomValue("armLength"); 
    result->setValue("armLength", armLength);
 
    constValue  =  getRandomValue("constValue");
    result->setValue("constValue", constValue);
    
    
    /**@todo find a better formula.*/
    float volumeCorpus = (bodyWidth*bodyHeight*bodyLength);
    float volumeLegs =   (armWidth*armHeight*armLength);

    force  = (volumeCorpus); // depends on body Size 
    result->setValue("force", force);
    
    for (int m = 1; m<= legCount; m++)
    {
        tmp =  getRandomValue("armComp1"); 
        result->setValue("axle"+toStdStr(m)+"_Comp1", tmp);     
        
        tmp =  getRandomValue("armComp2"); 
        result->setValue("axle"+toStdStr(m)+"_Comp2", tmp);     

        tmp =  getRandomValue("armComp1"); 
        result->setValue("elbow"+toStdStr(m)+"_Comp1", tmp);     
        
        tmp =  getRandomValue("armComp2"); 
        result->setValue("elbow"+toStdStr(m)+"_Comp2", tmp);     
    }
   // std::cout<<"RESULTTYPE:" <<result->toString()<<std::endl;
    
    return result;
}
//---------------------------------------------------------------------
void LeggedCreatureGenotype::setRequiredMinMaxValues()
{
    //default Values
    if (! (this->hasMinMaxValue("bodyWidth"))) {setMinMaxValue("bodyWidth", 0.2, 5.0);}       
    if (! (this->hasMinMaxValue("bodyHeight"))) {setMinMaxValue("bodyHeight", 0.2, 2.0);}
    if (! (this->hasMinMaxValue("bodyLength"))) {setMinMaxValue("bodyLength", 0.2, 10.0);}
    if (! (this->hasMinMaxValue("armWidth"))) {setMinMaxValue("armWidth", 0.2, 0.75);}      
    if (! (this->hasMinMaxValue("armLength"))) {setMinMaxValue("armLength", 0.2, 2.0);}         
    if (! (this->hasMinMaxValue("constValue"))) {setMinMaxValue("constValue", -2.5, 2.5);}   
    if (! (this->hasMinMaxValue("armComp1"))) {setMinMaxValue("armComp1", -1.0, 1.0);} 
    if (! (this->hasMinMaxValue("armComp2"))) {setMinMaxValue("armComp2", -3.15, 3.15);}   
    if (! (this->hasMinMaxValue("legCount"))) {setMinMaxValue("legCount", 0, 8);}   
}

};
