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
#ifndef _SPHERESEGMENT_H_
#define _SPHERESEGMENT_H_

#include "BodySegment.h"


/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * A SphereSegment is a segment with sphere shape.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 *
 */
class SphereSegment : public BodySegment
{
public:

    /**
     * Constructor
     * 
     * @see BodySegment::BodySegment
     */
    SphereSegment(Roal::Body* owner, std::string name, std::string meshFile);
    
    /**
     * Destructor
     */
    virtual ~SphereSegment();
    
    /**
     * @see BodySegment::initSegment
     */ 
    virtual void initSegment(OgreOde::Space* space);
    
    /**
     * Sets the Radius
     * 
     * @param The new radius
     */
    void setRadius(float radius); 
     
    
    /**
     * Returns the Radius
     * 
     * @return The Radius
     */
    float getRadius();
    
    /**
     * Sets the Density
     * 
     * @param The new density
     */
     void setDensity(float density);
    
    /**
     * Returns the Density
     * 
     * @return The Density
     */
    float getDensity();
    
    /**
     * Sets the scale of the sphere.
     * 
     * @param x the x-scale
     * @param y the y-scale
     * @param z the z-scale
     */    
    virtual void setScale(float x, float y, float z);
    

private:
     
    /**
     * Holds the radius
     */
    float radius;

    /**
     * Holds the density
     */
    float density;
    
    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */ 
    SphereSegment();
};

}

#endif //_SPHERESEGMENT_H_
