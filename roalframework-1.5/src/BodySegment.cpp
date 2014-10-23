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
#include "BodySegment.h"
namespace Roal
{

//------------------------------------------------------------------------------
BodySegment::BodySegment(Roal::Body* owner, std::string name, std::string meshFile)
{
    this->owner = owner;
    this->name = name;
    this->meshFile = meshFile;
    
    entity = 0;
    sceneNode = 0;
    body = 0; 
    collisionSensor = 0;
    forceSensor = 0;
    
    
    this->setMass(1.0);
    this->setIsRunnable(false);
    
    position = new Roal::Position(0,0,0);  
    
    resetCollisionCounter();
    
}

//------------------------------------------------------------------------------
BodySegment::~BodySegment()
{
    //unregister from OgreOde and delete  
    OgreOde::World::getSingleton().getSceneManager()->getRootSceneNode()->removeAndDestroyChild( this->name);
    if (body) {
       delete body;
    }
    
    if (geom) {
       delete geom;
    }
    
    if (entity) {
        delete entity;
    }
    
    if (collisionSensor) {
        delete collisionSensor;
    }
    
    if (forceSensor) {
        delete forceSensor;
    }
}

//------------------------------------------------------------------------------
void BodySegment::setIsRunnable(bool b)
{
    this->isRunnable = b;
}

//------------------------------------------------------------------------------
bool BodySegment::getIsRunnable()
{
    return this->isRunnable;
}

//------------------------------------------------------------------------------
void BodySegment::setMass(float mass)
{
    this->mass = mass;
}

//------------------------------------------------------------------------------
float BodySegment::getMass()
{
    return this->mass;
}


//------------------------------------------------------------------------------
void BodySegment::setPosition(float x, float y, float z)
{
    this->position->setX(x);
    this->position->setY(y);
    this->position->setZ(z);

    if (this->getIsRunnable()){
      this->getSceneNode()->setPosition(this->getPosition()->getAsVector());
    }
}

  
//------------------------------------------------------------------------------
Roal::Position* BodySegment::getPosition()
{  
   
    if (this->getIsRunnable()) {
         
        //get the position of the SceneNode in Ogre
        Vector3 vec = this->getSceneNode()->getPosition();
        
        float x = (vec*Vector3(1,0,0)).normalise();
        float y = (vec*Vector3(0,1,0)).normalise();
        float z = (vec*Vector3(0,0,1)).normalise();
    
        this->position->setX(x);
        this->position->setY(y);
        this->position->setZ(z);
    }
   
    
    return this->position;
}

//------------------------------------------------------------------------------
Roal::Body* BodySegment::getOwner()
{
    return this->owner;
}
    
//------------------------------------------------------------------------------
std::string BodySegment::getName()
{
    return this->name;
}
     
//------------------------------------------------------------------------------
Ogre::Entity* BodySegment::getOgreEntity()
{
    if (entity == 0) {
        throw(RoalException(typeid( this ).name(),"No OgreEntity set for "+this->getName()));
    }
    return entity;
}
    
//------------------------------------------------------------------------------
SceneNode* BodySegment::getSceneNode()
{
    if (sceneNode == 0) {
        throw(RoalException(typeid( this ).name(),"No OgreSceneNode set for "+this->getName()));
    }
    return sceneNode;
}
    
//------------------------------------------------------------------------------
OgreOde::Body* BodySegment::getOgreBody()
{
    if (body == 0) {
        throw(RoalException(typeid( this ).name(),"No OgreBody set for "+this->getName()));
    }
    return body;
}

//------------------------------------------------------------------------------
OgreOde::Geometry*  BodySegment::getOgreGeometry()
{
    if (geom == 0) {
        throw(RoalException(typeid( this ).name(),"No OgreGeometry set for "+this->getName()));
    }
    return geom;
}


//------------------------------------------------------------------------------
void BodySegment::setOgreEntity(Ogre::Entity* e)
{
    this->entity = e;
    //Decide if the Segment is runable or not
    if (entity !=0 and sceneNode !=0 and body !=0){
        this->setIsRunnable(true);
    }
}
    
//------------------------------------------------------------------------------
void BodySegment::setSceneNode(SceneNode* s)
{
   
    this->sceneNode = s;
    
    //Decide if the Segment is runable or not
    if (entity !=0 and sceneNode !=0 and body !=0){
        this->setIsRunnable(true);
    }
}
    
//------------------------------------------------------------------------------
void BodySegment::setOgreBody(OgreOde::Body* b)
{
    this->body = b;
    geom = body->getGeometry(body->getGeometryCount()-1);
    //Decide if the Segment is runable or not
    if (entity !=0 and sceneNode !=0 and body !=0){
        this->setIsRunnable(true);
    }
}
  
    
//------------------------------------------------------------------------------
void BodySegment::addForce(const Vector3 &force)
{
    if (this->getIsRunnable()) {
        body->addForce(force);
    }
}   

 
//------------------------------------------------------------------------------
void BodySegment::addTorque(const Vector3 &torque)
{
    if (this->getIsRunnable()) {
        body->addTorque(torque);
    }
}  
 
  
//------------------------------------------------------------------------------  
const Vector3 BodySegment::getForce()
{
    if (this->getIsRunnable()) {
        return body->getForce();
    }
    return Vector3(0,0,0);
}
//------------------------------------------------------------------------------
const Vector3 BodySegment::getTorque()  
{
    if (this->getIsRunnable()) {
        return body->getTorque();
    }
    return Vector3(0,0,0);     
}

//------------------------------------------------------------------------------
std::string BodySegment::getMeshFile()
{
    return this->meshFile;
} 

//------------------------------------------------------------------------------
void BodySegment::setOrientation(const Quaternion &ori)
{
    if (this->getIsRunnable()) {
        return body->setOrientation(ori);
    }
    this->orientation = ori; 
}

   
//------------------------------------------------------------------------------
Quaternion BodySegment::getOrientation()
{
    if (this->getIsRunnable()) {
        return body->getOrientation();
    }
    return this->orientation;
}  

//------------------------------------------------------------------------------
float BodySegment::getXScale()
{
    return this->xScale;
}

    
//------------------------------------------------------------------------------
float BodySegment::getYScale()
{
    return this->yScale;
}


    
//------------------------------------------------------------------------------
float BodySegment::getZScale()
{
    return this->zScale;
}

//------------------------------------------------------------------------------
void BodySegment::updateFromEffectors()
{

}

//------------------------------------------------------------------------------
void BodySegment::updateSensors()
{	
    if (collisionSensor) 
    {
        collisionSensor->setValue(collisionCount);
    }
    
    if (forceSensor) 
    {
        Vector3 vec = this->getForce();
        collisionSensor->setValue(vec.normalise());
    }
}

//------------------------------------------------------------------------------
void BodySegment::setCollisionSensor(ISensor* sensor)
{
  this->collisionSensor = sensor;
}

//------------------------------------------------------------------------------
void BodySegment::setForceSensor(ISensor* sensor)
{
  this->forceSensor = sensor;
}

//------------------------------------------------------------------------------
void BodySegment::incCollisionCounter()
{    
    if (collisionCount < ULONG_MAX)
    {
        collisionCount++;
    }
}

//------------------------------------------------------------------------------
void BodySegment::resetCollisionCounter()
{
    collisionCount = 0;
}

};
