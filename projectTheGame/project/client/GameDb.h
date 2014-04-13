#include <string>
#include <vector>
#include "../db/UserDb.h"

#define MIN_PLAYER 2
#define MAX_PLAYER 4

#ifndef GAME_DB_H
#define GAME_DB_H
/** @brief A proxy class for accessing UserDb

	Provides simplified interface for accessing data of multiple players.
*/
class GameDb{
private:
	///@brief A private struct for storing user data.
	struct Player{
		std::string username, password;
		int wins;
		bool ai;
	};
	///a list of players
	std::vector<Player> players;
	///the database for storing/accessing data
	std::unique_ptr<UserDb> userDb;
	///true if a remote database is being used, false else.
	bool remote;
	///true if loginStart() is called and loginDone() is not called, false else.
	bool loggingIn;
public:
	GameDb();

	/** @brief Bulk login functions<br>

		loginStart(), loginNext(), loginAiNext(), loginDone()<br>
		Used for logging in multiple players.<br>
		To use it, first call loginStart()<br>
		Then call loginNext() or loginAiNext() to add players to be logged in.<br>
		Finally, call loginDone() to end the login process<br>
		If loginNext() failes, it returns false and loginDone() should not be called.<br>
		The procedure above must be strictly followed. Otherwise, assert() in the functions will fail.
	*/
	void loginStart();
	///@see loginStart
	bool loginNext(std::string username, std::string password);
	///@see loginStart
	void loginAiNext();
	///@see loginStart
	void loginDone();

	//@return true if success, false else.
	bool registerAcc(std::string username, std::string password);

	//@return the status of connection, including error message.
	std::string getStatus() const;

	///@return the user name of the player of the index given
	std::string getUserName(int index) const;
	///@return a list of logged in player names.
	std::string getUserNames() const;
	///@return true if the player of the given index is AI, false else.
	bool isAi(int index) const;
	///@brief Increase the scode(win count) by one in the database.
	void addWins(int index);

	///@return true if the remote database is being used, false else.
	bool isRemote() const;

	///@brief all test cases of this class goes here
	static void test();
};

#endif