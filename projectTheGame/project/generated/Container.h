#include "Vec2.h"
#include "GameObject.h"

/// class Container - 
class Container : public GameObject {
  // Associations
  GameObject unnamed_3;
  // Attributes
private:
  std::vector<GameObject> children;
  // Operations
public:
  Container (Vec2 pos, Vec2 size, const Color& bgColor);
  /// Renders all childrens with pos shifted and clipped by the container size
  GameObject render () const;
  Container appendChild (GameObject* child);
  Container removeChild (GameObject* child);
};

