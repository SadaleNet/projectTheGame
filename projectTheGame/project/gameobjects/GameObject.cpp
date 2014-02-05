#include "GameObject.h"
#include <stdexcept>
#include <cassert>

GameObject::GameObject():
	parent(nullptr){
	/*this->on(UPDATE, [](EventData){
		return true;
	});*/
}

GameObject& GameObject::setShape(Shape* shape){
	this->shape = std::shared_ptr<Shape>(shape);
	return *this;
}

GameObject& GameObject::setRenderer(ShapeRenderer* renderer){
	this->renderer = std::shared_ptr<ShapeRenderer>(renderer);
	return *this;
}

GameObject& GameObject::on(EventType eventType, const std::function<bool(EventData)>& callback){
	this->callbackList[eventType] = callback;

	return *this;
}

GameObject& GameObject::trigger(EventType eventType, EventData eventData){
	bool propogate = true;
	try{
		propogate = this->callbackList.at(eventType)(eventData);
	}catch(std::out_of_range&){}

	if( parent != nullptr && propogate ){
		parent->trigger(eventType, eventData);
	}

	return *this;
}

GameObject& GameObject::off(EventType eventType){
	size_t removedNum = this->callbackList.erase(eventType);
	assert( removedNum == 1 );

	return *this;
}

void GameObject::update(){
	//TODO: recalculate trans and gTrans here.
}

void GameObject::render() const{
	if(renderer)
		this->renderer->render();
}


bool GameObject::isCollide(const Shape& b) const{
	if( this->shape == nullptr )
		return false;
	return this->shape->isCollide(*this);
}

bool GameObject::isCollide(const Vec2& p) const{
	if( this->shape == nullptr )
		return false;
	return this->shape->isCollide(*this);
}

const Mat33& GameObject::getTrans() const{
	return trans;
}

const Mat33& GameObject::getGTrans() const{
	return gTrans;
}