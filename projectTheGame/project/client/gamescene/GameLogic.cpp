#include "GameLogic.h"
#include "../GameDb.h"
#include <cassert>

GameLogic::GameLogic(GameDb* gameDb, bool winOn4, bool reuse)
	:deck(reuse),
	gameDb(gameDb),
	turn(0),
	currentPlayerIndex(0),
	winOn4(winOn4),
	gameStatus(GAME_IN_PROCESS),
	winner(-1){
	for(unsigned int i=0; i<gameDb->getUserNum(); i++)
		this->players.push_back(Player());
}

void GameLogic::nextTurn(){
	turn++;
	this->currentPlayerIndex = turn%this->players.size();
	if(this->nextTurnHook)
		this->nextTurnHook();
}

Card GameLogic::drawCard(){
	Card ret = this->deck.drawCard();
	bool cardsCollected = false;
	if(this->drawCardHook)
		this->drawCardHook(ret);
	if(this->deck.isLost()){
		if(this->lostHook)
			this->lostHook();
		this->nextTurn();
	}else if(this->deck.getUncollectedCardsNum()==MAX_CARD_UNCOLLECTED){
		this->collectCards();
		cardsCollected = true;
	}

	//all cards are drawn. Decide the winner.
	if(this->deck.isEmpty()){
		if(!cardsCollected)
			this->collectCards();
		//calculate the most silver merit that a player owns
		int bestSilverMerit = 0;
		for(std::vector<Player>::iterator it=this->players.begin(); it!=players.end(); it++){
			if(it->silverMeritNum>bestSilverMerit)
				bestSilverMerit = it->silverMeritNum;
		}
		
		//check for the player(s) with the most silver merits. If there are more than one player, then the game is tied.
		this->winner = -1;
		this->gameStatus = GAME_WON; //assumes there is only one player with the most silver merits
		for(unsigned int i=0; i<this->players.size(); i++){
			if(this->players[i].silverMeritNum==bestSilverMerit){
				//The assumsion is wrong. There are multiple players with most silver merits. The game is tied.
				if(this->winner!=-1){
					this->gameStatus = GAME_TIED;
					this->winner = -1;
					break;
				}
				this->winner = i;
			}
		}

		if(this->gameEndHook)
			this->gameEndHook();
	}

	return ret;
}

std::vector<Card> GameLogic::collectCards(){
	std::vector<Card> ret = this->deck.collectCards();

	for(std::vector<Card>::iterator it=ret.begin(); it!=ret.end(); it++){
		std::vector<Player> oldPlayerStates = this->players;
		int* items = this->players[this->getCurrentPlayerIndex()].items;

		if(it->type<CARD_ITEM_TYPES_NUM){ //handle ordinary card
			items[it->type] += it->quantity;
		}else if(it->type==CARD_WLCHAN){
			//WLChan: randomly add one item to each of the opponent
			for(unsigned int i=0; i<gameDb->getUserNum(); i++){
				if(i!=this->getCurrentPlayerIndex())
					this->players[i].items[rand()%CARD_ITEM_TYPES_NUM]++;
			}
		}else if(it->type==CARD_NOBEL){
			//Nobel: Add one silver merit
			this->players[this->getCurrentPlayerIndex()].silverMeritNum++;
		}else if(it->type==CARD_EINSTEIN){
			//Einstein: remove all items that the player have got
			for(int i=0; i<CARD_ITEM_TYPES_NUM; i++)
				items[i] = 0;
		}
		if(items[it->type]>=TARGET_NUM){
			if(items[it->type]==TARGET_NUM)
				this->players[this->getCurrentPlayerIndex()].silverMeritNum++;
			items[it->type] = 0;
		}
		if(this->collectCardHook)
			this->collectCardHook(oldPlayerStates, *it);
	}
	
	int silverMeritsDistributed = 0;
	for(unsigned int i=0; i<gameDb->getUserNum(); i++)
		silverMeritsDistributed += this->players[i].silverMeritNum;

	if((this->winOn4&&this->players[this->getCurrentPlayerIndex()].silverMeritNum==4)
		||(!this->winOn4&&silverMeritsDistributed>=11)){
		this->gameStatus = GAME_WON;
		this->winner = this->getCurrentPlayerIndex();
		if(this->gameEndHook)
			this->gameEndHook();
		return ret;
	}

	if(!this->deck.isEmpty())
		this->nextTurn();

	return ret;
}

int GameLogic::getCurrentPlayerIndex() const{
	return this->currentPlayerIndex;
}

Player GameLogic::getCurrentPlayer(){
	return this->players[this->getCurrentPlayerIndex()];
}

std::vector<Player> GameLogic::getPlayers(){
	return this->players;
}

int GameLogic::getWinner() const{
	if(this->gameStatus==GAME_WON)
		return this->winner;
	return -1;
}

bool GameLogic::isDeckEmpty() const{
	return this->deck.isEmpty();
}

int GameLogic::getCardsNum() const{
	return this->deck.getCardsNum();
}

std::vector<Card> GameLogic::getUncollectedCards() const{
	return this->deck.getUncollectedCards();
}

bool GameLogic::isLost(){
	return this->deck.isLost();
}

GameStatus GameLogic::getGameStatus() const{
	return this->gameStatus;
}

#include <iostream>
namespace{
	void printPlayersStatus(GameLogic* gameLogic, GameDb* gameDb){
		std::cerr <<"===Current Player: "<< gameDb->getUserName(gameLogic->getCurrentPlayerIndex()) <<"===" <<std::endl;
		std::vector<Player> players = gameLogic->getPlayers();
		for(unsigned int i=0; i<players.size(); i++){
			std::cerr << gameDb->getUserName(i) <<": ";
			for(int j=0; j<CARD_ITEM_TYPES_NUM; j++)
				std::cerr << players[i].items[j] <<", ";
			std::cerr << "|  "<< players[i].silverMeritNum <<std::endl;
		}
		std::cerr <<"==========" <<std::endl;
	}
	void printCard(Card card){
		std::cerr<< "You have drawn a ";
		switch(card.type){
			case CARD_APPLE:	std::cerr<< "Apple";	break;
			case CARD_PEAR:		std::cerr<< "Pear";		break;
			case CARD_CARROT:	std::cerr<< "Carrot";	break;
			case CARD_NUT:		std::cerr<< "Nut";		break;
			case CARD_WLCHAN:	std::cerr<< "WLChan";	break;
			case CARD_NOBEL:	std::cerr<< "Nobel";	break;
			case CARD_EINSTEIN:	std::cerr<< "Einstein";	break;
		}
		if((int)card.type<CARD_ITEM_TYPES_NUM)
			std::cerr<< " " <<card.quantity;
		std::cerr<< " card" <<std::endl;
	}
}

void GameLogic::test(){
	GameDb gameDb;
	gameDb.registerAcc("testPlayer1", "password");
	gameDb.registerAcc("testPlayer2", "password");
	gameDb.registerAcc("testPlayer3", "password");
	gameDb.registerAcc("testPlayer4", "password");

	bool winOn4, reuseLost;
	int playerNum;
	std::cerr<< "==Welcome to GameLogic Manual Testing Function==" <<std::endl;
	std::cerr<< "Win on 4 silver merits? [1/0]:";
	std::cin >> winOn4;
	std::cerr<< "Reuse lost cards? [1/0]:";
	std::cin >> reuseLost;
	std::cerr<< "How many players? [2~4]:";
	std::cin >> playerNum;

	gameDb.loginStart();
	assert(gameDb.loginNext("testPlayer1", "password"));
	assert(gameDb.loginNext("testPlayer2", "password"));
	if(playerNum>=3)
		assert(gameDb.loginNext("testPlayer3", "password"));
	if(playerNum>=4)
		assert(gameDb.loginNext("testPlayer4", "password"));
	gameDb.loginDone();

	GameLogic gameLogic(&gameDb, winOn4, reuseLost);
	std::cerr<< "====Game Begin!====" <<std::endl;
	bool lost = false;
	gameLogic.lostHook = [&](){ lost = true; };
	//main loop
	while(gameLogic.getGameStatus()==GAME_IN_PROCESS){
		lost = false;
		printPlayersStatus(&gameLogic, &gameDb);

		//draw a card then print it
		printCard(gameLogic.drawCard());
		int cardsDrawn = 1;
		//ask if the user want to draw more cards
		while(cardsDrawn<MAX_CARD_UNCOLLECTED && !lost){
			bool drawMore;
			std::cerr <<"Draw More? [1/0]:";
			std::cin >> drawMore;
			if(!drawMore){
				break;
			}
			printCard(gameLogic.drawCard());
			cardsDrawn++;
		}
		if(lost)
			std::cerr << "LOST!" <<std::endl;
		else if(gameLogic.deck.getUncollectedCardsNum()<MAX_CARD_UNCOLLECTED)
			gameLogic.collectCards();
		std::cerr <<std::endl <<std::endl;
	}
	printPlayersStatus(&gameLogic, &gameDb);
	std::cerr<< "====Winner: " <<gameLogic.getWinner() <<"====" <<std::endl;
	std::cerr<< "====Game End!====" <<std::endl;
}
