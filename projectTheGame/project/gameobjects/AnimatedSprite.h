class AnimatedSprite;

#ifndef ANIMATED_SPRITE_OBJECT_H
#define ANIMATED_SPRITE_OBJECT_H

#include "SpriteObject.h"

class AnimatedSprite: public SpriteObject{
protected:
	double lastUpdateTime;
public:
	double timePerFrame;
	int frameNum;

	AnimatedSprite(Vec2 pos, Vec2 size, std::string imagePath, Vec2 tileSize, double timePerFrame, int frameNum);
	
	//Updates sprite.tilePos
	virtual void updateHook() override;
};

#endif