#include "Scene.h"
#include <algorithm>
#include <cassert>

void Scene::handleExtraEvents(){
	//Does nothing! Subclasses may do something here by overriding this method.
}

Scene& Scene::add(GameObject* obj){
	this->gameObjects.push_back(std::shared_ptr<GameObject>(obj));
	return *this;
}

Scene& Scene::remove(GameObject* obj){
	assert( std::remove(this->gameObjects.begin(), this->gameObjects.end(), std::shared_ptr<GameObject>(obj)) == this->gameObjects.end() );
	return *this;
}