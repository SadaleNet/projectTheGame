#include "UserDb.h"

/**	@brief	UserDb implementation by using a remote database, communicating using Simple Game Database protocol over HTTP.
			For the use of the protocal, README-remoteGameDb in this directory.
*/

class RemoteDb : public UserDb {
private:
	std::string urlBase;
	std::string username;
	std::string password;

	virtual bool registerAcc(const std::string& username, const std::string& password) override;
	virtual bool deregisterAcc(const std::string& username, const std::string& password) override;

	virtual bool login(const std::string& username, const std::string& password) override;
	virtual bool logout() override;

	virtual bool putData(const std::string& data) override;
	virtual bool setHighScore(int score) override;

	virtual std::string getData() const override;
	virtual int getHighScore() const override;
	virtual std::string getHighScoreBoard() const override;

public:
	RemoteDb(const std::string& urlBase);
};

