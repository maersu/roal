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

#include "CreatureFactory.h"
using namespace std;
namespace Roal
{

//-----------------------------------------------------------------------------
CreatureFactory::CreatureFactory(string name)
{
    this->name = name;
}

//------------------------------------------------------------------------------
CreatureFactory::~CreatureFactory()
{

}

//------------------------------------------------------------------------------
string CreatureFactory::getName() 
{
    return this->name;
}

//------------------------------------------------------------------------------
string CreatureFactory::getCubeTextureFileName(int indexName)
{
    // Available textures
    if (0 > indexName || indexName > 27 )
    {
        throw(RoalException(typeid( this ).name(), 
                "Could not get CubeTextureFileName from index: "+toStdStr(indexName)));
    }
    
    string textures[28] = {"mat001.mesh", "mat002.mesh", "mat003.mesh", "mat004.mesh",
                          "mat005.mesh", "mat006.mesh", "mat007.mesh", "mat008.mesh",
                          "mat009.mesh", "mat010.mesh", "mat011.mesh", "mat012.mesh",
                          "mat013.mesh", "mat014.mesh", "mat015.mesh", "mat016.mesh",
                          "mat017.mesh", "mat018.mesh", "mat019.mesh", "mat020.mesh",
                          "mat021.mesh", "mat022.mesh", "mat023.mesh", "mat024.mesh",
                          "mat025.mesh", "mat026.mesh", "mat027.mesh", "mat028.mesh"};
    
    return textures[indexName];
}

//------------------------------------------------------------------------------
string CreatureFactory::getRandomCubeTextureFileName()
{
    return getCubeTextureFileName((int)(28*(rand()/(double)RAND_MAX)));
}


};
