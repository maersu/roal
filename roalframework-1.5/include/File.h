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
#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include "RoalException.h"

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * A simple file class for read/write operations.
 * 
 * Use this Class to write to a new or an existing text file.
 * 
 * @todo Support some read methods 
 *  
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */ 
class File
{
public:
    /**
     * Constructor.
     * 
     * Opens the File named by path and associates a stream with it.
     * 
     * @param path The path and the file name.
     */ 
    File(const string path);
    
    /**
     * Destructor.
     */
    ~File();
    
    /**
     * Writes a given string to the file.
     * 
     * @param The String which should written to the file
     */
    void write( const string s );
    
    /**
     * Writes a given string to the file appends a new line.
     * 
     * @param s The String which should written to the file
     */
    void writeln( const string s );
    
    /**
     * Writes a single new line.
     */
    void writeln();
    
    /**
     * Replaces single char.
     */
    void replace(char search, char replace);
    
    /**
     * Deletes the contents of a file to overwrite them.
     */
    void reset();
    
    /**
     * Returns true if the file exists, false otherwise.
     */
    bool exists();
    
protected:
    /**
     * Tests the given stream for an end-of-file indicator.
     * Once the indicator is set read operations on the file
     * return true until rewind is called or the file
     * is closed. The end-of-file indicator is reset with each
     * input operation.
     * 
     * @return True if an end-of-file indicator is reached
     */
     bool isEndOfFile( void ) const;
    
    /**
     * Checks if valid stream has been allocated.
     * 
     * @exception RoalException if the file instance is no valid
     */
    void checkValidInstance( void ) const;
    
    /**
     * Flushes the File. If the given File has buffered
     * output flush writes the output for File to the associated file.
     * 
     * @exception RoalException if a IO error occured
     */
    void flush( void );
    
    /**
     * Holds the File Stream
     */
    FILE* fp;
    
    /**
     * Holds the file name (incl. path if used)
     */
    string fileName;
    
private:
    /**
     * The default constructor may not be used.
     * 
     * @exception RoalException if this method is called.
     */
    File();
    
    /**
     * Copy Constructor.
     *
     * This is not allowed because there may be only one single instance of a 
     * specific file.
     * 
     * @exception Throws a RoalException if this method is called
     */
    File( const File& f );
    
    /**
     * Assignment Operator.
     *
     * This is not allowed because there may be only one single instance of a 
     * specific file.
     * 
     * @exception Throws a RoalException if this method is called
     */
    File& operator=( const File& f );
};

}

#endif //_FILE_H_
