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

#include "IEffector.h"


/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

//------------------------------------------------------------------------------
IEffector::IEffector()
{
}
//------------------------------------------------------------------------------    
IEffector::~IEffector()
{
}
//------------------------------------------------------------------------------
void IEffector::addValue(float value)
{
	this->value += value;
}	

//------------------------------------------------------------------------------
void IEffector::setValue(float value)
{
	this->value = value;
}

//------------------------------------------------------------------------------
float IEffector::getValue()	
{
	return this->value;
}

//------------------------------------------------------------------------------
void IEffector::listenerItereate()
{
    //at the moment not suported
}
};
