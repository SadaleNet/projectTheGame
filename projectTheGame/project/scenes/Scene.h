class Scene;
#ifndef SCENE_H
#define SCENE_H

#include "SceneRunner.h"
#include "../gameobjects/GameObject.h"
#include "EventData.h"
#include <vector>
#include <memory>

class Scene{
private:
	void handleEvents();
	void render();
	/** @brief	A hook function of handleEvents() for processing scene-defined events. */
	virtual void handleExtraEvents();
	friend SceneRunner;

protected:
	SceneRunner* parent;
	typedef std::vector<std::shared_ptr<GameObject>>::iterator GameObjectIt;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	Vec2 mousePos;

public:
	Scene& add(GameObject* obj);
	Scene& remove(GameObject* obj);

};

#endif
