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
#include "UniversalJoint.h"
namespace Roal
{
//------------------------------------------------------------------------------
UniversalJoint::UniversalJoint(Roal::Position* anchor)
:Joint(anchor)
{ 
}


//------------------------------------------------------------------------------
UniversalJoint::~UniversalJoint()
{   
}

//------------------------------------------------------------------------------
void UniversalJoint::setAxis(const Vector3 &axis1, const Vector3 &axis2)
{
    this->axis1 = axis1;
    this->axis2 = axis2;   
}

//------------------------------------------------------------------------------
void UniversalJoint::initJoint()
{
    
    this->setOgreJoint(new OgreOde::UniversalJoint());
    
    if(this->getIsRunnable()) {
        this->getOgreJoint()->attach(this->getFirstSegment()->getOgreBody(),
                                    this->getSecondSegment()->getOgreBody());
        this->getOgreJoint()->setAnchor(getAnchor()->getAsVector());
        this->getOgreJoint()->setAxis(this->axis1);
        this->getOgreJoint()->setAdditionalAxis(this->axis2);
    } else {
        throw(RoalException(typeid( this ).name(),"Couldn't initJoint: because the Joint is not runnable"));
    }
}

};
