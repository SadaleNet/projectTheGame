#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(Vec2 pos, Vec2 size, std::string imagePath, Vec2 tileSize, double timePerFrame, int frameNum)
	:SpriteObject(pos, size, imagePath, Vec2(0,0), tileSize),
	lastUpdateTime(-1),
	timePerFrame(timePerFrame),
	frameNum(frameNum){
}

void AnimatedSprite::updateHook(){
	if(this->lastUpdateTime==-1)
		this->lastUpdateTime = this->getScene()->getSec();

	if(this->getScene()->getSec() > this->lastUpdateTime+this->timePerFrame){
		this->tileIndex.x = (static_cast<int>(this->tileIndex.x)+1)%this->frameNum;
		this->lastUpdateTime += this->timePerFrame;
	}
}