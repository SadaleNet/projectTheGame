class MenuScene;
#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "../../scenes/SceneRunner.h"
#include "../../scenes/Scene.h"
#include "../GameDb.h"
#include <string>

/** @brief A scene providing a highscore board, options, a play button, etc. */
class MenuScene: public Scene{
private:
	void addWelcomeMessageColorAnimator();
public:
	MenuScene(SceneRunner* const sceneRunner, std::shared_ptr<GameDb> gameDb);
};

#endif