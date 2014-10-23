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
#ifndef _VALUEHANDLER_H_
#define _VALUEHANDLER_H_

#include <string>
#include <map>
#include <vector>
#include "Util.h"
#include "RoalException.h"
#include "Definitions.h"

namespace Roal
{

/**
 * A struct used in ConnectorMessageTokenizer that contains a key-value pair.
 */
struct KeyValue {
    string key;
    float value;
};      
 
/**
 * The ValueHandler Class supports some general methods to deal with Values and Keys.
 *    
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class ValueHandler
{
    
 
    
public:
    /**
     * Constructor
     */
	ValueHandler();
    
    /**
     * Destructor
     */
	virtual ~ValueHandler();
        
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
     * @exception Exception if a value with the given key does not exist.
     */
    float getValue(string key);
    
    /**
     * Setter for a value with key.
     *
     * @param key The value's name (key).
     * @param value The value.
     * @exception Exception if a value with the given key exists already or if
     *            the key's name is empty.
     */
    void setValue(string key, float value);
    
    /**
     * Returns the amount of values stored in this ValueHandler object.
     * 
     * @return The amount of registered values.
     */
    int getValuesCount();
    
    /**
     * Constructor 
     * 
     * Creates a ValueHandler with the Values given in handler.
     */
	void copyFrom(ValueHandler* handler);

    /**
     * creates a string with all keys and values
     *
     * @param valueDelimiter the string to separate key and value 
     * keypair ::=<key><valueDelimiter><value>.
     * @param valueDelimiter the string to separate key and value 
     * result ::=<keypair><separator><keypair>.
     * @return the concatenated string.
     */
    string toString(string valueDelimiter, string separator);

    /**
     * creates a string with all keys and values
     *
     * keypair ::=<key>DEFAULT_VALUE_DELIMITER<value>
     *
     * result ::=<keypair>DEFAULT_VALUEPAIR_DELIMITER<keypair>.
     *
     * @return the result
     */
    string toString();
    
    /**
     * returns the stored value in a map (key string)(value float)
     */
    std::map<string, float> getValuesAsValueMap() const;
 
    /**
     * Sets values (existing ones will be overwritten).
     *
     * @param valueString A value string in the form "key1=value1:key2=value2:...",
     * delimiters ('=', ':') in the key or value part have to be escaped with '\'.
     */
    void setValues(string valueString, int keyValuePairCount);

    /**
     * Crosses the given ValueHandler with this ValueHandler.
     *
     * @param partner the ValueHandler to cross with.
     * @param partnerValues the Keys which are take from the partner.
     * @param thisValues the Keys which are take from this ValueHandler.
     * @return A new ValueHandler generated from this and partner
     *
     * @exception RoalException
     */
    ValueHandler* crossWith(ValueHandler* partner, std::vector<string> partnerValues, std::vector<string> thisValues);

protected:
    /**
     * The ValueHandlers's values (key value)
     */
    std::map<string, float> values;


private:
    /**
     * Converts a flat value string into a map with all values (key-value pairs).
     * 
     * @param valueString A value string in the form "key1=value1:key2=value2:...",
     * @return A map containing all key-value pairs.
     * 
     * @exception RoalExeption on duplicate use of a key.
     */
    map<string, float> convertValueStringToValueMap(string valueString, int keyValuePairCount);

    /**
     * Check if more tokens are available.
     * 
     * @return true if more tokens are available.
     */
    bool hasMoreTokens();
    
    /**
     * Get the next token.
     * @return The next token as KeyValue.
     */
    KeyValue nextToken();
    
    /**
     * The flat value string containing separated key-value pairs.
     */
    string valueString;

    /**
     * The actual position in the valueString
     */
    string::iterator it;
};

}

#endif //_VALUEHANDLER_H_
