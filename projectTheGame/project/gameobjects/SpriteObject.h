class SpriteObject;

#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include "GameObject.h"


/** @brief	A class for rendering sprite. Supports tiling.

	For tileIndex, tileSize:<br>
		When the image is tiled, tileIndex and tileSize are used to set the tiled pos.<br>
		If you have an image like this:<br>
		AB<br>
		CD<br>
		(Assumes that A, B, C and D are taking 50x50 pixels)<br>
		Then you should set tileSize to Vec2(50,50)<br>
		If you want A to be shown, then set tileIndex = Vec2(0,0)<br>
		If you want B to be shown, then set tileIndex = Vec2(1,0)<br>
		Similarly, tileIndex = Vec2(0,1) for C and tileIndex = Vec2(1,1) for D
*/
class SpriteObject: public GameObject{
public:
	//These variables are used when the is image tiled.
	std::string imagePath;

	Vec2 tileIndex;
	Vec2 tileSize;

	///ctor with the image untiled. Entire image is shown
	SpriteObject(Vec2 pos, Vec2 size, std::string imagePath);
	///ctor with the image tiled
	SpriteObject(Vec2 pos, Vec2 size, std::string imagePath, Vec2 tileIndex, Vec2 tileSize);

	virtual void render() const override;

};

#endif