#include "Scene.h"
#include <algorithm>
#include <cassert>

Scene::Scene(const SceneRunner* sceneRunner):
	sceneRunner(sceneRunner),
	timeConstructed(sceneRunner->getSec()){
}


void Scene::handleExtraEvents(){
	//Does nothing! Subclasses may do something here by overriding this method.
}

void Scene::update(){
	EACH_GAME_OBJECT(i)
		i->update();
	END_EACH
}

void Scene::render(){
	EACH_GAME_OBJECT(i)
		i->render();
	END_EACH
}

Scene& Scene::add(GameObject* obj){
	this->gameObjects.push_back(std::shared_ptr<GameObject>(obj));
	obj->scene = this;
	obj->onSceneAdded();
	return *this;
}

Scene& Scene::remove(GameObject* obj){
	assert( std::remove(this->gameObjects.begin(), this->gameObjects.end(), std::shared_ptr<GameObject>(obj)) == this->gameObjects.end() );
	obj->scene = nullptr;
	obj->onSceneRemoved();
	return *this;
}

double Scene::getSec() const{
	assert( this->sceneRunner != nullptr );
	return this->sceneRunner->getSec()-this->timeConstructed;
}

double Scene::getDeltaSec() const{
	return this->sceneRunner->getDeltaSec();
}
