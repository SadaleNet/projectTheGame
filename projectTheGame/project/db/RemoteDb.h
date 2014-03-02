#ifndef REMOTE_DB_H
#define REMOTE_DB_H

#include "UserDb.h"
#include <string>

/**	@brief	UserDb implementation by using a remote database, communicating using Simple Game Database protocol over HTTP.<br>
			For the use of the protocal, please refer to README-remoteGameDb in this directory.
*/
class RemoteDb: public UserDb{
private:
	std::string urlBase; //URL to the game database server. Example: example.com/gamedb/
	std::string username; //username of the current logged in user
	std::string password; //password of the current logged in user

protected:
	/**	@brief	Send HTTP request and store the response. Timeout: 5 seconds
		@param	url	The request url
		@param[out]	responseBody	The response body
		@throw	std::runtime_error if there is a connection problem
		@return	HTTP status code
	*/
	int HttpGetRequest(const std::string& url, std::string& responseBody) const;
	/// @brief Implements rawurlencode() as in PHP
	std::string urlEncode(const std::string& data) const;

public:
	///@throw	std::runtime_error if unable to connect to server
	RemoteDb(const std::string& urlBase);

	//Note: All methods below invoke a connection to server. Expect a delay when calling methods in this class.

	virtual bool registerAcc(const std::string& username, const std::string& password) override;
	virtual bool deregisterAcc(const std::string& username, const std::string& password) override;

	virtual bool login(const std::string& username, const std::string& password) override;
	virtual bool logout() override;

	virtual bool putData(const std::string& data) override;
	virtual bool setHighScore(int score) override;

	virtual std::string getData() const override;
	virtual int getHighScore() const override;
	virtual std::string getHighScoreBoard() const override;

	///Automatic testcases
	static void test();
};

#endif