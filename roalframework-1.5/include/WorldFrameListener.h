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
#ifndef _WORLDFRAMELISTENER_H_
#define _WORLDFRAMELISTENER_H_

#include <OGRE/Ogre.h>
#include <OgreOde_Core/OgreOde_Core.h>
#include <OgreOde_Prefab/OgreOde_Prefab.h>
#include <OgreOde_Prefab/ExampleFrameListener.h>
#include "World.h"




namespace Roal
{
class World; // Forward declaration for World

/**
 * The World's frame listener.
 * 
 * This Frame Listener handles all Keyborad inputsand calls the iteration 
 * Method of the World
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class WorldFrameListener : public ExampleFrameListener
{
public:
    /**
     * Constructor
     * 
     * @param win Instance of the RenderWindow.
     * @param cam The camera.
     * @param time_step ???
     * @param root The root node of the simulation.
     * @param world Instance of the Roal::World.
     */
    WorldFrameListener(RenderWindow* win, Camera* cam, float time_step,
         Root* root, World* world);
            
    /**
     * Destructor
     */
    virtual ~WorldFrameListener();
        
    /**
     * The iteration method before each frame.
     * 
     * This method is called, before a frame will be rendered. Use this method
     * to change the world when the simualtion is running.
     * 
     * @param evt An instance of the FrameEvent object.
     * @return ???
     */
    bool frameStarted(const FrameEvent& evt);
    
    /**
     * The iteration method after each frame.
     * 
     * This method is called, after a frame has been rendered. Use this method
     * to add or remove Ogre entities.
     * 
     * @param evt An instance of the FrameEvent object.
     * @return ???
     */ 
    bool frameEnded(const FrameEvent& evt);
    
    InputReader* getInputReader();
private:
    /**
     * ???
     */
    OgreOde::Stepper *_stepper;
     
    /**
     * ???
     */
    RaySceneQuery *_ray_query;
    
    /**
     * The World instance of this WorldFrameListener
     */
    World* world;

    /**
     * Number of screenshoot sience start
     */
    int mNumScreenShots;

    /**
     * Given Render windoe
     */
    RenderWindow* win;
};

}

#endif //_WORLDFRAMELISTENER_H_
