class Scene;
#ifndef SCENE_H
#define SCENE_H
#include "SceneRunner.h"

class Scene{
	friend SceneRunner;
protected:
	SceneRunner* parent;
public:
	virtual void handleEvents() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif
