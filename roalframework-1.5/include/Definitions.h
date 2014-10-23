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

#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
    using std::string;
    
    // Distributed
    const string DIST_ROAL_COM_NAME = "RoalCommand";
    const string DIST_VALUE_IPADDRESS = "IpAdress";    
    const string DIST_VALUE_PORT = "Port";    
    
    const string DIST_COM_REGISTERSLAVE = "RegisterSlave";
    const string DIST_COM_UNREGISTERSLAVE = "UnRegisterSlave";
    const string DIST_ERROR_PREFIX = "Error: ";
    
    const string DIST_DEFAULT_RESULT = "Message Received";
    const string DIST_AGENT_NAME ="Name of the Agent";

    const string INIT_POPULATION ="Initalize Population";
    const string NEED_POPULATION ="Need Population";
    const string POPULATION_EVAL = "Populatin Evaluation";
    
    //commands for Line Statistic 
    
    const string PHENOTYPES_PACK ="Phenotypes Pack";
    const string STOP_SIM ="Stop Simulation";
    const string START_SIM ="Start Simulation";
    
    const string DIST_STAT_FROM_AGENT ="Line Statistic from Agent";
    const string DIST_LINE_STAT_LINE = "Line Statistic Line";
    const string DIST_STAT_GENCOUNT = "Generation Count";
    const string DIST_LINE_STAT_VALUECOUNT = "Value Count";
    
    const string DIST_BLOODLINE_STAT_LINES ="Bloodline Statistic Lines";
    
    const int DIST_MASTER_POLLING_SLEEP_US = 1000000; //1000000 micro seconds = 1 second 
    
    const string DEFAULT_VALUE_DELIMITER = "=";
    const string DEFAULT_VALUEPAIR_DELIMITER = ":";
    
    const string MAX_PREFIX = "max_";
    const string MIN_PREFIX = "min_";
    
    //Emergency Handling
    const int KILL_COLLISION_TRESHOLD = 800;
    const float MIN_DIST_BETWEEN_BODYSEGMENT = 0.1;
    
}


#endif //_DEFINITIONS_H_
