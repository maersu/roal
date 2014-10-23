/**     
    This file is part of Roal, a framework for simulations in the field
    of Artificial Intelligence and Aritificial Life.
    See http://roal.sourceforge.net/ for more informations.

    Copyright (c) 2005 Project Roal

    Roal is free software; you can redistribute it anFixedJointd/or modify
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
#include "FixedJoint.h"
namespace Roal
{
//------------------------------------------------------------------------------
FixedJoint::FixedJoint(Roal::Position* anchor)
:Joint(anchor)
{ 
}


//------------------------------------------------------------------------------
FixedJoint::~FixedJoint()
{   
}
//------------------------------------------------------------------------------
void FixedJoint::setAxis(const Vector3 &axis)
{
    this->axis = axis;   
}

//------------------------------------------------------------------------------
void FixedJoint::initJoint()
{
    //do ogre ode stuff
    this->setOgreJoint(new OgreOde::FixedJoint());
    
    if(this->getIsRunnable()) {
	    
        this->getOgreJoint()->attach(this->getFirstSegment()->getOgreBody(),
                                    this->getSecondSegment()->getOgreBody());
	    
        this->getOgreJoint()->setAnchor(getAnchor()->getAsVector());
	    
	this->getOgreJoint()->setAxis(Ogre::Vector3::UNIT_Y);
        this->getOgreJoint()->setAdditionalAxis(Ogre::Vector3::NEGATIVE_UNIT_X);
        this->getOgreJoint()->setParameter(OgreOde::Joint::Parameter_FudgeFactor,OgreOde::Joint::Parameter_FudgeFactor);
	    	    
    } else {
        throw(RoalException(typeid( this ).name(),"Couldn't initJoint: because the Joint is not runnable"));
    }
}

};

