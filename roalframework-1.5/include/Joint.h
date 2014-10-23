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
#ifndef _JOINT_H_
#define _JOINT_H_


#include <OgreOde_Core/OgreOde_Core.h>
#include <OGRE/Ogre.h>
#include <OgreOde_Core/OgreOdeSpace.h>
#include <stdio.h>
#include <iostream>
#include "File.h"
#include "BodySegment.h"
#include "Position.h"
#include "RoalException.h"
#include "IEffector.h"
#include "ISensor.h"
#include "Util.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
class Body; // Forward declaration for Body
class BodySegment;

/**
 * Joint objects connect two BodySegment objects in different ways.
 *
 * @image html joint.png
 * @image latex joint.ps
 *
 * There are different types of Joint objects that each have its own properties
 * and features. Note that that a Joint has no visible forms.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class Joint
{
public:
    /**
     * Constructor.
     * 
     * @param anchor the joint anchor point, in world coordinates
     */
	Joint(Position* anchor);
    
    /**
     * Destructor.
     */
	virtual ~Joint();
    
    /**
     * init the joint.
     */
    virtual void initJoint()=0;

        
    /**
     * Returns the Anchor of the Joint.
     * 
     * @return the joint anchor point, in world coordinates.
     */    
    virtual Position* getAnchor();
    
    /**
     * Attaches the segments to the joint.
     *
     * @param seg1 The first BodySegment which is attached to the joint.
     * @param seg2 The first BodySegment which is attached to the joint.
     */
    void attach(BodySegment* seg1, BodySegment* seg2);

    /**
     * Returns the runnable state of the Joint.
     * 
     * @return the runnable state
     */
    bool getIsRunnable(); 

    /**
     * Return the first segment wich is attached to the joint.
     * 
     * @return the first segment. 
     */
    BodySegment* getFirstSegment();
    
    
    /**
     * return the second segment wich is attached to the joint.
     * 
     * @return the second segment. 
     */
    BodySegment*  getSecondSegment();

    /**
     * Returns the current accumulated force vector of the first segment.
     * 
     * @return the current accumulated torque vector.
     * @exception RoalException
     */
     virtual const Vector3& getFirstForce();
      
    /**
     * Returns the current accumulated force vector of the first segment. 
     * 
     * @return the current accumulated torque vector.
     * @exception RoalException
     */
     virtual const Vector3& getFirstTorque();

    /**
     * Returns the current accumulated force vector of the first segment. 
     * 
     * @return the current accumulated torque vector.
     * @exception RoalException
     */
     virtual const Vector3& getSecondForce();
      
    /**
     * Returns the current accumulated force vector of the first segment. 
     * 
     * @return the current accumulated torque vector.
     * @exception RoalException
     */
     virtual const Vector3& getSecondTorque();  
     
    /**
     * Returns the angle measured between the two bodies.
     * 
     * The angle is measured between the two bodies.
     * Note that a joint angle of zero corresponds to the initial 
     * body positions.
     * The angle will be between -pi..pi
     * 
     * @return the angle
     * @exception RoalException
     */ 
     virtual float getAngle(); 

    /**
     * Add torque to the Joints.
     * 
     * The torque are accumulated on to each body, and the accumulators are 
     * zeroed after each time step.
     * 
     * @exception RoalException
     */     
    virtual void addTorque(float torqueX, float torqueY=0.0, float torqueZ=0.0);

    /**
     * Sets the OgreOde::Joint.
     * 
     * @param j the OgreOde::Joint.
     * @exception RoalException
     */
    virtual void setOgreJoint(OgreOde::Joint* j); 
      
    /**
     * Returns the OgreOde::joint.
     * 
     * @return the OgreOde::joint.
     */
    OgreOde::Joint* getOgreJoint(); 

    /**
     * Sets the torque effector.
     *
     * @param the torque Effector.
     */     
    void setTorqueEffector(IEffector* effector);
  
    /**
     * Sets the torque effector.
     *
     * @param the angle sensor.
     */     
    void setAngleSensor(ISensor* sensor);
  
    /**
     * updates from the registered effectors.
     */
    virtual void updateFromEffectors();
   
    /**
     * updates the registered sensors.
     */
    virtual void updateSensors();

    /**
     * Both values are used as boundaries for the Joint. Use this method to 
     * prevent your creature from unnatural movments. 
     *
     * @param lowStop should be more than -pi.
     * @param highStop should be less than -pi.
     */
    void setLowHighStop(float lowStop, float highStop);

 protected:
     
    /**
     * the low stop
     */
    float m_lowStop;

    /**
     * the high stop
     */
    float m_highStop;
 
 private:    
 
    /**
     * the torque effector
     */
     IEffector* torqueEffector;
    
    /**
     * the angle sensor
     */ 
     ISensor*  angleSensor;
 
    /**
     * Holds the acnhor position
     */
    Position* anchor;
    
    /**
     * Holds the Joint
     */
    OgreOde::Joint* joint;
    
    /**
     * one body segments which are attached to this Joint
     */
    BodySegment* segment1; 
    
    /**
     * one body segments which are attached to this Joint
     */
    BodySegment* segment2;
    
    /**
     * Holds the runable state
     */
     bool isRunnable;
     
    /**
     * Defines if the Joint is runable or not
     * 
     * @param b new runnable state
     */
    void setIsRunnable(bool b);

 private:
    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */  
     Joint() {};
    
};
}

#endif //_JOINT_H_
