#include "SpriteObject.h"

SpriteObject::SpriteObject(Vec2 pos, Vec2 size, std::string imagePath)
	:GameObject(pos, size),
	imagePath(imagePath),
	showWholeImage(true){
}

SpriteObject::SpriteObject(Vec2 pos, Vec2 size, std::string imagePath, Vec2 tilePos, Vec2 tileSize)
	:GameObject(pos, size),
	imagePath(imagePath),
	tilePos(tilePos),
	tileSize(tileSize),
	showWholeImage(false){
}

SpriteObject& SpriteObject::setTilePos(Vec2 tilePos){
	this->showWholeImage = false;
	this->tilePos = tilePos;
	return *this;
}

//TODO: does it even make sense to change the size of the tile? Should I remove this method?
SpriteObject& SpriteObject::setTile(Vec2 tilePos, Vec2 tileSize){
	this->showWholeImage = false;
	this->tilePos = tilePos;
	this->tileSize = tileSize;
	return *this;
}