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

#include "LeggedCreatureBrain.h"
using namespace std;

namespace Roal
{

//------------------------------------------------------------------------------
LeggedCreatureBrain::LeggedCreatureBrain(const std::string name)
:Brain(name)
{
    age = 0;
}


//------------------------------------------------------------------------------
LeggedCreatureBrain::~LeggedCreatureBrain()
{
    delete phenotype;
}


//------------------------------------------------------------------------------
void LeggedCreatureBrain::iterate(float elapsedTime)
{
    
    
    if (body->getIsRunnable()) 
    {
                
        //use the age because elapsed time nearly 0
        age = age + elapsedTime;
        Phenotype* pheno = this->getPhenotype();
        int legCount = pheno->getValue("legCount");
        float constValue = pheno->getValue("constValue");
        float force = pheno->getValue("force");

        //render the forces and applay them to the body
        for (int i = 1; i <= legCount; i++)
        {
            float axleForce = force * sin(constValue *
                                        (age + pheno->getValue("axle"+toStdStr(i)+"_Comp2"))
                                        - pheno->getValue("axle"+toStdStr(i)+"_Comp1"));
            IEffector* axelEffe = body->getEffector("axle"+toStdStr(i));
            axelEffe->setValue(axleForce);

            float elbowForce = force * sin(constValue *
                                        (age + pheno->getValue("elbow"+toStdStr(i)+"_Comp2"))
                                        - pheno->getValue("elbow"+toStdStr(i)+"_Comp1"));
        
            IEffector* elbowEffe = body->getEffector("elbow"+toStdStr(i));
            elbowEffe->setValue(elbowForce);
        }

        //update the body from the effector
        body->updateFromEffectors();

    }
    
}

//------------------------------------------------------------------------------
float LeggedCreatureBrain::getDistanceTravelled()
{
    return lastPos->getPlanarDistanceTo(body->getPosition());
}

//------------------------------------------------------------------------------
void LeggedCreatureBrain::resetDistanceTravelled()
{
    lastPos = new Position(body->getPosition());
}

//------------------------------------------------------------------------------
void LeggedCreatureBrain::registerBody(Body* body)
{
    this->body = body;
}

//------------------------------------------------------------------------------
std::string LeggedCreatureBrain::toString(string valueDelimiter, string separator)
{
  return "Age" +valueDelimiter+ toStdStr(this->age)
      +separator+phenotype->toString(valueDelimiter,separator);        
}

};
