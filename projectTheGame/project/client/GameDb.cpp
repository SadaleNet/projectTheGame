#include "GameDb.h"
#include "../db/RemoteDb.h"
#include <cassert>

GameDb::GameDb():
	loggingIn(false){
	this->userDb = UserDb::instantiate();
	this->remote = ( dynamic_cast<RemoteDb*>(this->userDb.get())!=nullptr );
}

void GameDb::loginStart(){
	assert(!this->loggingIn);
	this->loggingIn = true;
	this->players.clear();
}

bool GameDb::loginNext(std::string username, std::string password){
	assert(this->loggingIn);
	//Try login. If success, append the user to player list, otherwise, stop the login process.
	if(this->userDb->login(username, password)){
		Player player;
		player.ai = false;
		player.wins = this->userDb->getHighScore();
		this->userDb->logout();
		this->players.push_back(player);
		return true;
	}
	this->loggingIn = false;
	return false;
}
void GameDb::loginAiNext(){
	assert(this->loggingIn);
	Player player;
	player.ai = true;
	player.wins = 0;
	this->players.push_back(player);
}
void GameDb::loginDone(){
	assert(this->loggingIn);
	assert(this->players.size()>=MIN_PLAYER&&this->players.size()<=MAX_PLAYER);
	this->loggingIn = false;
}

std::string GameDb::getUserName(int index) const{
	return this->players.at(index).username;
}
bool GameDb::isAi(int index) const{
	return this->players.at(index).ai;
}
void GameDb::addWins(int index){
	Player player = this->players.at(index);
	if(!player.ai){
		assert(this->userDb->login(player.username, player.password));
		this->userDb->setHighScore(player.wins);
		assert(this->userDb->logout());
	}
}

bool GameDb::isRemote() const{
	return this->remote;
}

void GameDb::test(){
	//TODO
}