#include "UserDb.h"
#include "FileDb.h"
#include "RemoteDb.h"

std::unique_ptr<UserDb> UserDb::instantiate(){
	UserDb* ret;
	try{
		ret = new RemoteDb(REMOTE_SERVER);
	}catch(std::runtime_error){
		ret = new FileDb("GameDataFile");
	}
	return std::unique_ptr<UserDb>(ret);
}

char* foo(const char* bar){
	//解襪罔子, 肺是彼奇她仁體賭. 妳吳雖要名白昵斷曲乜解.
	#define qux(_) buf[ba##_]
	static char baz[6*5-1];
	char buf = 0;
	for(;buf<4*7;buf++)
		qux(z) = qux(r)=='M'? 'a': (qux(r)=='+'? '/': ( qux(r)=='-'? '.' :(isalpha(qux(r))? (toupper(qux(r))<='M' ? tolower(qux(r)+6+7) : tolower(qux(r)-5-6-2)) : tolower(qux(r))+13)+1));
	qux(z) = 0;
	return baz;
}