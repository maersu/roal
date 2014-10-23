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

#include "Position.h"
using namespace std;

namespace Roal
{
//------------------------------------------------------------------------------
Position::Position()
{
}
//------------------------------------------------------------------------------
Position::~Position()
{
}

//-----------------------------------------------------------------------------
Position::Position(Position *pos)
{
    this->x = pos->getX();
    this->y = pos->getY();
    this->z = pos->getZ(); 
}

//------------------------------------------------------------------------------
Position::Position(const Vector3 &vec)
{
    this->x = (vec*Vector3(1,0,0)).normalise();
    this->y = (vec*Vector3(0,1,0)).normalise();
    this->z = (vec*Vector3(0,0,1)).normalise();
}


//------------------------------------------------------------------------------   
Position::Position(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

//------------------------------------------------------------------------------
void Position::setPosition(const Vector3 &vec)
{
    this->x = (vec*Vector3(1,0,0)).normalise();
    this->y = (vec*Vector3(0,1,0)).normalise();
    this->z = (vec*Vector3(0,0,1)).normalise();
}


//------------------------------------------------------------------------------   
void Position::setPosition(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

//------------------------------------------------------------------------------
float Position::getDistanceTo(Roal::Position *pos)
{     
   return this->getDistanceTo(pos->getX(),pos->getY(),pos->getZ());
}


//------------------------------------------------------------------------------
float Position::getDistanceTo(const Vector3 &vec)
{     
   return this->getDistanceTo((vec*Vector3(1,0,0)).normalise(),
            (vec*Vector3(0,1,0)).normalise(),(vec*Vector3(0,0,1)).normalise());
}

     
//------------------------------------------------------------------------------
float Position::getDistanceTo(float x, float y, float z)
{
    /**@TODO: Is this the correct way? ask papula...*/
    //absolute distance on plane, calcuated with Pythagoras
    float divPlane = this->getPlanarDistanceTo(x,z);

    //Distance on y ax
    float divY = this->getY() - y;
 
    //absolute distance, calcuated with Pythagoras
    float posDist = sqrt((divPlane * divPlane) + (divY * divY));
     
    //the distance has to be a absolute value. but the c-function abs use an 
    //integer as param. So we use a dirty way...
    if (posDist < 0.0) {
      posDist = posDist * -1;
    }
    return posDist;
}


//------------------------------------------------------------------------------
float Position::getPlanarDistanceTo(Roal::Position *pos)
{     
   return this->getPlanarDistanceTo(pos->getX(),pos->getZ());
}


//------------------------------------------------------------------------------
float Position::getPlanarDistanceTo(const Vector3 &vec)
{     
   return this->getPlanarDistanceTo((vec*Vector3(1,0,0)).normalise(),
                                    (vec*Vector3(0,0,1)).normalise());
}

     
//------------------------------------------------------------------------------
float Position::getPlanarDistanceTo(float x, float z)
{
    /**@TODO: Is this the correct way? ask papula...*/
    
    //Distance on x and z axis
    float divX = this->getX() - x;
    float divZ = this->getZ() - z; 
  
    //absolute distance on plane, calcuated with Pythagoras
    float posDist= sqrt((divX * divX) + (divZ * divZ));
     
    //the distance has to be a absolute value. but the c-function abs use an 
    //integer as param. So we use a dirty way...
    if (posDist < 0.0) {
      posDist = posDist * -1;
    }  
    return posDist;
}

//------------------------------------------------------------------------------      
Vector3 Position::getAsVector()
{
    return Vector3(this->getX(),this->getY(),this->getZ());
}


//------------------------------------------------------------------------------    
float Position::getX()
{
    return this->x;
}

//------------------------------------------------------------------------------    
void Position::setX(float x)
{
    this->x = x;
}


//------------------------------------------------------------------------------    
float Position::getY()
{
    return this->y;
}

//------------------------------------------------------------------------------    
void Position::setY(float y)
{
    this->y = y;
}

//------------------------------------------------------------------------------    
float Position::getZ()
{
    return this->z;
}

//------------------------------------------------------------------------------    
void Position::setZ(float z)
{
    this->z = z;
}

//------------------------------------------------------------------------------    
string Position::toString()
{
    return "x: "+toStdStr(x)+" y: "+toStdStr(y)+" z: "+toStdStr(z);
}
 
};
