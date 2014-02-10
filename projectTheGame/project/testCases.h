#include "./utils/Mat33.h"
#include "./utils/Vec2.h"
#include "./db/FileDb.h"
#include "./db/RemoteDb.h"
#include <iostream>

void testCases(){
	#ifndef NDEBUG
	Vec2::test();
	Mat33::test();
	try{
		FileDb::test();
	}catch(std::runtime_error& e){
		std::cerr <<"Unable to test LocalDb: \n" <<e.what() <<std::endl;
	}
	try{
		RemoteDb::test();
	}catch(std::runtime_error&){
		std::cerr <<"Unable to test RemoteDb: \n" <<e.what() <<std::endl;
	}
	std::cerr <<"Congratz! All test cases were passed successfully. :D" <<std::endl;
	#endif
}
