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

#include "WalkerMaster.h"

namespace Roal
{
    
//------------------------------------------------------------------------------
WalkerMaster::WalkerMaster(string ipAddress, int port)
    : Master(ipAddress, port)
{
}


//------------------------------------------------------------------------------
WalkerMaster::~WalkerMaster()
{
}


//------------------------------------------------------------------------------
void WalkerMaster::run()
{
    bool abort = false;
    
    int i = 0;
    
    while(!abort) {     
        usleep(DIST_MASTER_POLLING_SLEEP_US);  
        i++;        
        while (this->connector->hasMessage()) {
            ConnectorMessage* m = this->connector->getNextMessage();
            
            // Register slave
            if ((m->getCommand().compare(DIST_COM_REGISTERSLAVE)) == 0 ) {
                
                cout << DIST_COM_REGISTERSLAVE <<": " << *m << endl;
                this->registerSlave(m->getSessionID());
                
            // Unregister slave
            } else if ((m->getCommand().compare(DIST_COM_UNREGISTERSLAVE)) == 0 ) {
                
                cout << DIST_COM_UNREGISTERSLAVE <<": " << *m  << endl;
                this->unregisterSlave(m->getSessionID());
                
            // Statistic
            } else if ((m->getCommand().compare(DIST_STAT_FROM_AGENT)) == 0 ) {
                
                cout << DIST_STAT_FROM_AGENT <<": " << *m << endl;
                this->handleStatistic(m);
                
            // Unknown message
            } else {
                cerr << "Unknown message from Slave: " << *m << endl;
            }
            
        }
    }
}

};
