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

#include "World.h"

using namespace std;

namespace Roal
{

//------------------------------------------------------------------------------
World::World(string terrainConfigFile, string resourcesConfigFile)
{
    this->setConfigFileName(terrainConfigFile);
    this->resourcesConfigFile = resourcesConfigFile;
    
    isPause = true;
    isRunnable = false;
    
    _time_step = 0.01;
    
    mRoot = new Root();
    // Set some default values
    this->setGravity(Vector3(0,-9.80665,0)); 
    this->setBackgroundColor(ColourValue(0.0, 0.0, 0.76));     
    this->setCameraPosition(Vector3(710,15,530)); 
    this->setCameraLookAt(Vector3(0,0,0)); 
    this->setMainLightPosition(Vector3(20,800,50));
    this->setMainLightColor(ColourValue(1,0.9,0.5));  
    this->setIsUseShadow(true);
    this->setShowDebugObjects(false);
    this->setTheme("lab");
}


//------------------------------------------------------------------------------
World::~World()
{

    if (mRoot) { delete mRoot; }
//    if (_terrain) { delete _terrain;}
//    if (mFrameListener) { delete mFrameListener;}
    if (_stepper) { delete _stepper;}
    mCamera->getSceneManager()->destroyQuery(_ray_query);
    if (_world) { delete _world;}

}


//------------------------------------------------------------------------------
void World::frameStarted(const FrameEvent& evt)
{
    float time = evt.timeSinceLastFrame;
    // Call the Agent's iterate method
    for(AgentsMap::iterator it = agents.begin(); it != agents.end(); it++) {
        it->second->iterate(time);
    }
}


//------------------------------------------------------------------------------
void World::frameEnded(const FrameEvent& evt)
{  
    float time = evt.timeSinceLastFrame;

    _world->synchronise();
    
    // Step the world and then synchronise the scene nodes with it, 
    // we could get this to do this automatically, but we 
    // can't be sure of what order the framelisters will fire in
    //_world->synchronise();
    
    // Call the Agent's prepareNextStep() method
    for(AgentsMap::iterator it = agents.begin(); it != agents.end(); it++) {
        it->second->prepareNextStep();
    }
    
    //add all registered bodies
    updateOgreOde();    

}


//------------------------------------------------------------------------------
void World::run()
{
    isPause = false;
    if (!setup())
        return;

    // Starts the Simulation
    mRoot->startRendering();

    // clean up
    destroyScene();
}


//------------------------------------------------------------------------------
void World::registerBody(Body* body)
{
    //add every BodySegment and Joint to a Container
    SegmentsMap seg = body->getBodySegments();
    
    for(SegmentsMap::iterator bi = seg.begin();bi != seg.end(); bi++) {
        
        // check if the segment is already registerd
        if (newSegments.count(bi->second->getName()) == 0 
                && toTrackSegments.count(bi->second->getName()) == 0){
            newSegments[bi->second->getName()] = bi->second;

        } else {
           throw(RoalException(typeid( this ).name(), "A BodySegment with the name " +
                        bi->second->getName() + " is already registered"));
        }
    } 
        
    vector<Roal::Joint*> vec = body->getJoints();
    
    for(vector<Roal::Joint*>::iterator joi = vec.begin(); joi != vec.end(); joi++) {
        newJoints.push_back(*joi);
    } 
}

//------------------------------------------------------------------------------
void World::unregisterBody(Body* body)
{
    SegmentsMap seg = body->getBodySegments();
    
    for(map<string, BodySegment*>::iterator it = seg.begin(); it != seg.end(); it++) 
    {
        toTrackSegments.erase(it->first);
    }

}

//------------------------------------------------------------------------------
void World::updateOgreOde()
{
    //add every BodySegment to the scene. DO THIS BEFORE THE JOINTS!!!
    for(SegmentsMap::iterator seg = newSegments.begin();
            seg != newSegments.end(); seg++) {
		    
		    
                /**@todo dynamic_cast could not used anymore!!!! GCC4.0???*/
		    //if (dynamic_cast<EyeSegment*>((EyeSegment*)(seg->second))!=NULL) {
            //   ((EyeSegment*)(seg->second))->setRenderWindow(mWindow);
		    //}
		    
        seg->second->initSegment(_world->getDefaultSpace());
        
        //we need to track the segments to performe a godd collision dedection
        toTrackSegments[seg->second->getName()] = seg->second; 
    }
   
    //add every Joint to the scene
    for(std::vector<Roal::Joint*>::iterator joi = newJoints.begin();
            joi != newJoints.end(); joi++) {
        (*joi)->initJoint();
    }
   
    //we need no track
    newJoints.clear(); 
    newSegments.clear(); 
}


//------------------------------------------------------------------------------
bool World::isBodyRegistered(string name)
{  
    SegmentsMap::iterator ts, ns;
    
    //try to find the Segment
    ts = toTrackSegments.find(name);
    ns = newSegments.find(name);
    
    return ((ts != toTrackSegments.end()) || (ns != newSegments.end()));
}


//------------------------------------------------------------------------------
void World::registerAgent(Agent* agent)
{
    if (!this->isAgentRegistered(agent->getName())) {
        // Add the Agent to the map
        agents[agent->getName()] = agent;
    } else {
        throw(RoalException(typeid( this ).name(),"An Agent with the name "
                    + agent->getName() + " is already registered"));
    }
}


//------------------------------------------------------------------------------
bool World::isAgentRegistered(string name)
{    
    AgentsMap::iterator a;
    
    //try to find the Agent
    a = agents.find(name);

    return (a != agents.end());
}


//------------------------------------------------------------------------------
bool World::collision(OgreOde::Contact* contact)
{
   
    bool handleCollision = true;
     
    // Default values (the objects that collide can overwrite these values)
    contact->setBouncyness(0.0);
    contact->setCoulombFriction(18.0);

    BodySegment* bs1 = 0;
    BodySegment* bs2 = 0;
    
    // Get the two OgreOde geometries that are involved in the collision
    OgreOde::Geometry* g1 = contact->getFirstGeometry();
    OgreOde::Geometry* g2 = contact->getSecondGeometry();
           
    // Get Roal::BodySegment objects from the geometries
    SegmentsMap::iterator seg = toTrackSegments.begin();
    while(seg != toTrackSegments.end()&& (bs1 == 0 || bs2 == 0)) {  

        if (seg->second->getOgreGeometry() == g1) {
             bs1 = seg->second;
        }
        if (seg->second->getOgreGeometry() == g2) {
             bs2 = seg->second;
        }      
        seg++;     
    }
    
    if (bs1 && bs2) { // Both segments are Roal::BodySegment objects
        
        // Let the body or bodies of the involved BodySegments decide whether
        // to handle the collision or not
        
        if (bs1->getOwner() != bs2->getOwner()) {           
            // The segments belong to two different bodies
            handleCollision = handleCollision && bs1->getOwner()->handleCollision(
                                                            contact, bs1, bs2);
            handleCollision = handleCollision && bs2->getOwner()->handleCollision(
                                                            contact, bs2, bs1);
        } else {
            // The segments belong to the same body (inner collision)
            handleCollision = handleCollision && bs1->getOwner()->handleCollision(
                                                            contact, bs1, bs2);
        }    
        
    } else if (bs1 && !bs2) { // Only one segment is a Roal::BodySegment, the
                              // other may be the ground or another Ogre object
    
        handleCollision = handleCollision && bs1->getOwner()->handleCollision(
                                                            contact, bs1, NULL);
    
    } else if (!bs1 && bs2) { // Only one segment is a Roal::BodySegment, the
                              // other may be the ground or another Ogre object
        
        handleCollision = handleCollision &&  bs1->getOwner()->handleCollision(
                                                            contact, bs2, NULL);
        
    }   
    
    return handleCollision;
}

//------------------------------------------------------------------------------
float World::getClosestBodyDistance(Position* pos, float maxRadius
                    , string ignoreName, std::vector<string> ignoreAgent)
{
    float dist = maxRadius;
    float tmpDist = 0.0;
    
    /** @todo make ignoreAgent more dynamicly.*/
    vector<string>::iterator start = ignoreAgent.begin();
    vector<string>::iterator end = ignoreAgent.end();
    vector<string>::iterator iter;
    
    // Call the Agent's iterate method
    for(AgentsMap::iterator it = agents.begin(); it != agents.end(); it++) {

        iter = find(start,end,it->second->getName());
        //cout << " CheckAgent: "<< it->second->getName(); 
        if (iter == end)
        {
            tmpDist = it->second->getClosestBodyDistance(pos,maxRadius,ignoreName);
                        
            if (tmpDist<dist)
            {
                dist = tmpDist;

            }
          //  cout << " Distance: "<< tmpDist << " currentDist" << dist <<endl;   
            
        } else {
            //cout << " IGNORE!!! " << " currentDist" << dist <<endl;     
        }
    }
    
    return dist;
}


//------------------------------------------------------------------------------
bool World::setup(void)
{
    // Display the the configuration task
    bool carryOn = configure();
    if (!carryOn) return false;

    setupResources();
    createSceneManager();
    
    // Set default mipmap level (NB some APIs ignore this)
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    
    // Create any resource listeners (for loading screens)
    //createResourceListener();
    
    // Load resources
    loadResources();
    
    // Setup theme (ground, sky, color)
    setupTheme(this->theme);
    
    // create the scene
    createScene();
    
    // this method has to be placed after the createScene
    createFrameListener();    
    return true;
}


//------------------------------------------------------------------------------
bool World::configure(void)
{
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by
        // passing 'true'
        mWindow = mRoot->initialise(true, "ROAL Main Window");
        return true;
    }
    else
    {
        return false;
    }
}


//------------------------------------------------------------------------------
void World::createSceneManager(void)
{
    // Get the SceneManager ST_GENERIC or ST_EXTERIOR_CLOSE 
    mSceneMgr = mRoot->getSceneManager(ST_EXTERIOR_CLOSE);
}


//------------------------------------------------------------------------------
void World::createLight(void)
{
    // Create a light
    mainLight = mSceneMgr->createLight("RoalLight");
    mainLight->setVisible(true);
}


//------------------------------------------------------------------------------
void World::createFrameListener(void)
{
    mFrameListener = new WorldFrameListener(mWindow, mCamera, _time_step, mRoot, this);
    
    //Switch off framerate display an Ogre logo
    mFrameListener->showDebugOverlay(false);
    
    //Display the roal logo
    overlay = OverlayManager::getSingleton().getByName("RoalCore/RoalOverlay");
    overlay->show();
    
    //register FrameListener
    mRoot->addFrameListener(mFrameListener);
}


//------------------------------------------------------------------------------
void World::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("RoalCam");     
    mCamera->setNearClipDistance(5);
}


//------------------------------------------------------------------------------
void World::createViewports(void)
{
    // Create one viewport, entire window
    Viewport* vp = mWindow->addViewport(mCamera);

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
                float(vp->getActualWidth()) / float(vp->getActualHeight()));
}


//------------------------------------------------------------------------------
void World::setupTheme(string theme)
{
    string groundMaterial;
    if (theme == "lab") {
        groundMaterial = string("landscape/labground");
        this->setBackgroundColor(ColourValue(0.0, 0.0, 0.76));
        mSceneMgr->setFog(FOG_LINEAR, backgroundColor, .001, 500, 1000);
    } else if (theme == "labsky") {
        groundMaterial = string("landscape/labground");
        mSceneMgr->setSkyDome(true, "landscape/labsky", 5, 8);
        this->setBackgroundColor(ColourValue(0.62, 0.69, 0.99));
        mSceneMgr->setFog(FOG_LINEAR, backgroundColor, .001, 300, 1000);
    } else if (theme == "marshigh") {
        groundMaterial = string("landscape/marshighground");
        mSceneMgr->setSkyBox(true, "landscape/marshighsky", 50);
    } else if (theme == "marslow") {
        groundMaterial = string("landscape/marslowground");
        mSceneMgr->setSkyBox(true, "landscape/marslowsky", 50);
    } else if (theme == "desert") {
        groundMaterial = string("landscape/desertground");
        mSceneMgr->setSkyBox(true, "landscape/desertsky", 50);
    } else if (theme == "mountain") {
        groundMaterial = string("landscape/mountainground");
        mSceneMgr->setSkyBox(true, "landscape/mountainsky", 50);
    } else if (theme == "grass") {
        groundMaterial = string("landscape/grassground");
        this->setBackgroundColor(ColourValue(0.0, 0.0, 0.76));
        mSceneMgr->setFog(FOG_LINEAR, backgroundColor, .001, 500, 1000);
    } else {
        throw(RoalException(typeid( this ).name(),
              "Invalid theme: '" + theme + "'"));
    }
    mSceneMgr->setOption("CustomMaterialName", &groundMaterial);
}


//------------------------------------------------------------------------------
void World::createScene(void) 
{
    //create required objects
    createCamera();
    createViewports();
    createLight();
    
    // Shadow State
    this->setIsUseShadow(isUseShadows); 
  
    isRunnable = true;

    // Set the behaviour of the camera    
    this->setCameraPosition(cameraPosition);
    this->setCameraLookAt(cameraLookAt);
 
    // Set the background Color
    this->setBackgroundColor(backgroundColor);   
    
    // Set the behaviour of the Main Light
    this->setMainLightPosition(mainLightPosition);
    this->setMainLightColor(mainLightColor);

    // Shadow State
    this->setIsUseShadow(isUseShadows); 
    
    // Set ambient light
    mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    
    // Set up the terrain according to our own settings
    mSceneMgr->setWorldGeometry(config_file);  
   
    // Define the required skyplane
    Plane plane;
    plane.d = 5000;
    plane.normal = -Vector3::UNIT_Y;

    // create new OgreOde World and set the params
    _world = new OgreOde::World(mSceneMgr);
    _world->setCFM(10e-5);
    _world->setERP(0.8);
    _world->setAutoSleep(true);
    _world->setContactCorrectionVelocity(0.5); 
    _world->setCollisionListener(this);
    _world->setShowDebugObjects(this->showDebugObjects);
    this->setGravity(gravity); 

    // create the terrain
    _terrain = new OgreOde::TerrainGeometry(config_file,_world->getDefaultSpace());
    _terrain->setHeightListener(this);
} 


//------------------------------------------------------------------------------
void World::destroyScene(void)
{
    //nothing to be done, yet...
}


//------------------------------------------------------------------------------
float World::heightAt(const Vector3& position)
{
    return _terrain->getHeightAt(position);
}


//------------------------------------------------------------------------------
void World::setupResources(void)
{
    // Load resource paths from config file
    ConfigFile cf;
    cf.load(this->resourcesConfigFile);

    // Go through all sections & settings in the file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    string secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(
                                                archName, typeName, secName);
        }
    }
}


//------------------------------------------------------------------------------
void World::loadResources(void)
{
    // Initialise, parse scripts etc
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

//------------------------------------------------------------------------------
KeySensor* World::createKeySensor()
{
    return new KeySensor(this);
}

//------------------------------------------------------------------------------
WorldFrameListener* World::getFrameListener()
{
    return mFrameListener;
}

/************* Setter and Getter Methods **************************************/

//------------------------------------------------------------------------------
void World::setTheme(string theme)
{
    this->theme = theme;
}


//------------------------------------------------------------------------------
string World::getTheme()
{
    return this->theme;
}


//------------------------------------------------------------------------------
void World::setIsUseShadow(bool flag)
{
    this->isUseShadows = flag;
    
    //If the simulation is runnable perform a realtime update
    if (isRunnable) {
        
        if (isUseShadows) {
            
            mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
            mSceneMgr->setShadowColour(ColourValue(0.5,0.5,0.5));
            
            
        } else {
            mSceneMgr->setShadowTechnique(SHADOWTYPE_NONE);
        }
        
        mainLight->setVisible(true);
        mainLight->setCastShadows(flag);
    }
    
}

//------------------------------------------------------------------------------
bool World::getIsUseShadow()
{
   return this->isUseShadows;
}    


//------------------------------------------------------------------------------
void World::setMainLightPosition(const Vector3 &vec)
{
    mainLightPosition = vec;
    
    //If the simulation is runnable perform a realtime update
    if (isRunnable) {
        mainLight->setPosition(mainLightPosition);
    }
}


//------------------------------------------------------------------------------
 Vector3 World::getMainLightPosition()
{
    return this->mainLightPosition;
}

//------------------------------------------------------------------------------
void World::setMainLightColor(ColourValue color)
{
    mainLightColor = color;
    
    //If the simulation is runnable perform a realtime update
    if (isRunnable) {
        mainLight->setSpecularColour(mainLightColor);
    }
        
}

//------------------------------------------------------------------------------
 ColourValue World::getMainLightColor()
{
    return this->mainLightColor;
}


//------------------------------------------------------------------------------
void World::setGravity(const Vector3 &gravity)
{
    this->gravity = gravity;

    //If the simulation is runnable perform a realtime update
    if (isRunnable) {
        _world->setGravity(gravity);
    }

}


//------------------------------------------------------------------------------
Vector3  World::getGravity()
{
    return  this->gravity;
}


//------------------------------------------------------------------------------
void World::setCameraPosition(const Vector3 &vec)
{
    this->cameraPosition = vec;
    
    //If the simulation is runnable perform a realtime update
    if (isRunnable) {
        mCamera->setPosition(cameraPosition);
	    }
}


//------------------------------------------------------------------------------
Vector3 World::getCameraPosition()
{
    return this->cameraPosition;
}


//------------------------------------------------------------------------------
void World::setCameraLookAt(const Vector3 &vec)
{  
    this->cameraLookAt = vec;

    //If the simulation is runnable perform a realtime update
    if (isRunnable) {
       mCamera->lookAt(cameraLookAt);
    }
}


//------------------------------------------------------------------------------
Vector3 World::getCameraLookAt()
{
    return this->cameraLookAt;
}


//------------------------------------------------------------------------------
void World::setBackgroundColor(ColourValue color)
{
    backgroundColor = color;
    
    //If the simulation is runnable perform a realtime update
    if (isRunnable) {
        mWindow->getViewport(0)->setBackgroundColour(backgroundColor);    
    }
}


//------------------------------------------------------------------------------
ColourValue World::getBackgroundColor()
{
    return this->backgroundColor;
}


//------------------------------------------------------------------------------
string World::getConfigFileName()
{
    return this->config_file;
}

   
//------------------------------------------------------------------------------
void World::setConfigFileName(string fileName)
{
    this->config_file = fileName;
}


//------------------------------------------------------------------------------
bool World::isShowDebugObjects()
{
    return this->showDebugObjects;
}

   
//------------------------------------------------------------------------------
void World::setShowDebugObjects(bool flag)
{
    this->showDebugObjects = flag;
}



};
