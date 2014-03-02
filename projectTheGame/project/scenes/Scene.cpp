#include "Scene.h"
#include <algorithm>
#include <cassert>

Scene::Scene(SceneRunner* const sceneRunner):
	sceneRunner(sceneRunner),
	timeInitialized(-1.0){
}


void Scene::handleExtraEvents(){
	//Does nothing! Subclasses may do something here by overriding this method.
}

void Scene::update(){
	if(this->timeInitialized==-1.0)
		this->timeInitialized = sceneRunner->getSec();

	EACH_GAME_OBJECT_INCLUDES_HIDDEN(i)
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
	obj->scene = nullptr;
	obj->onSceneRemoved();

	//remove the obj from this->gameObjects. assert() that obj is removed.
	assert( this->gameObjects.end() ==
				this->gameObjects.erase(
					std::remove_if(this->gameObjects.begin(), this->gameObjects.end(),
					[=](const std::shared_ptr<GameObject>& a){ 
						return (a.get() == obj);
					})
				)
			);
	return *this;
}

double Scene::getSec() const{
	assert( this->sceneRunner != nullptr );
	return this->sceneRunner->getSec()-this->timeInitialized;
}

double Scene::getDeltaSec() const{
	return this->sceneRunner->getDeltaSec();
}
