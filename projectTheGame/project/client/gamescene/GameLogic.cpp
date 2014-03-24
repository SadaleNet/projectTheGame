#include "GameLogic.h"

GameLogic::GameLogic(User* userList, int userNum, bool winOn4, bool reuse)
	:deck(reuse),
	turn(0),
	currentPlayerIndex(0),
	gameStatus(GAME_IN_PROCESS),
	winner(-1){
	for(int i=0; i<userNum; i++)
		this->players.push_back(Player(userList[userNum]));
}

void GameLogic::nextTurn(){
	turn++;
	this->currentPlayerIndex = turn%this->players.size();
}

Card GameLogic::drawCard(){
	Card ret = this->deck.drawCard();
	if(this->drawCardHook)
		this->drawCardHook(ret);
	return ret;
}

std::vector<Card> GameLogic::collectCards(){
	std::vector<Card> ret = this->deck.collectCards();

	for(std::vector<Card>::iterator it=ret.begin(); it!=ret.end(); it++){
		int* items = this->players[this->getCurrentPlayerIndex()].items;

		if(it->type<CARD_ITEM_TYPES_NUM){ //handle ordinary card
			items[it->type] += it->quantity;
		}else if(it->type==CARD_WLCHAN){
			//WLChan: TODO
		}else if(it->type==CARD_NOBEL){
			//Nobel: Add one silver merit
			this->players[this->getCurrentPlayerIndex()].silverMeritNum++;
		}else if(it->type==CARD_EINSTEIN){
			//Einstein: remove all items that the playre have got
			for(int i=0; i<CARD_ITEM_TYPES_NUM; i++)
				items[i] = 0;
		}
		items[it->type] = items[it->type]%TARGET_NUM;
		if(this->collectCardHook)
			this->collectCardHook(*it);
	}

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

bool GameLogic::isLost(){
	return this->deck.isLost();
}

GameStatus GameLogic::getGameStatus() const{
	return this->gameStatus;
}

void GameLogic::test(){
	//TODO
}
