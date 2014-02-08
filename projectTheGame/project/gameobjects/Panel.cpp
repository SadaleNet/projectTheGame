#include "Panel.h"
#include "../utils/utils.h"
#include <algorithm>

Panel::Panel(Vec2 pos, Vec2 size, Color fillColor, double borderSize, Color borderColor)
	:GameObject(pos, size),
	rectObj(Vec2(0,0), size, fillColor, borderSize, borderColor){
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
	for( GameObjectIt it = children.begin(); it != children.end(); it++ ){
		GameObject* i = it->get();
		this->getSceneVariable()->add(i);
	}
}

void Panel::onSceneRemoved(){
	for( GameObjectIt it = children.begin(); it != children.end(); it++ ){
		GameObject* i = it->get();
		this->getSceneVariable()->remove(i);
	}
}

Panel& Panel::add(GameObject* child){
	assert( child->getScene()==nullptr ); //ensure that Scene::add(child) is NOT called.
	child->setParent(this);
	if( this->getSceneVariable() != nullptr )
		this->getSceneVariable()->add(child);
	this->children.push_back(std::shared_ptr<GameObject>(child));
	return *this;
}

Panel& Panel::remove(GameObject* child){
	child->setParent(nullptr);
	if( this->getSceneVariable() != nullptr )
		this->getSceneVariable()->remove(child);
	assert( std::remove(this->children.begin(), this->children.end(), std::shared_ptr<GameObject>(child)) == this->children.end() );
	return *this;
}

std::vector<std::shared_ptr<GameObject>>::iterator Panel::begin(GameObject* child){
	return this->children.begin();
}
std::vector<std::shared_ptr<GameObject>>::iterator Panel::end(GameObject* child){
	return this->children.end();
}