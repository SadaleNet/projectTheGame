class Scene;
#ifndef SCENE_H
#define SCENE_H

#include "SceneRunner.h"
#include "../gameobjects/GameObject.h"
#include "EventData.h"
#include <vector>

class Scene{
	friend SceneRunner;
protected:
	SceneRunner* parent;
	typedef std::vector<std::shared_ptr<GameObject>>::iterator GameObjectIt;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	Vec2 mousePos;

public:
	virtual void handleEvents();
	virtual void render() = 0;
};

#endif
