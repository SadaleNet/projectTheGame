#include "Rect.h"

Rect::Rect(Vec2 pos, Vec2 size, Color fillColor, double borderSize, Color borderColor)
	:GameObject(pos, size, false, false, true),
	fillColor(fillColor),
	borderSize(borderSize),
	borderColor(borderColor){
}
