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
	//Search whether the player is already logged in. If so, return false.
	for(std::vector<Player>::iterator it=this->players.begin(); it!=this->players.end(); it++){
		if( it->username==username ){
			this->loggingIn = false;
			return false;
		}
	}
	//Try login. If success, append the user to player list, otherwise, stop the login process.
	if(this->userDb->login(username, password)){
		Player player;
		player.username = username;
		player.password = password;
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

bool GameDb::registerAcc(std::string username, std::string password){
	return this->userDb->registerAcc(username, password);
}

std::string GameDb::getStatus() const{
	return this->userDb->getStatus();
}

std::string GameDb::getHighScoreBoard() const{
	return this->userDb->getHighScoreBoard();
}

std::string GameDb::getUserName(int index) const{
	return this->players.at(index).username;
}
std::string GameDb::getUserNames() const{
	std::string ret;
	for(std::vector<Player>::const_iterator it=this->players.begin(); it!=this->players.end(); it++)
		ret += it->username+", ";
	//remove the tailing ", "
	ret.pop_back(); ret.pop_back();
	return ret;
}
unsigned int GameDb::getUserNum() const{
	return this->players.size();
}
int GameDb::getWins(int index) const{
	return this->players.at(index).wins;
}

bool GameDb::isAi(int index) const{
	return this->players.at(index).ai;
}
void GameDb::addWins(int index){
	Player player = this->players.at(index);
	if(!player.ai){
		assert(this->userDb->login(player.username, player.password));
		this->userDb->setHighScore(++player.wins);
		assert(this->userDb->logout());
	}
}

bool GameDb::isRemote() const{
	return this->remote;
}

void GameDb::test(){
	//TODO
}