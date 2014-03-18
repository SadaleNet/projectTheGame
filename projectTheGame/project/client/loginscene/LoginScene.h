class LoginScene;
#ifndef LOGIN_SCENE_H
#define LOGIN_SCENE_H

#include "../../scenes/SceneRunner.h"
#include "../../scenes/Scene.h"
#include <string>

class LoginScene: public Scene{
public:
	LoginScene(SceneRunner* const sceneRunner);
};

#endif