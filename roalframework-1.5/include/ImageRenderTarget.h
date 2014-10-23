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
    along with Roal; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _IMAGERENDERTARGET_H_
#define _IMAGERENDERTARGET_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <OGRE/OgreRenderTarget.h>

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/**
 * This class can be used as a render target in the EyeSegment.
 * 
 * @warning This Segment is for experimental usage. At the moment the ImageRenderTarget
 * is not usfull. Use at your own fun/risk.
 *   
 * @todo implement the whole class!
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class ImageRenderTarget : public Ogre::RenderTarget
{
public:
	ImageRenderTarget();
	
	/** 
	 * Overridden - see Ogre::RenderTarget.
     */
	void writeContentsToFile(const Ogre::String& filename);
};

}
#endif //IMAGERENDERTARGET

