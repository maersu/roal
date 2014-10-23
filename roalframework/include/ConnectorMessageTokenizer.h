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
#ifndef _CONNECTORMESSAGETOKENIZER_H_
#define _CONNECTORMESSAGETOKENIZER_H_

#include <stdio.h>
#include <string>
#include "RoalCore.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * The delimiter that separates key-value pairs.
 */
static const char* KEYVALUE_PAIR_DELIMITER = ":";

/**
 * The delimiter that separates key from value.
 */
static const char* KEYVALUE_DELIMITER = "=";

/**
 * The escape character that escapes the delimiters.
 */
static const char* ESCAPE_CHAR = "\\";


/**
 * A struct used in ConnectorMessageTokenizer that contains a key-value pair.
 */
struct KeyValuePair {
    string key;
    string value;
};
    

/**
 * The tokenizer for the ConnectorMessage's value.
 * 
 * Explodes key value pairs from a ConnectorMessage's flat value string.
 *  
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */ 
class ConnectorMessageTokenizer
{
public:
    /**
     * Constructor.
     * 
     * @param valueString The flat value string containing separated key-value pairs.
     * @param keyValuePairDelimiter The delimiter that separates key-value pairs.
     * @param keyValueDelimiter The delimiter that separates key from value.
     */ 
    ConnectorMessageTokenizer(string valueString);
    
    /**
     * Destructor.
     */
    ~ConnectorMessageTokenizer();
    
    /**
     * Check if more tokens are available.
     * 
     * @return true if more tokens are available.
     */
    bool hasMoreTokens();
    
    /**
     * Get the next token.
     * @return The next token as KeyValuePair.
     */
    KeyValuePair nextToken();


protected:
    /**
     * The flat value string containing separated key-value pairs.
     */
    string valueString;

    /**
     * The actual position in the valueString
     */
    string::iterator it;


private:
    /**
     * Default constructor, may not be used.
     */
    ConnectorMessageTokenizer();
};

}

#endif //_CONNECTORMESSAGETOKENIZER_H_
