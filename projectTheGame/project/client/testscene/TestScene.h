class TestScene;
#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "../../scenes/SceneRunner.h"
#include "../../scenes/Scene.h"
#include <string>

/** @brief A scene for testing whether our framework is working, require manual testing. */
class TestScene : public Scene{
public:
	TestScene(SceneRunner* const sceneRunner);
};

#endif
