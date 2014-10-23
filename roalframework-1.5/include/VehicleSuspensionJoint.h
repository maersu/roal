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
#ifndef _VEHICLESUSPENSIONJIONT_H_
#define _VEHICLESUSPENSIONJIONT_H_

#include "Joint.h"
#include "BodySegment.h"
#include "Position.h"
#include "File.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The VehicleSuspensionJoint can be used to simulate the suspension of a Vehicle.
 *
 * @warning This Joint is for experimental usage
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class VehicleSuspensionJoint: public Joint
{
public:
    /**
     * Constructor
     * 
     * @param anchor The joint anchor point, in world coordinates.
     */
    VehicleSuspensionJoint(Position* anchor);
    
    /**
     * Destructor
     */
    virtual ~VehicleSuspensionJoint();
    
    /**
     * Sets axis parameter. 
     * 
     * @param axis The axis.
     */
    void setAxis(const Vector3&  axis);
     
    /**
     * @see Joint::initJoint().
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
     VehicleSuspensionJoint();
          
    /**
     * The Axis
     */
    Vector3 axis;
};

}

#endif //_VEHICLESUSPENSIONJIONT_H_
