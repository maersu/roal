/**     
    This file is part of Roal, a framework for simulations in the field
    of Artificial Intelligence and Aritificial Life.
    See http://roal.sourceforge.net/ for more informations.

    Copyright (c) 2005 Project Roal

    Roal is free software; you can redistribute it and/or modify
    it under the terms of the GNU Genweehleral Public License as published by
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

#include "Cage.h"

namespace Roal
{

//------------------------------------------------------------------------------
Cage::Cage(const std::string name, Position* pos, string meshFile, 
        float wallLength, float wallHight, float wallWidth)
        :Body(name, pos)
{	    
   /* 
    float wallHight = 5; 
    float wallWidth = 2; 
    */
    float mass = 80.0;
    
    // creaturess walls
    cs1 = new CubeSegment(this,name+"_cs1", meshFile);    
    cs1->setPosition(pos->getX(),pos->getY()+wallHight/2.0+1,pos->getZ()+wallLength/2.0);
    cs1->setScale(wallLength/2.0,wallHight/2.0,wallWidth/2.0);
    cs1->setMass(mass);     
    this->registerSegment(cs1);
    
    cs2 = new CubeSegment(this,name+"_cs2", meshFile);   
    cs2->setPosition(pos->getX()+wallLength/2.0,pos->getY()+wallHight/2.0+1,pos->getZ());
    cs2->setScale(wallWidth/2.0,wallHight/2.0,wallLength/2.0-1.1*wallWidth);
    cs2->setMass(mass);  
    this->registerSegment(cs2);
    
    cs3 = new CubeSegment(this,name+"_cs3", meshFile);   
    cs3->setPosition(pos->getX(),pos->getY()+wallHight/2.0+1,pos->getZ()-wallLength/2.0);
    cs3->setScale(wallLength/2.0,wallHight/2.0,wallWidth/2.0); 
    cs3->setMass(mass); 
    this->registerSegment(cs3);
    
    cs4 = new CubeSegment(this,name+"_cs4", meshFile);   
    cs4->setPosition(pos->getX()-wallLength/2.0,pos->getY()+wallHight/2.+1,pos->getZ());
    cs4->setScale(wallWidth/2.0,wallHight/2.0,wallLength/2.0-1.1*wallWidth); 
    cs4->setMass(mass); 
    this->registerSegment(cs4);
    
    // foots
    foot1 = new CubeSegment(this,name+"_foot1", meshFile); 
    foot1->setPosition(pos->getX()+wallLength/2.0,pos->getY(),pos->getZ()+wallLength/2.0);
    foot1->setScale(2.0*wallWidth,0.1,2.0*wallWidth);
    this->registerSegment(foot1);   
    
    foot2 = new CubeSegment(this,name+"_foot2", meshFile); 
    foot2->setPosition(pos->getX()+wallLength/2.0,pos->getY(),pos->getZ()-wallLength/2.0);
    foot2->setScale(2.0*wallWidth,0.1,2.0*wallWidth);
    this->registerSegment(foot2); 
    
    foot3 = new CubeSegment(this,name+"_foot3", meshFile); 
    foot3->setPosition(pos->getX()-wallLength/2.0,pos->getY(),pos->getZ()-wallLength/2.0);
    foot3->setScale(2.0*wallWidth,0.1,2.0*wallWidth);
    this->registerSegment(foot3); 
    
    foot4 = new CubeSegment(this,name+"_foot4", meshFile); 
    foot4->setPosition(pos->getX()-wallLength/2.0,pos->getY(),pos->getZ()+wallLength/2.0);
    foot4->setScale(2.0*wallWidth,0.1,2.0*wallWidth);
    this->registerSegment(foot4); 
   
    //foot-wall fixer
    fixFoot12 = new FixedJoint(new Position(pos->getX()+wallLength/2.0,pos->getY()+0.15,pos->getZ()+wallLength/2.0));
    fixFoot12->attach(cs2, foot1);
    fixFoot12->setAxis(Vector3(0,1,0));
    this->registerJoint(fixFoot12);
    
    fixFoot23 = new FixedJoint(new Position(pos->getX()+wallLength/2.0,pos->getY()+0.15,pos->getZ()-wallLength/2.0));
    fixFoot23->attach(cs3, foot2);
    fixFoot23->setAxis(Vector3(0,1,0));
    this->registerJoint(fixFoot23);
    
    fixFoot34 = new FixedJoint(new Position(pos->getX()-wallLength/2.0,pos->getY()+0.15,pos->getZ()-wallLength/2.0));
    fixFoot34->attach(cs4, foot3);
    fixFoot34->setAxis(Vector3(0,1,0));
    this->registerJoint(fixFoot34);
    
    fixFoot41 = new FixedJoint(new Position(pos->getX()-wallLength/2.0,pos->getY()+0.15,pos->getZ()+wallLength/2.0));
    fixFoot41->attach(cs1, foot4);
    fixFoot41->setAxis(Vector3(0,1,0));
    this->registerJoint(fixFoot41);
    
    fixFoot11 = new FixedJoint(new Position(pos->getX()+wallLength/2.0,pos->getY()+0.15,pos->getZ()+wallLength/2.0));
    fixFoot11->attach(cs1, foot1);
    fixFoot11->setAxis(Vector3(0,1,0));
    this->registerJoint(fixFoot11);
    
    fixFoot22 = new FixedJoint(new Position(pos->getX()+wallLength/2.0,pos->getY()+0.15,pos->getZ()-wallLength/2.0));
    fixFoot22->attach(cs2, foot2);
    fixFoot22->setAxis(Vector3(0,1,0));
    this->registerJoint(fixFoot22);
    
    fixFoot33 = new FixedJoint(new Position(pos->getX()-wallLength/2.0,pos->getY()+0.15,pos->getZ()-wallLength/2.0));
    fixFoot33->attach(cs3, foot3);
    fixFoot33->setAxis(Vector3(0,1,0));
    this->registerJoint(fixFoot33);
    
    fixFoot44 = new FixedJoint(new Position(pos->getX()-wallLength/2.0,pos->getY()+0.15,pos->getZ()+wallLength/2.0));
    fixFoot44->attach(cs4, foot4);
    fixFoot44->setAxis(Vector3(0,1,0));
    this->registerJoint(fixFoot44);
    
    
    
}

}
