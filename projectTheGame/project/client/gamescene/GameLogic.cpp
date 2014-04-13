#include "GameLogic.h"
#include "../GameDb.h"

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
	if(this->drawCardHook)
		this->drawCardHook(ret);
	if(this->deck.isLost()&&this->lostHook)
		this->lostHook();

	//all cards are drawn. Decide the winner.
	if(this->deck.isEmpty()){
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

		//If someone won, add a score for him in the databate
		if(this->gameStatus==GAME_WON)
			this->gameDb->addWins(this->winner);

		if(this->gameEndHook)
			this->gameEndHook();
	}

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
			//Einstein: remove all items that the player have got
			for(int i=0; i<CARD_ITEM_TYPES_NUM; i++)
				items[i] = 0;
		}
		items[it->type] = items[it->type]%TARGET_NUM;
		if(this->collectCardHook)
			this->collectCardHook(*it);
	}

	if(this->winOn4&&this->players[this->getCurrentPlayerIndex()].silverMeritNum==4){
		this->gameStatus = GAME_WON;
		this->gameEndHook();
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
