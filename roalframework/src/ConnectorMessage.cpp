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

#include "ConnectorMessage.h"

namespace Roal
{

//------------------------------------------------------------------------------
ostream& operator<<(ostream& os, const ConnectorMessage& message)
{
    if (os) {
        
        string outputString;
        outputString.append("sid=");
        outputString.append(toStdStr(message.getSessionID()));
        outputString.append(" command=");
        outputString.append(message.getCommand());
        
        map<string, string> valueMap = message.getValuesAsValueMap();
        outputString.append(" value={");
        bool firstValue = true;
        for(map<string, string>::iterator it = valueMap.begin(); it != valueMap.end(); it++) {
            if (!firstValue) {
                outputString.append(",");
            } else {
                firstValue = false;
            }
            outputString.append("\""+it->first+"\"=>\""+it->second+"\"");
        }
        outputString.append("}");
        
        os.write(outputString.c_str(), outputString.size());
    }
    
    return os;
}

    
//------------------------------------------------------------------------------
ConnectorMessage::ConnectorMessage(string command)
{
    this->sessionID = 0;
    this->command = command;
}


//------------------------------------------------------------------------------
ConnectorMessage::ConnectorMessage(string command, string valueString)
{
    this->sessionID = 0;
    this->command = command;
    this->values = convertValueStringToValueMap(valueString);
}


//------------------------------------------------------------------------------
ConnectorMessage::ConnectorMessage(int sessionID, string command)
{
    this->sessionID = sessionID;
    this->command = command;
}


//------------------------------------------------------------------------------
ConnectorMessage::ConnectorMessage(int sessionID, string command, string valueString)
{
    this->sessionID = sessionID;
    this->command = command;
    this->values = convertValueStringToValueMap(valueString);
}


//------------------------------------------------------------------------------
ConnectorMessage::ConnectorMessage(XmlRpcValue xmlRpcValue)
{
    this->sessionID = xmlRpcValue["sid"];
    this->command = string(xmlRpcValue["command"]);
    this->values = convertValueStringToValueMap(string(xmlRpcValue["value"]));
}


//------------------------------------------------------------------------------
ConnectorMessage::~ConnectorMessage()
{
    
}


//------------------------------------------------------------------------------
void ConnectorMessage::setSessionID(int sessionID)
{
    this->sessionID = sessionID;
}


//------------------------------------------------------------------------------
int ConnectorMessage::getSessionID() const
{
    return sessionID;
}


//------------------------------------------------------------------------------
string ConnectorMessage::getCommand() const
{
    return command;
}


//------------------------------------------------------------------------------
bool ConnectorMessage::hasValue(string key)
{
    return (values.count(key) > 0);
}


//------------------------------------------------------------------------------
string ConnectorMessage::getValue(string key)
{
    if (!(this->hasValue(key))) {
        throw(RoalException(typeid(this).name(),
              "A value with key '"+key+"' does not exist"));
    } else {
        map<string, string>::iterator it;
        it = values.find(key);
        return it->second;
    }
}


//------------------------------------------------------------------------------
void ConnectorMessage::setValue(string key, string value)
{
    map<string, string>::iterator it;
    it = values.find(key);
    if (it != values.end()) {
        throw(RoalException(typeid(this).name(),
              "A value with key '"+key+"' exists already"));
    }
    if (key.size()==0) {
        throw(RoalException(typeid(this).name(),
              "Key must not be empty"));
    }
    
    values[key] = value;
}


//------------------------------------------------------------------------------
map<string, string> ConnectorMessage::getValuesAsValueMap() const
{
    return values;
}


//------------------------------------------------------------------------------
string ConnectorMessage::getValuesAsValueString()
{
    return convertValueMapToValueString(values);
}


//------------------------------------------------------------------------------
void ConnectorMessage::setValues(map<string, string> values)
{
    this->values = values;
}


//------------------------------------------------------------------------------
void ConnectorMessage::setValues(string valueString)
{
    values = convertValueStringToValueMap(valueString);
}


//------------------------------------------------------------------------------
XmlRpcValue ConnectorMessage::getXmlRpcValue()
{
    XmlRpcValue value;
    value["sid"] = this->sessionID;
    value["command"] = this->command;
    value["value"] = convertValueMapToValueString(values);
    
    return value;
}


//------------------------------------------------------------------------------
map<string, string> ConnectorMessage::convertValueStringToValueMap(string valueString)
{
    map<string, string> valueMap;
    ConnectorMessageTokenizer* tok = new ConnectorMessageTokenizer(valueString);
    KeyValuePair data;
    while (tok->hasMoreTokens()) {
        data = tok->nextToken();
        if (valueMap.count(data.key) > 0) {
            throw(RoalException(typeid(this).name(),
                  "Multiple use of key '"+data.key+"'"));
        } else {
            valueMap[data.key] = data.value;
        }
    }
    
    return valueMap;
}


//------------------------------------------------------------------------------
string ConnectorMessage::convertValueMapToValueString(map<string, string> valueMap)
{
    string valueString;
    
    for(map<string, string>::iterator it = valueMap.begin(); it != valueMap.end(); it++) {
        if (valueString.size() > 0) {
            valueString.append(KEYVALUE_PAIR_DELIMITER);
        }
        string key = it->first;
        string value = it->second;
        
        // Escape delimiters in key
        unsigned int pos = 0;
        while (pos < key.size() &&
               (pos = key.find(KEYVALUE_PAIR_DELIMITER, pos)) != string::npos) {
            key.insert(pos, ESCAPE_CHAR);
            pos = pos+2;
        }
        pos = 0;
        while (pos < key.size() &&
               (pos = key.find(KEYVALUE_DELIMITER, pos)) != string::npos) {
            key.insert(pos, ESCAPE_CHAR);
            pos = pos+2;
        }
        
        // Escape delimiters in value
        pos = 0;
        while (pos < value.size() &&
               (pos = value.find(KEYVALUE_PAIR_DELIMITER, pos)) != string::npos) {
            value.insert(pos, ESCAPE_CHAR);
            pos = pos+2;
        }
        pos = 0;
        while (pos < value.size() &&
               (pos = value.find(KEYVALUE_DELIMITER, pos)) != string::npos) {
            value.insert(pos, ESCAPE_CHAR);
            pos = pos+2;
        }
        
        valueString.append(key);
        valueString.append(KEYVALUE_DELIMITER);
        valueString.append(value);
    }
    
    return valueString;
}

}
