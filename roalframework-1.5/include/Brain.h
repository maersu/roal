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
#ifndef _BRAIN_H_
#define _BRAIN_H_

#include <math.h>
#include "Body.h"
#include "Phenotype.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
    class Phenotype;
/**
 * A creature's intellectual representation (mind).
 * 
 * The Brain object uses the Body's methods to control it. It is the intellectual
 * representation of the body and steers the different limbs. The brain is the
 * part that learns.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class Brain
{
public:
    /**
     * Constructor.
     * 
     * @param name The Brain's name.
     */
	Brain(const string name);
    
    /**
     * Destructor.
     */
	virtual ~Brain();
    
    /**
     * Register a Body the Brain will control.
     * 
     * Each subclass should implement this method and check if the Body
     * is of the right type and throw an exception if not.
     * 
     * @param body The Body the brain will control.
     * 
     * @exception RoalException if Body is of incorrect type.
     */
    virtual void registerBody(Body* body) = 0;
    
    /**
     * Returns a pointer of the registered Body.
     * 
     * @return a pointer of the registered Body.
     */
    Body* getBody();

    /**
     * The iteration method.
     * 
     * This method is called from the Agent::iterate() method every time a frame
     * is rendered. It calls the Body object's iterate method.
     * 
     * @param elapsedTime The time since last frame in seconds.
     */ 
	virtual void iterate(float elapsedTime) = 0;
	
    /**
     * Sets the name of the Brain.
     * 
     * @warning In a running simulation use this function at your own risk, since
     * the name is used to register the Brain in the OgreOde world.
     * 
     * @param name The Brain's name.
     */   
    void setName(const string name);
    
    /**
     * Returns the name of the Brain.
     * 
     * @return the name of the Brain.
     */
    string getName();
    
    /**
     * Returns the name of the registered Body.
     * 
     * @return the name of the registered Body.
     */
    string getBodyName();
    
    /**
     * Sets the Phenotype object that contains the genetic information.
     * 
     * @param phenotype The Phenotype object that contains the genetic information.
     */
    virtual void setPhenotype(Phenotype* newPhenotype);
    
    /**
     * Returns the Phenotype object that contains the genetic information.
     * 
     * @return the Phenotype object that contains the genetic information.
     */
    virtual Phenotype* getPhenotype();
    
protected:
    /**
     * The Body the Brain controls.
     */
	Body* body;

	/**
     * The Brain's name.
	 */
	string name;
    
    /**
     * The phenotype that contains also genetical data for the brain.
     */
    Phenotype* phenotype;

};

}

#endif //_BRAIN_H_
