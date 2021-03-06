#include "MenuScene.h"
#include "../../project.h"
#include <string>
#include <cstdlib>

#include "../../gameobjects/include.h"
#include "../../misc/soundPlayer.h"
#include "../../misc/messageBox.h"
#include "../../db/UserDb.h"
#include "../gamescene/GameScene.h"
#include "../loginscene/LoginScene.h"
#include "../showHelpMessage.h"

namespace{
	Text* welcomeMessage;
}

void MenuScene::addWelcomeMessageColorAnimator(){
	Timer* changeWelcomeMessageColorTimer = new Timer([=](){
		this->add( new Animator<Color>(welcomeMessage->fontColor, 0.2, Color((rand()%200/256.0), (rand()%200/256.0), (rand()%200/256.0), 1.0)) );
		addWelcomeMessageColorAnimator();
	}, 1.0);
	this->add(changeWelcomeMessageColorTimer);
}

MenuScene::MenuScene(SceneRunner* const sceneRunner, std::shared_ptr<GameDb> gameDb)
	:Scene(sceneRunner){
	//add background
	SpriteObject* background = new SpriteObject(Vec2(0, 0), Vec2(800, 650), "./assets/background.png", Vec2(0, 0), Vec2(800, 600));
	this->add( new Animator<double>(background->tileIndex.x, 1e10, 1e10/50) );
	this->add(background);

	//create a bannar
	SpriteObject* bannar = new SpriteObject(Vec2(100, 50), Vec2(600, 150), "./assets/bannar.png");
	this->add(bannar);

	//create welcome message
	welcomeMessage = new Text(Vec2(50, 250), Vec2(700, 30), std::string("Welcome! ")+gameDb->getUserNames(), 20, Color(0, 0, 0, 1), Text::CENTER);
	this->add(welcomeMessage);
	this->addWelcomeMessageColorAnimator();

	//create a play panel
	Panel* playPanel = new Panel(Vec2(200, 300), Vec2(410, 80), Color(0.9, 0.9, 0.9, 1.0), 1, Color(0.8, 0.8, 0.8, 1));
	//add checkboxes to play panel
	CheckBox* winOn4 = new CheckBox(Vec2(10, 10), Vec2(210, 20), "Win on 4 silver merits", Color(0,0,0,1), Color(0.5,0.5,0.5,1));
	CheckBox* reuseLost = new CheckBox(Vec2(10, 35), Vec2(210, 20), "Reuse lost cards", Color(0,0,0,1), Color(0.5,0.5,0.5,1));
	playPanel->add(winOn4);
	playPanel->add(reuseLost);
	//add button to play panel
	Button* playButton = new Button(Vec2(220, 10), Vec2(180, 40), "Play Now!", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	playButton->action = [=](){ //event handler of playButton
		this->getSceneRunner()->setScene(new GameScene(this->getSceneRunner(), gameDb, winOn4->checked, reuseLost->checked));
	};
	playPanel->add(playButton);
	this->add(playPanel);

	//add highscore button
	Button* highScoreButton = new Button(Vec2(190, 400), Vec2(200, 35), "High Score", Color(0,0,0,1), Color(0.5,0.5,0.5,1));
	highScoreButton->action = [=](){
		showMessage(gameDb->getHighScoreBoard(), "High Score");
	};
	this->add(highScoreButton);

	//add logout button
	Button* logoutButton = new Button(Vec2(410, 400), Vec2(200, 35), "Logout", Color(0,0,0,1), Color(0.5,0.5,0.5,1));
	logoutButton->action = [=](){
		this->getSceneRunner()->setScene(new LoginScene(this->getSceneRunner()));
	};
	this->add(logoutButton);

	//add a help button
	Button* helpButton = new Button(Vec2(530, 440), Vec2(80, 20), "Help", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	helpButton->action = showHelpMessage;
	this->add(helpButton);
	
	std::string scoreBoardStr = "Scores\n";
	for(unsigned int i=0; i<gameDb->getUserNum(); i++)
		scoreBoardStr += gameDb->getUserName(i)+std::string(": ")+std::to_string((long long)gameDb->getWins(i))+"\n";
	Text* scoreBoard = new Text(Vec2(200, 450), Vec2(400, 150), scoreBoardStr, 20, Color(0, 0, 0, 1));
	this->add(scoreBoard);

	this->addWelcomeMessageColorAnimator();

	//Finally, play bgm.
	playBgm("./assets/bgm2.wav");
}