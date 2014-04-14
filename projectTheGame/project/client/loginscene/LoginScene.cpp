#include "LoginScene.h"
#include "../../project.h"
#include <string>

#include "../../gameobjects/include.h"
#include "../../misc/soundPlayer.h"
#include "../../misc/messageBox.h"
#include "../GameDb.h"
#include "../menuscene/MenuScene.h"
#include "../../misc/environment.h"

#define PANEL_WIDTH 150

namespace{
	Button* addPlayerButton;
	int playerPanelShownNum = 0;
	Panel* playerPanelPtrs[MAX_PLAYER];
	TextBox* playerNamePtr[MAX_PLAYER];
	TextBox* passwordPtr[MAX_PLAYER];
	Button* removePlayerButtonPtrs[MAX_PLAYER];
	std::shared_ptr<GameDb> gameDb;
}

LoginScene::LoginScene(SceneRunner* const sceneRunner)
	:Scene(sceneRunner){
	//connect to database
	gameDb = std::shared_ptr<GameDb>(new GameDb);
	if(!gameDb->isRemote())
		showMessage("Unable to connect to remote server. Falling back to file database.", "Info");

	//add background
	SpriteObject* background = new SpriteObject(Vec2(0, 0), Vec2(800, 650), "./assets/background.png", Vec2(0, 0), Vec2(800, 600));
	this->add( new Animator<double>(background->tileIndex.x, 1e10, 1e10/50) );
	this->add(background);

	//create a bannar
	SpriteObject* bannar = new SpriteObject(Vec2(100, 50), Vec2(600, 150), "./assets/bannar.png");
	this->add(bannar);

	//add the panels to the scene
	//Vec2 panelPos[] = {Vec2(20, 200), Vec2(210, 200), Vec2(400, 200), Vec2(590, 200)};
	for(int i=0; i<MAX_PLAYER; i++){
		Panel* playerPanel = new Panel(Vec2(800, 200), Vec2(PANEL_WIDTH, 220), Color(0.9, 0.9, 0.9, 1.0), 1, Color(0.8, 0.8, 0.8, 1));
		//add the player name+password UI to the player panel
		Text* playerText = new Text(Vec2(10, 10), Vec2(110, 20), std::string("Player ")+std::to_string((long long)i+1)+":", 16);
		TextBox* playerName = new TextBox(Vec2(15, 40), Vec2(120, 20), Color(0,0,0,1), Color(0.5,0.5,0.5,1));
		Text* passwordText = new Text(Vec2(10, 70), Vec2(110, 20), "Password: ", 16);
		TextBox* password = new TextBox(Vec2(15, 100), Vec2(120, 20), Color(0,0,0,1), Color(0.5,0.5,0.5,1));
		password->secret = true;
		playerPanel->add(playerText);
		playerPanel->add(playerName);
		playerPanel->add(passwordText);
		playerPanel->add(password);
		//add the remove player button
		Button* removePlayerButton = new Button(Vec2(120, 10), Vec2(20, 20), "-", Color(0,0,0,1), Color(0.8,0.0,0.0,1));
		removePlayerButton->hide();
		removePlayerButton->action = [=](){ this->removePlayer(); };
		playerPanel->add(removePlayerButton);
		//add radio buttons to play panel. TODO: unimplemented
		/*RadioButton* human = new RadioButton(Vec2(10, 130), Vec2(110, 20), "Human", Color(0,0,0,1), Color(0.5,0.5,0.5,1));
		RadioButton* computer = new RadioButton(Vec2(10, 160), Vec2(110, 20), "Computer", Color(0,0,0,1), Color(0.5,0.5,0.5,1));
		playerPanel->add(human);
		playerPanel->add(computer);*/
		//add the register button
		Button* registerButton = new Button(Vec2(10, 190), Vec2(120, 20), "Register", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
		registerButton->action = [=](){ this->registerPlayer(playerName->text, password->text); };
		playerPanel->add(registerButton);
		//finally, add the playerPanel to the current scene
		playerPanel->hide();
		this->add(playerPanel);
		//and do assign some variables to some pointers for later manipulation purpose.
		playerPanelPtrs[i] = playerPanel;
		removePlayerButtonPtrs[i] = removePlayerButton;
		playerNamePtr[i] = playerName;
		passwordPtr[i] = password;
	}

	//add a button for adding new player(s)
	addPlayerButton = new Button(Vec2(400, 200), Vec2(PANEL_WIDTH, 200), "+", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	addPlayerButton->action = [=](){ this->addPlayer(false); };
	this->add(addPlayerButton);

	//pre-add player panels
	for(int i=0; i<MIN_PLAYER; i++)
		this->addPlayer(true);
	
	//add a login button
	Button* loginButton = new Button(Vec2(300, 450), Vec2(180, 40), "Login", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	loginButton->action = [=](){
		gameDb->loginStart();
		for(int i=0; i<playerPanelShownNum; i++){
			if(!gameDb->loginNext(playerNamePtr[i]->text, passwordPtr[i]->text)){
				showMessage(std::string("Error: failed logging in Player ")+std::to_string((long long)i+1), "Login Failed");
				return;
			}
		}
		gameDb->loginDone();
		this->getSceneRunner()->setScene(new MenuScene(this->getSceneRunner(), gameDb));
	};
	this->add(loginButton);

	//add a lazy button for filling login info.
	//TODO: remove this button in release
	Button* fillUsernamePassword = new Button(Vec2(500, 450), Vec2(180, 40), "Fill", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	fillUsernamePassword->action = [=](){
		playerNamePtr[0]->text = "ALPHA";
		passwordPtr[0]->text = "ALPHA";
		playerNamePtr[1]->text = "BETA";
		passwordPtr[1]->text = "BETA";
		playerNamePtr[2]->text = "GAMMA";
		passwordPtr[2]->text = "GAMMA";
		playerNamePtr[3]->text = "DELTA";
		passwordPtr[3]->text = "DELTA";
	};
	this->add(fillUsernamePassword);

	//add a help button
	Button* helpButton = new Button(Vec2(350, 500), Vec2(80, 20), "Help", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	helpButton->action = [=](){
		//TODO: show the real help message
		showMessage("TODO: Display help message here -- You are now helpless!", "Help");
	};
	this->add(helpButton);

}

void LoginScene::addPlayer(bool init){
	assert(playerPanelShownNum<MAX_PLAYER);
	//show one more player panel
	playerPanelShownNum++;
	
	this->updateUIs(init);
}

void LoginScene::removePlayer(){
	assert(playerPanelShownNum>MIN_PLAYER);
	playerPanelShownNum--;
	this->updateUIs(false);
}

void LoginScene::updateUIs(bool init){
	//move the panels to a proper position
	bool maxed = (playerPanelShownNum==MAX_PLAYER);
	for(int i=0; i<playerPanelShownNum+(maxed?0:1); i++){
		int targetX = WINDOW_WIDTH/(playerPanelShownNum+(maxed?1:2))*(i+1)-PANEL_WIDTH/2;
		//In the last iteration, move the position of the addPlayerButton; In other iterations, move the position of panels
		double& target = (i==playerPanelShownNum)? addPlayerButton->pos.x: playerPanelPtrs[i]->pos.x;
		if(init){
			target = targetX;
		}else{
			//animate the panels: translation effect
			this->add( new Animator<double>(target, 0.2, targetX) );
		}
	}
	
	//show the add panel button, if appropiate.
	if(playerPanelShownNum==MAX_PLAYER){
		addPlayerButton->hide();
		addPlayerButton->pos.x = WINDOW_WIDTH;
	}else{
		addPlayerButton->show();
	}

	//shows only the remove player button on the last panel
	for(int i=0; i<MAX_PLAYER; i++){
		removePlayerButtonPtrs[i]->hide();
	}
	if(playerPanelShownNum>MIN_PLAYER)
		removePlayerButtonPtrs[playerPanelShownNum-1]->show();

	//show/hide the appropiate panels
	for(int i=0; i<playerPanelShownNum; i++)
		playerPanelPtrs[i]->show();
	for(int i=playerPanelShownNum; i<MAX_PLAYER; i++){
		playerPanelPtrs[playerPanelShownNum]->hide();
		playerPanelPtrs[i]->pos.x = WINDOW_WIDTH;
	}
}

void LoginScene::registerPlayer(std::string username, std::string password){
	bool success = gameDb->registerAcc(username, password);
	showMessage(gameDb->getStatus(), (success?"Success":"Failed") );
}