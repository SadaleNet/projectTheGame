class SpriteObject;

#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include "GameObject.h"

class SpriteObject: public GameObject{
protected:
	std::string imagePath;
	bool showWholeImage;
	Vec2 tilePos;
	Vec2 tileSize;
public:
	SpriteObject(Vec2 pos, Vec2 size, std::string imagePath);
	SpriteObject(Vec2 pos, Vec2 size, std::string imagePath, Vec2 tilePos, Vec2 tileSize);
	
	virtual void render() const override;

	//setters and getters
	SpriteObject& setTilePos(Vec2 tilePos);
	SpriteObject& setTile(Vec2 tilePos, Vec2 tileSize);
	SpriteObject& setImagePath(const std::string& imagePath){ this->imagePath = imagePath; return *this; }
	std::string getImagePath() const{ return imagePath; }

};

#endif