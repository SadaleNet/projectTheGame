class FileDb;

#ifndef FILE_DB_H
#define FILE_DB_H

#include "UserDb.h"
#include <map>
#include <stdint.h>

struct UserData{
	uint64_t password; //hashed password.
	int highScore;
	std::string data;
	UserData(){}
	UserData(uint64_t password, int highScore, std::string data)
		:password(password), highScore(highScore), data(data){}
};

/**	@brief	UserDb implementation of storing data into a file.
			File format:
				For each user:
				<username>\t<hashedPassword>\t<highScore>\t<serializedData>\n,
				where <hashedPassword> is a FNV-1 hashed password.
*/
class FileDb: public UserDb{
private:
	std::string filePath;
	std::string username;

	std::map<std::string, UserData> dataTable; //key: username
	void save() const;

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
	FileDb(const std::string& filePath);

	static void test();
};

#endif