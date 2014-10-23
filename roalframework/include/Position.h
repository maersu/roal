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
#ifndef _POSITION_H_
#define _POSITION_H_

#include <OgreOde_Core/OgreOde_Core.h>
#include <math.h>
#include "Util.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * Stores a position in 3D space.
 * 
 * The Position class is used to store positions in 3D space, but also provides
 * methods to calculate the distance to another Position.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class Position
{
public:
    /**
     * Constructor with additional parameters.
     * 
     * Creates a position from a given position-vector.
     * 
     * @param vec Init the new Position with the coordinates from a vector.
     */
    Position(const Vector3 &vec);
    
    /**
     * Constructor with additional parameters.
     * 
     * Creates a position from a given Position
     * 
     * @param pos Init the new Position with an existing one.
     */
    Position(Position *pos);
    
    /**
     * Constructor with additional parameters.
     * 
     * Creates a position from the given Coordinates.
     * 
     * @param x the x-coordinate
     * @param y the y-coordinate
     * @param z the z-coordinate
     */
    Position(float x, float y, float z);
    
    /**
     * Destructor
     */      
    virtual ~Position();
    
    /**
     * Returns a position-vector of the current Position.
     * 
     * @return a position-vector.
     */
    Vector3 getAsVector();
    
    /**
     * Returns the x-coordinate.
     * 
     * @return the x-coordinate.
     */
    float getX();
    
    /**
     * Set a new x-coordinate
     *
     * @param x the x-coordinate
     */
    void setX(float x);
    
    /**
     * Returns the y-coordinate.
     * 
     * @return the y-coordinate.
     */
    float getY();

    /**
     * Set a new y-coordinate
     *
     * @param y the y-coordinate
     */
    void setY(float y);
    
    /**
     * Returns the z-coordinate.
     * 
     * @return the z-coordinate.
     */
    float getZ();
    
    /**
     * Set a new z-coordinate
     *
     * @param z the z-coordinate
     */
    void setZ(float z);  
    
    /**
     * Override the Position with the coordinates of a vector.
     * 
     * @param vec A position-vector containing three coordinates.
     */
    void setPosition(const Vector3 &vec);
     
    /**
     * Override the Position with new coordinates.
     * 
     * @param x the x-coordinate
     * @param y the y-coordinate
     * @param z the z-coordinate
     */
    void setPosition(float x, float y, float z);
    
    /**
     * Calculates the distance to a given Position.
     * 
     * @param pos A Position to calculate the distance to.
     * @return the distance to a given Position.
     * 
     * @bug somtimes this mwthod leads in strange effects.
     */
    float getDistanceTo(Position *pos);
     
    /**
     * Calculates the distance to a given position.
     * 
     * @param pos A position-vector to calculate the distance to.
     * @return the distance to a given position.
     *
     * @bug somtimes this mwthod leads in strange effects.
     */
    float getDistanceTo(const Vector3 &vec);
    
    /**
     * Calculates the distance to a given position.
     * 
     * @param x the x-coordinate
     * @param y the y-coordinate
     * @param z the z-coordinate
     * @return the distance to a given position.
     *
     * @bug somtimes this mwthod leads in strange effects.
     */
    float getDistanceTo(float x, float y, float z);
    
    /**
     * Calculates the planar distance to a given Position.
     * Only the x and z axis are used
     *
     * @param pos A Position to calculate the distance to.
     * @return the distance to a given Position.
     */
    float getPlanarDistanceTo(Position *pos);
     
    /**
     * Calculates the planar distance to a given position.
     * Only the x and z axis are used
     * 
     * @param pos A position-vector to calculate the distance to.
     * @return the distance to a given position.
     */
    float getPlanarDistanceTo(const Vector3 &vec);
    
    /**
     * Calculates the planar distance to a given position.
     * Only the x and z axis are used
     * 
     * @param x the x-coordinate
     * @param z the z-coordinate
     * @return the distance to a given position.
     */
    float getPlanarDistanceTo(float x, float z);
    
    /**
     * returns a string that represents the curren position (x,y,z)
     */
    string toString();
    
private:
    /**
     * The coordinates of the position.
     */
    float x, y, z;
    
    /**
     * Default Constructor.
     * 
     * Should not be uesed!
     */
    Position();  
    
    
};

}

#endif //_POSITION_H_
