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
#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_

#include <stdio.h>
#include <queue>
#include <map>
#include <pthread.h>
#include <XmlRpc/XmlRpc.h>

#include "RoalCore.h"
#include "ConnectorMessage.h"
#include "ConnectorServerMethod.h"

using namespace std;
using namespace XmlRpc;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * A struct used in Connector containing informations of a distributed network node.
 */
struct Node {
    string ipAddress;
    int port;        
};

/**
 * A thread struct used in Connector and ConnectorServerMethod.
 */
struct ConnectorThreadStruct {
    /**
     * A mutex to lock critical sections.
     */
    pthread_mutex_t mutex;
    
    /**
     * The message queue containing incoming ConnectorMessage objects.
     */
    queue<ConnectorMessage*> messageQueue;
    
    /**
     * The server host's IP Address
     */
    string serverIPAddress;
    
    /**
     * The port the server is listening on.
     */
    int serverPort;
    
    /**
     * A map containing the nodes with a session.
     */
    map<int, Node*> nodes;
};


/**
 * Sends and receives messages to or from a host.
 * 
 * The Connector builds an abstraction layer to the underlying network technology.
 * In this implementation this is XML-RPC.
 *  
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */ 
class Connector
{
public:
    /**
     * Constructor.
     * 
     * @param localIPAddress The IP address of the local server.
     * @param localServerPort The port the server should listen on.
     *
     * @exception throws a RoalException in case the Server thread could not created
     */ 
    Connector(string localIPAddress, int localServerPort);
    
    /**
     * Destructor.
     */
    ~Connector();
    
    /**
     * Check if message are in queue.
     *
     * @return True if messages are in queue
     */
    bool hasMessage();
    
    /**
     * Dequeue the oldest message in the queue (receive message).
     * 
     * @return A ConnectorMessage object containing the message data.
     *
     * @exception throws a RoalException in case the Server has no message left.
     */
    ConnectorMessage* getNextMessage();
    
        
    /**
     * Send a register message to a host.
     * 
     * @param destinationIPAddress The address to sent the message to.
     * @param destinationPort The port to send the message to.
     *
     * @return the new SessionID
     *
     * @exception throws a RoalException in case no valid SessionID or Answer received.
     */
    int sendRegisterMessage(string destinationIPAddress, int destinationPort);
    
    /**
     * Send a message to a host.
     * 
     * A session has to pre exist since to target host/port will be specified.
     * 
     * @param message A ConnectorMessage object to send to a host.
     *
     * @exception throws a RoalException in case no answer received.
     */
    string sendMessage(ConnectorMessage* message);
    
    /**
     * Returns true if localhost is registered to a foreign host.
     * 
     * @return true if localhost is registered to a foreign host.
     */
    bool getIsRegistered();
    
    /**
     * Removes a registered node from nodes map.
     * 
     * @param sessionID The node's session ID.
     */
    void unregisterNode(int sessionID);
    
    /**
     * returns the information string of the node.
     * 
     * @param sessionID The node's session ID.
     * @return a string with different informations (SessionID,ipAdr,Port)
     */
    string getNodeInfoString(int sessionID);
    
    /**
     * returns the server port of the node.
     * 
     * @param sessionID The node's session ID.
     * @return the port number
     */
    int getNodePort(int sessionID);
    
    /**
     * returns the server IP address of the node.
     * 
     * @param sessionID The node's session ID.
     * @return the IP address as string
     */
    string getNodeIpAdress(int sessionID);
    
    /**
     * returns the IpAddress and Port of the node.
     * 
     * @param sessionID The node's session ID.
     * @return a string with the Form: <ipAdress>:<Port>
     */
    string getNodeIpAdressPort(int sessionID);
    
private:
    /**
     * May not be used.
     */
    Connector();

    /**
     * The connector thread.
     */
    pthread_t connectorThread;
    
    /**
     * Struct containing the necessary data for the connector threads.
     */
    ConnectorThreadStruct* threadStruct;
    
    /**
     * Is set to true if localhost is registered to a foreign host.
     */
    bool isRegistered;
    
    /**
     * The IP address of the local host.
     */
    string localIPAddress; 
    
    /**
     * The port the local server is listening on.
     */
    int localServerPort;
    
    /**
     * Actually sends a message.
     * 
     * @param destinationIPAddress The address to sent the message to.
     * @param destinationPort The port to send the message to.
     * @param message A ConnectorMessage object containing the message data.
     * @return Result message.
     */
    string execSendMessage(string destinationIPAddress, int destinationPort, ConnectorMessage* message);
};


/**
 * Function used by Connector to start the XML-RPC server (used to create thread).
 */
void* startConnectorServerFunction(void* threadStruct);

}

#endif //_CONNECTOR_H_
