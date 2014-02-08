﻿#include "GameObject.h"
#include <stdexcept>
#include <cassert>

GameObject::GameObject(Vec2 pos, Vec2 size)
	:pos(pos),
	size(size),
	scene(nullptr),
	hovered(false),
	focused(false){
	for(int i=0; i<MOUSE_KEY_NUM; i++)
		this->held[i] = false;
}

void GameObject::update(){
	this->pos += this->vel*this->scene->getDeltaSec();
	this->updateHook();
	this->onStep();
}

bool GameObject::isCollide(const GameObject& b) const{
	return (b.pos.x+b.size.x > this->pos.x && b.pos.x < this->pos.x+this->size.x)
		&& (b.pos.y+b.size.y > this->pos.y && b.pos.y < this->pos.y+this->size.y);
}

bool GameObject::isCollide(const Vec2& p) const{
	return (p.x > this->pos.x && p.x < this->pos.x+this->size.x)
		&& (p.y > this->pos.y && p.y < this->pos.y+this->size.y);
}