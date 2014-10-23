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

#include "Connector.h"

namespace Roal
{
    
//------------------------------------------------------------------------------
Connector::Connector(string localIPAddress, int localServerPort)
{
    // Init thread struct
    isRegistered = false;
    
    this->localIPAddress = localIPAddress; 
    this->localServerPort = localServerPort;
    
    threadStruct = new ConnectorThreadStruct;
    threadStruct->serverIPAddress = localIPAddress;
    threadStruct->serverPort = localServerPort;
    pthread_mutex_init(&threadStruct->mutex, NULL);
    
    // Create the connector thread
    int rc = pthread_create(&connectorThread, NULL, startConnectorServerFunction,
                        (void*)threadStruct);
    if (rc) {        
        throw(RoalException(typeid( this ).name(), 
              "Could not create thread. Return code from pthread_create() is "
              + toStdStr(rc)));
    }
}


//------------------------------------------------------------------------------
Connector::~Connector()
{
    delete threadStruct;
}


//------------------------------------------------------------------------------
bool Connector::hasMessage()
{
    bool hasMessage;
    
    pthread_mutex_lock(&threadStruct->mutex);
    hasMessage = !threadStruct->messageQueue.empty();
    pthread_mutex_unlock(&threadStruct->mutex);
    
    return hasMessage;
}


//------------------------------------------------------------------------------
ConnectorMessage* Connector::getNextMessage()
{
    if (!this->hasMessage()) {
        throw(RoalException(typeid( this ).name(), 
           "No message(s) in queue"));
    }
    
    ConnectorMessage* message;
    
    pthread_mutex_lock(&threadStruct->mutex);
    message = threadStruct->messageQueue.front();
    threadStruct->messageQueue.pop();
    pthread_mutex_unlock(&threadStruct->mutex);
    
    return message;
}


//------------------------------------------------------------------------------
int Connector::sendRegisterMessage(string destinationIPAddress, int destinationPort)
{
        
    // Create a register message and send it
    ConnectorMessage* conMsg = new ConnectorMessage(0, DIST_COM_REGISTERSLAVE);
    conMsg->setValue(DIST_VALUE_IPADDRESS, localIPAddress);
    conMsg->setValue(DIST_VALUE_PORT, toStdStr(localServerPort));
    string str_sessionID = this->execSendMessage(destinationIPAddress,
                                                 destinationPort, conMsg);
    int i_sessionID;
    
    // Check if there is an error
    unsigned int loc = str_sessionID.find( DIST_ERROR_PREFIX, 0 );
        
    if( loc == string::npos ) {
        i_sessionID = atoi(str_sessionID.c_str()); 
            
    } else {
        throw(RoalException(typeid( this ).name(),
              "Could not get valid SessionID: "+str_sessionID));
    }
        
    // Create new node
    Node* n = new Node;
    n->ipAddress = destinationIPAddress;
    n->port = destinationPort;
        
    // Save node into map
    pthread_mutex_lock(&threadStruct->mutex);
    threadStruct->nodes[i_sessionID] = n;
    pthread_mutex_unlock(&threadStruct->mutex);
        
    isRegistered = true;

    return i_sessionID;
}


//------------------------------------------------------------------------------
string Connector::sendMessage(ConnectorMessage* message)
{
    // Get IP address and port of the destination host by session ID
    pthread_mutex_lock(&threadStruct->mutex);
    string destinationHost = threadStruct->nodes[message->getSessionID()]->ipAddress;
    int destinationPort = threadStruct->nodes[message->getSessionID()]->port;
    pthread_mutex_unlock(&threadStruct->mutex);
    
    return this->execSendMessage(destinationHost, destinationPort, message);
}


//------------------------------------------------------------------------------
string Connector::getNodeInfoString(int sessionID)
{
    string result = "";
    
    // Concat the info string
    pthread_mutex_lock(&threadStruct->mutex);
    
    result = 
        "SessionID: " + toStdStr(sessionID)
        + " IpAddress: " + threadStruct->nodes[sessionID]->ipAddress
        + " Port: " + toStdStr(threadStruct->nodes[sessionID]->port);
    
    pthread_mutex_unlock(&threadStruct->mutex);
    
    return result;
}


//------------------------------------------------------------------------------
string Connector::getNodeIpAdress(int sessionID)
{
    string result = "";
    
    pthread_mutex_lock(&threadStruct->mutex);
    result = threadStruct->nodes[sessionID]->ipAddress;
    pthread_mutex_unlock(&threadStruct->mutex);
    
    return result;
}


//------------------------------------------------------------------------------
int Connector::getNodePort(int sessionID)
{
    int port;
    
    pthread_mutex_lock(&threadStruct->mutex);
    port = threadStruct->nodes[sessionID]->port;
    pthread_mutex_unlock(&threadStruct->mutex);
    
    return port;
}


//------------------------------------------------------------------------------
string Connector::getNodeIpAdressPort(int sessionID)
{
    string ipAddress = "";
    
    // Concat the info string
    pthread_mutex_lock(&threadStruct->mutex);
    ipAddress = threadStruct->nodes[sessionID]->ipAddress
            + ":" + toStdStr(threadStruct->nodes[sessionID]->port);
    pthread_mutex_unlock(&threadStruct->mutex);
    
    return ipAddress;
}


//------------------------------------------------------------------------------
string Connector::execSendMessage(string destinationIPAddress, int destinationPort,
                                  ConnectorMessage* message)
{    
    // Create a client and connect to the server at hostname/port
    XmlRpcClient* c = new XmlRpcClient(destinationIPAddress.c_str(), destinationPort);
    
    XmlRpcValue arg, result;
    
    arg = message->getXmlRpcValue();
    
    
    // Call the remote procedure Echo and print the result value
    if (c->execute(DIST_ROAL_COM_NAME.c_str(), arg, result)) {
        c->close();
        delete c;
        return string(result);
    } else {
        c->close();
        delete c;
        throw(RoalException(typeid( this ).name(), "No answer received from: "
                +this->getNodeInfoString(message->getSessionID())));
    }    
}


//------------------------------------------------------------------------------
bool Connector::getIsRegistered()
{
    return isRegistered;
}


//------------------------------------------------------------------------------
void Connector::unregisterNode(int sessionID)
{
    // Save node into map
    pthread_mutex_lock(&threadStruct->mutex);
    threadStruct->nodes.erase(sessionID);
    pthread_mutex_unlock(&threadStruct->mutex);
}


//------------------------------------------------------------------------------
void* startConnectorServerFunction(void* threadStruct)
{
    ConnectorThreadStruct* ts = (ConnectorThreadStruct*)threadStruct;
    
    //The Server
    XmlRpcServer* s = new XmlRpcServer();
    
    ConnectorServerMethod* serverMethod = new ConnectorServerMethod(s, ts);
    
    // Create the server socket on the specified port
    s->bindAndListen(ts->serverPort);
    
    // Wait for requests and process indefinitely
    s->work(-1.0);
}

};
