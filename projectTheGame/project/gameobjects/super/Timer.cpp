#include "Timer.h"

Timer::Timer(std::function<void()> action, double timeout, bool absolute)
	:GameObject(Vec2(0,0), Vec2(0,0)),
	action(action),
	absolute(absolute),
	timeout(timeout){
}

void Timer::updateHook(){
	if( this->getScene()->getSec() >= this->timeout ){
		this->execute();
	}
}

void Timer::onSceneAdded(){
	this->timeout = this->absolute?this->timeout:this->getScene()->getSec()+this->timeout;
	if( this->getScene()->getSec() > this->timeout ){
		this->execute();
	}
}

void Timer::execute(){
	this->action();
	this->destroy();
}