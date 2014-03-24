class MenuScene;
#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "../../scenes/SceneRunner.h"
#include "../../scenes/Scene.h"
#include <string>

class MenuScene: public Scene{
public:
	MenuScene(SceneRunner* const sceneRunner);
};

#endif