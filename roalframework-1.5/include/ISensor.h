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
#ifndef _ISENSOR_H_
#define _ISENSOR_H_
#include "IListener.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
/**
 * The sensor is contained within a specific part of the Body, and measures a 
 * part of the world or the Body.
 * 
 * Supports some read and write method. The interface is usable and instancable.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class ISensor: public IListener
{
public:
    /**
     * Constructor
     * 
     */
     ISensor();
    
    /**
     * Destructor 
     */
    virtual ~ISensor();

    /**
     * @see IListener::addValue().
     */
    virtual void addValue(float value) ;

    /**
     * @see IListener::getValue().
     */
    virtual float getValue();	

    /**
     * @see IListener::setValue()
     */
    virtual void setValue(float value);

    /**
     * @see IListener::listenerItereate().
     *
     * @warning not supported at the moment.
     */
    virtual void listenerItereate();

private:
    /**
     * The actual Value of the effector
     */
    float value;	
};

}

#endif //_ISENSOR_H_
