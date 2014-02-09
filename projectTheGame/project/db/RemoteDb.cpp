#include "RemoteDb.h"
#include <cstdlib>
#include <cassert>
#include <stdexcept>

#define SEND_REQUEST(_page, _suffix, _response) \
	HttpGetRequest(this->urlBase+_page"?username="+urlEncode(username)+"&password="+urlEncode(password)+_suffix, _response)

RemoteDb::RemoteDb(const std::string& urlBase)
	:urlBase(urlBase){
	if( SEND_REQUEST("test.php", "", this->status)!=200 && this->status!="It's working!\n" )
		throw std::runtime_error("Error: server side error.");
}

bool RemoteDb::registerAcc(const std::string& username, const std::string& password){
	return (SEND_REQUEST("register.php", "", this->status) == 200);
}

bool RemoteDb::deregisterAcc(const std::string& username, const std::string& password){
	return (SEND_REQUEST("deregister.php", "", this->status) == 200);
}

bool RemoteDb::login(const std::string& username, const std::string& password){
	this->username = username;
	this->password = password;
	return (SEND_REQUEST("login.php", "", this->status) == 200);
}

bool RemoteDb::logout(){
	return (SEND_REQUEST("logout.php", "", this->status) == 200);
}

bool RemoteDb::putData(const std::string& data){
	return (SEND_REQUEST("store.php", std::string("&content=")+urlEncode(data), this->status) == 200);
}

bool RemoteDb::setHighScore(int score){
	if(score<=this->getHighScore())
		return false;
	return (SEND_REQUEST("store.php", std::string("&score=1&content=")+std::to_string((long long)score), this->status) == 200);
}

std::string RemoteDb::getData() const{
	std::string responseBody;
	if ( SEND_REQUEST("fetch.php", "", responseBody) == 200 )
		return responseBody;
	throw std::runtime_error(responseBody);
}

int RemoteDb::getHighScore() const{
	std::string responseBody;
	if ( SEND_REQUEST("fetch.php", "&score=1", responseBody) == 200 )
		return atoi(&responseBody[0]);
	throw std::runtime_error(responseBody);
}

std::string RemoteDb::getHighScoreBoard() const{
	std::string responseBody;
	if ( HttpGetRequest(urlBase+"highscore.php", responseBody) == 200 )
		return responseBody;
	throw std::runtime_error(responseBody);
}

std::string RemoteDb::urlEncode(const std::string& data) const{
	std::string ret;
	for(size_t i=0; i<data.size(); i++){
		if( isalnum(data[i]) || data[i] == '-' || data[i] == '_' || data[i] == '.' || data[i] == '~' ){
			ret += data[i];
		}else{
			//encode a byte to %xx , where xx is hex.
			ret += '%';
			int temp;

			//convert the first hex digit
			temp = (static_cast<int>(data[i])&0xF0)>>4;
			if(temp>=10)	ret += temp-10+'A';
			else			ret += temp+'0';

			//convert the second hex digit
			temp = static_cast<int>(data[i])&0x0F;
			if(temp>=10)	ret += temp-10+'A';
			else			ret += temp+'0';
		}
	}
	return ret;
}

void RemoteDb::test(){
	RemoteDb db(REMOTE_SERVER);
	db.registerAcc("alpha", "password");
	db.registerAcc("beta", "meowie");

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

	assert(db.getHighScoreBoard()==
		"Username            Score\n"
		"beta                30000\n"
		"alpha               200\n");

}