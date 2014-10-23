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
#ifndef _BODYSEGMENT_H_
#define _BODYSEGMENT_H_

#include <OgreOde_Core/OgreOde_Core.h>
#include <OGRE/Ogre.h>
#include <OgreOde_Core/OgreOdeSpace.h>
#include <OgreOde_Core/OgreOdeGeometry.h>
#include "Position.h"
#include "RoalException.h"
#include "Body.h"
#include "ISensor.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
class Body; // Forward declaration for Body

/**
 * The BodySegment objects are used to build a Body.
 * 
 * BodySegment objects are segments or limbs of a body. A Body consists of one
 * or more BodySegment objects that are connected through Joint objects.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class BodySegment
{
public:
    /**
     * Constructor.
     * 
     * @param owner The Body the BodySegment belongs to.
     * @param name The name of the BodySegment. This has to be unique in the system!
     * @param meshFile The name of the mesh file.
     */
	BodySegment(Body* owner, std::string name, std::string meshFile);
    
    /**
     * Destructor.
     */
	virtual ~BodySegment();
    
    /**
     * Returns the Body the BodySegment belongs to.
     *
     * @return the Body the BodySegment belongs to.
     */
    Roal::Body* getOwner();
    
    /**
     * Returns the name of the BodySegment.
     *
     * @return the name of the BodySegment.
     */
    std::string getName();
     
    /**
     * Returns the Ogre::Entity* of the BodySegment.
     *
     * @return the Ogre::Entity* of the BodySegment.
     * 
     * @exception RoalException in case the Body has no Entity
     */
    Ogre::Entity* getOgreEntity();

    /**
     * Returns the OgreOde::Geometry* of the BodySegment.
     *
     * @return the OgreOde::Geometry* of the BodySegment.
     * 
     * @exception RoalException in case the Body has no Geometry
     */
    OgreOde::Geometry* getOgreGeometry();
    
    /**
     * Returns the Ogre::Entity* of the BodySegment.
     *
     * @return the Ogre::Entity* of the BodySegment.
     * 
     * @exception RoalException in case the Body has no SceneNode
     */
    SceneNode* getSceneNode();
    
    /**
     * Returns the Ogre::Entity* of the BodySegment.
     *
     * @return the Ogre::Entity* of the BodySegment.
     *
     * @exception RoalException in case the Body has no OgreOde::Body
     */
    OgreOde::Body* getOgreBody();
    
    /**
     * Sets the Segement to this position.
     * 
     * @param x The x coordinate of the BodySegment.
     * @param y The y coordinate of the BodySegment.
     * @param z The z coordinate of the BodySegment.
     */    
    void setPosition(float x, float y, float z);
    
    /**
     * Gets the Position of the BodySegment.
     * 
     * @return The Position of the BodySegment.
     */
    Roal::Position* getPosition();

    /**
     * Returns the runnable state of the BodySegment.
     * 
     * @return The runnable state of the BodySegment.
     */
    bool getIsRunnable(); 

    /**
     * Adds the given force to the BodySegment.
     * 
     * @param force The force to add to the BodySegment.
     */
    void addForce(const Vector3 &force);
    
    /**
     * Adds a given torque force to the BodySegment.
     * 
     * @param torque The torque force to add to the BodySegment.
     */
    void addTorque(const Vector3 &torque);
    
    /**
     * Returns the force of the BodySegment.
     * 
     * @return The force of the BodySegment.
     */
    const Vector3 getForce();
    
    /**
     * Returns the torque of the BodySegment.
     * 
     * @return the torque of the BodySegment.
     */     
    const Vector3 getTorque();

    /**
     * Sets the orientation of the BodySegment in the World.
     * 
     * @param ori The orientation of the BodySegment in the World.
     */   
    void setOrientation(const Quaternion &ori);
    
    /**
     * Returns the orientation of the BodySegment in the World.
     * 
     * @return the orientation of the BodySegment in the World.
     */
    Quaternion getOrientation();

    /**
     * Returns the name of the mesh file.
     * 
     * @return the name of the mesh file.
     */
    std::string getMeshFile();  
    
    /**
     * Sets the physical mass of the BodySegment.
     * 
     * @param mass The physical mass of the BodySegment.
     */    
    void setMass(float mass); 
    
    /**
     * Returns the physical mass of the BodySegment.
     * 
     * @return the physical mass of the BodySegment.
     */
    float getMass();  
    
    /**
     * Sets the scale of the cube.
     * 
     * @param x the x-scale
     * @param y the y-scale
     * @param z the z-scale
     */    
    virtual void setScale(float x, float y, float z) = 0;
    
    /**
     * Returns the x-scale
     * 
     * @return the x-scale
     */
    float getXScale();
    
    /**
     * Returns the y-scale
     * 
     * @return the y-scale
     */
    float getYScale();
    
    /**
     * Returns the z-scale
     * 
     * @return the z-scale
     */
    float getZScale();

    /**
     * updates from the registered effectors
     */
    virtual void updateFromEffectors();
   
    /**
     * updates the registered sensors
     */
    virtual void updateSensors();
    
    /**
     * Sets a ISensor which is handled by the updateSensors.
     */     
    void setCollisionSensor(ISensor* sensor);   
    
    /**
     * Sets a ISensor which is handled by the updateSensors.
     */    
    void setForceSensor(ISensor* sensor);   

    /**
     * Increments the internal body collision counter.
     */
    void incCollisionCounter();
    
    /**
     * Sets the internal body collision counter to zero.
     */   
    void resetCollisionCounter();
   
    /**
     * This method does all the OgreOde stuff.
     * 
     * This method musst set the Body the Ogre::Entity, the OgreOde::Body
     * and the OgreOde::SceneNode.
     * 
     * @param space The space in which the segment has to be added.
     */
    virtual void initSegment(OgreOde::Space* space) = 0;

protected:

    /**
     * The scale values of all three dimensions.
     */
     float xScale, yScale, zScale;

    /**
     * Sets the Ogre::Entity* of the segment.
     *
     * Setting this method is mandatory! 
     * @param e The Ogre::Entity* of the segment.
     */
    void setOgreEntity(Ogre::Entity* e);
    
    /**
     * Sets the Ogre::Entity* of the segment.
     *
     * Setting this method is mandatory! 
     * @param s The Ogre::Entity* of the segment.
     */
     void setSceneNode(SceneNode* s);
    
    /**
     * sets the Ogre::Entity* of the segment.
     *
     * Setting this method is mandatory!  
     * @param b The Ogre::Entity* of the segment.
     */
     void setOgreBody(OgreOde::Body* b);


private : 
    /**
     * The orientation of the Body
     */
    Quaternion orientation;
    
    /**
     * The physical mass of the segment
     */
     float mass;
     
    /**
     * The runnable state
     */
     bool isRunnable;
     
    /**
     * Defines if the Body is runable or not.
     * 
     * @param b The new runnable state.
     */
    void setIsRunnable(bool b);

    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */   
    BodySegment(); 
    
    /**
     * The Body the BodySegment belongs to.
     */
    Body* owner;

    /**
     * The name of the BodySegment.
     */
    std::string name;
    
    /**
     * The filename of the mesh file
     */
    std::string meshFile;
    
    /**
     * The graphical representation in of the BodySegment in the world.
     */
    Ogre::Entity* entity;

    /**
     * The OgreOde::SceneNode
     */
    SceneNode* sceneNode;

    /**
     * The physical representation in of the BodySegment in the world.
     */
    OgreOde::Body* body; 

    /**
     * The geometry of the OgreOde::Body.
     */    
    OgreOde::Geometry* geom;
    
    /**
     * The position of the BodySegment.
     */
    Position* position; 

    /**
     * The eventually registered coollision ISensor.
     */
    ISensor* collisionSensor;

    /**
     * The eventually registered force ISensor.
     */
    ISensor* forceSensor;

    /**
     * This count of the collision sience last resetCollisionCounter() .
     */
    long collisionCount;
};

}

#endif //_BODYSEGMENT_H_
