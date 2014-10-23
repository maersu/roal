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
#include "CubeSegment.h"

using namespace std;

namespace Roal
{
//------------------------------------------------------------------------------
CubeSegment::CubeSegment(Roal::Body* owner, std::string name, std::string meshFile)
:BodySegment(owner,name,meshFile)
{
}


//------------------------------------------------------------------------------
CubeSegment::~CubeSegment()
{
}


//------------------------------------------------------------------------------
void CubeSegment::initSegment(OgreOde::Space* space)
{
    // Visuals (Ogre Stuff)
    Ogre::Entity* entity = OgreOde::World::getSingleton().getSceneManager()
                    ->createEntity(this->getName(),this->getMeshFile());
    entity->setNormaliseNormals(true);
    entity->setCastShadows(true);

    SceneNode* node = OgreOde::World::getSingleton().getSceneManager()
                    ->getRootSceneNode()->createChildSceneNode(entity->getName());
    node->attachObject(entity);
    node->setScale(this->getXScale(),this->getYScale(),this->getZScale());
    node->setPosition(Vector3(this->getPosition()->getX(),this
                    ->getPosition()->getY(),this->getPosition()->getZ()));
    
    // Physicals (OgreOde Stuff)
    OgreOde::EntityInformer ei(entity,Matrix4::getScale(node->getScale()));
    OgreOde::Body* body = ei.createSingleDynamicBox(this->getMass(),space); 
  
    
    //Set the required OgreOde stuff. This is is mandatory if you want to update
    //the Segment during the Simulation or getting current positio and stuff like that 
    this->setOgreEntity(entity);
    this->setSceneNode(node);
    this->setOgreBody(body);
}


//------------------------------------------------------------------------------
void CubeSegment::setScale(float x, float y, float z)
{
   this->xScale = x; 
   this->yScale = y;     
   this->zScale = z; 
   if (this->getIsRunnable()) {
 
     this->getSceneNode()->setScale(this->getXScale(),this->getYScale(),this->getZScale());
     this->getOgreBody()->setMass(OgreOde::BoxMass(this->getMass(), 
                    Vector3(this->getXScale(),this->getYScale(),this->getZScale())));
   }     
  
}  

     
}
