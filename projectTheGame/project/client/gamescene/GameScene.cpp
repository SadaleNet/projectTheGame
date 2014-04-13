#include "GameScene.h"
#include "../../project.h"
#include <string>
#include <cassert>

#include "../../gameobjects/include.h"
#include "../menuscene/MenuScene.h"
#include "../../misc/soundPlayer.h"
#include "../../misc/messageBox.h"
#include "../../db/UserDb.h"
#include "GameLogic.h"
#include "Deck.h"

namespace{
	struct StatusPanel{
		Panel* statusPlate;
		SpriteObject* statusPlateBackground;
		SpriteObject* item[CARD_ITEM_TYPES_NUM+1][TARGET_NUM];
	};
	StatusPanel sp[MAX_PLAYER];

	const Vec2 platePos[MAX_PLAYER] = { Vec2(32.5, 5), Vec2(32.5, 100), Vec2(32.5, 415), Vec2(32.5, 510) };
	const Vec2 itemPos[CARD_ITEM_TYPES_NUM+1] = { Vec2(5, 25), Vec2(5, 55), Vec2(365, -5), Vec2(365, 25), Vec2(365, 55) };
	SpriteObject* uncolldectedCards[MAX_CARD_UNCOLLECTED];
	int uncollectedCardsNum, collectedCardNum;

	std::shared_ptr<GameLogic> gameLogic;
	std::shared_ptr<GameDb> gameDb;

	int playerNum;
	bool winOn4;

	Panel* gameBoardPanel;
	SpriteObject* cardDeckSprite;
	Button *flipMoreButton, *collectCardsButton;
	const int CARD_MARGIN = 120;

}

GameScene::GameScene(SceneRunner* const sceneRunner, std::shared_ptr<GameDb> gameDb, bool winOn4, bool reuseLost)
	:Scene(sceneRunner){
	//initialize variables
	::gameDb = gameDb;
	::winOn4 = winOn4;
	gameLogic = std::shared_ptr<GameLogic>(new GameLogic(gameDb.get(), winOn4, reuseLost));
	playerNum = gameLogic->getPlayers().size();

	//attach event handllers
	gameLogic->drawCardHook = [=](Card card){ this->drawCard(card); };
	gameLogic->collectCardHook = [=](std::vector<Player> oldStates, Card card){ this->collectCard(oldStates, card); };
	gameLogic->lostHook = [=](){ this->cardsLost(); };
	gameLogic->nextTurnHook = [=](){ this->initTurn(); };
	gameLogic->gameEndHook = [=](){ this->gameEnd(); };

	//add background
	SpriteObject* background = new SpriteObject(Vec2(0, 0), Vec2(800, 650), "./assets/background.png", Vec2(0, 0), Vec2(800, 600));
	this->add( new Animator<double>(background->tileIndex.x, 1e10, 1e10/50) );
	this->add(background);

	//construct game board
	gameBoardPanel = new Panel(Vec2(30, 205), Vec2(800, 270), Color(0, 0, 0, 0), 0, Color(0, 0, 0, 0));

	//add game board(background)
	SpriteObject* gameBoard = new SpriteObject(Vec2(-30, -35), Vec2(800, 270), "./assets/gamescene/board.png");
	gameBoardPanel->add(gameBoard);

	//add flip and collect buttons
	flipMoreButton = new Button(Vec2(0, 40), Vec2(100, 30), "More", Color(1,1,0,1), Color(0.5,0.5,0.6,1));
	collectCardsButton = new Button(Vec2(0, 110), Vec2(100, 30), "Collect", Color(1,1,0,1), Color(0.5,0.5,0.6,1));
	flipMoreButton->action = [=](){ gameLogic->drawCard(); };
	collectCardsButton->action = [=](){ gameLogic->collectCards(); };
	gameBoardPanel->add(flipMoreButton);
	gameBoardPanel->add(collectCardsButton);

	//add card deck
	cardDeckSprite = new SpriteObject(Vec2(gameBoardPanel->size.x-220, 22), Vec2(100, 150), "./assets/gamescene/cards.png", Vec2(0, 0), Vec2(100, 150));
	gameBoardPanel->add(cardDeckSprite);

	this->add(gameBoardPanel);

	for(int i=0; i<playerNum; i++){
		sp[i].statusPlate = new Panel(platePos[i], Vec2(800, 270), Color(0, 0, 0, 0), 0, Color(0, 0, 0, 0));
		sp[i].statusPlateBackground
			= new SpriteObject(Vec2(0, 0), Vec2(735, 90), "./assets/gamescene/statusPlate.png");
		sp[i].statusPlate->add(sp[i].statusPlateBackground);

		Text* playerName = new Text(Vec2(10, 0), Vec2(0, 0), gameDb->getUserName(i), 20);
		sp[i].statusPlate->add(playerName);
		
		this->add(sp[i].statusPlate);
	}

	initTurn();
}

void GameScene::initTurn(){
	//reinitialize variables
	uncollectedCardsNum = 0;
	collectedCardNum = 0;

	//set the color of the status plates appropiately.
	for(int i=0; i<playerNum; i++)
		sp[i].statusPlateBackground->imagePath = "./assets/gamescene/statusPlate.png";
	sp[gameLogic->getCurrentPlayerIndex()].statusPlateBackground->imagePath = "./assets/gamescene/statusPlateActive.png";

	//finally, start a turn with a ccard drawn.
	if(!gameLogic->isDeckEmpty())
		gameLogic->drawCard();
}

void GameScene::removeCardsOnPanel(){
	for(int i=0; i<uncollectedCardsNum; i++)
		this->remove(uncolldectedCards[i]);
}

void GameScene::collectCard(std::vector<Player> oldStates, Card card){
	//show the changes of each items
	std::vector<Player> newStates = gameLogic->getPlayers();
	assert(newStates.size()==oldStates.size());
	for(unsigned int i=0; i!=oldStates.size(); i++){
		for(int j=0; j<CARD_ITEM_TYPES_NUM; j++)
			this->showDeltaItem(i, j, oldStates[i].items[j], newStates[i].items[j]);
		this->showDeltaItem(i, CARD_ITEM_TYPES_NUM, oldStates[i].silverMeritNum, newStates[i].silverMeritNum);
	}

	this->remove(uncolldectedCards[collectedCardNum++]);
}
void GameScene::drawCard(Card card){
	//shows the card drawn
	if((int)card.type<CARD_ITEM_TYPES_NUM){
		uncolldectedCards[uncollectedCardsNum]
			= new SpriteObject(Vec2(50+uncollectedCardsNum*120, 22), Vec2(100, 150), "./assets/gamescene/cards.png", Vec2(0, 0), Vec2(100, 150));
		uncolldectedCards[uncollectedCardsNum]->tileIndex.y = (int)card.type+1;
		switch(card.quantity){
			case 2: uncolldectedCards[uncollectedCardsNum]->tileIndex.x = 0; break;
			case 4: uncolldectedCards[uncollectedCardsNum]->tileIndex.x = 1; break;
			case 6: uncolldectedCards[uncollectedCardsNum]->tileIndex.x = 2; break;
			default: assert(false);
		}
	}else{
		//the card is a special character card.
		uncolldectedCards[uncollectedCardsNum]
			= new AnimatedSprite(Vec2(50+uncollectedCardsNum*120, 22), Vec2(100, 150), "./assets/gamescene/cards.png", Vec2(100, 150), 0.05, 3);
		uncolldectedCards[uncollectedCardsNum]->tileIndex.y = (int)card.type+1;
	}
	gameBoardPanel->add(uncolldectedCards[uncollectedCardsNum]);

	//adjust the position of flipMoreButton and collectCardsButton
	uncollectedCardsNum++;
	flipMoreButton->pos.x = 50+uncollectedCardsNum*CARD_MARGIN;
	collectCardsButton->pos.x = 50+uncollectedCardsNum*CARD_MARGIN;
}

void GameScene::cardsLost(){
	this->removeCardsOnPanel();
}

void GameScene::gameEnd(){
	//hide the deck sprite, if it is empty.
	if(gameLogic->isDeckEmpty())
		cardDeckSprite->hide();
	this->getSceneRunner()->render();

	//execute in next frame so that the new graphic is rendered before the message is shown.
	this->add(new Timer([=](){
		//show winner message
		if(gameLogic->getWinner()==-1){
			showMessage("Tied! How sad. :(", "Game Over");
		}else{
			showMessage(std::string("The winner is ")+gameDb->getUserName(gameLogic->getWinner())
				+std::string("\r\nCongratulation! This player gain 1 score in the highscore board(yes, 1 only)."), "Game Over");
		}

		//back to MeunScene
		this->getSceneRunner()->setScene(new MenuScene(this->getSceneRunner(), gameDb));
	}, 0.05));
}

void GameScene::showDeltaItem(int playerIndex, int itemType, int oldNum, int newNum){
	if(newNum==oldNum)
		return;

	//new item is added.
	if(newNum>oldNum){
		for(int i=oldNum; i<newNum; i++){
			sp[playerIndex].item[itemType][i] = new SpriteObject(itemPos[itemType]+Vec2(i*30, 0), Vec2(30, 30),
				"./assets/gamescene/items.png", Vec2(itemType, 0), Vec2(30, 30));
			sp[playerIndex].statusPlate->add(sp[playerIndex].item[itemType][i]);
		}
	}else{
		for(int i=oldNum; i-->newNum; )
			sp[playerIndex].statusPlate->remove(sp[playerIndex].item[itemType][i]);
	}
}