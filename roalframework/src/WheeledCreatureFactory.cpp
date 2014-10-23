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

#include "WheeledCreatureFactory.h"
using namespace std;
namespace Roal
{

   
    
//-----------------------------------------------------------------------------
WheeledCreatureFactory::WheeledCreatureFactory(string name, WheeledCreatureGenotype* genotype, 
        Agent* agent)
    : CreatureFactory(name)
{
    this->m_genotype = genotype;
    bodyCnt = 0;   
    this->agent = agent;
}

//-----------------------------------------------------------------------------
WheeledCreatureFactory::WheeledCreatureFactory(string name, Agent* agent)
    : CreatureFactory(name)
{    
    WheeledCreatureGenotype* genotype = new WheeledCreatureGenotype();
    this->m_genotype = genotype;
    bodyCnt = 0; 
    this->agent = agent;    
}


//------------------------------------------------------------------------------
WheeledCreatureFactory::~WheeledCreatureFactory()
{

}

//------------------------------------------------------------------------------
Brain* WheeledCreatureFactory::generateRandomCreature(string name, Position* pos)
{
    Phenotype* phenotype = this->m_genotype->getRandomPhenotype(); 
    return generateCreature(name,pos,phenotype);
}


//------------------------------------------------------------------------------
Brain* WheeledCreatureFactory::generateCreature(string name, Position* pos, Phenotype* phenotype)
{
/*
    Brain* brain = new Brain(name+"_brain");
    brain->setPhenotype(phenotype);
    brain->registerBody(generateBody(name,pos,phenotype));
    brain->resetDistanceTravelled();
    return brain;
*/    
}

//------------------------------------------------------------------------------
Body* WheeledCreatureFactory::generateRandomBody(string name, Position* pos)
{
    Phenotype* phenotype = this->m_genotype->getRandomPhenotype(); 
    return generateBody(name,pos,phenotype);
}    

//------------------------------------------------------------------------------
Body* WheeledCreatureFactory::generateBody(string name, Position* pos, Phenotype* phenotype)
{

    // Get required values
    float x = pos->getX();
    float y = pos->getY();
    float z = pos->getZ();

    float bodyWidth             = phenotype->getValue("bodyWidth");
    float bodyHeight            = phenotype->getValue("bodyHeight");
    float bodyLength            = phenotype->getValue("bodyLength");
    float wheelCount            = phenotype->getValue("wheelCount");
    float hasFrontNbrSensors    = phenotype->getValue("hasFrontNbrSensors");
    float hasBackNbrSensors     = phenotype->getValue("hasBackNbrSensors");
    float hasCollisionCage      = phenotype->getValue("hasCollisionCage");
    float frontNbrSensorsRadius = phenotype->getValue("frontNbrSensorsRadius");
    float backNbrSensorsRadius  = phenotype->getValue("backNbrSensorsRadius");
    float texture               = phenotype->getValue("texture");
    float corpusMass            = phenotype->getValue("corpusMass");
    float wheelMass             = phenotype->getValue("wheelMass");

    float motorBreach = 0.0; // Breach between corpus and weehl
    float wheelRadius = bodyLength*0.35;
    int wheelPerSide = wheelCount/2;
    float distanceBetweenWheels =  (2*bodyLength/(wheelPerSide-1));
    
    // create flags etc.
    int sign = 1; 
    int mul = 1;
    float curZ = z-(bodyLength);

    // increment BodyCount;
    bodyCnt ++;

    //create body
    Body* body = new Body(name+"_body",pos);
    body->setPhenotype(phenotype); 
    
    // Create the corpus
    CubeSegment* corpus = new CubeSegment(body,name+"_corpus", getCubeTextureFileName((int)floor(texture)));
    body->registerSegment(corpus);
    corpus->setMass(corpusMass);
    corpus->setScale(bodyWidth, bodyHeight, bodyLength);    
    corpus->setPosition(x, y, z);
    body->setPositionSegment(corpus);  
    
    IEffector* rightEffector = new IEffector();
    body->registerEffector("rightMotorEffector", rightEffector);
    
    IEffector* leftEffector = new IEffector();
    body->registerEffector("leftMotorEffector", leftEffector); 

    // create wheels
    for (int i = 1; i <= wheelCount; i++)
    {
        if (i == (wheelPerSide+1)) 
        {
            sign = -1;
            mul =2;
            curZ = z-(bodyLength);
        }
        
        SphereSegment* weehl =  new SphereSegment(body,name+"_weehl"+toStdStr(i),"Jeep_WheelR.mesh");
        body->registerSegment(weehl);
        weehl->setMass(wheelMass);
        weehl->setScale(wheelRadius, wheelRadius, wheelRadius);
        
        weehl->setPosition(x + (sign * bodyWidth) + (sign * wheelRadius*0.8) + (sign * motorBreach),
                           (y-1.5*bodyHeight+(wheelRadius/2.0)), curZ);
        
        // Define joint
        MotorJoint* motor = new MotorJoint(new Position(x + (sign * bodyWidth) + (sign * motorBreach),
                                        (y-1.5*bodyHeight+(wheelRadius/2.0)), curZ));
        body->registerJoint(motor);
        motor->attach(corpus, weehl);
        motor->setAxis(Vector3(0,1,0));
       
        
        if (sign == 1)
        {
            motor->setMotorVelocityEffector(rightEffector);
        } else {
            motor->setMotorVelocityEffector(leftEffector);
        }
        
        
        curZ = curZ + distanceBetweenWheels;
    }
    
    // if required create front NeighborDistanceSensor
    if (hasFrontNbrSensors>0.0)
    {
       
        NeighborDistanceSensor* senLF = new NeighborDistanceSensor(this->agent,body,
                                                body->getName()+"_neighborSensor_left_front","mat000.mesh",frontNbrSensorsRadius);
        NeighborDistanceSensor* senRF = new NeighborDistanceSensor(this->agent,body,
                                                body->getName()+"_neighborSensor_right_front","mat000.mesh",frontNbrSensorsRadius);
        body->registerSegment(senLF);
        body->registerSegment(senRF);
        senRF->setMass(0.1);
        senLF->setMass(0.1);
        
        senLF->setPosition(x-bodyWidth-0.1,y+bodyHeight+0.1,z+bodyLength);
        senRF->setPosition(x+bodyWidth+0.1,y+bodyHeight+0.1,z+bodyLength); 
        
        senLF->setScale(0.1, 0.1, 0.1);
        senRF->setScale(0.1, 0.1, 0.1);
        
        FixedJoint* senLHolderF = new FixedJoint(new Position(x-bodyWidth,y+bodyHeight,z+bodyLength));
        FixedJoint* senRHolderF = new FixedJoint(new Position(x+bodyWidth,y+bodyHeight,z+bodyLength)); 
        
        body->registerJoint(senLHolderF);
        senLHolderF->attach(body->getPositionSegment(), senLF);
        senLHolderF->setAxis(Vector3(0,1,0));  
        
        body->registerJoint(senRHolderF);
        senRHolderF->attach(body->getPositionSegment(), senRF);
        senRHolderF->setAxis(Vector3(0,1,0)); 
        
        body->registerStandaloneSensor("distSenFront_L", senLF);
        body->registerStandaloneSensor("distSenFront_R", senRF);
    }

    // if required create front NeighborDistanceSensor
    if (hasBackNbrSensors>0.0)
    {
        NeighborDistanceSensor* senLB = new NeighborDistanceSensor(this->agent,body,
                                                body->getName()+"_neighborSensor_left_back","mat000.mesh",backNbrSensorsRadius);
        NeighborDistanceSensor* senRB = new NeighborDistanceSensor(this->agent,body,
                                                body->getName()+"_neighborSensor_right_back","mat000.mesh",backNbrSensorsRadius);
        body->registerSegment(senLB);
        body->registerSegment(senRB);
        senRB->setMass(0.1);
        senLB->setMass(0.1);
        
        senLB->setPosition(x-bodyWidth-0.1,y+bodyHeight+0.1,z-bodyLength);
        senRB->setPosition(x+bodyWidth+0.1,y+bodyHeight+0.1,z-bodyLength); 
        
        senLB->setScale(0.1, 0.1, 0.1);
        senRB->setScale(0.1, 0.1, 0.1);
        
        FixedJoint* senLHolderB = new FixedJoint(new Position(x-bodyWidth,y+bodyHeight,z-bodyLength));
        FixedJoint* senRHolderB = new FixedJoint(new Position(x+bodyWidth,y+bodyHeight,z-bodyLength)); 
        
        body->registerJoint(senLHolderB);
        senLHolderB->attach(body->getPositionSegment(), senLB);
        senLHolderB->setAxis(Vector3(0,1,0));  
        
        body->registerJoint(senRHolderB);
        senRHolderB->attach(body->getPositionSegment(), senRB);
        senRHolderB->setAxis(Vector3(0,1,0)); 
        
        body->registerStandaloneSensor("distSenBack_L", senLB);
        body->registerStandaloneSensor("distSenBack_R", senRB);
    }
    
    // create collision cage
    if (hasCollisionCage>0.0) 
    {
        float colItemBranch = 0.3;
        float colItemWidth = 0.2;
        
        for (int i = 1; i <= 4; i++)
        {
            CubeSegment* colCageItem = new CubeSegment(body,name+"_colCageItem"+toStdStr(i), getCubeTextureFileName(26));
            body->registerSegment(colCageItem);
            colCageItem->setMass(0.1);
         
            FixedJoint* cageHolderItem; 
            
            if (i == 1) 
            {
                colCageItem->setScale(bodyWidth+wheelRadius+colItemBranch, bodyHeight/2.0, colItemWidth);    
                colCageItem->setPosition(x, y, z+bodyLength+colItemBranch+wheelRadius);
                cageHolderItem = new FixedJoint(new Position(x, y, z+bodyLength/2.0+colItemBranch+wheelRadius));
                
                
            } else if (i == 2) 
            {
                colCageItem->setScale(colItemWidth, bodyHeight/2.0, bodyLength+wheelRadius);    
                colCageItem->setPosition(x+bodyWidth+1.35*wheelRadius+colItemBranch, y, z);
                cageHolderItem = new FixedJoint(new Position(x+bodyWidth/2.0+wheelRadius+colItemBranch, y, z));
                
            } else if (i == 3) 
            {
                colCageItem->setScale(bodyWidth+wheelRadius+colItemBranch, bodyHeight/2.0, colItemWidth);    
                colCageItem->setPosition(x, y, z-bodyLength-colItemBranch-wheelRadius);
                cageHolderItem = new FixedJoint(new Position(x, y, z-bodyLength+colItemBranch));
                
            } else if (i == 4) 
            {
                colCageItem->setScale(colItemWidth, bodyHeight/2.0, bodyLength+wheelRadius);    
                colCageItem->setPosition(x-bodyWidth-colItemBranch-1.35*wheelRadius, y, z);
                cageHolderItem = new FixedJoint(new Position(x-bodyWidth+colItemBranch, y, z));
            } 
            
            //Configure Joint
            body->registerJoint(cageHolderItem);
            cageHolderItem->attach(corpus, colCageItem);
            cageHolderItem->setAxis(Vector3(0,1,0));  
            
            //Collision Sensor
            ISensor* colSen = new ISensor();
            colCageItem->setCollisionSensor(colSen);
            body->registerSensor("colSensor"+toStdStr(i),colSen);
            
        }
    }
    
    
    // Set the position segment of the corpus    
    return body;
}

};
