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

#include "Body.h"

using namespace std;

namespace Roal
{

Body::Body(const std::string name, Roal::Position* pos)
{
    this->setIsRunnable(false);
    this->setName(name);
    position = new Roal::Position(pos); 
    //set some default values. This necessary to avoid runtime errors
    // Set default value. This necessary to avoid runtime errors
    positionSegment = 0;
    movableText = NULL;
    resetCollisionCounter();
    
    setCheckEmergency(true);
}

   
//------------------------------------------------------------------------------
Body::~Body()
{
    delete position;

    for(SegmentMap::iterator it = segments.begin(); it != segments.end(); it++) 
    {
        delete it->second;
    }
    
    for (int i = 0; i<joints.size() ;i++){
         Roal::Joint* j = joints.at(i);
          delete j;
    } 
    
    segments.clear();
    joints.clear();
    
    if (movableText) {
        delete movableText;
    }
}
//------------------------------------------------------------------------------
bool Body::handleCollision(OgreOde::Contact* contact, Roal::BodySegment* segment1, Roal::BodySegment* segment2)
{
    bool handle = true;
   
    // check if there are some igonre cases...    
    if (segment2 && ignoreSegs.size() > 0)
    {
        string ignore_str= ""; 
        if (segment1->getName().compare(segment1->getName()) > 0)
        {
           ignore_str = segment1->getName()+"+"+segment2->getName(); 
        } else {
            ignore_str = segment2->getName()+"+"+segment1->getName(); 
        }  

        string tmp = "";
        
        for (int i = 0; i<ignoreSegs.size() ;i++){
            tmp = ignoreSegs.at(i);
            
            if (tmp.compare(ignore_str) == 0)
            {
                handle = false;
            }
        }
    }
    
    if (handle) //Collision should be handled
    { 
        incCollisionCounter();
        if (segment1) {segment1->incCollisionCounter();}
        if (segment2) {segment2->incCollisionCounter();}
    }
    return handle;
}


//------------------------------------------------------------------------------
void Body::ignoreCollision(BodySegment* segment1, BodySegment* segment2)
{
    string ignore_str= ""; 
    
    if (segment1->getName().compare(segment1->getName()) > 0)
    {
       ignore_str = segment1->getName()+"+"+segment2->getName(); 
    } else {
        ignore_str = segment2->getName()+"+"+segment1->getName(); 
    }
    
    ignoreSegs.push_back(ignore_str);    
}  
//------------------------------------------------------------------------------
void Body::setPosition(float x, float y, float z)
{
    this->position->setX(x);
    this->position->setY(y);
    this->position->setZ(z);
}

  
//------------------------------------------------------------------------------
Roal::Position* Body::getPosition()
{
    if (this->getIsRunnable()) {
        return positionSegment->getPosition();
    }
    return this->position;
}

   
//------------------------------------------------------------------------------
void Body::setOrientation(const Quaternion &ori)
{
    this->orientation = ori; 
}

   
//------------------------------------------------------------------------------
Quaternion Body::getOrientation()
{
    return this->orientation;
}

    
//------------------------------------------------------------------------------
void Body::setName(const std::string name)
{
    this->name = name;
}

//------------------------------------------------------------------------------
void Body::setIsRunnable(bool b)
{
    this->isRunnable = b;
    if (b && !this->movableText) {
        this->movableText = new MovableText(this->getName()+"_msg",
                                            " ", // Emtpy message
                                            "AndaleMono",
                                            16, // Character height
                                            ColourValue::White);
        SceneNode* movableTextNode = this->getPositionSegment()->getSceneNode()
                        ->createChildSceneNode(this->getName()+"_msg_node");
        movableTextNode->attachObject(movableText);
        movableTextNode->setScale(0.1, 0.1, 0.1);
        movableTextNode->setPosition(Vector3(0, 10, 0));
        movableTextNode->setVisible(false); // Don't show per default
    }
}

//------------------------------------------------------------------------------
std::string Body::getName()
{
    return this->name;
}

//------------------------------------------------------------------------------
void Body::setMovableTextCaption(string caption)
{
    if (this->movableText) {
        this->movableText->setCaption(caption);
    }
}

//------------------------------------------------------------------------------
void Body::setMovableTextVisible(bool flag)
{
    if (this->movableText) {
        this->movableText->setVisible(flag);
    }
}

//------------------------------------------------------------------------------
bool Body::isMovableTextVisible()
{
    if (this->movableText) {
        return this->movableText->isVisible();
    } else {
        return false;
    }
}

//------------------------------------------------------------------------------
bool Body::getCheckEmergency()
{
    return this->checkEmergency;
}

//------------------------------------------------------------------------------
void Body::setCheckEmergency(bool b)
{
    this->checkEmergency = b;
}

//------------------------------------------------------------------------------
bool Body::getIsRunnable()
{
    if (positionSegment) {
        this->setIsRunnable(positionSegment->getIsRunnable());
    }
    return this->isRunnable;
}

//------------------------------------------------------------------------------
string Body::getSensorInfoString(string valueDelimiter, string separator)
{
    string valueString;
    //concat all values of the registered sensor
    for(std::map<string, IStandaloneSensor*>::iterator it = standaloneSensorMap.begin(); it != standaloneSensorMap.end(); it++) {
        if (valueString.size() > 0) {
            valueString.append(separator);
        }
        string key = it->first;
        float value = it->second->getValue();
        
        valueString.append(key);
        valueString.append(valueDelimiter);
        valueString.append(toStdStr(value));
    }
        
    for(std::map<string, ISensor*>::iterator it = sensorMap.begin(); it != sensorMap.end(); it++) {
        if (valueString.size() > 0) {
            valueString.append(separator);
        }
        string key = it->first;
        float value = it->second->getValue();
        
        valueString.append(key);
        valueString.append(valueDelimiter);
        valueString.append(toStdStr(value));
    }
    return valueString;
}
//------------------------------------------------------------------------------
void Body::setPositionSegment(BodySegment* positionSegment)
{
    this->positionSegment = positionSegment;
    this->setIsRunnable(positionSegment->getIsRunnable());
}
    

//------------------------------------------------------------------------------
BodySegment* Body::getPositionSegment()
{
    return this->positionSegment;
} 


//------------------------------------------------------------------------------
Roal::Joint* Body::registerJoint(Roal::Joint* joint)
{
   joints.push_back(joint);
   return joint;
}
 	 
 	 
//------------------------------------------------------------------------------
Roal::BodySegment* Body::registerSegment(Roal::BodySegment* segment)
{
    if (segments.count(segment->getName()) > 0) {
       throw(RoalException(typeid(this).name(),
              "A BodySegment with name '"+segment->getName()+"' already exists"));
    } else {
        segments[segment->getName()] =  segment;
    } 

   return segment;
}
 	 
 	 
//------------------------------------------------------------------------------
 std::map<std::string,Roal::BodySegment*>  Body::getBodySegments()
{
    return segments;
}    
 	 
//------------------------------------------------------------------------------
 std::vector<Roal::Joint*> Body::getJoints()  
{
    return joints;
}

 //------------------------------------------------------------------------------
 void Body::updateFromEffectors()
{
    //Call all update methods of the registered objects
    for(SegmentMap::iterator it = segments.begin(); it != segments.end(); it++) 
    {
        it->second->updateFromEffectors();
    } 
    
    for (int i = 0; i<joints.size() ;i++){
         Roal::Joint* j = joints.at(i);
         j->updateFromEffectors();
    }
 }   
//------------------------------------------------------------------------------
void Body::updateSensors()
{
    //Call all update methods of the registered sensors
    for(SegmentMap::iterator it = segments.begin(); it != segments.end(); it++) 
    {
        it->second->updateSensors();
    }  
     
    for (int i = 0; i<joints.size() ;i++){
         Roal::Joint* j = joints.at(i);
         j->updateSensors();
    }
 
    for(std::map<std::string, IStandaloneSensor*>::iterator it = standaloneSensorMap.begin(); 
                it != standaloneSensorMap.end(); it++) 
    {
        it->second->update();
    }      
    
} 
//------------------------------------------------------------------------------
void Body::setPhenotype(Phenotype* newPhenotype) 
{
    this->phenotype = newPhenotype;
}
    
 //------------------------------------------------------------------------------
Phenotype* Body::getPhenotype() 
{
    return this->phenotype;
}

//------------------------------------------------------------------------------
void Body::registerEffector(string name, IEffector* effector)
{
    if (effectorMap.count(name) > 0) {
       throw(RoalException(typeid(this).name(),
              "A Effector with name '"+name+"' already exists"));
    } else {
        effectorMap[name] =  effector;
    }
}

//------------------------------------------------------------------------------
IEffector* Body::getEffector(string name)
{
    if (effectorMap.count(name) > 0) {
       return effectorMap[name];
    } else {
       throw(RoalException(typeid(this).name(),
              "A Effector with name '"+name+"' does not exist"));
    }
}


//------------------------------------------------------------------------------
void Body::registerSensor(string name, ISensor* sensor)
{
    if (sensorMap.count(name) > 0) {
       throw(RoalException(typeid(this).name(),
              "A Sensor with name '"+name+"' already exists"));
    } else {
        sensorMap[name] =  sensor;
    }
}

//------------------------------------------------------------------------------
ISensor* Body::getSensor(string name)
{
    if (sensorMap.count(name) > 0) {
       return sensorMap[name];
    } else if (standaloneSensorMap.count(name) > 0) {
       return standaloneSensorMap[name];
    }  else {
       throw(RoalException(typeid(this).name(),
              "A Sensor with name '"+name+"' does not exist"));
    }
}


//------------------------------------------------------------------------------
void Body::registerStandaloneSensor(string name, IStandaloneSensor* sensor)
{
    if (standaloneSensorMap.count(name) > 0) {
       throw(RoalException(typeid(this).name(),
              "A Sensor with name '"+name+"' already exists"));
    } else {
        standaloneSensorMap[name] =  sensor;
    }
}


//------------------------------------------------------------------------------
void Body::incCollisionCounter()
{
    if (collisionCount < ULONG_MAX)
    {
        collisionCount++;
    }
}

//------------------------------------------------------------------------------
void Body::resetCollisionCounter()
{
    collisionCount = 0;
    
    for(SegmentMap::iterator it = segments.begin(); it != segments.end(); it++) 
    {
        it->second->resetCollisionCounter();
    }  
}

//------------------------------------------------------------------------------    
unsigned long  Body::getCollisionCount()
{
    return collisionCount;
}


};
