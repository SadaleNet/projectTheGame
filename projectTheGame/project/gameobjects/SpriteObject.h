class SpriteObject;

#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include "GameObject.h"

class SpriteObject: public GameObject{
public:
	//These variables are used when the is image tiled.
	std::string imagePath;
	
	/** @brief	When the image is tiled, tileIndex and tileSize are used to set the tiled pos.
				For example, if you have a enemy.png contains a image of a normal enemy and a freezed enemy,
				you can change the part of image being used by this function.
				If tileSize == Vec(0,0), then the whole image is shown.
	*/
	Vec2 tileIndex;
	Vec2 tileSize;

	SpriteObject(Vec2 pos, Vec2 size, std::string imagePath);
	SpriteObject(Vec2 pos, Vec2 size, std::string imagePath, Vec2 tileIndex, Vec2 tileSize);
	
	virtual void render() const override;

};

#endif