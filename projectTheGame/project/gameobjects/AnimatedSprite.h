class AnimatedSprite;

#ifndef ANIMATED_SPRITE_OBJECT_H
#define ANIMATED_SPRITE_OBJECT_H

#include "SpriteObject.h"

/**	@brief	A class for simple sprite animation with the use of sprite tiling.<br>
			Columns being frames of animation. Rows being sets of frames.
	@note	To set the frame being displayed, set tileIndex.x to some value.<br>
			To set the sprite being used, set tileIndex.y to some value.
*/
class AnimatedSprite: public SpriteObject{
protected:
	double lastUpdateTime;
public:
	double timePerFrame; ///time being displayed for each frame of the image
	int frameNum; ///number of frame that is currently being displayed.

	/**	@param	pos		position of the object
		@param	size	size of the object
		@param	imagePath	path to the image
		@param	tileSize		the size of each frame of animation, in pixels
		@param	timePerFrame	time being displayed for each frame of the image
		@param	frameNum		number of frames of the animation
	*/
	AnimatedSprite(Vec2 pos, Vec2 size, std::string imagePath, Vec2 tileSize, double timePerFrame, int frameNum);
	
	//Shifts tilePos.x when it should
	virtual void updateHook() override;
};

#endif