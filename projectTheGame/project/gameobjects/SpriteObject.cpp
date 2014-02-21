#include "SpriteObject.h"

SpriteObject::SpriteObject(Vec2 pos, Vec2 size, std::string imagePath)
	:GameObject(pos, size),
	imagePath(imagePath),
	tileSize(Vec2(0,0)){
}

SpriteObject::SpriteObject(Vec2 pos, Vec2 size, std::string imagePath, Vec2 tileIndex, Vec2 tileSize)
	:GameObject(pos, size),
	imagePath(imagePath),
	tileIndex(tileIndex),
	tileSize(tileSize){
}