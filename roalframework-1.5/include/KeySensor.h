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
#ifndef _KEYSENSOR_H_
#define _KEYSENSOR_H_
#include <OGRE/Ogre.h>
#include <OGRE/OgreEventListeners.h>
#include <OGRE/OgreKeyEvent.h>
#include <OGRE/OgreInput.h>
#include "IStandaloneSensor.h"
#include "World.h"

using namespace std;
using namespace Ogre;
/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
class World;
    
/**
 * The KeySensor listen to a given key of host keybord. 
 *
 * The value is set if the  specified key is pressed and the method update() 
 * is called. This sensor implements the IStandaloneSensor interface.
 *
 * How to initalize:
 *      
 *   <code> 
 *   KeySensor* ksN = Agent->createKeySensor();
 *   ksN->setToListenKey("n");
 *   Body->registerStandaloneSensor("ksN", ksN);
 *   </code>
 *   
 * How to update:
 *      
 *   <code> 
 *   Body->updateSensors(); //which updates all registered sensors of the Body
 *   </code>
 *
 * How to catch: 
 *      
 *   <code> 
 *   Body->getSensor("ksN")->getValue();
 *   </code>
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class KeySensor: public IStandaloneSensor
{
public:
    /**
     * Constructor
     *
     */
     KeySensor(Roal::World* world);
    
    /**
     * Destructor 
     */
    virtual ~KeySensor();

    /**
     * Sets the Key which the Sensorshould listen to. The following keys are suported:
     *
     *  <b> on main keyboard: </b>
     *   @li Numbers: 1 2 3 4 5 6 7 8 9 0
     *   @li Letters: q w e r t y u i o p a s d f g h j k l z x c v b n m
     *   @li Signs: - = [ ] ; ' ` \ , / * <space>.
     *
     * <b> on numeric keypad: </b>
     *   @li Numbers: N1 N2 N3 N4 N5 N6 N7 N8 N9 N0 (used for 1,2,3,4,5,6,7,8,9,0)
     *   @li Signs: N- N+ N= N, N/ N* (used for -, +, =, /, *)
    */
    void setToListenKey(string toListenKey);

    /**
     * @see IStandaloneSensor::update().
     *
     * @warning Do not call this method in a non runing simulation!
     */
    virtual void update();

private:
    
    /**
     * Default Constructor.
     * 
     * Do Not Use!
     */  
     KeySensor() {};

    /**
     * the key the sensor will listen to.
     */
    string toListenKey;

    /**
     * the world.
     */
    World* world;

};

}

#endif //_KEYSENSOR_H_
