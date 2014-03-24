#include "MenuScene.h"
#include "../../project.h"
#include <string>

#include "../../gameobjects/include.h"
#include "../../misc/soundPlayer.h"
#include "../../misc/messageBox.h"
#include "../../db/UserDb.h"
#include "../../db/User.h"

MenuScene::MenuScene(SceneRunner* const sceneRunner)
	:Scene(sceneRunner){
	//create a bannar
	SpriteObject* bannar = new SpriteObject(Vec2(100, 50), Vec2(600, 150), "./assets/bannar.png");
	this->add(bannar);

	//create a play panel
	Panel* playPanel = new Panel(Vec2(200, 300), Vec2(410, 70), Color(0.9, 0.9, 0.9, 1.0), 1, Color(0.8, 0.8, 0.8, 1));
	//add checkboxes to play panel
	CheckBox* winOn4 = new CheckBox(Vec2(10, 10), Vec2(200, 20), "Win on 4 silver merits", Color(0,0,0,1), Color(0.5,0.5,0.5,1));
	CheckBox* reuseLost = new CheckBox(Vec2(10, 35), Vec2(200, 20), "Reuse lost cards", Color(0,0,0,1), Color(0.5,0.5,0.5,1));
	playPanel->add(winOn4);
	playPanel->add(reuseLost);
	//add button to play panel
	Button* playButton = new Button(Vec2(220, 10), Vec2(180, 40), "Play Now!", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	playPanel->add(playButton);
	this->add(playPanel);

	Button* highScoreButton = new Button(Vec2(300, 400), Vec2(200, 35), "High Score", Color(0,0,0,1), Color(0.5,0.5,0.5,1));
	this->add(highScoreButton);
}