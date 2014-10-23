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

#include "Walker.h"

#define RAND_TEXTURE textures[(int)(28*(rand()/(double)RAND_MAX))]

namespace Roal
{

//------------------------------------------------------------------------------
Walker::Walker(const std::string name, Position* pos)
:Body(name, pos)
{

    // Available textures
    string textures[28] = {"mat001.mesh", "mat002.mesh", "mat003.mesh", "mat004.mesh",
                          "mat005.mesh", "mat006.mesh", "mat007.mesh", "mat008.mesh",
                          "mat009.mesh", "mat010.mesh", "mat011.mesh", "mat012.mesh",
                          "mat013.mesh", "mat014.mesh", "mat015.mesh", "mat016.mesh",
                          "mat017.mesh", "mat018.mesh", "mat019.mesh", "mat020.mesh",
                          "mat021.mesh", "mat022.mesh", "mat023.mesh", "mat024.mesh",
                          "mat025.mesh", "mat026.mesh", "mat027.mesh", "mat028.mesh"};
    
    // Create and register
    corpus = new CubeSegment(this, name+"_corpus", RAND_TEXTURE);
    this->registerSegment(corpus);
    
    string legTexture = RAND_TEXTURE;
    
    upperarm1 =  new CubeSegment(this,name+"_upperarm1", legTexture);
    this->registerSegment(upperarm1);
    forearm1 =  new Roal::CubeSegment(this, name+"forearm1", legTexture);
    this->registerSegment(forearm1);
    
    upperarm2 =  new CubeSegment(this, name+"_upperarm2", legTexture);
    this->registerSegment(upperarm2);
    forearm2 =  new CubeSegment(this, name+"forearm2", legTexture);
    this->registerSegment(forearm2);
    
    upperarm3 =  new CubeSegment(this, name+"_upperarm3", legTexture);
    this->registerSegment(upperarm3);
    forearm3 =  new CubeSegment(this, name+"forearm3", legTexture);
    this->registerSegment(forearm3);
    
    upperarm4 =  new CubeSegment(this, name+"_upperarm4", legTexture);
    this->registerSegment(upperarm4);
    forearm4 =  new CubeSegment(this, name+"forearm4", legTexture);
    this->registerSegment(forearm4);
     
    // Get destination position of the whole body
    float x = this->getPosition()->getX();
    float y = this->getPosition()->getY();
    float z = this->getPosition()->getZ();

    // Set the masses
    corpus->setMass(0.1);
    upperarm1->setMass(0.1);
    forearm1->setMass(0.1);
    upperarm2->setMass(0.1);
    forearm2->setMass(0.1);
    upperarm3->setMass(0.1);
    forearm3->setMass(0.1);
    upperarm4->setMass(0.1);
    forearm4->setMass(0.1);
    
    // Define the sizes
    float bodyWidth = 1;
    float bodyHeight = 0.3;
    float bodyLength = 2;
    
    float armWidth = 0.25;
    float armHeight = 0.25;
    float armLength = 0.5;
    
    // Define transitions of the segments
    float armZTrans = 1.7; // z-Transition of the arm from the corpus center
    float armYTrans = 0.1; // y-Transition of the arm from the corpus center
    float axleBreach = 1.1; // Breach between corpus and upperarm
    float elbowBreach = 0.8; // Breach between upperarm and forearm
 
    // Set scales
    corpus->setScale(bodyWidth, bodyHeight, bodyLength);
    
    upperarm1->setScale(armLength, armHeight, armWidth);
    forearm1->setScale(armLength, armHeight, armWidth);
    
    upperarm2->setScale(armLength, armHeight, armWidth);
    forearm2->setScale(armLength, armHeight, armWidth);
    
    upperarm3->setScale(armLength, armHeight, armWidth);
    forearm3->setScale(armLength, armHeight, armWidth);
    
    upperarm4->setScale(armLength, armHeight, armWidth);
    forearm4->setScale(armLength, armHeight, armWidth);
    
    // Set the position of the arms relative to the corpus position
    corpus->setPosition(x, y, z);
    upperarm1->setPosition(x + bodyWidth/2 + armLength/2 + axleBreach,
                           y+armYTrans, z+armZTrans);
    forearm1->setPosition(x + bodyWidth/2 + 1.5*armLength + axleBreach + elbowBreach,
                          y+armYTrans, z+armZTrans);
    
    upperarm2->setPosition(x - bodyWidth/2 - armLength/2 - axleBreach,
                           y+armYTrans, z+armZTrans);
    forearm2->setPosition(x - bodyWidth/2 - 1.5*armLength - axleBreach - elbowBreach,
                          y+armYTrans, z+armZTrans);
    
    upperarm3->setPosition(x + bodyWidth/2 + armLength/2 + axleBreach,
                           y+armYTrans, z-armZTrans);
    forearm3->setPosition(x + bodyWidth/2 + 1.5*armLength + axleBreach + elbowBreach,
                          y+armYTrans, z-armZTrans);
    
    upperarm4->setPosition(x - bodyWidth/2 - armLength/2 - axleBreach,
                           y+armYTrans, z-armZTrans);
    forearm4->setPosition(x - bodyWidth/2 - 1.5*armLength - axleBreach - elbowBreach,
                          y+armYTrans, z-armZTrans);
    
    // Define joints
    axle1 = new HingeJoint(new Position(x + bodyWidth/2 + axleBreach/2,
                                        y+armYTrans, z+armZTrans));
    this->registerJoint(axle1);
    axle1->attach(corpus, upperarm1);
    axle1->setAxis(Vector3(0,1,0));
    
    elbow1 = new HingeJoint(new Position(x + bodyWidth/2 + armLength + axleBreach
                                         + elbowBreach/2, y+armYTrans, z+armZTrans));
    this->registerJoint(elbow1);
    elbow1->attach(upperarm1, forearm1);
    elbow1->setAxis(Vector3(0,0,1));
    elbow1->setLowHighStop(0.0,1.5);
    
    axle2 = new HingeJoint(new Position(x - bodyWidth/2 - axleBreach/2,
                                        y+armYTrans, z+armZTrans));
    this->registerJoint(axle2);
    axle2->attach(corpus, upperarm2);
    axle2->setAxis(Vector3(0,1,0));
    
    elbow2 = new HingeJoint(new Position(x - bodyWidth/2 - armLength - axleBreach
                                         - elbowBreach/2, y+armYTrans, z+armZTrans));
    this->registerJoint(elbow2);
    elbow2->attach(upperarm2, forearm2);
    elbow2->setAxis(Vector3(0,0,1));
    elbow2->setLowHighStop(-1.5,0.0);
    
    axle3 = new HingeJoint(new Position(x + bodyWidth/2 + axleBreach/2,
                                        y+armYTrans, z-armZTrans));
    this->registerJoint(axle3);
    axle3->attach(corpus, upperarm3);
    axle3->setAxis(Vector3(0,1,0));
    
    elbow3 = new HingeJoint(new Position(x + bodyWidth/2 + armLength + axleBreach
                                         + elbowBreach/2, y+armYTrans, z-armZTrans));
    this->registerJoint(elbow3);
    elbow3->attach(upperarm3, forearm3);
    elbow3->setAxis(Vector3(0,0,1));
    elbow3->setLowHighStop(0.0,1.5); 
 
    axle4 = new HingeJoint(new Position(x - bodyWidth/2 - axleBreach/2,
                                        y+armYTrans, z-armZTrans));
    this->registerJoint(axle4);
    axle4->attach(corpus, upperarm4);
    axle4->setAxis(Vector3(0,1,0));
    
    elbow4 = new HingeJoint(new Position(x - bodyWidth/2 - armLength - axleBreach
                                         - elbowBreach/2, y+armYTrans, z-armZTrans));
    this->registerJoint(elbow4);
    elbow4->attach(upperarm4, forearm4);
    elbow4->setAxis(Vector3(0,0,1));
    elbow4->setLowHighStop(-1.5,0.0); 
    
    travelledDistance = 0;
    this->lastPosition = this->getPosition();
    
    // Set the position segment of the corpus
    this->setPositionSegment(corpus);
}


//------------------------------------------------------------------------------
Walker::~Walker()
{
// do not delete bodysegments and joint this is done by the Body Class Destructor
}


//------------------------------------------------------------------------------
void Walker::setElbow1Torque(float torqueX, float torqueY, float torqueZ)
{
    elbow1->addTorque(torqueX, torqueY, torqueZ);
}


//------------------------------------------------------------------------------
void Walker::setElbow2Torque(float torqueX, float torqueY, float torqueZ)
{
    elbow2->addTorque(torqueX, torqueY, torqueZ);
}


//------------------------------------------------------------------------------
void Walker::setElbow3Torque(float torqueX, float torqueY, float torqueZ)
{
    elbow3->addTorque(torqueX, torqueY, torqueZ);
}


//------------------------------------------------------------------------------
void Walker::setElbow4Torque(float torqueX, float torqueY, float torqueZ)
{
    elbow4->addTorque(torqueX, torqueY, torqueZ);
}



//------------------------------------------------------------------------------
void Walker::setAxle1Torque(float torqueX, float torqueY, float torqueZ)
{
    axle1->addTorque(torqueX, torqueY, torqueZ);
}


//------------------------------------------------------------------------------
void Walker::setAxle2Torque(float torqueX, float torqueY, float torqueZ)
{
    axle2->addTorque(torqueX, torqueY, torqueZ);
}


//------------------------------------------------------------------------------
void Walker::setAxle3Torque(float torqueX, float torqueY, float torqueZ)
{
    axle3->addTorque(torqueX, torqueY, torqueZ);
}


//------------------------------------------------------------------------------
void Walker::setAxle4Torque(float torqueX, float torqueY, float torqueZ)
{
    axle4->addTorque(torqueX, torqueY, torqueZ);
}


//------------------------------------------------------------------------------
float Walker::getElbow1Angle()
{
    return this->elbow1->getAngle();
}


//------------------------------------------------------------------------------
float Walker::getElbow2Angle()
{
    return this->elbow2->getAngle();
}


//------------------------------------------------------------------------------
float Walker::getElbow3Angle()
{
    return this->elbow3->getAngle();
}


//------------------------------------------------------------------------------
float Walker::getElbow4Angle()
{
    return this->elbow4->getAngle();
}


//------------------------------------------------------------------------------
float Walker::getAxle1Angle()
{
    return this->axle1->getAngle();
}


//------------------------------------------------------------------------------
float Walker::getAxle2Angle()
{
    return this->axle2->getAngle();
}


//------------------------------------------------------------------------------
float Walker::getAxle3Angle()
{
    return this->axle3->getAngle();
}


//------------------------------------------------------------------------------
float Walker::getAxle4Angle()
{
    return this->axle4->getAngle();
}


//------------------------------------------------------------------------------
float Walker::getDistanceTravelled()
{
    this->updateDistanceTravelled();
    return this->travelledDistance;
}


//------------------------------------------------------------------------------
void Walker::resetDistanceTravelled()
{
    this->travelledDistance = 0.0;
    this->lastPosition = this->getPosition();
}


//------------------------------------------------------------------------------
void Walker::updateDistanceTravelled()
{
   float x = lastPosition->getX();
   float z = lastPosition->getZ();
   
   travelledDistance = travelledDistance + (this->getPosition())->getPlanarDistanceTo(x,z);
   this->lastPosition = this->getPosition();
}

};
