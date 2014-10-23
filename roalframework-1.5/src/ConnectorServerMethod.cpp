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

#include "RoalCore.h"
#include "ConnectorServerMethod.h"

namespace Roal
{

//------------------------------------------------------------------------------
ConnectorServerMethod::ConnectorServerMethod(XmlRpcServer* server,
                                             ConnectorThreadStruct* ts)
 : XmlRpcServerMethod(DIST_ROAL_COM_NAME, server)
{
    threadStruct = ts;
}


//------------------------------------------------------------------------------
void ConnectorServerMethod::execute(XmlRpcValue &params, XmlRpcValue &result)
{
    
    bool isValid = true;
        
    // Create CreatorMessage object
    ConnectorMessage* message = new ConnectorMessage(params[0]);
    
    if (message->getSessionID() == 0) {
        // Create new session ID (set timestamp as session ID)
        pthread_mutex_lock(&threadStruct->mutex);
        time_t sessionID = time(NULL);
        map<int, Node*>::iterator it =
            threadStruct->nodes.find(sessionID);

        while (it != threadStruct->nodes.end()) {
            // Prevent that two slaves that are connecting in the same second
            // get the same session ID.
            sessionID = time(NULL);
            it = threadStruct->nodes.find(sessionID);
        }

        pthread_mutex_unlock(&threadStruct->mutex);
            
        message->setSessionID(sessionID);
       
        //declare
        string ipAddress;
        int port;
        
        // check if the message has the required infos
        if (message->hasValue(DIST_VALUE_PORT))
        {
            port = atoi(message->getValue(DIST_VALUE_PORT).c_str());
        } else {
            result = DIST_ERROR_PREFIX + "Missing Port";
            isValid = false;
        }

        if (message->hasValue(DIST_VALUE_IPADDRESS))
        {
            ipAddress = message->getValue(DIST_VALUE_IPADDRESS);
        } else {
            result = DIST_ERROR_PREFIX + "Missing IpAdresss";
            isValid = false;
        }

        if (isValid) {
            // Create new node
            Node* n = new Node;
            n->ipAddress = ipAddress;
            n->port = port; 
            
            // Save node into map
            pthread_mutex_lock(&threadStruct->mutex);
            threadStruct->nodes[sessionID] = n;
            pthread_mutex_unlock(&threadStruct->mutex);
           
            result = toStdStr(sessionID);
        }
 
    } else {
        // Check session ID

        pthread_mutex_lock(&threadStruct->mutex);
        map<int, Node*>::iterator it =
        threadStruct->nodes.find(message->getSessionID());
    
        //check if the connector has a node with this sessionID
        if (it == threadStruct->nodes.end()) {
            result = DIST_ERROR_PREFIX + "Invalid session ID";
            isValid = false;
        } else {
           result = DIST_DEFAULT_RESULT; 
        }
        pthread_mutex_unlock(&threadStruct->mutex);
    }
    
    if (isValid) {      
        // Add message to message queue.
        pthread_mutex_lock(&threadStruct->mutex);
        threadStruct->messageQueue.push(message);
        pthread_mutex_unlock(&threadStruct->mutex);
        
    }
}

}
