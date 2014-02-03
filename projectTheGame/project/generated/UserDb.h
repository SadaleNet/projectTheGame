/// class UserDb - 
class UserDb {
  // Attributes
protected:
  username std::string;
  password std::string;
  std::string data;
  int highScore;
  // Operations
public:
  register (const std::string& username, const std::string& password);
  deregister (const std::string& username, const std::string& password);
  login (const std::string& username, const std::string& password);
  logout ();
  const std::string& putData (const std::string& data);
  int setHighScore (int score);
  std::string getData () const;
  int getHighScore () const;
  virtual std::map<std::string, int> getHighScores () const = 0;
private:
  virtual loginHook (const std::string& username, const std::string& password) = 0;
  virtual logoutHook () = 0;
  virtual const std::string& putDataHook (const std::string& data) = 0;
  virtual int setHighScoreHook (int score) = 0;
};

