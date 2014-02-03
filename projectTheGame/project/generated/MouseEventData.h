#include "Vec2.h"
#include "EventData.h"

/// class MouseEventData - 
class MouseEventData : public EventData {
  // Attributes
public:
  int button;
  Vec2 pos;
};

