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

#include "LeggedCreatureFactory.h"

namespace Roal
{

//-----------------------------------------------------------------------------
LeggedCreatureFactory::LeggedCreatureFactory(string name, LeggedCreatureGenotype* genotype)
    : CreatureFactory(name)
{
    this->m_genotype = genotype;
    bodyCnt = 0;      
}

//-----------------------------------------------------------------------------
LeggedCreatureFactory::LeggedCreatureFactory(string name)
    : CreatureFactory(name)
{    
    LeggedCreatureGenotype* genotype = new LeggedCreatureGenotype();
    this->m_genotype = genotype;
    bodyCnt = 0;     
}


//------------------------------------------------------------------------------
LeggedCreatureFactory::~LeggedCreatureFactory()
{

}

//------------------------------------------------------------------------------
Brain* LeggedCreatureFactory::generateRandomCreature(string name, Position* pos)
{
    Phenotype* phenotype = this->m_genotype->getRandomPhenotype(); 
    return generateCreature(name,pos,phenotype);
}


//------------------------------------------------------------------------------
Brain* LeggedCreatureFactory::generateCreature(string name, Position* pos, Phenotype* phenotype)
{

    LeggedCreatureBrain* brain = new LeggedCreatureBrain(name+"_brain");
    brain->setPhenotype(phenotype);
    brain->registerBody(generateBody(name,pos,phenotype));
    brain->resetDistanceTravelled();
    return brain;
}

//------------------------------------------------------------------------------
Body* LeggedCreatureFactory::generateRandomBody(string name, Position* pos)
{
    Phenotype* phenotype = this->m_genotype->getRandomPhenotype(); 
    return generateBody(name,pos,phenotype);
}    

//------------------------------------------------------------------------------
Body* LeggedCreatureFactory::generateBody(string name, Position* pos, Phenotype* phenotype)
{
    
    string legMeshFile  = getRandomCubeTextureFileName();
    string corpusMeshFile = getRandomCubeTextureFileName();
    // increment BodyCount;
    bodyCnt ++;
    
    Body* body = new Body(name+"_body",pos);
    body->setPhenotype(phenotype);
    
    // Define the sizes
    float bodyWidth  = phenotype->getValue("bodyWidth");
    float bodyHeight =  phenotype->getValue("bodyHeight");
    float bodyLength = phenotype->getValue("bodyLength");
    
    int legCnt = phenotype->getValue("legCount");
    
    float armWidth =  phenotype->getValue("armWidth");
    float armLength =  phenotype->getValue("armLength");
    
    float armHeight =  phenotype->getValue("armHeight");
    
    // Define transitions of the segments
    float armYTrans = bodyHeight/2; // y-Transition of the arm from the corpus center
    float axleBreach = armLength * 0.3; // Breach between corpus and upperarm
    float elbowBreach = armLength * 0.3; // Breach between upperarm and forearm
    
    if (axleBreach < MIN_DIST_BETWEEN_BODYSEGMENT) {axleBreach = MIN_DIST_BETWEEN_BODYSEGMENT;}
    if (elbowBreach < MIN_DIST_BETWEEN_BODYSEGMENT) {elbowBreach = MIN_DIST_BETWEEN_BODYSEGMENT;}
   
    // Get destination position of the whole body
    float x = body->getPosition()->getX();
    float y = body->getPosition()->getY();
    float z = body->getPosition()->getZ();
    
    // create root element
    CubeSegment* corpus = new CubeSegment(body, name+"_corpus", corpusMeshFile);
    corpus->setMass(0.1);
    corpus->setScale(bodyWidth, bodyHeight, bodyLength);
    body->registerSegment(corpus);
    corpus->setPosition(x, y, z);
    
    int legPerSide = legCnt/2;
    float distanceBetweenLegs =  (2*bodyLength/(legPerSide-1));
    int sign = 1; 
    int mul = 1;
    float curZ = z-(bodyLength);
 
    // create arms
    for (int i = 1; i <= legCnt; i++)
    {
    
        if (i == (legPerSide+1)) 
        {
            sign = -1;
            mul =2;
            curZ = z-(bodyLength);
        }
        
        CubeSegment* upperarm =  new CubeSegment(body,name+"_upperarm"+toStdStr(i),legMeshFile);
        body->registerSegment(upperarm);
        
        CubeSegment* forearm =  new Roal::CubeSegment(body, name+"forearm"+toStdStr(i), legMeshFile);
        body->registerSegment(forearm);
        
        // mass and scale
        upperarm->setMass(0.1);
        forearm->setMass(0.1);
        
        upperarm->setScale(armLength, armHeight, armWidth);
        forearm->setScale(armLength, armHeight, armWidth);
        
        //set Position
        upperarm->setPosition(x + (sign * bodyWidth) + (sign * armLength) + (sign * axleBreach),
                           y, curZ);
        forearm->setPosition(x + (sign * bodyWidth )+ (sign * 3*armLength) + (sign * axleBreach) + (sign * elbowBreach),
                          y, curZ);
                
        //Axle Joint
        IEffector* axleEffe = new IEffector();
        HingeJoint* axle = new HingeJoint(new Position(x + (sign * bodyWidth) + (sign * axleBreach),
                                        y, curZ));
        axle->attach(corpus, upperarm);
        axle->setAxis(Vector3(0,1,0));
        axle->setTorqueEffector(axleEffe);
        body->registerEffector("axle"+toStdStr(i), axleEffe);       
        body->registerJoint(axle);
        axle->setLowHighStop(-1,1);

        // elbow Joint
        IEffector* elbowEffe = new IEffector();
        HingeJoint* elbow = new HingeJoint(new Position(x + (sign * bodyWidth) + (sign * armLength) + (sign * axleBreach)
                                            + (sign * elbowBreach), y, curZ));

        elbow->attach(upperarm, forearm);
        elbow->setAxis(Vector3(0,0,1));
        elbow->setTorqueEffector(elbowEffe);
        
        if (sign < 1)
        {
            elbow->setLowHighStop(-1.5,0.0);
        } else {
           elbow->setLowHighStop(0.0,1.5); 
        }
        
        body->registerEffector("elbow"+toStdStr(i), elbowEffe);  
        body->registerJoint(elbow);

        curZ = curZ + distanceBetweenLegs;
    }    

    // Define joints

    body->setPositionSegment(corpus);
    return body;
}

};
