class LoginScene;
#ifndef LOGIN_SCENE_H
#define LOGIN_SCENE_H

#include "../../scenes/SceneRunner.h"
#include "../../scenes/Scene.h"
#include <string>

class LoginScene: public Scene{
public:
	LoginScene(SceneRunner* const sceneRunner);
private:
	bool loggingIn;
	void login();
	void addPlayer(bool init);
	void removePlayer();
	void updateUIs(bool init);
	void registerPlayer(std::string username, std::string password);
};

#endif