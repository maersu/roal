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
#ifndef _BOX_H_
#define _BOX_H_

#include "CubeSegment.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * A Body, that represents a simple box in the world. 
 *
 * @image html box.png
 * @image latex box.ps
 */
class Box : public Body 
{
public: 

    /**
     * Constructor.
     * 
     * @param name The name of the Box. This has to be unique in the system!
     * @param pos The Position of the Box. 
     * @param meshFile The name of the mesh file.
     */    
    Box(const std::string name, Position* pos, string meshFile);
    
    /**
     * Sets the scale of the box.
     * 
     * @param x the x-scale
     * @param y the y-scale
     * @param z the z-scale
     */    
    virtual void setScale(float x, float y, float z);
    
    /**
     * Sets the physical mass of the BodySegment.
     * 
     * @param mass The physical mass of the BodySegment.
     */    
    void setMass(float mass); 
    
private:
        
    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */  
     Box();

    /**
     * Holds the CubeSegment of the Box
     */
    CubeSegment* cs;
	
};
} 
#endif //_BOX_H_
