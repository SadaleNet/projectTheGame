#include "Vec2.h"
#include "GameObject.h"

/// class Text - 
class Text : public GameObject {
  // Attributes
private:
  std::string text;
  // Operations
public:
  Text (Vec2 pos, Vec2 size, const std::string& text, const Color& textColor);
  GameObject render () const;
};

