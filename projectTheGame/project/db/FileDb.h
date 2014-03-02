class FileDb;

#ifndef FILE_DB_H
#define FILE_DB_H

#include "UserDb.h"
#include <map>
#include <stdint.h>

/** @brief	A data struct for storing an entity of user data.<br>
			Used by FileDb to save/load user list from file
	@see	FileDb
*/
struct UserData{
	uint64_t password; //hashed password.
	int highScore;
	std::string data;
	UserData(){}
	UserData(uint64_t password, int highScore, std::string data)
		:password(password), highScore(highScore), data(data){}
};

/**	@brief	UserDb implementation of storing data into a file.

			File format:<br>
				For each user:<br>
				[username][tab][hashedPassword][tab][highScore][tab][serializedData][LF],<br>
				where [hashedPassword] is a FNV-1 hashed password.<br>
			In UserDb: registerAcc(), deregisterAcc(), login() and logout() set status message.
*/
class FileDb: public UserDb{
private:
	std::string filePath;
	std::string username;
protected:
	/**
		@brief	Save dataTable into a file<br>
				This function is called whenever dataTable is updated.
		@throw	std::runtime_error if fail saving dataTable into a file.
	*/
	void save() const;

public:
	///	@throw	std::runtime_error if fail opening the file
	FileDb(const std::string& filePath);

	///stores data of all users
	std::map<std::string, UserData> dataTable;

	//Note: Whenever dataTable is modified, this->save() is called by the methdos below.

	virtual bool registerAcc(const std::string& username, const std::string& password) override;
	virtual bool deregisterAcc(const std::string& username, const std::string& password) override;

	virtual bool login(const std::string& username, const std::string& password) override;
	virtual bool logout() override;

	virtual bool putData(const std::string& data) override;
	virtual bool setHighScore(int score) override;

	virtual std::string getData() const override;
	virtual int getHighScore() const override;
	virtual std::string getHighScoreBoard() const override;

	static void test();
};

#endif