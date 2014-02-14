class Scene;

#ifndef SCENE_H
#define SCENE_H

//create a clone before iterating so that the iterator will work even a gameobject get deleted during the iteration.
#define EACH_GAME_OBJECT(_identifier) \
	std::vector<std::shared_ptr<GameObject>> gameObjectsClone_##_identifier = gameObjects;\
	GameObjectIt it_##_identifier = gameObjectsClone_##_identifier.begin();\
	for( ; it_##_identifier != gameObjectsClone_##_identifier.end(); it_##_identifier++ ){\
		GameObject* _identifier = (*it_##_identifier).get();\
		if(_identifier->isHidden())\
			continue;\

#define EACH_GAME_OBJECT_INCLUDES_HIDDEN(_identifier) \
	std::vector<std::shared_ptr<GameObject>> gameObjectsClone_##_identifier = gameObjects;\
	GameObjectIt it_##_identifier = gameObjectsClone_##_identifier.begin();\
	for( ; it_##_identifier != gameObjectsClone_##_identifier.end(); it_##_identifier++ ){\
		GameObject* _identifier = (*it_##_identifier).get();

#define END_EACH }

#include "SceneRunner.h"
#include "../gameobjects/GameObject.h"
#include "EventData.h"
#include <vector>
#include <memory>

/**
	Override note: Please define the constructor of the subclasses as  SceneType(const SceneRunner* sceneRunner):Scene(sceneRunner){}
*/
class Scene{
private:
	void handleEvents();
	void update();
	void render();

	/** @brief	A hook function of handleEvents() for processing scene-defined events. */
	virtual void handleExtraEvents();

	const double timeConstructed;
	const SceneRunner* sceneRunner;

	friend SceneRunner;

protected:
	Scene(const SceneRunner* sceneRunner);

	std::vector<std::shared_ptr<GameObject>> gameObjects;
	Vec2 mousePos;

public:
	Scene& add(GameObject* obj);
	Scene& remove(GameObject* obj);

	double getSec() const;
	double getDeltaSec() const;
	const SceneRunner* getSceneRunner() const{ return sceneRunner; }

};

#endif
