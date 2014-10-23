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
#ifndef _MOTORJOINT_H_
#define _MOTORJOINT_H_
#include <OgreOde_Core/OgreOde_Core.h>
#include <OGRE/Ogre.h>
#include <OgreOde_Core/OgreOdeSpace.h>
#include "Joint.h"
#include "BodySegment.h"
#include "Position.h"
#include "File.h"

#include <OgreOde_Core/OgreOdeJoint.h>
#include <OgreOde_Core/OgreOdeGeometry.h>
#include <OgreOde_Core/OgreOdeSpace.h>
//#include <OgreOde_Core/OgreOdeVehicle.h>
#include <OgreOde_Core/OgreOdeUtility.h>

#include "OgreOdeVehicle.h"


/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The Motor is a Joint to simulate a motor. It accepts a velocity.
 * 
 * One of the attached bodies rotates around the Axis. This depends on the mass,
 * position etc. of the bodies 
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class MotorJoint: public Joint
{
public:
    /**
     * Constructor
     * 
     * @param anchor The joint anchor point, in world coordinates.
     */
    MotorJoint(Position* anchor);
    
    /**
     * Destructor
     */
    virtual ~MotorJoint();
    
    /**
     * Sets axis parameter. 
     * 
     * @param axis The axis.
     */
    void setAxis(const Vector3&  axis);
     
    /**
     * Inits the Joint to the OgreOde World
     * 
     * @exception RoalException
     */
    virtual void initJoint();
      
    /**
     * Sets the forces of the Motor.
     * 
     * @param motorVelocity this value defines the "speed" of the motor
     * @param maximumForce defines the maximum force the motor can reach.
     */     
    void setMotorVelocity(float motorVelocity, float maximumForce);
      
    /**
     * Registers a effector which controls the MotorVelocity
     * 
     * @param effector the effector which controls the velocity
     */
    void setMotorVelocityEffector(IEffector* effector);

    /**
     * @see Joint::updateFromEffectors
     */      
    virtual void updateFromEffectors();
      
private:
    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */  
    MotorJoint();
          
    /**
     * The Axis
     */
    Vector3 axis;

    /**
     * The registered Effector
     */
    IEffector* motorVelocityEffector;
};

}

#endif //_MOTORJOINT_H_
