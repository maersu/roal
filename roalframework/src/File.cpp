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

#include "File.h"

namespace Roal
{
    
//------------------------------------------------------------------------------
File::File(const string path)
{
    fileName = path;
    
    // Check if the file instance is valid
    /*fp = fopen(fileName.c_str(), "r");
    this->checkValidInstance();
    fclose(fp);*/
}


//------------------------------------------------------------------------------
File::~File()
{

}


//------------------------------------------------------------------------------
void File::write(const string s)
{
    fp = fopen(fileName.c_str(), "a");
    
    fputs(s.c_str(), fp);
    this->flush();
    
    fclose(fp);
}


//------------------------------------------------------------------------------
void File::writeln(const string s)
{
    fp = fopen(fileName.c_str(), "a");
    
    fputs(s.c_str(), fp);
    fputs("\n", fp);
    this->flush();
    
    fclose(fp);
}


//------------------------------------------------------------------------------
void File::writeln()
{
    fp = fopen(fileName.c_str(), "a");
    
    fputs("\n", fp);
    this->flush();
    
    fclose(fp);
}


//------------------------------------------------------------------------------
void File::replace(char search, char replace)
{
    int ch;
    fpos_t pos;
    
    FILE *fp = fopen(fileName.c_str(), "r+");

    rewind(fp);
    fgetpos(fp, &pos);       
    
    ch = fgetc(fp);
    
    while (ch != EOF) {
        if (ch == (int)(search)) {
            fseek(fp, -1, SEEK_CUR); 
            fputc((int) replace, fp);
        }
        ch = fgetc(fp);
    }
    
    fsetpos(fp, &pos);
    
    fclose(fp);
}


//------------------------------------------------------------------------------
void File::reset()
{
    fp = fopen(fileName.c_str(), "w");
    fclose(fp);
}


//------------------------------------------------------------------------------
bool File::exists()
{
    int ret;
    ret = access(this->fileName.c_str(), F_OK);
    
    return (ret == 0);
}


//------------------------------------------------------------------------------
void File::flush(void)
{
    int ret = fflush(fp);
    if (ret != 0) {
        throw(RoalException(typeid(this).name(), 
              "File IO Error:" + this->fileName));
    }
}


//------------------------------------------------------------------------------
bool File::isEndOfFile(void) const
{
    return feof(fp);
}


//------------------------------------------------------------------------------
void File::checkValidInstance(void) const
{
    if (!fp) {
        throw(RoalException(typeid(this).name(), 
              "Invalid File Instance:" +this->fileName));
    }
}


//------------------------------------------------------------------------------
File::File()
{
    throw(RoalException(typeid(this).name(), 
          "The default constructor may not be used."));
}


//------------------------------------------------------------------------------
File::File(const File& f)
{
    throw(RoalException(typeid(this).name(), 
          "Copy constructor may not be used: This is not allowed because there may be only one single instance of a specific file"));
}


//------------------------------------------------------------------------------
File& File::operator=(const File& f)
{
    throw(RoalException(typeid(this).name(), 
          "Assigment operator may not be used: This is not allowed because there may be only one single instance of a specific file"));
}

}
