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

#include "LeggedCreaturePhenotype.h"

namespace Roal
{

//-----------------------------------------------------------------------------
LeggedCreaturePhenotype::LeggedCreaturePhenotype(LeggedCreatureGenotype* creator)
    :Phenotype(creator)
{

}


//------------------------------------------------------------------------------
LeggedCreaturePhenotype::~LeggedCreaturePhenotype()
{
    
}

//-----------------------------------------------------------------------------
vector<float> LeggedCreaturePhenotype::toNormalizeVector()
{
    vector<float> normValues;

    normValues.push_back(getNormalizedValue(this->getValue("bodyWidth"), 
            creator->getMinValue("bodyWidth"), creator->getMaxValue("bodyWidth")));
    
    normValues.push_back(getNormalizedValue(this->getValue("bodyHeight"), 
            creator->getMinValue("bodyHeight"), creator->getMaxValue("bodyHeight")));
    
    normValues.push_back(getNormalizedValue(this->getValue("bodyLength"), 
            creator->getMinValue("bodyLength"), creator->getMaxValue("bodyLength")));
    
    normValues.push_back(getNormalizedValue(this->getValue("armHeight"), 
            0, creator->getMaxValue("bodyHeight")));
    
    normValues.push_back(getNormalizedValue(this->getValue("legCount"), 
            creator->getMinValue("legCount"), creator->getMaxValue("legCount")));
    
    normValues.push_back(getNormalizedValue(this->getValue("armWidth"), 
            creator->getMinValue("armWidth"), creator->getMaxValue("armWidth"))); 
    
    normValues.push_back(getNormalizedValue(this->getValue("armLength"), 
            creator->getMinValue("armLength"), creator->getMaxValue("armLength")));
            
    normValues.push_back(getNormalizedValue(this->getValue("constValue"), 
            creator->getMinValue("constValue"), creator->getMaxValue("constValue")));
            
    //normValues.push_back(getNormalizedValue(this->getValue("force"), 
    //        creator->getMinValue("force"), creator->getMaxValue("force"));
    
    for (int m = 1; m<= getValue("legCount"); m++)
    {

        normValues.push_back(getNormalizedValue(this->getValue("axle"+toStdStr(m)+"_Comp1"), 
            creator->getMinValue("armComp1"), 
            creator->getMaxValue("armComp1")));     
        
        normValues.push_back(getNormalizedValue(this->getValue("axle"+toStdStr(m)+"_Comp2"), 
            creator->getMinValue("armComp2"), 
            creator->getMaxValue("armComp2")));     
        
        normValues.push_back(getNormalizedValue(this->getValue("elbow"+toStdStr(m)+"_Comp1"), 
            creator->getMinValue("armComp1"), 
            creator->getMaxValue("armComp1")));    
        
        normValues.push_back(getNormalizedValue(this->getValue("elbow"+toStdStr(m)+"_Comp2"),
            creator->getMinValue("armComp2"), 
            creator->getMaxValue("armComp2")));         
    }   
    return normValues;
}

//------------------------------------------------------------------------------
string LeggedCreaturePhenotype::toNormalizeValueString(string separator)
{
    string result;

    vector<float> normValues = toNormalizeVector();   
    
    for (int i = 0; i<normValues.size() ;i++){
        if (i > 0) {result = result + separator;}
          result = result + toStdStr(normValues.at(i));
    }
    
    return result;
}

}
