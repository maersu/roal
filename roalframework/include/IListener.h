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
#ifndef _ILISTENER_H_
#define _ILISTENER_H_

#include <vector>

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The neural listener interface. this class offers different method to abstract 
 * classes like ISensor and IEffector.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class IListener
{
public:
    
    /**
     * Registers a listener .
     * 
     * @param listener listener to add.
     */
    void registerListener(IListener* listener); 

    /**
     * removes a registered listener .
     * 
     * @param listener to remove.
     */
    void removeListener(IListener* listener);

    /**
     * Adds the value to the internal Value.
     *
     * @todo Check if this has to be a singelton call.
     * @todo how to handle recursive calls.   
     * @param value new value.
     */
    virtual void addValue(float value) = 0;

    /**
     * Sets the value to the internal Value.
     *
     * @todo Check if this has to be a singelton call.
     * @todo how to handle recursive calls.   
     * @param value new value.
     */
    virtual void setValue(float value) = 0;

    /**
     * Returns the value.
     *
     * @todo Check if this has to be a singelton call.
     * @todo how to handle recursive calls.   
     * @param value new value.
     */
    virtual float getValue() = 0;

    /**
     *Iterates the Listener.
     */
    virtual void listenerItereate() = 0;

protected:
    
    /**
     * Sets the values of the registered listener.
     * 
     * @param value new value.
     */
    void informListeners(float value);

private:
    
    /**
     * Holds the registered Listeners
     */
    std::vector< Roal::IListener* > regListeners; 
};

}

#endif //_ILISTENER_H_
