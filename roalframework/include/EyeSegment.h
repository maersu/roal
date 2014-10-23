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
#ifndef _EYESEGMENT_H_
#define _EYESEGMENT_H_

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreLight.h>
#include <OGRE/OgreViewport.h>
#include <OgreOde_Core/OgreOde_Core.h>
#include "CubeSegment.h"
#include "ImageRenderTarget.h"
#include "World.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * A EyeSegment has the shape of a simple cube. It holds a camera that simulates
 * the eye. The output is placed on a Ogre::RenderableTarget.
 *
 * @warning This Segment is for experimental usage. At the moment the EyeSegment 
 * is not usfull. Use at your own fun/risk.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class EyeSegment : public CubeSegment
{
public:
    /**
     * Constructor
     * 
     * @see EyeSegment::EyeSegment
     */
    EyeSegment(Roal::Body* owner, std::string name, std::string meshFile);
    
    /**
     * Destructor
     */
	virtual ~EyeSegment();
    
    /**
     * @see EyeSegment::initSegment
     */ 
    virtual void initSegment(OgreOde::Space* space);


    /**
     * 
     * @return the point the camera looks at (orientation).
     */ 
    Vector3 getDirection();
    
    /**
     * Sets the look at of the camera.
     * 
     * @param vec A point (as vector) to look at (orientation).
     */ 
    void setCameraLookAt(const Vector3 &vec);
    
    /**
     * sets the window which holds the view of the eye
     */   
    void setRenderWindow(RenderWindow* rw);
    
    /**
     * sets the dimensions on the given render window
     */ 
    void setDimensions(float left, float top, float width, float height, int ZOrder);

private:

    /**
     * The Ogre Cam
     */
    Ogre::Camera* ogreCam;

    /**
     * The Ogre Viewport
     */
    Ogre::Viewport* vp;

    /**
     * The Ogre RenderWindow
     */
    RenderWindow* rWin;

    /**
     * The Ogre Cam Look at
     */
    Vector3 camLookAt;

    /**
     * The position and scale of the viewport in a Ogre::RenderableTarget 
     */
    float left; float top; float width; float height; int ZOrder;

    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */ 
    EyeSegment();

};

}

#endif //_EYESEGMENT_H_
