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

#include "ConnectorMessageTokenizer.h"

namespace Roal
{

//------------------------------------------------------------------------------
ConnectorMessageTokenizer::ConnectorMessageTokenizer(string valueString)
{
    this->valueString = valueString;
    this->it = valueString.begin();
}


//------------------------------------------------------------------------------
ConnectorMessageTokenizer::~ConnectorMessageTokenizer()
{
    
}


//------------------------------------------------------------------------------
bool ConnectorMessageTokenizer::hasMoreTokens()
{
    return it != valueString.end();
}


//------------------------------------------------------------------------------
KeyValuePair ConnectorMessageTokenizer::nextToken()
{
    KeyValuePair data;
    
    // Define states
    const int READING_KEY = 1; // Reading key part
    const int READING_VALUE = 2; // Reading value part
    const int FINISHED_PAIR = 3; // Key-value pair is finished
    int state = READING_KEY;
    
    // Walk through the value string
    while(state != FINISHED_PAIR && it != valueString.end()) {
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
        } else if (state == READING_KEY && *it == *KEYVALUE_PAIR_DELIMITER
                   || state == READING_VALUE && *it == *KEYVALUE_DELIMITER) {
            throw(RoalException(typeid( this ).name(), "Malformed value string"));
        }
        
        // The character is part of the key or value string
        if (state == READING_KEY) {
            data.key.append(1, *it);
        } else if (state == READING_VALUE) {
            data.value.append(1, *it);
        }
        *it++;
    }
    
    return data;
}

}
