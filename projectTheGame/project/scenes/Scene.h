class Scene;

#ifndef SCENE_H
#define SCENE_H

#include "SceneRunner.h"
#include "../gameobjects/GameObject.h"
#include "../misc/EventData.h"
#include <vector>
#include <memory>

/**
	@brief	Each game should only have one scene at a time. Example: LoginScene, LevelSelectionScene.
*/
class Scene{
private:
	///@brief convert system events into GameObject::onClick(), onMouseMove(), etc. Implementation is library-dependent.
	void handleEvents();
	///@brief invokes gameObjects[each].update() and set timeInitialized on first call.
	void update();
	///@brief invokes gameObjects[each].render()
	void render();

	///@brief	A hook function of handleEvents() for processing scene-defined events.
	virtual void handleExtraEvents();

	double timeInitialized; ///store the time that the first update() is called.
	SceneRunner* const sceneRunner;

	friend SceneRunner;

protected:
	Scene(SceneRunner* const sceneRunner);

	std::vector<std::shared_ptr<GameObject>> gameObjects;
	Vec2 mousePos;

public:
	///@brief	add obj to this scene
	Scene& add(GameObject* obj);
	///@brief	remove obj from this scene
	Scene& remove(GameObject* obj);

	///@brief	get seconds elasped since timeInitialized
	double getSec() const;
	///@brief	get seconds spent on the previous frame.
	double getDeltaSec() const;
	const SceneRunner* getSceneRunner() const{ return sceneRunner; }
	SceneRunner* getSceneRunner(){ return sceneRunner; }
};

//define convenient macros

/*Note: create a gameObjectsClone before iterating so that the iterator will work
even a gameobject get deleted during the iteration.*/
#define EACH_GAME_OBJECT(_identifier) \
	{\
		std::vector<std::shared_ptr<GameObject>> gameObjectsClone_##_identifier = gameObjects;\
		GameObjectIt it_##_identifier = gameObjectsClone_##_identifier.begin();\
		for( ; it_##_identifier != gameObjectsClone_##_identifier.end(); it_##_identifier++ ){\
			GameObject* _identifier = (*it_##_identifier).get();\
			if(_identifier->isHidden())\
				continue;\

#define EACH_GAME_OBJECT_INCLUDES_HIDDEN(_identifier) \
	{\
		std::vector<std::shared_ptr<GameObject>> gameObjectsClone_##_identifier = gameObjects;\
		GameObjectIt it_##_identifier = gameObjectsClone_##_identifier.begin();\
		for( ; it_##_identifier != gameObjectsClone_##_identifier.end(); it_##_identifier++ ){\
			GameObject* _identifier = (*it_##_identifier).get();

//For the sake of performance, the client may want to have clones shared.
//To do so, use EACH_GAME_OBJECT_USE_CLONE instead of EACH_GAME_OBJECT
#define EACH_GAME_OBJECT_USE_CLONE(_identifier, _cloneName) \
	{\
		GameObjectIt it_##_identifier = _cloneName.begin();\
		for( ; it_##_identifier != _cloneName.end(); it_##_identifier++ ){\
			GameObject* _identifier = (*it_##_identifier).get();\
			if(_identifier->isHidden())\
				continue;\


#define END_EACH }}

#endif
