class TestScene;
#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "SceneRunner.h"
#include "Scene.h"
#include <string>

class TestScene : public Scene{
public:
	TestScene(const SceneRunner* sceneRunner);
};

#endif
