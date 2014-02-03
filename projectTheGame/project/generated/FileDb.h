#include "UserDb.h"

/// class FileDb - 
class FileDb : public UserDb {
  // Attributes
private:
  std::string filepath;
  // Operations
public:
  FileDb (const std::string& filePath);
private:
  save () const;
};

