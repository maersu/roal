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
#ifndef _CONNECTORMESSAGE_H_
#define _CONNECTORMESSAGE_H_

#include <stdio.h>
#include <string>
#include <map>
#include <XmlRpc/XmlRpc.h>

#include "RoalCore.h"
#include "ConnectorMessageTokenizer.h"

using namespace std;
using namespace XmlRpc;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * Represents a message that is sent over the network from one host to another.
 * 
 * The message can contain multiple key-value pairs.
 *  
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */ 
class ConnectorMessage
{

/**
 * Overloaded stream operator.
 *
 * @param os The output stream.
 * @param message An instance of a ConnectorMessage to output.
 * @return The output stream.
 */
friend ostream& operator<<(ostream& os, const ConnectorMessage& message);


public:
    /**
     * Constructor.
     * 
     * Session ID is not available, since this is an initial message.
     * 
     * @param command A command to execute on the foreign host.
     */ 
    ConnectorMessage(string command);
    
    /**
     * Constructor.
     * 
     * Session ID is not available, since this is an initial message.
     * 
     * @param command A command to execute on the foreign host.
     * @param valueString A value string in the form "key1=value1:key2=value2:...",
     * delimiters ('=', ':') in the key or value part have to be escaped with '\'.
     */ 
    ConnectorMessage(string command, string valueString);
    
    /**
     * Constructor.
     * 
     * @param sessionID The connection's session id.
     * @param command A command to execute on the foreign host.
     */ 
    ConnectorMessage(int sessionID, string command);
    
    /**
     * Constructor.
     * 
     * @param sessionID The connection's session id.
     * @param command A command to execute on the foreign host.
     * @param valueString A value string in the form "key1=value1:key2=value2:...",
     * delimiters ('=', ':') in the key or value part have to be escaped with '\'.
     */ 
    ConnectorMessage(int sessionID, string command, string valueString);
    
    /**
     * Constructs an instance of ConnectorMessage from an XmlRpcValue.
     * 
     * @param xmlRpcValue An XmlRpcValue containing three values:
                          "sid", "command" and "value".
     * 
     * @exception RoalException if values in XmlRpcValue are invalid.
     * 
     * @warning The given XmlRpcValue will not be validated.
     */ 
    ConnectorMessage(XmlRpcValue xmlRpcValue);
    
    /**
     * Destructor.
     */
    ~ConnectorMessage();
    
    /**
     * Setter for the session ID.
     *
     * @param sessionID The new session ID.
     */
    void setSessionID(int sessionID);
    
    /**
     * Getter for the session ID.
     *
     * @return Session ID.
     */
    int getSessionID() const;
    
    /**
     * Getter for the command.
     *
     * @return The command.
     */
    string getCommand() const;
    
    /**
     * Checks if a value exists.
     *
     * @param key The value's name (key).
     * @return True if the value exists.
     */
    bool hasValue(string key);
    
    /**
     * Getter for a value with key.
     *
     * @param key The value's name.
     * @return The value.
     * 
     * @exception RoalException if a value with the given key does not exist.
     */
    string getValue(string key);
    
    /**
     * Setter for a value with key.
     *
     * @param key The value's name (key).
     * @param value The value.
     * 
     * @exception RpalException if a value with the given key exists already or if
     *            the key's name is empty.
     */
    void setValue(string key, string value);
    
    /**
     * Returns all values in a map.
     *
     * @return A map containing all values (key-value pairs).
     */
    map<string, string> getValuesAsValueMap() const;
    
    /**
     * Returns all values as value string.
     *
     * @return A value string in the form "key1=value1:key2=value2:...", delimiters
     * ('=', ':') in the key or value part have to be escaped with '\'.
     */
    string getValuesAsValueString();
    
    /**
     * Sets values (existing ones will be overwritten).
     *
     * @param values A map containing all values (key-value pairs).
     */
    void setValues(map<string, string> values);
    
    /**
     * Sets values (existing ones will be overwritten).
     *
     * @param valueString A value string in the form "key1=value1:key2=value2:...",
     * delimiters ('=', ':') in the key or value part have to be escaped with '\'.
     */
    void setValues(string valueString);
    
    /**
     * Getter for a XmlRpcValue containing the ConnectorMessage's data.
     *
     * @return The XmlRpcValue.
     */
    XmlRpcValue getXmlRpcValue();


protected:
    /**
     * Converts a flat value string into a map with all values (key-value pairs).
     * 
     * @param valueString A value string in the form "key1=value1:key2=value2:...",
     * delimiters ('=', ':') in the key or value part have to be escaped with '\'.
     * @return A map containing all key-value pairs.
     * 
     * @exception RoalExeption on duplicate use of a key.
     */
    map<string, string> convertValueStringToValueMap(string valueString);
    
    /**
     * Converts a map with values into a flat value string.
     * 
     * @param valueMap A map containing key-value pairs.
     * @return A value string in the form "key1=value1:key2=value2:...", delimiters
     * ('=', ':') in the key or value part have to be escaped with '\'.
     */
    string convertValueMapToValueString(map<string, string> valueMap);
    
    /**
     * The message's session ID to authenticate with.
     */
    int sessionID;
    
    /**
     * The message's command.
     */
    string command;
    
    /**
     * The message's values (key value pairs).
     */
    map<string, string> values;


private:
    /**
     * Default constructor, may not be used.
     */
    ConnectorMessage();
};

}

#endif //_CONNECTORMESSAGE_H_
