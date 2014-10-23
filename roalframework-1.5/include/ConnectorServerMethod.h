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
#ifndef _CONNECTORSERVERMETHOD_H_
#define _CONNECTORSERVERMETHOD_H_

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <XmlRpc/XmlRpc.h>

#include "RoalCore.h"
#include "Connector.h" //needed for ConnectorThreadStruct declaration

using namespace std;
using namespace XmlRpc;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

struct ConnectorThreadStruct;
    
/**
 * An XmlRpc server listening on a port.
 *  
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */ 
class ConnectorServerMethod : public XmlRpcServerMethod
{
public:
    /**
     * Constructor.
     * 
     * @param server A pointer to the XmlRpcServer.
     * @param ts A pointer to the thread struct containing shared data.
     */
    ConnectorServerMethod(XmlRpcServer* server, ConnectorThreadStruct* ts);
    
    /**
     * The execute server method.
     * 
     * @param params A XmlRpcValue filled with the parameters of the RPC.
     * @param result A XmlRpcValue that will be filled with the return values.
     */
    void execute(XmlRpcValue &params, XmlRpcValue &result);
  
private:
    /**
     * Struct containing the necessary data for the connector threads.
     */
    ConnectorThreadStruct* threadStruct;
};

}

#endif //_CONNECTORSERVERMETHOD_H_
