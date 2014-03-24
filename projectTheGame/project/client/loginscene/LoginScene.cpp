#include "LoginScene.h"
#include "../../project.h"
#include <string>

#include "../../gameobjects/include.h"
#include "../../misc/soundPlayer.h"
#include "../../misc/messageBox.h"
#include "../../db/UserDb.h"
#include "../menuscene/MenuScene.h"

LoginScene::LoginScene(SceneRunner* const sceneRunner)
	:Scene(sceneRunner){
	//add background
	SpriteObject* background = new SpriteObject(Vec2(0, 0), Vec2(800, 650), "./assets/background.png", Vec2(0, 0), Vec2(800, 600));
	this->add( new Animator<double>(background->tileIndex.x, 1e10, 1e10/50) );
	this->add(background);

	//create a bannar
	SpriteObject* bannar = new SpriteObject(Vec2(100, 50), Vec2(600, 150), "./assets/bannar.png");
	this->add(bannar);

	//TODO: add UI controls here.

	//add a login button
	Button* loginButton = new Button(Vec2(300, 300), Vec2(180, 40), "Login", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	loginButton->action = [=](){
		this->getSceneRunner()->setScene(new MenuScene(this->getSceneRunner()));
	};
	this->add(loginButton);
}