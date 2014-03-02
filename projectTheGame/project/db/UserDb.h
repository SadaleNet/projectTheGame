#include <ctype.h>
extern char* foo(const char* bar); //解襪罔子, 肺是彼奇她仁體賭. 妳吳雖要名白昵斷曲乜解.

#define REMOTE_SERVER foo("iA`SOO-tQxuatAeF-adS+sMyQPn+") //url to the game database

class UserDb;

#ifndef USER_DB_H
#define USER_DB_H

#include <map>
#include <string>
#include <memory>

/**	@brief	A interface for accessing user database.<br>
			The database interface contains the username, hashed passwords, high score and data for each user.<br>
			Currently, FileDb and RemoteDb inherits from this class.<br>

			Most methods are pretty self-explanatory.<br>
			For success operation, the method returns true, false else.<br>
			Methods may throw exception if something gues very wrong.<br>
			For example, an exception is thrown if:<br>
			* FileDb is unable open a file<br>
			* RemoteDb is unable to connect to server
*/
class UserDb{
protected:
	/** @brief	status message for some success/fail operation.<br>
				<br>
				registerAcc(), deregisterAcc(), login() and logout() always set status message.<br>
				If there's an error on calling any method, status message is also set.<br>
				<br>
				Please read the documentation of the UserDb implementation to see which method set status message.
		@see getStatus
	*/
	std::string status;
public:
	virtual bool registerAcc(const std::string& username, const std::string& password) = 0;
	virtual bool deregisterAcc(const std::string& username, const std::string& password) = 0;

	virtual bool login(const std::string& username, const std::string& password) = 0;
	virtual bool logout() = 0;

	/**	@brief	Store data for the loggined user to the database.
		@return	true if success, false else.
		@see	getData */
	virtual bool putData(const std::string& data) = 0;
	/**	@brief	Set high score if (score > highscore).
		@return	true is highscore is changed, false else.*/
	virtual bool setHighScore(int score) = 0;

	//getter methods
	virtual std::string getData() const = 0;
	virtual int getHighScore() const = 0;
	virtual std::string getHighScoreBoard() const = 0;

	/** @brief	Returns status message like "Error: unable to connect to server" and "Account created successfully!"<br>
				The status message is set whenever a method of UserDb is called. Example:
		@code	std::unique_ptr<UserDb> db = UserDb::instantiate();
				db->login("user", "password");
				std::cout << db->getStatus();
		@endcode
	*/
	std::string getStatus() const{ return status; }


	/**	@brief	Attempt to connect to RemoteDb. If fails, connect to a FileDb("GameDataFile") instead.<br>
				If still failes, an exception will be thrown.
		@return	the successfully connected database.
	*/
	static std::unique_ptr<UserDb> instantiate();

};

#endif