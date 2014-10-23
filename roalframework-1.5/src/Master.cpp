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

#include "Master.h"

namespace Roal
{
    
//------------------------------------------------------------------------------
Master::Master(string ipAddress, int port)
{
    connector = new Connector(ipAddress, port);
}


//------------------------------------------------------------------------------
Master::~Master()
{
    delete connector; 
}


//------------------------------------------------------------------------------
void Master::registerSlave(int sessionID)
{
    slaves.push_back(sessionID);
}


//------------------------------------------------------------------------------
void Master::unregisterSlave(int sessionID)
{
    connector->unregisterNode(sessionID);
    
    for (vector<int>::iterator it = slaves.begin(); it != slaves.end(); it++) {
        if (*it == sessionID) {
            slaves.erase(it, it);
            break;
        }
    }
}


//------------------------------------------------------------------------------
void Master::sendCommandToAllSlaves(string command, string value)
{
    for (vector<int>::iterator it = slaves.begin(); it != slaves.end(); it++) {
        this->sendCommandToSlave(*it, command, value);
    } 
}


//------------------------------------------------------------------------------
string Master::sendCommandToSlave(int sessionID, string command, string value)
{
    ConnectorMessage* conMsg = new ConnectorMessage(sessionID, command);
    conMsg->setValue("value", value);
    
    string result;
    try {
        result = connector->sendMessage(conMsg);
    } catch (RoalException& e) {
        unregisterSlave(sessionID);
        e.print();
        return "";
    }
        
    return result;
}


//------------------------------------------------------------------------------
void Master::writeAgentLineStatMsgToFile(ConnectorMessage* message)
{
    if (message->hasValue(DIST_AGENT_NAME) 
            && message->hasValue(DIST_LINE_STAT_LINE)
            && message->hasValue(DIST_STAT_GENCOUNT)
            && message->hasValue(DIST_LINE_STAT_VALUECOUNT)) {
        // Write generation data to file
        string filename = "/tmp/" + message->getValue(DIST_AGENT_NAME) + "_"
            + connector->getNodeIpAdress(message->getSessionID()) + "_"
            + toStdStr(connector->getNodePort(message->getSessionID()))
            + "_lineStat";
        string dataFilename = filename + ".data";
        string configFilename = filename + ".plot";
        
        File* gnuplotData = new File(dataFilename);
        
        if (atoi(message->getValue(DIST_STAT_GENCOUNT).c_str())==1) {
            // Create GnuPlot config file
            string cfg = "set title 'Roal Agent: "
                + message->getValue(DIST_AGENT_NAME)
                + "'\nset xlabel 'Generation'\nset ylabel 'Covered distance [m]'\n"
                + "set autoscale\nplot ";
            for (int i=0; i<atoi(message->getValue(DIST_LINE_STAT_VALUECOUNT).c_str()); i++) {
                if (i>0) {
                    cfg += ", ";
                }
                cfg += "'" + dataFilename + "' using 1:" + toStdStr(i+2)
                    + " with lines title 'Creature " + toStdStr(i+1) + "'";
            }
            cfg += "\npause 30\nreread\n";
            
            File* gnuplotConfig = new File(configFilename);
            gnuplotConfig->reset();
            gnuplotConfig->writeln(cfg);
            delete gnuplotConfig;
            
            // Create thread to start gnuplot process
            /**@bug Starting gnuplot in a thread does not work: it crashed
                    when doing the second reread or so.*/
            /*int rc = pthread_create(&plotThread, NULL, startGnuPlot,
                                      (void*)configFilename.c_str());
            if (rc) {        
                throw(RoalException(typeid( this ).name(), 
                      "Could not create gnuplot thread. Return code from pthread_create() is "
                      + toStdStr(rc)));
            }*/
            
            // Empty data file
            gnuplotData->reset();
        }
        
        gnuplotData->writeln(message->getValue(DIST_LINE_STAT_LINE));
        delete gnuplotData;
        
    } else {
        throw(RoalException(typeid( this ).name(), 
            "Message does not contain a valid Agent Line Statistic"));    
    }
}


//------------------------------------------------------------------------------
void Master::writeAgentBloodLineStatMsgToFile(ConnectorMessage* message)
{
    
    if (message->hasValue(DIST_AGENT_NAME) 
            && message->hasValue(DIST_STAT_GENCOUNT)
            && message->hasValue(DIST_BLOODLINE_STAT_LINES)) {
    
        string fileName = "/tmp/" + message->getValue(DIST_AGENT_NAME) + "_"
            + connector->getNodeIpAdress(message->getSessionID()) + "_"
            + toStdStr(connector->getNodePort(message->getSessionID()))
            + "_bloodline.dot";
        
        File* bloodline = new File(fileName);
        
        if (atoi(message->getValue(DIST_STAT_GENCOUNT).c_str())==1) {
            string s = "digraph g { \n graph [\n   rankdir = \"LR\"\n ];\n node [ fontsize = \"11\" shape=record];\n";
            bloodline->writeln(s);
        } else {
            bloodline->replace('}',' ');
        }
        
        bloodline->writeln(message->getValue(DIST_BLOODLINE_STAT_LINES));
        bloodline->writeln("}");
        
        delete bloodline;
        
    } else {
        throw(RoalException(typeid( this ).name(), 
            "Message does not contain a valid Agent Blood Line Statistic"));    
    }
}


//------------------------------------------------------------------------------
void Master::handleStatistic(ConnectorMessage* message)
{
    if (message->hasValue(DIST_LINE_STAT_LINE)) {
        writeAgentLineStatMsgToFile(message);
    }
        
    if (message->hasValue(DIST_BLOODLINE_STAT_LINES)) {
        writeAgentBloodLineStatMsgToFile(message);
    }
}


//------------------------------------------------------------------------------
void* startGnuPlot(void* plotFile)
{
    int ret; 
    char *cmd[] = { "gnuplot", (char*)plotFile, (char *)0 };
    ret = execv("/usr/bin/gnuplot", cmd);
}

};
