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

#include "ValueHandler.h"

namespace Roal
{

//-----------------------------------------------------------------------------
ValueHandler::ValueHandler()
{

}
    
//------------------------------------------------------------------------------
ValueHandler::~ValueHandler()
{
}

//-----------------------------------------------------------------------------
void ValueHandler::copyFrom(ValueHandler* handler)
{
    values.clear();
    std::map< string, float> fromMap = handler->getValuesAsValueMap();
    for(std::map<string, float>::iterator it = fromMap.begin(); it != fromMap.end(); it++)
    {
        this->setValue(it->first, it->second);
    }
}

//------------------------------------------------------------------------------
bool ValueHandler::hasValue(string key)
{
    return (values.count(key) > 0);
}


//------------------------------------------------------------------------------
float ValueHandler::getValue(string key)
{
    if (!(this->hasValue(key))) {
        throw(RoalException(typeid(this).name(),
              "A value with key '"+key+"' does not exist"));
    } else {
        std::map<string, float>::iterator it;
        it = values.find(key);
        return it->second;
    }
}


//------------------------------------------------------------------------------
void ValueHandler::setValue(string key, float value)
{
    if (hasValue(key)) {
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
int ValueHandler::getValuesCount()
{
    return values.size();
}


//------------------------------------------------------------------------------
string ValueHandler::toString(string valueDelimiter, string separator)
{
    string valueString;
    
    for(std::map<string, float>::iterator it = values.begin(); it != values.end(); it++) {
        if (valueString.size() > 0) {
            valueString.append(separator);
        }
        string key = it->first;
        float value = it->second;
        
        valueString.append(key);
        valueString.append(valueDelimiter);
        valueString.append(toStdStr(value));
    }
    
    return valueString;
}

//------------------------------------------------------------------------------
string ValueHandler::toString()
{
    return this->toString(DEFAULT_VALUE_DELIMITER, DEFAULT_VALUEPAIR_DELIMITER);
}


//------------------------------------------------------------------------------
std::map<string, float> ValueHandler::getValuesAsValueMap() const
{
    return values;
}

//------------------------------------------------------------------------------
void ValueHandler::setValues(string valueString, int keyValuePairCount)
{
    values = convertValueStringToValueMap(valueString, keyValuePairCount);
}

//------------------------------------------------------------------------------
map<string, float> ValueHandler::convertValueStringToValueMap(string valueString, int keyValuePairCount)
{
    map<string, float> valueMap;

    this->valueString = valueString;
    this->it = valueString.begin();

    KeyValue data;
    for (int i = 1; i<=keyValuePairCount;i++) {
        data = this->nextToken();
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
ValueHandler* ValueHandler::crossWith(ValueHandler* partner, std::vector<string> partnerValues, std::vector<string> thisValues)
{
    // Generate the successor's Genotype
    ValueHandler* successor  = new ValueHandler();
    
    int count = this->getValuesAsValueMap().size();
        
    if (partner->getValuesAsValueMap().size() != this->getValuesAsValueMap().size())
    {
        throw(RoalException(typeid( this ).name(), "Could not cross values: Not the same number of values"));
    }
    
    // Add Partners Value
    for(std::vector<string>::iterator partnerIt = partnerValues.begin(); partnerIt != partnerValues.end(); partnerIt++) {
       
        if (partner->hasValue(*partnerIt))
        {
            successor->setValue(*partnerIt, partner->getValue(*partnerIt));
        } else {
            throw(RoalException(typeid( this ).name(), "Could not cross values: Partner Value not Found"));
        }
    } 

    // Add This Value
    for(std::vector<string>::iterator thisIt = thisValues.begin(); thisIt != thisValues.end(); thisIt++) {
       
        if (this->hasValue(*thisIt))
        {
            successor->setValue(*thisIt, this->getValue(*thisIt));
        } else {
            throw(RoalException(typeid( this ).name(), "Could not cross values: This alue not Found: "));
        }
    } 
    
   // std::cout << "--- CROSS WITH ---\n" << "THIS: "+this->toString() +"\n" << "PARTNER: "+partner->toString() +"\n" << "SUCCESSOR: "+successor->toString() +"\n" << std::endl;
    
    return successor;
}

//------------------------------------------------------------------------------
bool ValueHandler::hasMoreTokens()
{
    return it != this->valueString.end();
}

//------------------------------------------------------------------------------
KeyValue ValueHandler::nextToken()
{
    KeyValue data;
    
    // Define states
    const int READING_KEY = 1; // Reading key part
    const int READING_VALUE = 2; // Reading value part
    const int FINISHED_PAIR = 3; // Key-value pair is finished
    int state = READING_KEY;
    const char* KEYVALUE_PAIR_DELIMITER = ":";
    const char* KEYVALUE_DELIMITER = "=";
    const char* ESCAPE_CHAR = "\\";
    string tmpValue; 
    // Walk through the value string
    while(state != FINISHED_PAIR && it != this->valueString.end()) {
        char nextChar = *++it; *it--;
        

        if (*it == *ESCAPE_CHAR && (nextChar == *KEYVALUE_DELIMITER
            || nextChar == *KEYVALUE_PAIR_DELIMITER)) {
            // Omit escape character
            *it++;
        } else if (state == READING_KEY && *it == *KEYVALUE_DELIMITER) {
            // Key-value delimiter found (key is finished)
            *it++;
            state = READING_VALUE;
        } else if (state == READING_VALUE && *it == *KEYVALUE_PAIR_DELIMITER) {
            // Pair delimiter found (key-value pair is finished)
            state = FINISHED_PAIR;
        }
        
        // The character is part of the key or value string
        if (state == READING_KEY) {
            data.key.append(1, *it);
            
        } else if (state == READING_VALUE) {
            tmpValue.append(1, *it);
        }
        *it++;
    }
        
    data.value = atof(tmpValue.c_str()); 
    return data;
}



}
