#include "Vec2.h"
#include "GameObject.h"

/// class Sprite - 
class Sprite : public GameObject {
  // Attributes
private:
  SpriteResource sprite;
  // Operations
public:
  Sprite (Vec2 pos, Vec2 size, const std::string& path, Vec2 tileOffset = Vec2(0,0), Vec2 tileSize = Vec2(-1,-1));
  GameObject render () const;
};

