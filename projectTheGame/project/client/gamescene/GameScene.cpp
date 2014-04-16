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
	double nextTurnDelay;

	bool hideButtons;

	Panel* gameBoardPanel;
	SpriteObject* cardDeckSprite;
	Text* cardDeckNumText;
	Button *flipMoreButton, *collectCardsButton;
	const int CARD_MARGIN = 120;
}

GameScene::GameScene(SceneRunner* const sceneRunner, std::shared_ptr<GameDb> gameDb, bool winOn4, bool reuseLost)
	:Scene(sceneRunner){
	//initialize variables
	::gameDb = gameDb;
	::winOn4 = winOn4;
	for(int i=0; i<uncollectedCardsNum; i++)
		uncolldectedCards[i] = nullptr;
	gameLogic = std::shared_ptr<GameLogic>(new GameLogic(gameDb.get(), winOn4, reuseLost));
	playerNum = gameLogic->getPlayers().size();

	//attach event handllers
	gameLogic->drawCardHook = [=](Card card){ this->drawCard(card); };
	gameLogic->collectCardHook = [=](std::vector<Player> oldStates, Card card){ this->collectCard(oldStates, card); };
	gameLogic->lostHook = [=](){ this->cardsLost(); };
	gameLogic->nextTurnHook = [=](){
		GameScene* DIS = this;
		this->add(new Timer([=]{ DIS->initTurn(); }, nextTurnDelay));
	};
	gameLogic->gameEndHook = [=](){
		GameScene* DIS = this;
		this->add(new Timer([=]{ DIS->gameEnd(); }, nextTurnDelay));
	};

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

	cardDeckNumText = new Text(cardDeckSprite->pos+cardDeckSprite->size*0.5-Vec2(50/2, 30/2), Vec2(50, 30), "", 20, Color(1, 1, 1, 1), Text::CENTER);
	this->updateDeckCardsNum();
	gameBoardPanel->add(cardDeckNumText);

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

	stopBgm();
	initTurn();
}

void GameScene::initTurn(){
	//reinitialize variables
	this->removeCardsOnPanel();
	uncollectedCardsNum = 0;
	collectedCardNum = 0;
	nextTurnDelay = 0.6;
	hideButtons = false;

	//set the color of the status plates appropiately.
	for(int i=0; i<playerNum; i++)
		sp[i].statusPlateBackground->imagePath = "./assets/gamescene/statusPlate.png";
	sp[gameLogic->getCurrentPlayerIndex()].statusPlateBackground->imagePath = "./assets/gamescene/statusPlateActive.png";

	//finally, start a turn with a ccard drawn.
	if(!gameLogic->isDeckEmpty())
		gameLogic->drawCard();
}

void GameScene::removeCardsOnPanel(){
	for(int i=0; i<uncollectedCardsNum; i++){
		if(uncolldectedCards[i]!=nullptr)
			gameBoardPanel->remove(uncolldectedCards[i]);
	}
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

	//hide the cards, with zoom out animation
	uncolldectedCards[collectedCardNum]->pos = Vec2(50+collectedCardNum*120, cardDeckSprite->pos.y);
	uncolldectedCards[collectedCardNum]->size = cardDeckSprite->size;
	this->add(new Animator<Vec2>(uncolldectedCards[collectedCardNum]->size, 0.25*(collectedCardNum+1), uncolldectedCards[collectedCardNum]->size, 0.3+0.25*(collectedCardNum+1), Vec2(0, 0)));
	this->add(new Animator<Vec2>(uncolldectedCards[collectedCardNum]->pos, 0.25*(collectedCardNum+1), uncolldectedCards[collectedCardNum]->pos, 0.3+0.25*(collectedCardNum+1), uncolldectedCards[collectedCardNum]->pos+uncolldectedCards[collectedCardNum]->size*0.5));
	nextTurnDelay += 0.25;
	collectedCardNum++;

	//hide the buttons
	flipMoreButton->hide();
	collectCardsButton->hide();
	hideButtons = true;
}
void GameScene::drawCard(Card card){
	//hide the deck sprite, if it is empty.
	if(gameLogic->isDeckEmpty())
		cardDeckSprite->hide();

	Vec2 targetPos = Vec2(50+uncollectedCardsNum*120, cardDeckSprite->pos.y);

	//shows the card drawn
	if((int)card.type<CARD_ITEM_TYPES_NUM){
		uncolldectedCards[uncollectedCardsNum]
			= new SpriteObject(cardDeckSprite->pos+Vec2(cardDeckSprite->size.x/2, 0), Vec2(0, cardDeckSprite->size.y), "./assets/gamescene/cards.png", Vec2(0, 0), Vec2(100, 150));
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
			= new AnimatedSprite(cardDeckSprite->pos, cardDeckSprite->size, "./assets/gamescene/cards.png", Vec2(100, 150), 0.05, 3);
		uncolldectedCards[uncollectedCardsNum]->tileIndex.y = (int)card.type+1;
	}
	gameBoardPanel->add(uncolldectedCards[uncollectedCardsNum]);
	//show the flip in effect
	this->add(new Animator<double>(uncolldectedCards[uncollectedCardsNum]->pos.x, 0.25, targetPos.x));
	this->add(new Animator<double>(uncolldectedCards[uncollectedCardsNum]->size.x, 0.25, cardDeckSprite->size.x));

	//play flip card sfx
	if(card.type==CARD_WLCHAN||card.type==CARD_NOBEL)
		playSfx("./assets/gamescene/holy.wav");
	else
		playSfx("./assets/gamescene/flip.wav");

	//adjust the position of flipMoreButton and collectCardsButton, hide it until the card drawing animation is completed.
	uncollectedCardsNum++;
	flipMoreButton->hide();
	collectCardsButton->hide();
	if(uncollectedCardsNum>=MAX_CARD_UNCOLLECTED){
		hideButtons = true;
	}else{
		flipMoreButton->pos.x = 50+uncollectedCardsNum*CARD_MARGIN;
		collectCardsButton->pos.x = 50+uncollectedCardsNum*CARD_MARGIN;
		this->add(
			new Timer([=](){
				if(!hideButtons){
					if(!gameDb->isAi(gameLogic->getCurrentPlayerIndex())){
						flipMoreButton->show();
						collectCardsButton->show();
					}else{
						processAi();
					}
				}
			}, 0.3)
		);
	}

	this->updateDeckCardsNum();
}

void GameScene::cardsLost(){
	//hide the all cards at the same time, with zoom out animation
	for(int i=0; i<uncollectedCardsNum; i++){
		assert(uncolldectedCards[i]!=nullptr);
		this->add(new Animator<double>(uncolldectedCards[i]->size.y, 0.3, uncolldectedCards[i]->size.y, 0.5, 0));
		this->add(new Animator<double>(uncolldectedCards[i]->pos.y, 0.3, uncolldectedCards[i]->pos.y, 0.5, uncolldectedCards[i]->pos.y+uncolldectedCards[i]->size.y*0.5));
	}
	nextTurnDelay += 0.5;
	hideButtons = true;
	playSfx("./assets/gamescene/lost.wav");
	this->updateDeckCardsNum();
}

void GameScene::gameEnd(){
	//show winner message
	if(gameLogic->getWinner()==-1){
		showMessage("Tied! How sad. :(", "Game Over");
	}else{
		showMessage(std::string("The winner is ")+gameDb->getUserName(gameLogic->getWinner())
			+std::string("\r\nCongratulation! This player gain 1 score in the highscore board(yes, 1 only)."), "Game Over");
		gameDb->addWins(gameLogic->getWinner());
	}

	//back to MeunScene
	this->getSceneRunner()->setScene(new MenuScene(this->getSceneRunner(), gameDb));
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
			//zoom animation for items being shown
			this->add(new Animator<Vec2>(sp[playerIndex].item[itemType][i]->size, 0.25*collectedCardNum, Vec2(0, 0), 0.2+0.25*collectedCardNum, sp[playerIndex].item[itemType][i]->size));
			this->add(new Animator<Vec2>(sp[playerIndex].item[itemType][i]->pos, 0.25*collectedCardNum, sp[playerIndex].item[itemType][i]->pos+sp[playerIndex].item[itemType][i]->size*0.5, 0.2+0.25*collectedCardNum, sp[playerIndex].item[itemType][i]->pos));
			sp[playerIndex].item[itemType][i]->size = Vec2(0, 0);
		}
		//play sfx. Note: CARD_ITEM_TYPES_NUM menas silver merit
		this->add( new Timer([=](){
			if(itemType==CARD_ITEM_TYPES_NUM)
				playSfx("./assets/gamescene/silverMerit.wav");
			else
				playSfx("./assets/gamescene/add.wav");
		}, 0.25*collectedCardNum));
	}else{
		for(int i=oldNum; i-->newNum; ){
			//remove the items with zoom out effect
			SpriteObject* itemPtr = sp[playerIndex].item[itemType][i];
			this->add(new Animator<Vec2>(itemPtr->pos, 0.25*collectedCardNum, itemPtr->pos, 0.2+0.25*collectedCardNum, itemPtr->pos+itemPtr->size*0.5));
			this->add(new Animator<Vec2>(itemPtr->size, 0.25*collectedCardNum, itemPtr->size, 0.2+0.25*collectedCardNum, Vec2(0, 0)));
			this->add( new Timer([=](){
				sp[playerIndex].statusPlate->remove(itemPtr);
			}, 0.25+0.25*collectedCardNum));
		}
		//play sfx of removel of item
		this->add( new Timer([=](){
			playSfx("./assets/gamescene/remove.wav");
		}, 0.25*collectedCardNum));
	}
}

void GameScene::updateDeckCardsNum(){
	int cardsNum = gameLogic->getCardsNum();
	cardDeckNumText->text = std::to_string((long long)cardsNum);
	if(cardsNum==0)
		cardDeckNumText->hide();
}

void GameScene::processAi(){
	Player aiPlayer = gameLogic->getCurrentPlayer();
	std::vector<Card> cards = gameLogic->getUncollectedCards();

	//If there is a damn einstein card in the uncollected cards, don't collect it.
	bool haveEinstein = false;
	for(unsigned int i=0; i<cards.size(); i++){
		if(cards[i].type==CARD_EINSTEIN){
			haveEinstein = true;
			break;
		}
	}
	if(haveEinstein){
		gameLogic->drawCard();
		return;
	}
	//If the card drawn is a great card, then collect it.
	if(cards.back().type==CARD_WLCHAN||cards.back().type==CARD_NOBEL){
		gameLogic->collectCards();
		return;
	}
	
	int totalQuantity = 0;
	//If a silver merit can be gained by collecting the cards, then collect it.
	for(unsigned int i=0; i<cards.size(); i++){
		if(aiPlayer.items[cards[i].type]+cards[i].quantity==TARGET_NUM){
			gameLogic->collectCards();
			return;
		}
		totalQuantity += cards[i].quantity;
	}
	//If the total quantity of items is large enough, then collect it. The more items are there, the higher the chance it is being collected
	if(totalQuantity>0 && (rand()%totalQuantity)>=4){
		gameLogic->collectCards();
		return;
	}

	//depending on the chance of busting, collect the cards.
	double bustProbability = cards.size()/4.0;
	if(rand()%100*bustProbability>20){
		gameLogic->collectCards();
		return;
	}

	//After all consideration, the AI decide not the collect the card.
	gameLogic->drawCard();
	
}