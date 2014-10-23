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

#include "VictimBraitenbergBrain.h"

using namespace std;
namespace Roal
{

//------------------------------------------------------------------------------
VictimBraitenbergBrain::VictimBraitenbergBrain(const std::string name)
:Brain(name)
{
    age = 0;
    this->energy = 10000;
}


//------------------------------------------------------------------------------
VictimBraitenbergBrain::~VictimBraitenbergBrain()
{
}


//------------------------------------------------------------------------------
void VictimBraitenbergBrain::iterate(float elapsedTime)
{
    
	this->getBody()->updateSensors();

    float lf = 0;
    float rf = 0;
    float lb = 0;
    float rb = 0;
    float l = 0;
    float r = 0;
    float c1 = 0;
    float c2 = 0;
    float c3 = 0;
    float c4 = 0;
    
    if (phenotype->getValue("hasFrontNbrSensors"))
    {
        lf = body->getSensor("distSenFront_L")->getValue();
        rf = body->getSensor("distSenFront_R")->getValue();
    }
    
    if (phenotype->getValue("hasBackNbrSensors"))
    {
        lb = body->getSensor("distSenBack_L")->getValue();
        rb = body->getSensor("distSenBack_R")->getValue();
    }
    
    if (phenotype->getValue("hasCollisionCage")>0.0)
    {
        c1 = body->getSensor("colSensor1")->getValue();
        c2 = body->getSensor("colSensor2")->getValue();
        c3 = body->getSensor("colSensor3")->getValue();
        c4 = body->getSensor("colSensor4")->getValue();
    }    
    
    if (c1>0.0)
    {
       this->energy = this->energy - c1;
        c1 = 0.7;
    }

    if (c2>0.0)
    {
        this->energy = this->energy - c2;
        c2 = 0.7;
    }  

    if (c3>0.0)
    {
        this->energy = this->energy - c3;
        c3 = 0.7;
    }  

    if (c4>0.0)
    {
        this->energy = this->energy - c4;
        c4 = 0.7;
    }     
    
    if ((rf+lf) < (lb+rb))
    {
        l =  lf;
        r =  rf;
    } else {
        l = -lb;
        r = -rb;
    }
        
    l = l - c1;
    r = r - c1;

    l = l - c2;
    r = r + c2;

    l = l + c3;
    r = r - c3;
    
    l = l + c4;
    r = r + c4;
    
   this->getBody()->setMovableTextCaption(body->getSensorInfoString(": ","\n")
                      //  +"\n"+phenotype->toString(": ","\n")
                        +"\nright:" +toStdStr(r)
                        +"\nleft:" +toStdStr(l)
                        +"\nenergy:" +toStdStr(energy));
    
    IEffector* rightMotorEffector = body->getEffector("rightMotorEffector");
    IEffector* leftMotorEffector = body->getEffector("leftMotorEffector"); 
  
    if (r > l) 
    {
            rightMotorEffector->setValue((r)*10.0);
    }  else {   
    
        leftMotorEffector->setValue((l)*10.0);
    } 
    

	this->getBody()->updateFromEffectors();
    
}


//------------------------------------------------------------------------------
void VictimBraitenbergBrain::registerBody(Body* body)
{
    this->body = body;    
}

//------------------------------------------------------------------------------
float VictimBraitenbergBrain::getEnergy()
{
    return this->energy;
}

//------------------------------------------------------------------------------
void VictimBraitenbergBrain::addEnergy(float energy)
{
    this->energy = this->energy + energy;
}


};