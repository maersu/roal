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

#include "Plant.h"

namespace Roal
{

//------------------------------------------------------------------------------
Plant::Plant(const std::string name, Position* pos, string meshFile)
:Body(name, pos)
{	
	cs = new CubeSegment(this,name+"_cs", meshFile);
    this->registerSegment(cs);
	cs->setScale(2, 2, 2);
	cs->setPosition(pos->getX(),pos->getY(), pos->getZ());
    this->setPositionSegment(cs);
    
    birth = time(NULL);
}

//------------------------------------------------------------------------------
void Plant::setScale(float x, float y, float z)
{
    cs->setScale(x, y, z);

}
    
//------------------------------------------------------------------------------
void Plant::setMass(float mass)
{
    cs->setMass(mass);
}

//------------------------------------------------------------------------------
double Plant::getAge()
{
    return difftime(time(NULL),birth);
}

}
