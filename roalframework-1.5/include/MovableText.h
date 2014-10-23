/**     
    This file is part of the Ogre DSISceneManager and is used by Roal, a
    framework for simulations in the field of Artificial Intelligence and
    Aritificial Life.
    See http://roal.sourceforge.net/ for more informations.

    Original Version: Copyright (c) 2003 by cTh, gavocanov@rambler.ru
    Modifications: Copyright (c) 2005 Project Roal
    
    We do not know the licensing terms of the original file. If possible, the
    modifications made by the Roal project, should be released under the terms
    of the GNU General Public License.
*/

#ifndef _MOVABLETEXT_H_
#define _MOVABLETEXT_H_

#include <Ogre.h>
#include <OgreKeyEvent.h>
#include <OgreEventListeners.h>
#include <OgreString.h>
#include <OgreMovableObject.h>
#include <OgreColourValue.h>
#include <OgreOverlay.h>
#include <OgreRenderWindow.h>
#include <OgreFrameListener.h>
#include <OgreSingleton.h>
#include <OgreSceneManager.h>
#include <OgreLight.h>
#include <OgreRenderWindow.h>
#include <OgreOverlay.h>
#include <OgreStringConverter.h>
#include <OgreFontManager.h>
#include <OgreCamera.h>
#include <OgreResourceManager.h>
#include <OgreMaterialManager.h>
#include <OgreBillboardSet.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreConfigFile.h>
#include <OgreFont.h>

using namespace std;
using namespace Ogre;

namespace Roal
{

/**
 * Displays in-simulation text above objects in the scene.
 * 
 * This class is part of the Ogre DSISceneManager. It displays text that is
 * rendered as a billboard, e.g. above some (possible moving) object in the scene.
 * It may look like this:
 * @image html MovableText.png
 * @image latex MovableText.ps
 */
class MovableText : public MovableObject, public Renderable
{
public:
    /**
     * Constructor.
     * 
     * @param name The name of the SceneNode.
     * @param caption The text that will be displayed.
     * @param fontName The name of the font to use, this has to be defined in an
     *                 Ogre fontdef-file (default is TrebuchetMSBold).
     * @param charHeight The character height (default is 16).
     * @param color The color of the font (default is ColorValue::White).
     */
    MovableText(const String &name, const String caption,
                const String &fontName = "TrebuchetMSBold", int charHeight = 16,
                const ColourValue &color = ColourValue::White);
    
    /**
     * Deconstructor.
     */
    virtual ~MovableText();
    
    /**
     * Sets a given font.
     * 
     * @param fontName The name of the font to use, this has to be defined in an
     *                 Ogre fontdef-file.
     */
    void setFontName(const String &fontName);
    
    /**
     * Sets the text that will be displayed.
     * 
     * @param caption The text that will be displayed.
     */
    void setCaption(String caption);
    
    /**
     * Sets the text color.
     * 
     * @param color The color of the font as ColorValue.
     */
    void setColor(const ColourValue &color);
    
    /**
     * Sets the character height.
     * 
     * @param height The character height.
     */
    void setCharacterHeight(Ogre::uint height);
    
    /**
     * Sets the spece with.
     * 
     * @param width The space width.
     */
    void setSpaceWidth(Ogre::uint width);
    
    /**
     * Defines whether to show the text above all objects or not.
     * 
     * @param show true if the text should be displayed above objects, false otherwise.
     */
    void showOnTop(bool show);
    
    /**
     * Returns the text that is displayed.
     * 
     * @return The text that is displayed.
     */
    String getCaption() const {return mCaption;}
    
    /**
     * Returns the name of the font that is used.
     * 
     * @return The name of the font that is used.
     */
    const String &getFontName() const {return mFontName;}
    
    /**
     * Returns the character height.
     * 
     * @return The current character height.
     */
    Ogre::uint getCharacterHeight() const {return mCharHeight;}
    
    /**
     * Returns the space width.
     * 
     * @return The currect space width.
     */
    Ogre::uint getSpaceWidth() const {return mSpaceWidth;}
    
    /**
     * Returns the font color that is used.
     * 
     * @return The font color that is used.
     */
    const ColourValue &getColor() const {return mColor;}
    
    /**
     * Returns whether the text is displayed above all other objects or not.
     * 
     * @return true if the text is displayed above all other object, false otherwise.
     */
    bool getShowOnTop() const {return mOnTop;}

private:
    /**
     * The name of the font.
     */
    String			mFontName;
    
    /**
     * The font type (truetype or image).
     */
    String			mType;
    
    /**
     * The name of the node.
     */
    String			mName;
    
    /**
     * The text that is displayed.
     */
    String			mCaption;
    
    /**
     * The color of the displayed text.
     */
    ColourValue		mColor;
    
    /**
     * The render operation (internal use).
     */
    RenderOperation	mRenderOp;
    
    /**
     * The axis aligned box (internal use).
     */
    AxisAlignedBox	mAABB;
    
    /**
     * The light list (internal use).
     */
    LightList		mLList;
    
    /**
     * The height of the displayed characters.
     */
    Ogre::uint			mCharHeight;
    
    /**
     * The space width of the displayed characters.
     */
    Ogre::uint			mSpaceWidth;
    
    /**
     * A flag to sign whether to update the text.
     */
    bool			mNeedUpdate;
    
    /**
     * A flag to sign whether to update the colors.
     */
    bool			mUpdateColors;
    
    /**
     * A flag to sign whether the text is displayed above all other objects.
     */
    bool			mOnTop;
    
    /**
     * The time until the next toggle (internal use).
     */
    Real			mTimeUntilNextToggle;
    
    /**
     * The radius (internal use).
     */
    Real			mRadius;
    
    /**
     * An instance of the camera.
     */
    Camera			*mpCam;
    
    /**
     * An instance of the RenderWindow.
     */
    RenderWindow	*mpWin;
    
    /**
     * The font that is chosen.
     */
    Font			*mpFont;
    
    /**
     * The material that is used to display the text.
     */
    MaterialPtr		mpMaterial;

    /**
     * Translate from 3D to 2D view.
     */
    Vector3 _translate3Dto2D(Camera *pCam, const Vector3 vertex);
    
    /**
     * Translate pixels from 3D to 2D view.
     */
    void	_translate3Dto2DPixels(Camera *pCam, const Vector3 vertex, int *x, int *y);
    
    /**
     * Renders the text.
     */
    void	_setupGeometry();
    
    /**
     * Sets the colors.
     */
    void	_updateColors();

    // from MovableObject
    void getWorldTransforms(Matrix4 *xform) const;
    const Quaternion& getWorldOrientation(void) const;
    const Vector3& getWorldPosition(void) const;
    void _notifyCurrentCamera(Camera *cam);
    void _updateRenderQueue(RenderQueue* queue);

    const AxisAlignedBox &getBoundingBox(void) const {return mAABB;};
    const String &getName(void) const {return mName;};
    const String &getMovableType(void) const {static Ogre::String movType = "MovableText"; return movType;};
    Real getBoundingRadius(void) const {return mRadius;};
    Real getSquaredViewDepth(const Camera *cam) const {return 0;};

    // from renderable
    void getRenderOperation(RenderOperation &op);
    const MaterialPtr& getMaterial(void) const {assert(!mpMaterial.isNull());return mpMaterial;};
    const LightList& getLights(void) const {return mLList;};
};

}

#endif //_MOVABLETEXT_H_
