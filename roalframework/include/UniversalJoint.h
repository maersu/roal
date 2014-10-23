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
#ifndef _UNIVERSALJOINT_H_
#define _UNIVERSALJOINT_H_

#include "Joint.h"
#include "BodySegment.h"
#include "Position.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The UniversalJoint is a joint with two axis.
 * 
 * A universal joint is like a ball and socket joint that constrains an extra
 * degree of rotational freedom. Given axis 1 on body 1, and axis 2 on body 2
 * that is perpendicular to axis 1, it keeps them perpendicular. In other words,
 * rotation of the two bodies about the direction perpendicular to the two axes
 * will be equal. 
 * 
 * @image html universaljoint.jpg
 * @image latex universaljoint.ps
 *    
 * @see <a href="http://ode.org/ode-latest-userguide.html#sec_7_3_4" target="_blank">ODE Userguide Section 7.3.4</a>
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class UniversalJoint: public Joint
{
public:
    /**
     * Constructor
     * 
     * @param anchor The joint anchor point, in world coordinates.
     */
	UniversalJoint(Position* anchor);
    
    /**
     * Destructor
     */
	virtual ~UniversalJoint();
    
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
     UniversalJoint();
          
     /**
      * The first axis.
      */
     Vector3 axis1;

     /**
      * The second axis.
      */      
     Vector3 axis2;
};

}

#endif //_UNIVERSALJOINT_H_
