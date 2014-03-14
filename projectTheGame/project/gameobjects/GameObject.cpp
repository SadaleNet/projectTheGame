#include "GameObject.h"
#include "Panel.h"
#include <stdexcept>
#include <cassert>

GameObject::GameObject(Vec2 pos, Vec2 size, bool detectMouseEvents, bool detectKeyEvents, bool detectCollisionEvents)
	:pos(pos),
	size(size),
	scene(nullptr),
	parent(nullptr),
	hovered(false),
	focused(false),
	hidden(false),
	detectMouseEvents(detectMouseEvents),
	detectKeyEvents(detectKeyEvents),
	detectCollisionEvents(detectCollisionEvents){
	for(int i=0; i<MOUSE_KEY_NUM; i++)
		this->held[i] = false;
}

void GameObject::update(){
	assert( this->getScene() != nullptr );
	this->pos += this->getAbsVel()*this->getScene()->getDeltaSec();
	this->updateHook();
	this->onStep();
}

bool GameObject::isCollide(const GameObject& b) const{
	return (b.getAbsPos().x+b.size.x > this->getAbsPos().x && b.getAbsPos().x < this->getAbsPos().x+this->getAbsPos().x)
		&& (b.getAbsPos().y+b.size.y > this->getAbsPos().y && b.getAbsPos().y < this->getAbsPos().y+this->getAbsPos().y);
}

bool GameObject::isCollide(const Vec2& p) const{
	return (p.x > this->getAbsPos().x && p.x < this->getAbsPos().x+this->size.x)
		&& (p.y > this->getAbsPos().y && p.y < this->getAbsPos().y+this->size.y);
}

//since this->scene holds the ownership of this, by deregistering this from this->scene, the object is destroyed.
void GameObject::destroy(){
	if(this->parent==nullptr){
		this->scene->remove(this);
	}else{
		//TODO: generalize Panel to Container, and have Panel inherit from it.
		dynamic_cast<Panel*>(this->parent)->remove(this);
	}
}