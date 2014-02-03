#include "UserDb.h"

/// class RemoteDb - 
class RemoteDb : public UserDb {
  // Attributes
private:
  std::string urlBase;
  // Operations
public:
  RemoteDb (const std::string& urlBase);
};

