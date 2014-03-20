#include "Panel.h"
#include "../utils/utils.h"
#include <algorithm>

Panel::Panel(Vec2 pos, Vec2 size, Color fillColor, double borderSize, Color borderColor)
	:GameObject(pos, size),
	rectObj(Vec2(0,0), size, fillColor, borderSize, borderColor),
	fillColor(rectObj.fillColor),
	borderSize(rectObj.borderSize),
	borderColor(rectObj.borderColor){
	rectObj.setParent(this);
}

void Panel::render() const{
	this->rectObj.render();

	//Since children are added the scene, the scene will hendle the rendering on it. We need not to render it here.
	/*for( GameObjectConstIt it = children.begin(); it != children.end(); it++ ){
		GameObject* i = it->get();
		i->render();
	}*/
}


void Panel::onSceneAdded(){
	for( std::vector<GameObject*>::iterator it = children.begin(); it != children.end(); it++ ){
		GameObject* i = *it;
		this->getSceneVariable()->add(i);
	}
}

void Panel::onSceneRemoved(){
	for( std::vector<GameObject*>::iterator it = children.begin(); it != children.end(); it++ ){
		GameObject* i = *it;
		this->getSceneVariable()->remove(i);
	}
}

Panel& Panel::add(GameObject* child){
	assert( child->getScene()==nullptr ); //ensure that Scene::add(child) is NOT called.
	child->setParent(this);
	if( this->getSceneVariable() != nullptr )
		this->getSceneVariable()->add(child);
	this->children.push_back(child);
	return *this;
}

Panel& Panel::remove(GameObject* child){
	child->setParent(nullptr);
	if( this->getSceneVariable() != nullptr )
		this->getSceneVariable()->remove(child);
	assert( this->children.end() == this->children.erase( std::remove(this->children.begin(), this->children.end(), child) ) );
	return *this;
}

std::vector<GameObject*>::iterator Panel::begin(){
	return this->children.begin();
}
std::vector<GameObject*>::iterator Panel::end(){
	return this->children.end();
}

std::vector<GameObject*>::const_iterator Panel::begin() const{
	return this->children.begin();
}

std::vector<GameObject*>::const_iterator Panel::end() const{
	return this->children.end();
}