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

#include "WalkerBrain.h"

namespace Roal
{

//------------------------------------------------------------------------------
WalkerBrain::WalkerBrain(const std::string name)
:Brain(name)
{
    genotype = new WalkerGenotype();
    age = 0;
    updateMovableTextCounter = 0;
}


//------------------------------------------------------------------------------
WalkerBrain::~WalkerBrain()
{
    delete genotype;
}


//------------------------------------------------------------------------------
void WalkerBrain::iterate(float elapsedTime)
{
    if (body->getIsRunnable()) {
        float force = 10;

        //use the age because elapsed time nearly 0
        age = age + elapsedTime;
        
        float torque0 = force * sin(genotype->getBrainDataAtIndex(8) *
                                    (age + genotype->getBrainDataAtIndex(4))
                                    - genotype->getBrainDataAtIndex(0));
                                    
        float torque1 = force * sin(genotype->getBrainDataAtIndex(8) *
                                    (age + genotype->getBrainDataAtIndex(5))
                                    - genotype->getBrainDataAtIndex(1));
                                    
        float torque2 = force * sin(genotype->getBrainDataAtIndex(8) *
                                    (age + genotype->getBrainDataAtIndex(6))
                                    - genotype->getBrainDataAtIndex(2));
                                    
        float torque3 = force * sin(genotype->getBrainDataAtIndex(8) *
                                    (age + genotype->getBrainDataAtIndex(7))
                                    - genotype->getBrainDataAtIndex(3));
        
        ((Walker*)body)->setElbow1Torque(torque0);
        ((Walker*)body)->setAxle1Torque(torque1);
        
        ((Walker*)body)->setElbow2Torque(torque2);
        ((Walker*)body)->setAxle2Torque(torque3);
        
        ((Walker*)body)->setElbow3Torque(-torque3);
        ((Walker*)body)->setAxle3Torque(-torque2);
        
        ((Walker*)body)->setElbow4Torque(-torque0);
        ((Walker*)body)->setAxle4Torque(-torque1);
        
        if (updateMovableTextCounter<10) {
            updateMovableTextCounter++;
        } else {
            body->setMovableTextCaption("Walker:\n"+this->getName()+"\n"+toStdStr(((Walker*)body)->getDistanceTravelled()));
            updateMovableTextCounter = 0;
        }
        //((Walker*)body)->updateDistanceTravelled();
    }
}


//------------------------------------------------------------------------------
void WalkerBrain::registerBody(Body* body)
{
    if (dynamic_cast<Roal::Walker*>(body)!=NULL) {
        this->body = body;
    } else {
        throw(RoalException(typeid( this ).name(),"Body '"+body->getName() +
                            "' is wrong " + "subclass of Body (not Walker)"));
    }
}


//------------------------------------------------------------------------------
WalkerGenotype* WalkerBrain::getGenotype()
{
    return this->genotype;
}


//------------------------------------------------------------------------------
void WalkerBrain::setGenotype(WalkerGenotype* genotype)
{
    this->genotype = genotype;
}


//------------------------------------------------------------------------------
std::string WalkerBrain::toString(std::string sep)
{
  return "Name" + sep + this->getName() + sep + "Age" + sep + toStdStr(this->age)
    + sep + "Travelled Distance" + sep + toStdStr(((Walker*)getBody())->getDistanceTravelled())
    + sep + "genotypeData[0]" + sep + toStdStr(genotype->getBrainDataAtIndex(0))
    + sep + "genotypeData[1]" + sep + toStdStr(genotype->getBrainDataAtIndex(1))
    + sep + "genotypeData[2]" + sep + toStdStr(genotype->getBrainDataAtIndex(2))   
    + sep + "genotypeData[3]" + sep + toStdStr(genotype->getBrainDataAtIndex(3))
    + sep + "genotypeData[4]" + sep + toStdStr(genotype->getBrainDataAtIndex(4))
    + sep + "genotypeData[5]" + sep + toStdStr(genotype->getBrainDataAtIndex(5))   
    + sep + "genotypeData[6]" + sep + toStdStr(genotype->getBrainDataAtIndex(6))
    + sep + "genotypeData[7]" + sep + toStdStr(genotype->getBrainDataAtIndex(7))
    + sep + "genotypeData[8]" + sep + toStdStr(genotype->getBrainDataAtIndex(8));              
}




};
