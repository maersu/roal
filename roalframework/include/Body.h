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
#ifndef _BODY_H_
#define _BODY_H_

#include <map>
#include "Position.h"
#include "BodySegment.h"
#include "Joint.h"
#include "Phenotype.h"
#include "IEffector.h"
#include "ISensor.h"
#include "IStandaloneSensor.h"
#include "MovableText.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
class BodySegment; // Forward declaration of BodySegment
class Joint; // Forward declaration of BodySegment

/**
 * The Body is a creature's graphical and physical representation.
 * 
 * The body is a container for BodySegment, Joint and Phenotype objects. 
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class Body
{
public:
    /**
     * Constructor
     * 
     * @param name see Body::name
     * @param pos see Body::position
     */
	Body(const std::string name, Position* pos);
    
    /**
     * Destructor 
     */
	virtual ~Body();

    /**
     * Sets the position of the Body in the world.
     * 
     * @param x The x coordinate of the Body.
     * @param y The y coordinate of the Body.
     * @param z The z coordinate of the Body.
     */
    void setPosition(float x, float y, float z);
    
    /**
     * Returns the Position of the Body in the world.
     * 
     * @return the Position of the Body in the world.
     */
	Position* getPosition();
               
    /**
     * Sets the orientation of the Body in the world.
     * 
     * @param ori A Quaternion that defines the orientation of the Body.
     */   
    void setOrientation(const Quaternion &ori);
    
    /**
     * Returns the orientation of the body in the world.
     * 
     * @return a Quaternion that defines the orientation of the Body.
     */
    Quaternion getOrientation();

    /**
     * Sets the name of the Body.
     * 
     * Sets the name of the Body. 
     * 
     * @warning In a running simulation use this function at your own risk!
     * Because this name is used to register the body in the World
     * 
     * @param name see Body::name
     */   
    void setName(const std::string name);
    
    /**
     * Returns the name of the Body.
     * 
     * @return the name of the Body.
     */
    std::string getName();
    
    /**
     * Sets the movable text caption above the body.
     */
    void setMovableTextCaption(string caption);
    
    /**
     * Sets the movable text above the body visible or not.
     */
    void setMovableTextVisible(bool flag);
    
    /**
     * Returns whether the movable text above the body is visible or not.
     */
    bool isMovableTextVisible();
    
    /**
     * Returns the BodySegment of the Body.
     * 
     * @return the BodySegment of the Body.
     */
    BodySegment* getPositionSegment(); 
    
    /**
     * Returns the runnable state of the Body.
     * 
     * @return the runnable state of the Body.
     */
    bool getIsRunnable(); 

    /**
     * Collision Callback.
     * 
     * This method is called when a Collision occurs.
     * At least one of the Roal::BodySegment is owned by this Body.
     * Its not shure that both of them holds valid pointer! you hav to verfiy!
     * e.g one segment Colide with the Terrain or a userdified body...
     * 
     * @param contact the OgreOde::Contact* Object. This holds a lot of prameters
     * @param segment1 this segment is one of this body ()
     * @param segment1 another involved Segment object
     * 
     * @return true if the collision must be handled.
     */   
    virtual bool handleCollision(OgreOde::Contact* contact, 
                    Roal::BodySegment* segment1, Roal::BodySegment* segment2);

    /**
     * Returns the BodySegment objects.
     * 
     * @return the BodySegment objects.
     */
     std::map<std::string,Roal::BodySegment*> getBodySegments();

    /**
     * Returns the Joint objects that connect the BodySegment objects.
     * 
     * @return the Joint objects that connect the BodySegment objects.
     */    
    std::vector<Roal::Joint*> getJoints(); 

    /**
     * Sets the Position BodySegment which is used to define the 
     * Position and Orientation in the World.
     * 
     * @param node A BodySegment to add to the Body.
     */
    void setPositionSegment(BodySegment* node); 

    /**
     * A Collision of the given BodySegment objects does not have any influence
     * 
     * @param segment1 a BodySegment
     * @param segment2 a BodySegment
     */
    void ignoreCollision(BodySegment* segment1, BodySegment* segment2);
    
    /**
     * Adds a Joint to the the Body.
     *
     * @warning There is no test if the joint is already registered.
     * 
     * @param joint A Joint to add to the the Body.
 	 */
    Joint* registerJoint(Joint* joint);
 	 
    /**
     * Adds a BodySegment to the Body.
     * 
     * @param segment a BodySegment to add to the Body.
     * 
     * @exception RoalException
     */
    BodySegment* registerSegment(BodySegment* segment);

    /**
     * Sets the Emergency state of the Body.
     *
     * @param b the new state. True means that every iteration the owner Agent should 
     * checks if there was an unexpected behaviour of this body.  
     */
    void setCheckEmergency(bool b);

    /**
     * returns the Emergency state of the body
     */
    bool getCheckEmergency();

    /**
     * Updates all registered Sensor of the Body.
     *
     * This method calls the BodySegment::updateSensors() and IStandaloneSensor::update()
     * method of the registered BodySegment objects and IStandaloneSensor objects.
     */
    void updateSensors();
    

    /**
     * Updates the body from the given Effectors. 
     *
     * This method calls the BodySegment::updateFromEffectors() and Joint::updateFromEffectors()
     * method of the registered BodySegment objects and IStandaloneSensor objects.
     */    
     void updateFromEffectors();
    
    /**
     * Sets the Phenotype object that contains the genetic information.
     * @warning the correctnes of the Phenotype object will not be verfied.
     * 
     * @param phenotype The Phenotype object that contains the genetic information.
     */
    virtual void setPhenotype(Phenotype* newPhenotype);
    
    /**
     * Returns the Phenotype object that contains the genetic information.
     * @warning the correctnes of the Phenotype object is not verfied.
     * 
     * @return the Phenotype object that contains the genetic information.
     */
    virtual Phenotype* getPhenotype();

    /**
     * Registers a IEffector.
     *
     * This Effector is handled by Body::updateFromEffectors().
     *
     * @param name a unique name of the effector.
     * @param effector the effector to register.
     *
     * @exception RoalException in case a effector with this name does alreay exists
     */
    void registerEffector(string name, IEffector* effector);
  
    /**
     * Rreturns a IEffector from the given name.
     *
     * @param name the unique name of the effector.
     * @return the required IEffector.
     *
     * @exception RoalException in case the effector with this name does not exists
     */      
    IEffector* getEffector(string name);
    
    /**
     * Registers a ISensor.
     *
     * This Sensor is handled by Body::updateSensors().
     *
     * @param name a unique name of the sensor.
     * @param sensor the sensor to register
     *
     * @exception RoalException in case a sensor with this name does alreay exists.
     */    
    void registerSensor(string name, ISensor* sensor);

    /**
     * Returns ISensor and IStandaloneSensor with the given name.
     *
     * @param name the unique name of the sensor.
     * @return the required ISensor or IStandaloneSensor.
     *
     * @exception RoalException in case the sensor with this name does not exists
     */     
    ISensor* getSensor(string name);
    
    /**
     * Registers a IStandaloneSensor.
     *
     * This Sensor is handled by Body::updateSensors().
     *
     * @param name a unique name of the sensor.
     * @param sensor the sensor to register.
     *
     * @exception RoalException in case a sensor with this name does alreay exists.
     */
    void registerStandaloneSensor(string name, IStandaloneSensor* sensor);
     
    /**
     * Increments the internal body collision counter.
     */
    void incCollisionCounter();
    
    /**
     * Sets the internal body collision counter to zero.
     */
    void resetCollisionCounter();
    
    /**
     * Returns the internal collision count.
     *
     * @warning if the collision count is equal to LONG_MAX the value of the 
     * counter is LONG_MAX or more.
     *
     * @return the internal collision count.
     */
    unsigned long getCollisionCount();

    /**
     * Returns a string with the values of the registered sensors.
     */
    string getSensorInfoString(string valueDelimiter, string separator);


protected:      
  
    /**
     * The name of the Body
     */ 
    std::string name;
    
    /**
     * The orientation of the Body
     */
    Quaternion orientation;
    
    /**
     * The position of the Body
     */
    Position* position;
	
private:
    
    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */   
    Body(); 

    /**
     * Map to hold the BodySegment objects
     */
    typedef std::map<std::string, BodySegment*> SegmentMap;
    SegmentMap segments;
 	
    /**
     *  Vector to hold the Joint objects
     */
    std::vector<Joint*> joints; 
 
    /**
     * A tuple of this do not any collision handling.
     * Stored in the form "bodySegmentName1+bodySegmentName2"
     */
    std::vector<string> ignoreSegs;
	
    /**
     * The runnable state
     */
    bool isRunnable;
 	
    /**
     * Defines if the Body is runnable or not
     * 
     * @param b defines if the Body is runnable or not
     */
    void setIsRunnable(bool b);
    
    /**
     * The position of the Body
     */
    BodySegment* positionSegment;
    
    /**
     * Holds emergency state
     */
    bool checkEmergency;

    /**
     * The registered Phenotype object.
     */
    Phenotype* phenotype;
    
    /**
     * This map holds all registered IEffector objects.
     */    
    std::map<std::string, IEffector*> effectorMap;
    
    /**
     * This map holds all registered ISensor objects.
     */
    std::map<std::string, ISensor*> sensorMap;

    /**
     * This map holds all registered IStandaloneSensor objects.
     */
    std::map<std::string, IStandaloneSensor*> standaloneSensorMap;

    /**
     * This count of the collision sience last resetCollisionCounter() .
     */
    unsigned long collisionCount;

    /**
     * The text displayed in the Ogre world.
     */       
    MovableText* movableText;

};

}

#endif //_BODY_H_
