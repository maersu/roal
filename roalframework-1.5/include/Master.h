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
#ifndef _MASTER_H_
#define _MASTER_H_

#include <stdio.h>
#include <map>
#include <pthread.h>

#include "RoalException.h"
#include "Connector.h"
#include "Util.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The Master class that runs on the master node in a distributed environment.
 * 
 * In a distributed environment the master node that controls multiple slave
 * nodes. It can send and received messages to and from a slave nodes.
 *  
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */ 
class Master
{
public:
    /**
     * Constructor.
     * 
     * Creates a Connector object that starts listening on a port and
     * waits for registration requests from slave nodes.
     *
     * @param ipAddress the IP Address of the Host which runs this Master
     * @param port the port for incoming messages
     */ 
    Master(string ipAddress, int port);
    
    /**
     * Destructor.
     */
    ~Master();

protected:
    /**
     * The Connector object that manages the communication.
     */
    Connector* connector;

    /**
     * A vector containing the session ID's of the registered slave nodes.
     */
    vector<int> slaves;

    /**
     * Registers a slave.
     *
     * @param sessionID the session ID of a slave.
     */
    virtual void registerSlave(int sessionID);
    
    /**
     * Unregisters a slave.
     *
     * @param sessionID the session ID of a slave.
     */
    virtual void unregisterSlave(int sessionID);

    /**
     * Send a command to all registered slaves.
     *
     * @param command the command to send
     * @param command the value to sen
     */
    virtual void sendCommandToAllSlaves(string command, string value);
    
    /**
     * Send a command to a given registered slave.
     *
     * @param sessionID session ID for the communication with the slave.
     * @param command the command to send
     * @param value the value to send
     * @return the return message
     */
    virtual string sendCommandToSlave(int sessionID, string command, string value);
   
    /**
     * Starts the master listening.
     */
    virtual void run() = 0;
    
    /**
     * Writes GnuPlot and GraphViz statistics to file.
     * 
     * @see Master::writeAgentLineStatMsgToFile
     * @see Master::writeAgentBloodLineStatMsgToFile
     * 
     * @param message A ConnectorMessage object containing the values
     *                DIST_LINE_STAT_LINE and DIST_BLOODLINE_STAT_LINES.
     */
     virtual void handleStatistic(ConnectorMessage* message);
    
private:
    Master();

    /**
     * Writes the GnuPlot statistics record from Slave's message to the file.
     * 
     * @param message A ConnectorMessage object containing the value DIST_LINE_STAT_LINE.
     */
    virtual void writeAgentLineStatMsgToFile(ConnectorMessage* message);    

    /**
     * Writes the GraphViz bloodline statistics from Slave's message to the file.
     * 
     * @param message A ConnectorMessage object containing the value DIST_BLOODLINE_STAT_LINES.
     */
    virtual void writeAgentBloodLineStatMsgToFile(ConnectorMessage* message);
    
    /**
     * A thread to start Gnuplot.
     */
    pthread_t plotThread;

};

/**
 * Starts Gnuplot.
 */
void* startGnuPlot(void* cfg);

}

#endif //_MASTER_H_
