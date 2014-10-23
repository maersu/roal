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
#ifndef _WALKERMASTER_H_
#define _WALKERMASTER_H_

#include <unistd.h>
#include <RoalFramework/Master.h>

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The Master implementation of the distributed walker example.
 *  
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */ 
class WalkerMaster : public Master
{
public:
    /**
     * Constructs an instance of Master.
     * 
     * Creates a Connector object that starts listening on a port and
     * waits for registration requests from slave nodes.
     */ 
    WalkerMaster(string ipAddress, int port);
    
    /**
     * Destructor.
     */
    ~WalkerMaster();

    /**
     * Starts the Master listening on a port.
     * 
     * @see Master::run
     */
    virtual void run();

private:
    /**
     * Default constructor, may not be used.
     */
    WalkerMaster();
};

}

#endif //_WALKERMASTER_H_
