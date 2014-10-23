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
#ifndef _CAGE_H_
#define _CAGE_H_

#include "CubeSegment.h"
#include "FixedJoint.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * This Cage represents a qaudratic wall struct.
 *
 * @image html cage.png
 * @image latex cage.ps
 *
 * Use the cage e.g to prevent creatures 
 * leaving an area.
 *
 * @warning the cage stands on four foots. This foots are necessary to avoid a
 * collision overflow (with large Object the OgreOde world seems too have troubles).
 * This leads to a small space between the ground and the walls. 
 */
class Cage : public Body 
{

public: 

    /**
     * Constructor.
     * 
     * @param name The name of the Cage. This has to be unique in the system!
     * @param pos The Position of the Cage. 
     * @param wallLength The length of the four walls.
     * @param wallHight The hight of the four walls.
     */    
    Cage(const std::string name, Position* pos, string meshFile, float wallLength, 
            float wallHight, float wallWidth);
    
private:

    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */  
    Cage();

    //all the segments and joints used to construct the cage
    CubeSegment* cs1;
    CubeSegment* cs2;
    CubeSegment* cs3;
    CubeSegment* cs4;

    CubeSegment* foot1;
    CubeSegment* foot2;
    CubeSegment* foot3;
    CubeSegment* foot4;

    FixedJoint* fixFoot11;
    FixedJoint* fixFoot22;
    FixedJoint* fixFoot33;
    FixedJoint* fixFoot44;
    FixedJoint* fixFoot12;
    FixedJoint* fixFoot23;
    FixedJoint* fixFoot34;
    FixedJoint* fixFoot41;

};
} 
#endif //_CAGE_H_
