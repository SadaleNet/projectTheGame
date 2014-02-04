#ifndef EVENT_H
#define EVENT_H

enum EventType{
	UPDATE,
	KEY_UP, KEY_DOWN,
	MOUSE_UP, MOUSE_DOWN, MOUSE_MOVE,
	COLLIDE, CLICKED
};

struct EventData{};
enum MouseButton{ NA, LEFT, RIGHT, MIDDLE, SCROLL_UP, SCROLL_DOWN };
struct MouseEvent:public EventData{ MouseButton button; Vec2 pos; };
struct KeyboardEvent:public EventData{ char c; };

#endif