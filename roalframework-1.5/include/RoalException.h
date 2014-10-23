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
#ifndef _ROALEXCEPTION_H_
#define _ROALEXCEPTION_H_

#include <iostream>

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * Exception class for the Roal Framework.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class RoalException
{
public:
    /**
     * Constructor
     * 
     * @param className The name of the class.
     * @param message The error message.
     */
    RoalException(std::string className, std::string message) 
    {
        this->message = message;
        this->className = " in "+className;
    };

    /**
     * Constructor
     * 
     * @param message The error message.
     */
    RoalException(std::string message) 
    {
        this->message = message;
        this->className = "";
    };

    
    /**
     * Returns the exception message.
     * 
     * @return the exception message.
     */
    virtual std::string getMessage(void) {
        return this->message;
    };
    
    /**
     * Prints the error message to std::cerr.
     */
    virtual void print() 
    {
        std::cerr << std::endl<< "A RoalException occurs: "<< className << std::endl << "    "<< message << std::endl << std::endl;
    };
        
protected:

    /**
     * The exception's error message.
     */
    std::string message;
    
    /**
     * The class name that threw the exception.
     */
    std::string className;
};

}



#endif //_ROALEXCEPTION_H_
