class TextBox;

#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "GameObject.h"
#include "Button.h"
#include "Rect.h"
#include "Text.h"
#include <string>

/**
TextBox has a Rect and Text
The following variables are automatically calculated, and cannot be changed:
Variable		Value
Text::align		LEFT
Text::fontSize	80% of height
*/
class TextBox: public GameObject{
private:
	Button* button;
protected:
	Text textObj;
	Rect rectObj;
	Color fillColor;
	std::string text;
public:
	TextBox(Vec2 pos, Vec2 size, Color fontColor, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	virtual void render() const override;

	virtual void updateHook() override;
	virtual void onSceneAdded() override;
	virtual void onSceneRemoved() override;
	virtual void onKeyUp(char key) override;

	//setters and getters
	TextBox& setButton(Button* button){ this->button = button; return *this; }
	TextBox& setFontColor(Color fontColor){ textObj.setFontColor(fontColor); return *this; }
	TextBox& setFillColor(Color fillColor){ this->fillColor = fillColor; return *this; }
	TextBox& setBorderSize(double borderSize){ rectObj.setBorderSize(borderSize); return *this; }
	TextBox& setBorderColor(Color borderColor){ rectObj.setBorderColor(borderColor); return *this; }
	
	Button* getButton(){ return this->button; }
	Color getFontColor() const{ return textObj.getFontColor(); }
	Color getFillColor() const{ return fillColor; }
	double getBorderSize() const{ return rectObj.getBorderSize(); }
	Color getBorderColor() const{ return rectObj.getBorderColor(); }

};

#endif