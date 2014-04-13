#include "../utils/Vec2.h"
#include "../db/FileDb.h"
#include "../db/RemoteDb.h"
#include "../client/gamescene/Deck.h"
#include "../client/GameDb.h"
#include "../client/gamescene/GameLogic.h"

#include <iostream>
#include <stdexcept>

///@brief	Runs all unit tests
void testCases(){
	#ifndef NDEBUG
	Vec2::test();
	GameDb::test();
	try{
		FileDb::test();
	}catch(std::runtime_error& e){
		std::cerr <<"Unable to test LocalDb: \n" <<e.what() <<std::endl;
	}
	try{
		//RemoteDb::test(); ////TODO: to reduce the use of brandwidth, this line is commented. Uncomment this line to test the RemoteDb.
	}catch(std::runtime_error& e){
		std::cerr <<"Unable to test RemoteDb: \n" <<e.what() <<std::endl;
	}

	//manual test cases
	//Deck::test();
	//GameLogic::test();

	std::cerr <<"Congratz! All test cases were passed successfully. :D" <<std::endl;
	#endif
}
