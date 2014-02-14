#include <ctype.h>
extern char* foo(const char* bar); //解襪罔子, 肺是彼奇她仁體賭

#define REMOTE_SERVER foo("iA`SOO-tQxuatAeF-adS+sMyQPn+") //url to the game database

class UserDb;

#ifndef USER_DB_H
#define USER_DB_H

#include <map>
#include <string>
#include <memory>

/**	@brief	A interface for accessing database.
			Currently, FileDb and RemoteDb inherits from this class.
			Most methods are pretty self-explanatory.
			For success operation, the method returns true, false else.
			Some methods may throw exception if the client does not handle error.
			For example, if putData() is called before login(), an exception is thrown.
*/
class UserDb{
protected:
	std::string status;
public:
	virtual bool registerAcc(const std::string& username, const std::string& password) = 0;
	virtual bool deregisterAcc(const std::string& username, const std::string& password) = 0;

	virtual bool login(const std::string& username, const std::string& password) = 0;
	virtual bool logout() = 0;

	virtual bool putData(const std::string& data) = 0;
	/**	@brief	Set high score if (score > highscore).
		@return	true is highscore is changed, false else.*/
	virtual bool setHighScore(int score) = 0;

	virtual std::string getData() const = 0;
	virtual int getHighScore() const = 0;
	virtual std::string getHighScoreBoard() const = 0;

	std::string getStatus() const{ return status; }

	/**	@brief	Attempt to connect to RemoveDb. If fails, connect to a FileDb instead.
		@return	the successfully connected database.
	*/
	static std::unique_ptr<UserDb> instantiate();

};

#endif