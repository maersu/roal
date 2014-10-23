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
#include "WorldFrameListener.h"

namespace Roal
{

//------------------------------------------------------------------------------
WorldFrameListener::WorldFrameListener(RenderWindow* win, Camera* cam,
    float time_step, Root* root, Roal::World* world): ExampleFrameListener(win, cam)
{
    // Reduce move speed
    mMoveSpeed = 25;
    
    //Set the World
    this->world = world;
    
    // Create something that will step the world automatically
    _stepper = new OgreOde::ForwardFixedQuickStepper(time_step);
    //_stepper = new OgreOde::ExactVariableQuickStepper(time_step);
    _stepper->setAutomatic(OgreOde::Stepper::AutoMode_PostFrame, root);
   
    
    _ray_query = mCamera->getSceneManager()->createRayQuery(Ray());
	
    mNumScreenShots=0;

    this->win=win;
}


//------------------------------------------------------------------------------
WorldFrameListener::~WorldFrameListener()
{
}


//------------------------------------------------------------------------------
bool WorldFrameListener::frameStarted(const FrameEvent& evt)
{      
    float time = evt.timeSinceLastFrame;
   // mDebugOverlay->hide();
    bool ret = ExampleFrameListener::frameStarted(evt);

    if(mInputDevice->isKeyDown(KC_U)) _stepper->pause(false);
    if(mInputDevice->isKeyDown(KC_P)) _stepper->pause(true);
    
    if(!_stepper->isPaused())
    {
      world->frameStarted(evt);
    } 
    
    if (mInputDevice->isKeyDown(KC_C))
     {
	char tmp[20];
	sprintf(tmp, "screenshot_%d.png", ++mNumScreenShots);
        mWindow->writeContentsToFile(tmp);
     }
    
    return ret;

    
}

//------------------------------------------------------------------------------
bool WorldFrameListener::frameEnded(const FrameEvent& evt)
{
    float time = evt.timeSinceLastFrame;
    _stepper->step(time);   
    //_stepper->pause(true);
         
    world->frameEnded(evt);   
    //_stepper->pause(false);
    //_stepper->pause(time);   TODO is this a better way??
}

//------------------------------------------------------------------------------
InputReader* WorldFrameListener::getInputReader()
{
    return mInputDevice;
}

};
