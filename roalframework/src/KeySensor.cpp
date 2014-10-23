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

#include "KeySensor.h"


/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

//------------------------------------------------------------------------------
KeySensor::KeySensor(Roal::World* world):IStandaloneSensor()
{
    this->world = world;
    this->toListenKey = "";
    this->setValue(0);
}
//------------------------------------------------------------------------------    
KeySensor::~KeySensor()
{
}

//------------------------------------------------------------------------------    
void KeySensor::setToListenKey(string toListenKey)
{
    this->toListenKey= toListenKey; 
}

//------------------------------------------------------------------------------ 
void KeySensor::update()
{
    Ogre::KeyCode key;

    if (toListenKey == "1") {key = KC_1;}
    else if (toListenKey == "2") {key = KC_2;}
    else if (toListenKey == "3") {key = KC_3;}
    else if (toListenKey == "4") {key = KC_4;}
    else if (toListenKey == "5") {key = KC_5;}
    else if (toListenKey == "6") {key = KC_6;}
    else if (toListenKey == "7") {key = KC_7;}
    else if (toListenKey == "8") {key = KC_8;}
    else if (toListenKey == "9") {key = KC_9;}
    else if (toListenKey == "0") {key = KC_0;}
    else if (toListenKey == "-") {key = KC_MINUS;} //- on main keyboard
    else if (toListenKey == "=") {key = KC_EQUALS;}
    else if (toListenKey == "q") {key = KC_Q;}
    else if (toListenKey == "w") {key = KC_W;}
    else if (toListenKey == "e") {key = KC_E;}
    else if (toListenKey == "r") {key = KC_R;}
    else if (toListenKey == "t") {key = KC_T;}
    else if (toListenKey == "y") {key = KC_Y;}
    else if (toListenKey == "u") {key = KC_U;}
    else if (toListenKey == "i") {key = KC_I;}
    else if (toListenKey == "o") {key = KC_O;}
    else if (toListenKey == "p") {key = KC_P;}
    else if (toListenKey == "[") {key = KC_LBRACKET;}
    else if (toListenKey == "]") {key = KC_RBRACKET;}
    else if (toListenKey == "a") {key = KC_A;}
    else if (toListenKey == "s") {key = KC_S;}
    else if (toListenKey == "d") {key = KC_D;}
    else if (toListenKey == "f") {key = KC_F;}
    else if (toListenKey == "g") {key = KC_G;}
    else if (toListenKey == "h") {key = KC_H;}
    else if (toListenKey == "j") {key = KC_J;}
    else if (toListenKey == "k") {key = KC_K;}
    else if (toListenKey == "l") {key = KC_L;}
    else if (toListenKey == ";") {key = KC_SEMICOLON;}
    else if (toListenKey == "\'") {key = KC_APOSTROPHE;}
    else if (toListenKey == "`") {key = KC_GRAVE;}
    else if (toListenKey == "\\") {key = KC_GRAVE;}
    else if (toListenKey == "z") {key = KC_Z;}
    else if (toListenKey == "x") {key = KC_X;}
    else if (toListenKey == "c") {key = KC_C;}
    else if (toListenKey == "v") {key = KC_V;}
    else if (toListenKey == "b") {key = KC_B;}
    else if (toListenKey == "n") {key = KC_N;}
    else if (toListenKey == "m") {key = KC_M;}
    else if (toListenKey == ",") {key = KC_COMMA;}
    else if (toListenKey == ".") {key = KC_PERIOD;} //. on main keyboard 

    else if (toListenKey == "*") {key = KC_MULTIPLY;}
    else if (toListenKey == " ") {key = KC_SPACE;}
    else if (toListenKey == "N7") {key = KC_NUMPAD7;}
    else if (toListenKey == "N8") {key = KC_NUMPAD8;}
    else if (toListenKey == "N9") {key = KC_NUMPAD9;}
    else if (toListenKey == "N-") {key = KC_SUBTRACT;}
    else if (toListenKey == "N4") {key = KC_NUMPAD4;}
    else if (toListenKey == "N5") {key = KC_NUMPAD5;}
    else if (toListenKey == "N6") {key = KC_NUMPAD6;}
   
    else if (toListenKey == "N+") {key = KC_ADD;}
    else if (toListenKey == "N1") {key = KC_NUMPAD1;}
    else if (toListenKey == "N2") {key = KC_NUMPAD2;}
    else if (toListenKey == "N3") {key = KC_NUMPAD3;}
    else if (toListenKey == "N0") {key = KC_NUMPAD0;}
    else if (toListenKey == "N.") {key = KC_DECIMAL;}
    else if (toListenKey == "N=") {key = KC_NUMPADEQUALS;}
    else if (toListenKey == "N,") {key = KC_NUMPADCOMMA;}
    else if (toListenKey == "N/") {key = KC_DIVIDE;}
    else {key = KC_AT;} // default sign: '@' ....
    
    
    InputReader* mInputDevice = world->getFrameListener()->getInputReader();
    
    if (mInputDevice->isKeyDown(key))
    {
        this->setValue(1); 
    } else {
        this->setValue(0); 
    }
    

}

};
