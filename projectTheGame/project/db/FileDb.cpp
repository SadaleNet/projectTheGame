#define _CRT_SECURE_NO_WARNINGS

#include "FileDb.h"
#include <fstream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>

namespace{ //helper functions
	uint64_t hash(std::string str){
		//FNV-1 hash function. Ref: https://en.wikipedia.org/wiki/Fowler_Noll_Vo_hash
		//TODO:	Use a cryto-secure hash function. I use this hash simply because it is easy to implement and that
		//		I am not allow to use 3rd party library.
		uint64_t hash = 0xcbf29ce484222325;
		for(size_t i=0; i<str.size(); i++){
			hash *= 0x100000001b3;
			hash ^= str[i];
		}
		return hash;
	}
}

FileDb::FileDb(const std::string& filePath)
	:filePath(filePath){

	std::ifstream file(filePath);
	if(!file){
		//The file cannot be opened. Let's create a new one.
		std::ofstream newFile(filePath);
		if(!newFile)
			throw std::runtime_error(std::string("Failed creating the file ")+filePath);
		newFile.close();
	}else{
		//The file can be opened. Let's load it.
		while(!file.eof()){
			std::string username;
			UserData userData;
			file >> username >> userData.password >> userData.highScore >> userData.data;
			if(file.eof())
				break;
			this->dataTable[username] = userData;
		}
		file.close();
	}
}

bool FileDb::registerAcc(const std::string& username, const std::string& password){
	try{
		//check whether the user exists. If it does not exists, throws an exception to be catched.
		this->dataTable.at(username);
		return false;
	}catch(std::out_of_range&){
		//the user does not exist. Let's create one
		this->dataTable[username] = UserData( hash(password), 0, "" );
		this->save();
	}
	return true;
}

bool FileDb::deregisterAcc(const std::string& username, const std::string& password){
	if(hash(password)==this->dataTable.at(username).password){
		this->dataTable.erase(username);
		this->save();
		return true;
	}
	return false;
}

bool FileDb::login(const std::string& username, const std::string& password){
	if(hash(password)==this->dataTable.at(username).password){
		this->username = username;
		return true;
	}
	return false;
}

bool FileDb::logout(){
	this->username.clear();
	this->save();
	return true;
}

bool FileDb::putData(const std::string& data){
	this->dataTable.at(username).data = data;
	this->save();
	return true;
}

bool FileDb::setHighScore(int score){
	if( this->dataTable.at(username).highScore < score ){
		this->dataTable.at(username).highScore = score;
		this->save();
		return true;
	}
	return false;
}

std::string FileDb::getData() const{
	return this->dataTable.at(username).data;
}

int FileDb::getHighScore() const{
	return this->dataTable.at(username).highScore;
}

std::string FileDb::getHighScoreBoard() const{
	//initialize a new vector for sorting.
	std::vector< std::pair<std::string, int> > dummy;
	for(std::map<std::string, UserData>::const_iterator it=this->dataTable.begin(); it!=this->dataTable.end(); it++)
		dummy.push_back(std::make_pair<std::string, int>(it->first, it->second.highScore));

	//do the sorting
	std::sort(dummy.begin(), dummy.end(),
		[](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b){ return a.second >= b.second; } );

	const int PADDING = 20;
	std::string ret = "Username            Score\n";
	size_t count = 0;
	for(std::vector< std::pair<std::string, int> >::iterator it=dummy.begin(); it!=dummy.end(); it++){
		if(count>=10)
			break;
		ret += it->first;
		ret += std::string(PADDING-it->first.size(), ' ');
		ret += std::to_string((long long)it->second); //cast it to long long to make VSC++ happy
		ret += '\n';
		count++;
	}
	return ret;
}

void FileDb::save() const{
	std::ofstream saveFile(filePath);
	if(!saveFile)
		throw std::runtime_error(std::string("Failed saving the file ")+filePath);
	for(std::map<std::string, UserData>::const_iterator it= dataTable.begin(); it!=dataTable.end(); it++){
		saveFile << it->first <<'\t'
				<< it->second.password <<'\t'
				<< it->second.highScore <<'\t'
				<< it->second.data << std::endl;
	}
	saveFile.close();
}

void FileDb::test(){
	char fileName[L_tmpnam];
	tmpnam(fileName);

	FileDb db(fileName);
	assert(db.registerAcc("alpha", "password"));
	assert(db.registerAcc("beta", "meowie"));

	assert( !db.login("alpha", "wrong password") );
	assert( db.login("alpha", "password") );
	db.putData("DATA");
	db.setHighScore(200);
	db.setHighScore(50);
	assert(db.getData()=="DATA");
	assert(db.getHighScore()==200);
	db.logout();

	assert( !db.login("beta", "password") );
	assert( db.login("beta", "meowie") );
	db.putData("~beta~");
	db.setHighScore(9999);
	db.setHighScore(30000);
	assert(db.getData()=="~beta~");
	assert(db.getHighScore()==30000);
	db.logout();

	FileDb db2(fileName);

	//already registered. Should not fail here(hence return false)
	assert(!db2.registerAcc("alpha", "password"));
	assert(!db2.registerAcc("beta", "meowie"));

	assert( db2.login("alpha", "password") );
	assert(db2.getData()=="DATA");
	assert(db2.getHighScore()==200);
	db2.logout();
	assert( db2.login("beta", "meowie") );
	assert(db2.getData()=="~beta~");
	assert(db2.getHighScore()==30000);
	db2.logout();
	assert(db2.getHighScoreBoard()==
		"Username            Score\n"
		"beta                30000\n"
		"alpha               200\n");
	remove(fileName);
}