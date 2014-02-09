#ifndef REMOTE_DB_H
#define REMOTE_DB_H

#include "UserDb.h"
#include <string>

/**	@brief	UserDb implementation by using a remote database, communicating using Simple Game Database protocol over HTTP.
			For the use of the protocal, README-remoteGameDb in this directory.

			In UserDb,	registerAcc(), deregisterAcc(), login() and logout() always set status message.
			If there's an error on calling any method, status message is set.
*/

class RemoteDb: public UserDb{
private:
	std::string urlBase;
	std::string username;
	std::string password;

public:
	///@param	the location of the resource. example: www.example.com/gamedb . Do NOT use http:// prefix
	RemoteDb(const std::string& urlBase);

	virtual bool registerAcc(const std::string& username, const std::string& password) override;
	virtual bool deregisterAcc(const std::string& username, const std::string& password) override;

	virtual bool login(const std::string& username, const std::string& password) override;
	virtual bool logout() override;

	virtual bool putData(const std::string& data) override;
	virtual bool setHighScore(int score) override;

	virtual std::string getData() const override;
	virtual int getHighScore() const override;
	virtual std::string getHighScoreBoard() const override;

	/**	@brief	Send HTTP request and store the response
		@param	The request url
		@param	The response body
		@return	HTTP status code
	*/
	int HttpGetRequest(const std::string& url, std::string& responseBody) const;
	/// @brief Implements rawurlencode() in PHP
	std::string urlEncode(const std::string& data) const;
	
	static void test();
};

#endif