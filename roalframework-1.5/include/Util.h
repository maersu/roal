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
#ifndef _UTIL_H_
#define _UTIL_H_

#include <sstream>
#include <string>
#include "RoalException.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
/** 
 * converts a int to std::string
 * 
 * @param the int
 * @return the string
 */
inline std::string toStdStr(int i) {
    std::ostringstream oss;
    oss << i;
    return oss.str();
};

/** 
 * convert a float to std::string
 * 
 * @param the float
 * @return the string
 */
inline std::string toStdStr(float f) {
    std::ostringstream oss;
    oss << f;
    return oss.str();
};

/** 
 * convert a long to std::string
 * 
 * @param the long
 * @return the string
 */
inline std::string toStdStr(long f) {
    std::ostringstream oss;
    oss << f;
    return oss.str();
};

/** 
 * interprets a given value to a color value, there exits 10 colors.
 * 
 * @todo a picture with the color sheme
 * 
 * @param currentValue the value which should represented by the color.
 * @param min the minima this value is represented by dark red.
 * @param max the maxima this value is represented by dark green.
 * @return the string
 */
inline string getHexColor(float currentValue, float min, float max)
{
    string color = "";
    
    if (min <= currentValue && currentValue <= max) {
        
        float diff = max - min;
        float step = diff/10.0;
        
        if (currentValue < (min+step))                              
            {color = "\"#a50021\"";} //65 0 13
        else if ((currentValue >= (min+step)) && (currentValue < (min+2*step)))   
            {color = "\"#d63121\"";} //84 19 13
        else if ((currentValue >= (min+2*step)) && (currentValue < (min+3*step)))   
            {color = "\"#f86d42\"";} //97 43 26
        else if ((currentValue >= (min+3*step)) && (currentValue < (min+4*step)))   
            {color = "\"#ffad63\"";} //100 68 39
        else if ((currentValue >= (min+4*step)) && (currentValue < (min+5*step)))   
            {color = "\"#ffe28c\"";} //100 89 55 
        else if ((currentValue >= (min+5*step)) && (currentValue < (min+6*step)))   
            {color = "\"#ddef8c\"";} //87 94 55 
        else if ((currentValue >= (min+6*step)) && (currentValue < (min+7*step)))   
            {color = "\"#a5db6b\"";} //65 86 42
        else if ((currentValue >= (min+7*step)) && (currentValue < (min+8*step)))   
            {color = "\"#63bf63\"";} //39 75 39
        else if ((currentValue >= (min+8*step)) && (currentValue < (min+9*step)))   
            {color = "\"#169952\"";} //9 60 32
        else if ((currentValue >= (min+9*step)))                      
            {color = "\"#006931\"";} //0 41 19 
        else 
            {color = "\"#ffffff\"";}
    
    return color; 
    } else {
        throw(RoalException("Could not Create HexColor String: wrong values")); 
    }
};
}

#endif //_UTIL_H_
