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
#ifndef _IEFFECTOR_H_
#define _IEFFECTOR_H_
#include "IListener.h"

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The effector affects the dynamic simulation and the resulting behavior of the
 * creature. Mostly they affect a BodySegment or a Joint. The given value is often 
 * scaled by a constant weight before the value is applied to the specified 
 * destination.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class IEffector: public IListener
{
public:
    /**
     * Constructor
     * 
     */
    IEffector();
    
    /**
     * Destructor 
     */
    virtual ~IEffector();

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
     * The actual Value of the effector.
     */
    float value;	

};

}

#endif //_IEFFECTOR_H_
