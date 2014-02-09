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