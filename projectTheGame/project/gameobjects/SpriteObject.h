class SpriteObject;

#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include "GameObject.h"

class SpriteObject: public GameObject{
protected:
	std::string imagePath;
	bool showWholeImage;

	//These variables are used when the is image tiled.
	Vec2 tilePos;
	Vec2 tileSize;
public:
	SpriteObject(Vec2 pos, Vec2 size, std::string imagePath);
	SpriteObject(Vec2 pos, Vec2 size, std::string imagePath, Vec2 tilePos, Vec2 tileSize);
	
	virtual void render() const override;

	//setters and getters
	/**	@brief	Similar to setTile() with tileSize unchanged.
		@see	setTile
	*/
	SpriteObject& setTilePos(Vec2 tilePos);
	/** @brief	When the image is tiled, this function can be used to set the tiled pos.
				For example, if you have a enemy.png contains a image of a normal enemy and a freezed enemy,
				you can change the part of image being used by this function.
	*/
	SpriteObject& setTile(Vec2 tilePos, Vec2 tileSize);
	SpriteObject& setImagePath(const std::string& imagePath){ this->imagePath = imagePath; return *this; }
	std::string getImagePath() const{ return imagePath; }

};

#endif