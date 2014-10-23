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
#ifndef _BALLJOINT_H_
#define _BALLJOINT_H_

#include <OgreOde_Core/OgreOde_Core.h>
#include <OGRE/Ogre.h>
#include <OgreOde_Core/OgreOdeSpace.h>
#include "Joint.h"
#include "BodySegment.h"
#include "Position.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The BallJoint is a joint that can move freely in all directions.
 * 
 * \image html balljoint.jpg
 * \image latex balljoint.ps
 * 
 * @see <a href="http://ode.org/ode-latest-userguide.html#sec_7_3_1" target="_blank">ODE Userguide Section 7.3.1</a>
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class BallJoint: public Joint
{
public:
    /**
     * Constructor
     * 
     * @param anchor The joint anchor point, in world coordinates.
     */
    BallJoint(Position* anchor);
    
    /**
     * Destructor
     */
    virtual ~BallJoint();
    
    /**
     * Sets axis parameters. 
     * 
     * Axis 1 and axis 2 should be perpendicular to each other.
     * 
     * @param axis1 The first axis.
     * @param axis2 The second axis.
     */
    void setAxis(const Vector3&  axis1, const Vector3& axis2);
     
     /**
      * Inits the Joint to the OgreOde World
      * 
      * @exception RoalException
      */
     virtual void initJoint();
      
private:
    /**
     * Default Constructor. 
     * 
     * Do Not Use!
     */  
     BallJoint();
          
     /**
      * The first axis.
      */
     Vector3  axis1;

     /**
      * The second axis.
      */      
     Vector3 axis2;
};

}

#endif //_BALLJOINT_H_
