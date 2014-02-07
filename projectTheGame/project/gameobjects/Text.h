#ifndef TEXT_H
#define TEXT_H
#include "GameObject.h"
#include "../utils/Color.h"

class Text: public GameObject{
public:
	enum Align{ LEFT, CENTER, RIGHT };
protected:
	std::string text;
	Align align;
	int fontSize;
	Color fontColor;

public:
	Text(Vec2 pos, Vec2 size, std::string text, int fontSize, Color fontColor=Color(0.0, 0.0, 0.0, 1.0), Align align=LEFT);
	virtual void render() const override;

	//setters and getters
	Text& setText(const std::string& text){ this->text = text; return *this; }
	Text& setAlign(Align align){ this->align = align; return *this; }
	Text& setFontSize(int fontSize){ this->fontSize = fontSize; return *this; }
	Text& setFontColor(Color fontColor){ this->fontColor = fontColor; return *this; }

	std::string getText() const{ return text; }
	Align getAlign() const{ return align; }
	int getFontSize() const{ return fontSize; }
	Color getFontColor() const{ return fontColor; }
};

#endif