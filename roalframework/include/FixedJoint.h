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
#ifndef _FIXEDJOINT_H_
#define _FIXEDJOINT_H_

#include "Joint.h"
#include "BodySegment.h"
#include "Position.h"


/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The FixedJoint is a joint with fixed angles and Positions. Use this Joint
 * to static connect between two bodies.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class FixedJoint: public Joint
{
public:
    /**
     * Constructor
     * 
     * @param anchor The joint anchor point, in world coordinates.
     */
    FixedJoint(Position* anchor);
    
    /**
     * Destructor
     */
    virtual ~FixedJoint();
    
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
           
private:
          
     /**
      * The Axis
      */
     Vector3 axis;
};

}

#endif //_FIXEDJOINT_H_
