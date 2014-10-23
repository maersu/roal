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
#include "Joint.h"


namespace Roal
{
//-----------------------------------------------------------------------------
Joint::Joint(Roal::Position* anchor)
{
    this->anchor = new Position(anchor); 
    this->segment1 = 0;
    this->segment2 = 0;
    this->joint = 0;
    this->setIsRunnable(false);
    this->m_lowStop = -1;
    this->m_highStop = 1;
    
}


//-----------------------------------------------------------------------------
Joint::~Joint()
{
    if (joint){
        delete joint;
    }
}    
    
//-----------------------------------------------------------------------------  
Position* Joint::getAnchor()
{
    return this->anchor;
}


//----------------------------------------------------------------------------- 
void Joint::attach(Roal::BodySegment* seg1, Roal::BodySegment* seg2)
{
    this->segment1 = seg1;
    this->segment2 = seg2;
    //check if the joint is runnable
    this->setIsRunnable((this->segment1 !=0) and (this->segment2 !=0) and ( this->joint !=0));
		
}


//----------------------------------------------------------------------------- 
Roal::BodySegment*  Joint::getFirstSegment()
{
    return this->segment1;
}


//----------------------------------------------------------------------------- 
Roal::BodySegment*  Joint::getSecondSegment()
{
    return this->segment2;
}

//------------------------------------------------------------------------------
void Joint::setIsRunnable(bool b)
{
    this->isRunnable = b;
}

//------------------------------------------------------------------------------
void Joint::setLowHighStop(float lowStop, float highStop)
{
    if(this->getIsRunnable()) {
        this->getOgreJoint()->setParameter(OgreOde::Joint::Parameter_CFM,0.2);
        this->getOgreJoint()->setParameter(OgreOde::Joint::Parameter_StopERP,0.8);
        this->getOgreJoint()->setParameter(OgreOde::Joint::Parameter_StopCFM ,0.2);
        this->getOgreJoint()->setParameter(OgreOde::Joint::Parameter_SuspensionERP ,0.8);
        this->getOgreJoint()->setParameter(OgreOde::Joint::Parameter_SuspensionCFM  ,0.2);
        this->getOgreJoint()->setParameter(OgreOde::Joint::Parameter_FudgeFactor ,0.7);
        
     this->getOgreJoint()->setParameter(OgreOde::Joint::Parameter_LowStop,lowStop);
     this->getOgreJoint()->setParameter(OgreOde::Joint::Parameter_HighStop,highStop);

    }
    
    this->m_lowStop = lowStop;
    this->m_highStop = highStop;
}

//------------------------------------------------------------------------------
bool Joint::getIsRunnable()
{
    return this->isRunnable;
}

//------------------------------------------------------------------------------
void Joint::setOgreJoint(OgreOde::Joint* j)
{
    if(j != 0) {
        this->joint = j;
    } else {
        throw(RoalException(typeid( this ).name(),"Couldn't set joint: because the given joint is 0"));
    } 
    //check if the joint is runnable   
    this->setIsRunnable((this->segment1 !=0) and (this->segment2 !=0) and ( this->joint !=0));
} 

      
//------------------------------------------------------------------------------
OgreOde::Joint* Joint::getOgreJoint()
{
    return this->joint;   
}

//------------------------------------------------------------------------------
const Vector3& Joint::getFirstForce()    
{
    if(this->getIsRunnable()) {
        return this->joint->getFirstForce();
    } else {
        throw(RoalException(typeid( this ).name(),"Couldn't get first force: because the Joint is not runnable"));
    }    
}
  
      
//------------------------------------------------------------------------------
const Vector3& Joint::getFirstTorque()    
{
    if(this->getIsRunnable()) {
        return this->joint->getFirstTorque();
    } else {
        throw(RoalException(typeid( this ).name(),"Couldn't get first torque: because the Joint is not runnable"));
    }
}

//------------------------------------------------------------------------------
const Vector3& Joint::getSecondForce()    
{
    if(this->getIsRunnable()) {
        return this->joint->getSecondForce();
    } else {
        throw(RoalException(typeid( this ).name(),"Couldn't get second force: because the Joint is not runnable"));
    }
}
 
      
//------------------------------------------------------------------------------
const Vector3& Joint::getSecondTorque()    
{
    if(this->getIsRunnable()) {
        return this->joint->getSecondTorque();
    } else {
        throw(RoalException(typeid( this ).name(),"Couldn't get second torque: because the Joint is not runnable"));
    }
} 


//------------------------------------------------------------------------------
float Joint::getAngle()
{    
    /**@bug this does not work for the UniversalJoint. The return value
     * is always 0 
     */ 
    if(this->getIsRunnable()) {
        return this->joint->getAngle();
    } else {
        throw(RoalException(typeid( this ).name(),"Couldn't get angle: because the Joint is not runnable"));
    }
}


//------------------------------------------------------------------------------
void Joint::addTorque(float torqueX, float torqueY, float torqueZ)
{

    if(this->getIsRunnable()) {
       this->joint->addTorque(torqueX,torqueY,torqueZ); 
	    } else {
        throw(RoalException(typeid( this ).name(),"Couldn't set torque: because the Joint is not runnable"));
    }
}

//------------------------------------------------------------------------------
void Joint::setTorqueEffector(IEffector* effector)
{
   this->torqueEffector = effector;
}

//------------------------------------------------------------------------------
void Joint::setAngleSensor(ISensor* sensor)
{
   this->angleSensor = sensor;
}

//------------------------------------------------------------------------------
void Joint::updateFromEffectors()
{
   if (torqueEffector) {
       this->addTorque(torqueEffector->getValue());
   }
}

//------------------------------------------------------------------------------
void Joint::updateSensors()
{	
   if (angleSensor) {
      angleSensor->addValue(this->getAngle());
   }
}

};

