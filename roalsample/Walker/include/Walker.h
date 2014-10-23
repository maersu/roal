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
#ifndef _WALKER_H_
#define _WALKER_H_

#include <stdlib.h>
#include <string>
#include <RoalFramework/CubeSegment.h>
#include <RoalFramework/UniversalJoint.h>
#include <RoalFramework/HingeJoint.h>

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * Walker is the Body implementation of a simple four-legged creature.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class Walker : public Body 
{
public:
    /**
     * Constructor
     */
    Walker(const std::string name, Position* pos);
    
    /**
     * Destructor
     */
    virtual ~Walker();
    
    /**
     * Sets torque of elbow of first leg.
     *
     * Sets the torque of the joint that connects the corpus with the upperarm
     * of the first leg.
     * 
     * @param torqueX The torque in the x-axis
     * @param torqueY The torque in the y-axis (has default value 0.0)
     * @param torqueZ The torque in the z-axis (has default value 0.0)
     */
    void setElbow1Torque(float torqueX, float torqueY=0.0, float torqueZ=0.0);
    
    /**
     * Sets torque of elbow of second leg.
     *
     * Sets the torque of the joint that connects the corpus with the upperarm
     * of the second leg.
     * 
     * @param torqueX The torque in the x-axis
     * @param torqueY The torque in the y-axis (has default value 0.0)
     * @param torqueZ The torque in the z-axis (has default value 0.0)
     */
    void setElbow2Torque(float torqueX, float torqueY=0.0, float torqueZ=0.0);
    
    /**
     * Sets torque of elbow of third leg.
     *
     * Sets the torque of the joint that connects the corpus with the upperarm
     * of the third leg.
     * 
     * @param torqueX The torque in the x-axis
     * @param torqueY The torque in the y-axis (has default value 0.0)
     * @param torqueZ The torque in the z-axis (has default value 0.0)
     */
    void setElbow3Torque(float torqueX, float torqueY=0.0, float torqueZ=0.0);
    
    /**
     * Sets torque of elbow of fourth leg.
     *
     * Sets the torque of the joint that connects the corpus with the upperarm
     * of the fourth leg.
     * 
     * @param torqueX The torque in the x-axis
     * @param torqueY The torque in the y-axis (has default value 0.0)
     * @param torqueZ The torque in the z-axis (has default value 0.0)
     */
    void setElbow4Torque(float torqueX, float torqueY=0.0, float torqueZ=0.0);
    
    /**
     * Sets torque of axle of first leg.
     *
     * Sets the torque of the joint that connects the upperarm with the forearm
     * of the first leg.
     * 
     * @param torqueX The torque in the x-axis
     * @param torqueY The torque in the y-axis (has default value 0.0)
     * @param torqueZ The torque in the z-axis (has default value 0.0)
     */
    void setAxle1Torque(float torqueX, float torqueY=0.0, float torqueZ=0.0);
    
    /**
     * Sets torque of axle of second leg.
     *
     * Sets the torque of the joint that connects the upperarm with the forearm
     * of the second leg.
     * 
     * @param torqueX The torque in the x-axis
     * @param torqueY The torque in the y-axis (has default value 0.0)
     * @param torqueZ The torque in the z-axis (has default value 0.0)
     */
    void setAxle2Torque(float torqueX, float torqueY=0.0, float torqueZ=0.0);
    
    /**
     * Sets torque of axle of third leg.
     *
     * Sets the torque of the joint that connects the upperarm with the forearm
     * of the third leg.
     * 
     * @param torqueX The torque in the x-axis
     * @param torqueY The torque in the y-axis (has default value 0.0)
     * @param torqueZ The torque in the z-axis (has default value 0.0)
     */
    void setAxle3Torque(float torqueX, float torqueY=0.0, float torqueZ=0.0);
    
    /**
     * Sets torque of axle of fourth leg.
     *
     * Sets the torque of the joint that connects the upperarm with the forearm
     * of the fourth leg.
     * 
     * @param torqueX The torque in the x-axis
     * @param torqueY The torque in the y-axis (has default value 0.0)
     * @param torqueZ The torque in the z-axis (has default value 0.0)
     */
    void setAxle4Torque(float torqueX, float torqueY=0.0, float torqueZ=0.0);
    
    /**
     * Returns angle of elbow of first leg.
     *
     * Returns the angle of the joint that connects the corpus with the upperarm
     * of the first leg.
     * 
     * @return Angle of elbow of first leg.
     */
    float getElbow1Angle();
    
    /**
     * Returns angle of elbow of second leg.
     *
     * Returns the angle of the joint that connects the corpus with the upperarm
     * of the second leg.
     * 
     * @return Angle of elbow of second leg.
     */
    float getElbow2Angle();
    
    /**
     * Returns angle of elbow of third leg.
     *
     * Returns the angle of the joint that connects the corpus with the upperarm
     * of the third leg.
     * 
     * @return Angle of elbow of third leg.
     */
    float getElbow3Angle();
    
    /**
     * Returns angle of elbow of fouth leg.
     *
     * Returns the angle of the joint that connects the corpus with the upperarm
     * of the fourth leg.
     * 
     * @return Angle of elbow of fourth leg.
     */
    float getElbow4Angle();
    
    /**
     * Returns angle of axle of first leg.
     *
     * Returns the angle of the joint that connects the upperarm with the forearm
     * of the first leg.
     * 
     * @return Angle of axle of first leg.
     */
    float getAxle1Angle();
    
    /**
     * Returns angle of axle of second leg.
     *
     * Returns the angle of the joint that connects the upperarm with the forearm
     * of the second leg.
     * 
     * @return Angle of axle of second leg.
     */
    float getAxle2Angle();
    
    /**
     * Returns angle of axle of third leg.
     *
     * Returns the angle of the joint that connects the upperarm with the forearm
     * of the third leg.
     * 
     * @return Angle of axle of third leg.
     */
    float getAxle3Angle();
    
    /**
     * Returns angle of axle of fourth leg.
     *
     * Returns the angle of the joint that connects the upperarm with the forearm
     * of the fourth leg.
     * 
     * @return Angle of axle of fourth leg.
     */
    float getAxle4Angle();
    
    /**
     * Returns the distance the Walker travelled.
     *
     * Returns the distance the Walker travelled since he is alive.
     * 
     * @return the distance the Walker travelled.
     */
    float getDistanceTravelled();
    
    /**
     * Updates the value for the distance the Walker travelled.
     * 
     * Looks at which position the Walker is actually and adds the distance he
     * travelled since the last update to the total distance he travelled since
     * he is alive.
     */
    void updateDistanceTravelled();
    
    /**
     * reset the value for the distance the Walker travelled.
     */
    void resetDistanceTravelled();
   
protected:
    /** 
     * The distance the Walker travelled since he is alive.
     */
    float travelledDistance;
    
    /**
     * The position when the last distance update was made.
     * 
     * @see Walker::updateDistanceTravelled
     */
    Position* lastPosition;
    
    /**
     * The BodySegment that represents the corpus of the creature.
     */
    CubeSegment* corpus;
    
    /**
     * The upperarm of the first leg.
     */
    CubeSegment* upperarm1;
    
    /**
     * The forearm of the first leg.
     */
    CubeSegment* forearm1;
    
    /**
     * The joint that connects upperarm with forearm of the first leg.
     */
    HingeJoint* elbow1;
    
    /**
     * The joint that connects corpus with upperarm of the first leg.
     */
    HingeJoint* axle1;
    
    /**
     * The upperarm of the second leg.
     */
    CubeSegment* upperarm2;
    
    /**
     * The forearm of the second leg.
     */
    CubeSegment* forearm2;
    
    /**
     * The joint that connects corpus with upperarm of the second leg.
     */
    HingeJoint* elbow2;
    
    /**
     * The joint that connects corpus with upperarm of the second leg.
     */
    HingeJoint* axle2;
    
    /**
     * The upperarm of the third leg.
     */
    CubeSegment* upperarm3;
    
    /**
     * The forearm of the third leg.
     */
    CubeSegment* forearm3;
    
    /**
     * The joint that connects corpus with upperarm of the third leg.
     */
    HingeJoint* elbow3;
    
    /**
     * The joint that connects corpus with upperarm of the third leg.
     */
    HingeJoint* axle3;
    
    /**
     * The upperarm of the fourth leg.
     */
    CubeSegment* upperarm4;
    
    /**
     * The forearm of the fourth leg.
     */
    CubeSegment* forearm4;
    
    /**
     * The joint that connects corpus with upperarm of the fourth leg.
     */
    HingeJoint* elbow4;
    
    /**
     * The joint that connects corpus with upperarm of the fourth leg.
     */
    HingeJoint* axle4;
};

};

#endif //_WALKER_H_
