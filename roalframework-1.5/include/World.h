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
#ifndef _ROALWORLD_H_
#define _ROALWORLD_H_

#include <OGRE/Ogre.h>
#include <OGRE/OgreConfigFile.h>
#include <OgreOde_Core/OgreOde_Core.h>
#include <OgreOde_Prefab/OgreOde_Prefab.h>

#include "Body.h"
#include "Brain.h"
#include "Agent.h"
#include "WorldFrameListener.h"
#include "RoalException.h"
#include "Joint.h"
#include "EyeSegment.h"
#include "KeySensor.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
// Forward declarations
class Agent;
class WorldFrameListener;
class KeySensor;

/**
 * The graphical and physical environment of a simulation.
 * 
 * The World class represents the graphical and physical environment. It contains
 * several general attributes like gravity or camera position and is able to
 * start the simulation. It is compounds the Ogre with the OgreOde world.
 *
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class World: 
    public OgreOde::TerrainGeometryHeightListener ,
    public OgreOde::CollisionListener  
{
public:
    /**
     * Constructor.
     * 
     * @param terrainConfigFile The name of the config file to load.
     * @param resourcesConfigFile The Path to resource config file
     */
	World(string terrainConfigFile, string resourcesConfigFile);
    
    /**
     * Destructor.
     */
	virtual ~World();
	
    /**
     * The iteration method before each frame.
     * 
     * Calls Agent::iteration of every Agent registered in the World.
     * 
     * @see WorldFrameListener::frameStarted
     */
    virtual void frameStarted(const FrameEvent& evt);
  
    /**
     * The iteration method after each frame.
     * 
     * The FrameListener will let us know when a frame is s ended. So we
     * can do stuff that we can't do in a frame started event
     * e.g. delete things that we can't delete at the start of a frame,
     * presumably because some processing has already been done, leaving
     * things dangling, like particle systems.
     * 
     * @see WorldFrameListener::frameEnded
     */
    virtual void frameEnded(const FrameEvent& evt);  

    /**
     * Runs the simulation.
     * 
     * This method shows the setup dialog and starts the simulation.
     */
	void run();
    
    /**
     * Adds an Agent to the World.
     * 
     * The World will later call the methods Agent::iterate and
     * Agent::prepareNextStep.
     * 
     * @param agent The Agent to register in the World.
     * 
     * @exception RoalException
     */
    void registerAgent(Agent* agent);
    
    /**
     * Defines a Theme to use.
     * 
     * A theme defines the look of the environment (sky, ground, etc.). Possible
     * themes are:
     *   - "lab", a performance-safe theme with simple tiled ground and blue sky
     *     @image html theme_lab.png
     *     @image latex theme_lab.ps
     *   - "labsky", same as "lab" but with (slow-moving) cloud sky texture:
     *     @image html theme_labsky.png
     *     @image latex theme_labsky.ps
     *   - "marshigh", a high-resolution mars-like environment with red sky and gray ground:
     *     @image html theme_mars.png
     *     @image latex theme_mars.ps
     *   - "marslow", same as "marshigh" but with low-resolution textures.
     *   - "desert", desert environment with evening sunlight:
     *     @image html theme_desert.png
     *     @image latex theme_desert.ps
     *   - "mountain", beautiful mountains:
     *     @image html theme_mountain.png
     *     @image latex theme_mountain.ps
     *   - "grass", simple grass ground:
     *     @image html theme_grass.png
     *     @image latex theme_grass.ps
     * 
     * @param theme A theme to use.
     */
    void setTheme(string theme);
    
    /**
     * Get defined theme.
     * 
     * @see World::setTheme
     * 
     * @return The theme in use.
     */
    string getTheme();
    
    /**
     * Returns the gravity of the World.
     * 
     * @see World::gravity
     * 
     * @return the gravity of the World.
     */ 
	Vector3 getGravity();
    
    /**
     * Sets the gravity of the World.
     * 
     * @see World::gravity
     * 
     * @param gravity A gravity to set in the World.
     */ 
	void setGravity(const Vector3 &gravity);
	
    /**
     * Returns the position of the camera.
     * 
     * @see World::cameraPosition
     * 
     * @return the position of the camera.
     */ 
    Vector3 getCameraPosition();
    
    /**
     * Sets the position of the camera.
     * 
     * @see World::cameraPosition
     * 
     * @param vec A vector that describes the new camera position.
     */ 
    void setCameraPosition (const Vector3 &vec);
    
    /**
     * Returns the orientation of the camera.
     * 
     * @see World::cameraLookAt
     * 
     * @return the point the camera looks at (orientation).
     */ 
    Vector3 getCameraLookAt();
    
    /**
     * Sets the orientation of the camera.
     * 
     * @see World::cameraLookAt
     * 
     * @param vec A point (as vector) to look at (orientation).
     */ 
    void setCameraLookAt (const Vector3 &vec);
    
    /**
     * Returns the background color of the World.
     * 
     * @see World::backgroundColor
     * 
     * @return the background color of the World.
     */ 
    ColourValue getBackgroundColor();
    
    /**
     * Sets the background color of the World.
     * 
     * @see World::backgroundColor
     * 
     * @param color the new background color of the World.
     */ 
    void setBackgroundColor(ColourValue color);

    /**
     * Sets the position of the main light.
     * 
     * @see World::mainLightPosition
     * 
     * @param vec the new position of the main light.
     */ 
    void setMainLightPosition(const Vector3 &vec);
    
    /**
     * Returns the position of the main light.
     * 
     * @see World::mainLightPosition
     * 
     * @return the position of the main light.
     */ 
    Vector3 getMainLightPosition();
    
    /**
     * Returns the color of the main light.
     * 
     * @return the color of the main light.
     */ 
    ColourValue getMainLightColor();
    
    /**
     * Sets the color of the main light.
     * 
     * @return the color of the main light.
     */ 
    void setMainLightColor(ColourValue color);

    /**
     * Returns whether the simulation uses shadows or not.
     * 
     * @return true if the simulation uses shadows, else false.
     */ 
    bool getIsUseShadow();
    
    /**
     * Switch shadows on or off.
     * 
     * Default: If nothing is set, no shadows are used, because 
     * of bad performance.
     * 
     * @param flag true if shadows should be visible, false otherwise.
     */ 
    void setIsUseShadow(bool flag);
    
    /**
     * Returns the name of the config file.
     * 
     * @return the name of the config file.
     */ 
    string getConfigFileName();
    
    /**
     * Sets the config filename.
     * 
     * This method has no influnce if the simulation is 
     * already started (with World::run()).
     * 
     * @param fileName The name of the config file.
     */ 
    void setConfigFileName(string fileName);
    
    /**
     * Returns whether debug objects are displayed or not.
     * 
     * @return true, if debug objects are visible, false otherwise.
     */ 
    bool isShowDebugObjects();
    
    /**
     * Sets whether debug objects should be displayed or not.
     * 
     * If set true, the bounding boxes from ODE will be visible. This is useful
     * when debugging.
     * 
     * @param flag Set to true, if debug objects should be visible, false otherwise.
     */ 
    void setShowDebugObjects(bool flag);
        
    /**
     * Checks if an Agent is already registered.
     * 
     * @param name The name of an Agent to check.
     * 
     * @return true if the Agent is already registered.
     */    
    bool isAgentRegistered(string name);

    /**
     * Adds a Body to the World.
     * 
     * The World will get the Body's BodySegment objects and display them.
     * 
     * @param body A Body to register in the World.
     * 
     * @exception RoalException
     */
    void registerBody(Body* body);
 
    /**
     * removes a Body from the World.
     * 
     * @param body A Body to unregister in the World.
     * 
     * @exception RoalException
     */
    void unregisterBody(Body* body);

    /**
     * Checks if a Body is already registered.
     * 
     * @param name The name of a Body to check.
     * 
     * @return true if the Body is already registered.
     */
    bool isBodyRegistered(string name);
    
    /** 
     * Returns the height at a given position.
     * 
     * @param position A position-vector in 3D space.
     * @return the height at a given position.
     */
    virtual float heightAt(const Vector3& position);
    
    /**
     * Create a KeySensor to listen to key strokes.
     * 
     * @return a newly created KeySensor.
     */
    KeySensor* createKeySensor();
    
    /**
     * Get the instance of the FrameListener.
     * 
     * @return the instance of the FrameListener.
     */
    WorldFrameListener* getFrameListener();
    
    /**
     * Returns the distance to the closest body from a given Position.
     *
     * @param pos the position from which the distances starts.
     * @param maxRadius the maximum radius (discribes a sphere).
     * @param ignoreName a Body with this name will be not considered.
     * @param ignoreAgent an Agent which's Body objects will not be considered.
     * 
     * @return the distance to closest Body (maxRadius if no Body is in the maxRadius)
     */
    float getClosestBodyDistance(Position* pos, float maxRadius, string ignoreName,
                         vector<string> ignoreAgent);

protected:
    /**
 	 * A vector to with new Joint objects.
 	 */
    vector<Roal::Joint*> newJoints;
    
    /**
     * Path to resource config file
     */
    string resourcesConfigFile;
    
    typedef map<string, BodySegment*> SegmentsMap;
    /**
 	 * A map with the new BodySegment objects.
     *
     * These BodySegment objects will be added when the actual generation is
     * finished.
 	 */
    SegmentsMap newSegments;
    
    /**
     * A map with the BodySegment objects which collisions should be tracked.
     */
    SegmentsMap toTrackSegments;
    
    typedef map<string, Agent*> AgentsMap;
    /**
     * A map with the Agent objects.
     */
	AgentsMap agents;
  
    /**
     * The root node of Ogre simulation.
     */
    Root *mRoot;
    
    /**
     * Instance of the window with the simulation.
     */
    RenderWindow* mWindow;
    
    /**
     * The theme that descripes the look of the environment.
     * 
     * @see World::setTheme
     */
    string theme;
     
    /** 
     * The Camera of the World.
     * 
     * This Camera represents the view of the observer.
     */
    Camera* mCamera;
    
    /**
     * The main light in the simulation
     */
    Light* mainLight;
    
    /**
     * The SceneManager of the simulation that holds the camera and the light.
     */
    SceneManager* mSceneMgr;

    
    /**
     * The gravity of the World.
     * 
     * The gravity is a directed force represented by a vector with three
     * dimensions (x,y,z).
     */
    Vector3 gravity;
    
    /**
     * The Position of the MainLight.
     * 
     * The main light position is represented by a vector with three coordinates
     * (x,y,z).
     */
    Vector3 mainLightPosition;
    
    /**
     * The color of the main light.
     */
    ColourValue mainLightColor;
    
    /**
     * The position of the camera.
     * 
     * The camera position is represented by a vector with three coordinates
     * (x, y, z).
     */
    Vector3 cameraPosition;
    
    /**
     * The orientation of the camera.
     * 
     * The orientation is defined by a point in the World, at which the camera
     * looks. The point is a vector with three coordinates (x, y, z).
     */
    Vector3 cameraLookAt;
    
    /**
     * The World's background color.
     * 
     * This Color is only visible if no SkyBox is defined.
     */
    ColourValue backgroundColor;

    /**
     * A flag that is true if the shadows are on.
     */
    bool isUseShadows;
    
    /**
     * The config file of the World.
     */
    string config_file;
    
    /**
     * A flag that is true if debug objects are visible.
     */
    bool showDebugObjects;
    
    /**
     * The overlay object for the Roal logo.
     */
    Ogre::Overlay* overlay;
    
    /**
     * An instance of the WorldFrameListener.
     */
	WorldFrameListener* mFrameListener;
    
    /** 
     * The pause state.
     */
    bool isPause;
    
    /** 
     * The run state.
     */
    bool isRunnable;
    
    /**
     * Collision callback.
     * 
     * This method is called when a collision occurs.
     * 
     * @param contact the Contact object that contains the involved bodies.
     * @return true if the collision should be handled.
     */
    virtual bool collision(OgreOde::Contact* contact);
        
    /**
     * Defines the source of resources (that are different from the current folder).
     */
    void setupResources(void);
    
    /**
     * Initialise, parse scripts etc.
     */
    void loadResources(void);
    
private:
    /**
     * The terrain handler
     */ 
    OgreOde::TerrainGeometry *_terrain;
    
    /**
     * An instance of the OgreOde::World
     */
    OgreOde::World *_world;
    
    /**
     * The time step of the simulation
     */
    float _time_step;
    
    /**
     * ???
     */
    OgreOde::Stepper *_stepper;
    
    /**
     * ???
     */
    RaySceneQuery *_ray_query;

    /**
     * Sets up the simulation.
     */
    bool setup(void);
    
    /**
     * Sets up a theme.
     * 
     * Does the settings described by a theme (skybox, ground, etc.).
     * 
     * @see World::setTheme
     */
    void setupTheme(string theme);
    
    /** 
     * Show the configuration dialog and initialise the system.
     * 
     * You can skip this and use root.restoreConfig() to load configuration
     * settings if you were sure there are valid ones saved in ogre.cfg
     * 
     * @return true if the configuration was ok.
     */
    bool configure(void);
    
    /**
     * Creates the SceneManger of the World.
     * 
     * This SceneManager holds the camera, lights and other stuff
     */  
    void createSceneManager(void);
    
    /** 
     * Creates the Camera of the World.
     *
     * Sets a default position and orientation
     */ 
    void createCamera(void);
    
    /** 
     * Creates the light of the World.
     *
     * Sets a default position and color.
     */  
    void createLight(void);
    
    /**
     * Creates the WorldFrameListener.
     * 
     * This is listener implements the method frameStarted. Which is called before
     * a frame is rendered. This Method calls the method World::iterate
     */
    void createFrameListener(void);
    
    /**
     * This method constructs Scene of the world.
     *
     * This method defines the terrain, the light and other behaviour of the 
     * world but not its content    
     */ 
    void createScene(void);
    
    /**
     * Destroies the Scene
     */ 
    void destroyScene(void);
    
    /**
     * Create Viewports
     */
    void createViewports(void);
    
    /**
     * Creates the ResourceListener.
     * 
     * This is listener is able to find resources like mesh-files and pictures
     */
    void createResourceListener(void);  
    
    /**
     * Inserts all registered bodies into the scene.
     * 
     * This method has to be called after World::createSecene()
     */
    void updateOgreOde();  
};

}

#endif //_ROALWORLD_H_
