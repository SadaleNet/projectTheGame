#include "GameScene.h"
#include "../../project.h"
#include <string>

#include "../../gameobjects/include.h"
#include "../../misc/soundPlayer.h"
#include "../../misc/messageBox.h"
#include "../../db/UserDb.h"
#include "Deck.h"

GameScene::GameScene(SceneRunner* const sceneRunner, std::shared_ptr<GameDb> gameDb, bool winOn4, bool reuseLost)
	:Scene(sceneRunner){
	//add background
	SpriteObject* background = new SpriteObject(Vec2(0, 0), Vec2(800, 650), "./assets/background.png", Vec2(0, 0), Vec2(800, 600));
	this->add( new Animator<double>(background->tileIndex.x, 1e10, 1e10/50) );
	this->add(background);

	//construct game board
	Panel* gameBoardPanel = new Panel(Vec2(30, 205), Vec2(800, 270), Color(0, 0, 0, 0), 0, Color(0, 0, 0, 0));

	//add game board(background)
	SpriteObject* gameBoard = new SpriteObject(Vec2(-30, -35), Vec2(800, 270), "./assets/gamescene/board.png");
	gameBoardPanel->add(gameBoard);

	//add 3 cards
	for(int i=0; i<3; i++){
		AnimatedSprite* card
			= new AnimatedSprite(Vec2(50+i*120, 22), Vec2(100, 150), "./assets/gamescene/cards.png", Vec2(100, 150), 0.05, 3);
		card->tileIndex.y = 5+i;
		gameBoardPanel->add(card);
	}
	//add flip and collect buttons
	Button* flipMoreButton = new Button(Vec2(50+3*120, 40), Vec2(100, 30), "More", Color(1,1,0,1), Color(0.5,0.5,0.6,1));
	Button* collectCardsButton = new Button(Vec2(50+3*120, 110), Vec2(100, 30), "Collect", Color(1,1,0,1), Color(0.5,0.5,0.6,1));
	gameBoardPanel->add(flipMoreButton);
	gameBoardPanel->add(collectCardsButton);

	//add card deck
	SpriteObject* cardDeck
		= new SpriteObject(Vec2(gameBoardPanel->size.x-220, 22), Vec2(100, 150), "./assets/gamescene/cards.png", Vec2(0, 0), Vec2(100, 150));
	gameBoardPanel->add(cardDeck);

	this->add(gameBoardPanel);



	Vec2 platePos[4] = { Vec2(32.5, 5), Vec2(32.5, 100), Vec2(32.5, 415), Vec2(32.5, 510) };

	for(int i=0; i<4; i++){
		Panel* statusPlate = new Panel(platePos[i], Vec2(800, 270), Color(0, 0, 0, 0), 0, Color(0, 0, 0, 0));
		SpriteObject* statusPlateBackground
			= new SpriteObject(Vec2(0, 0), Vec2(735, 90), "./assets/gamescene/statusPlate.png");
		statusPlate->add(statusPlateBackground);

		Text* playerName = new Text(Vec2(10, 0), Vec2(0, 0), "Player Name", 20);
		statusPlate->add(playerName);

		Vec2 itemPos[5] = { Vec2(5, 25), Vec2(5, 55), Vec2(365, -5), Vec2(365, 25), Vec2(365, 55) };
		for(int j=0; j<5; j++){
			for(int k=0; k<12; k++){
				SpriteObject* item = new SpriteObject(itemPos[j]+Vec2(k*30, 0), Vec2(30, 30),
					"./assets/gamescene/items.png", Vec2(j, 0), Vec2(30, 30));
				statusPlate->add(item);
			}
		}
		this->add(statusPlate);
	}

}
