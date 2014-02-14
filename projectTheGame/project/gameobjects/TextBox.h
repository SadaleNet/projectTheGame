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
protected:
	Text textObj;
	Rect rectObj;
public:
	Button* button; ///button->action() is executed when enter is pressed while this textbox is focused.
	Color fillColor;
	std::string text;
	bool secret;
	Color& fontColor; //refers to textObj
	double& borderSize; //refers to rectObj
	Color& borderColor; //refers to rectObj
	 

	TextBox(Vec2 pos, Vec2 size, Color fontColor, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	virtual void render() const override;

	///change color if focused; simuilate blank cursor
	virtual void updateHook() override;
	///change the content of the textbox
	virtual void onKeyUp(char key) override;

	//setters and getters
	///button->action() is executed when enter is pressed while this textbox is focused.
	TextBox& setButton(Button* button){ this->button = button; return *this; }
	TextBox& setFontColor(Color fontColor){ textObj.fontColor = fontColor; return *this; }
	TextBox& setBorderSize(double borderSize){ rectObj.borderSize = borderSize; return *this; }
	TextBox& setBorderColor(Color borderColor){ rectObj.borderColor = borderColor; return *this; }
	
	Button* getButton(){ return this->button; }
	Color getFontColor() const{ return textObj.fontColor; }
	double getBorderSize() const{ return rectObj.borderSize; }
	Color getBorderColor() const{ return rectObj.borderColor; }

};

#endif