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

#include "IListener.h"


/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

//------------------------------------------------------------------------------
void IListener::registerListener(IListener* listener)
{
    regListeners.push_back( listener );
}

//------------------------------------------------------------------------------
void IListener::removeListener(IListener* listener)
{
	/** @todo implement the method */  
	//regListeners.erase( listener);
}	
//------------------------------------------------------------------------------
void IListener::informListeners(float value)
{
	
	// Display the list
  std:: vector< Roal::IListener* >::iterator it;
   for( it = regListeners.begin(); it != regListeners.end(); it++ ) {
     (*it)->addValue(value);
   }	
   
}


};
