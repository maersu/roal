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

#include <RoalFramework/RoalCore.h>
#include <RoalFramework/Connector.h>
#include "DDWalkerMaster.h"

using namespace Roal;
using Roal::World;
using namespace std;

int main(int argc, char *argv[])
{
    try {
        if (argc != 3) {  
            cerr << "Usage: WalkerMaster [Master IP address] [Master listener port]" << endl;  
            return -1;
        }
    
        DDWalkerMaster* master = new DDWalkerMaster(string(argv[1]),atoi(argv[2]), 100, 4);
        master->run();
        
    } catch (RoalException& e) {
        e.print();
    }    
        
    return 0;
}
