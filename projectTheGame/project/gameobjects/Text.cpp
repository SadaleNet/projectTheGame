#include "Text.h"

Text::Text(Vec2 pos, Vec2 size, std::string text, int fontSize, Color fontColor, Align align)
	:GameObject(pos, size),
	text(text),
	fontSize(fontSize),
	fontColor(fontColor),
	align(align){
}

