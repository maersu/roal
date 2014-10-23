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

#ifndef _GENOTYPE_H_
#define _GENOTYPE_H_

#include "ValueHandler.h"
#include "Phenotype.h"
namespace Roal
{

class Phenotype;
/**
 * The Genotype class represents the the genetic information of a creature race.
 * 
 * The information is stored in the form <keyString,minFloat,maxFloat>. From this 
 * values the genotype can create a random Phenotype.
 * The available values can be intellectual information (used in the Brain) 
 * or information about the physical nature of the creature (used in the Body). 
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class Genotype: protected ValueHandler
{
public:
    /**
     * Constructor.
     */
	Genotype();
    
    /**
     * Destructor.
     */
	virtual ~Genotype();

    /**
     * Sets a new generic information.
     *
     * @param key The key string to access this inforamtion.
     * @param minValue the minima the value could reach.
     * @param maxValue the maxima the value could reach.
     */
    virtual void setMinMaxValue(string key, float minValue, float maxValue);
 
    /**
     * Returns the minima of the information.
     *
     * @param key The key string to access this inforamtion.
     *
     */
    virtual float getMinValue(string key);

    /**
     * Returns the maxima of the information.
     *
     * @param key The key string to access this inforamtion.
     *
     */
    virtual float getMaxValue(string key);

    /**
     * Checks if the information exists.
     *
     * @param key The key string to access this inforamtion.
     *
     */
    virtual bool hasMinMaxValue(string key);
    
    /**
     * @see ValueHandler::getValuesCount().
     */
    int getValuesCount();

    /**
     * Returns a random value of the information.
     *
     * @param key The key string to access this inforamtion.
     * @return a random value between the stored minima and maxima
     *
     */
    virtual float getRandomValue(string key);
    
    /**
     * Returns a random created Phenotype with the stored informations.
     *
     * @param key The key string to access this inforamtion.
     *
     */
    virtual Phenotype* getRandomPhenotype() = 0;

protected:
    
    /**
     * Returns a random value between the given min and max.
     *
     * @param key The key string to access this inforamtion.
     * @param min the minima of the random value.
     * @param max the maxima of the random valu
     *
     * @return A random value between the min and max.
     *
     */
    float getRandomValue(float min, float max);

    /**
     * Returns a random value between values stored under the
     * given keys.
     *
     * @param key The key string to access this inforamtion.
     * @param minKey the key to acces the minima.
     * @param maxKey the key to acces the minima.
     *
     * @return A random value between the min and max.
     *
     */
    float getRandomValue(string minKey, string maxKey);
};

}

#endif //_GENOTYPE_H_
