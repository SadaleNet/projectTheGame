class GameScene;
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "../../scenes/SceneRunner.h"
#include "../../scenes/Scene.h"
#include "../GameDb.h"
#include <string>

class GameScene: public Scene{
public:
	GameScene(SceneRunner* const sceneRunner, std::shared_ptr<GameDb> gameDb, bool winOn4, bool reuseLost);
};

#endif
