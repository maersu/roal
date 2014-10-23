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
#include "EyeSegment.h"

namespace Roal
{
//------------------------------------------------------------------------------
EyeSegment::EyeSegment(Roal::Body* owner, std::string name, std::string meshFile)
:CubeSegment(owner,name,meshFile)
{
	this->setCameraLookAt(Vector3(1,1,1));
	this->setDimensions(0.2,0.2,0.2,0.2,1);
}

//------------------------------------------------------------------------------
EyeSegment::~EyeSegment()
{
}

//------------------------------------------------------------------------------
void EyeSegment::initSegment(OgreOde::Space* space)
{
    CubeSegment::initSegment(space);

    //do some Camera stuff
    ogreCam = this->getSceneNode()->getCreator()->createCamera(this->getName()+"_cam");     

   // ogreCam->setDetailLevel(SDL_WIREFRAME);	
    ogreCam ->setNearClipDistance(0.1);	

    this->setCameraLookAt(camLookAt);	

    if (rWin){
        
      // Create one viewport, entire window 
        vp =rWin->addViewport(ogreCam, this->ZOrder,this->left=left, this->top, this->width, this->height);
        
      // remove Overlay
      vp->setOverlaysEnabled(false);

      // get Color
      vp->setBackgroundColour(rWin->getViewport(0)->getBackgroundColour());   
    
      // Alter the camera aspect ratio to match the viewport
      ogreCam->setAspectRatio(
      float(vp->getActualWidth()) / float(vp->getActualHeight()));
	    
      this->getSceneNode()->attachObject(ogreCam);	
	   
	   
   } else {
         throw(RoalException(typeid( this ).name(),"No Ogre::RenderWindow set for "+this->getName()));
    }
}

//------------------------------------------------------------------------------
void EyeSegment::setDimensions(float left, float top, float width, float height, int ZOrder)
{
	this->left=left; this->top=top; this->width=width; this->height=height; this->ZOrder=ZOrder;
}

//------------------------------------------------------------------------------
void EyeSegment::setRenderWindow(RenderWindow* rw)
{
	this->rWin = rw;
}
//------------------------------------------------------------------------------
void EyeSegment::setCameraLookAt(const Vector3 &vec)
{  
    camLookAt = vec;	
    //If the simulation is runnable perform a realtime update
    if (this->getIsRunnable()) {
       ogreCam->lookAt(vec);
    }
}


//------------------------------------------------------------------------------
Vector3 EyeSegment::getDirection()
{
    if (this->getIsRunnable()) {
        return  ogreCam->getDirection();
    } else {
         throw(RoalException(typeid( this ).name(),"Eye not runnable for "+this->getName()));
    }
}
}
