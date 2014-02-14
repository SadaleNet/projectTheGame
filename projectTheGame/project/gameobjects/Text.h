class Text;

#ifndef TEXT_H
#define TEXT_H
#include "GameObject.h"
#include "../utils/Color.h"

class Text: public GameObject{
public:
	enum Align{ LEFT, CENTER, RIGHT };
	std::string text;
	Align align;
	int fontSize;
	Color fontColor;

	Text(Vec2 pos, Vec2 size, std::string text, int fontSize, Color fontColor=Color(0.0, 0.0, 0.0, 1.0), Align align=LEFT);
	virtual void render() const override;

};

#endif