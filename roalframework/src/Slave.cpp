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

#include <unistd.h>
#include "RoalCore.h"
#include "Slave.h"

namespace Roal
{
    
//------------------------------------------------------------------------------
Slave::Slave(string ipAddress, int port)
{
    connector = new Connector(ipAddress, port);
    this->sessionID = 0;
    this->port = port;
    this->ipAddress = ipAddress;
}


//------------------------------------------------------------------------------
Slave::~Slave()
{
    delete connector;
}


//------------------------------------------------------------------------------
void Slave::sendRegisterCommandToMaster(string destinationIPAddress, int destinationPort)
{
    
    if (!connector->getIsRegistered()) {
        this->sessionID = connector->sendRegisterMessage(destinationIPAddress,
                                                         destinationPort);  
    } else {
        throw(RoalException(typeid( this ).name(), "The Slave is already registered!"));
    }
}


//------------------------------------------------------------------------------
string Slave::sendCommandToMaster(ConnectorMessage* message)
{
    string s;

    if (connector->getIsRegistered()) {
        message->setSessionID(this->sessionID);
        s =  connector->sendMessage(message) ;
    } else {
        throw(RoalException(typeid( this ).name(),
              "Could not send a Command to the Master.\nThe Slave is not registered to a Master!"));
    }

    return s;
        
}

};
