#include "./utils/Mat33.h"
#include "./utils/Vec2.h"
#include <iostream>

void testCases(){
	#ifndef NDEBUG
	Vec2::test();
	Mat33::test();
	std::cout <<"Congratz! All test cases were passed successfully. :D" <<std::endl;
	#endif
}