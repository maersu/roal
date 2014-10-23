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
#ifndef _SLAVE_H_
#define _SLAVE_H_

#include <stdio.h>
#include "RoalException.h"
#include "Util.h"
#include "Connector.h"
#include "ConnectorMessage.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * Runs on the slave nodes in a distributed environment.
 * 
 * In a distributed environment the slave node is a node running a simlation. It
 * can send and received messages to and from a master node.
 *  
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */ 
class Slave
{
public:
    /**
     * Constructor.
     * 
     * Creates a Connector object that starts listening on a port and
     * creates a DistributedWorld.
     *
     * @param ipAddress The IP Address of the Host which runs this slave
     * @param port The server port for incoming messages
     */ 
    Slave(string ipAddress, int port);
    
    /**
     * Destructor.
     */
    ~Slave();

    /**
     * Registers the Slave at the Master.
     * 
     * The Master stores the Slave's IP address and returns a session ID that
     * can be used for future communication.
     * 
     * @param destinationIPAddress The Master's IP address.
     * @param destinationPort The Master's server port.
     *
     * @exception RoalException if the slave is already registered.
     */ 
   void sendRegisterCommandToMaster(string destinationIPAddress, int destinationPort);

    /**
     * Send a ConnectorMessage to the Master.
     * 
     * @param message The ConnectorMessage to send to the Master.
     *
     * @exception RoalException if an error occurs when sending the message.
     */ 
    string sendCommandToMaster(ConnectorMessage* message);

protected:
    /**
     * The Connector object that manages the communication between Master and Slave.
     */
    Connector* connector;
    
    /**
     * The session ID that is used for communication with the Master.
     */
    int sessionID;

private:
    /**
     * Default constructor, may not be used.
     */
    Slave();
    
    /**
     * The IP Address of the Host which runs this slave.
     */
    int port;
    
    /**
     * The server port for incoming messages.
     */
    string ipAddress;

};

}

#endif //_SLAVE_H_
