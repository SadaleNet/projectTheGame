#include "Vec2.h"

/// class GameObject - Problems: a) Assumes rectangular objects b) strongly coupled with Scene
class GameObject {
  // Attributes
private:
  std::map<EventType, std::function<bool(EventData)>> eventList;
  Vec2 pos;
  Vec2 size;
  double scale;
  double rot;
  // Operations
public:
  virtual update () = 0;
  virtual render () = 0;
  GameObject on (EventType eventType, const std::function<bool(EventData)>& callback);
  GameObject trigger (EventType eventType);
  GameObject off (EventType eventType);
  GameObject setPos (setPos pos);
  GameObject setSize (Vec2 size);
  GameObject setScale (double scale);
  GameObject setRot (double rot);
  Vec2 getPos () const;
  Vec2 getSize () const;
  double getScale () const;
  double getRot () const;
  /// GOTCHA: ONLY considers pos and size. IGNORES rot and scale.
  /// @param other		(???) 
  bool isCollide (GameObject other);
  /// GOTCHA: ONLY considers pos and size. IGNORES rot and scale,
  /// @param other		(???) 
  bool isCollide (Vec2 other);
  virtual GameObject render () const = 0;
};

