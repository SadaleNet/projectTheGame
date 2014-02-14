class Button;

#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"
#include "Rect.h"
#include "Text.h"

/**
Button has a Rect and Text
The following variables are automatically calculated, and cannot be changed:
Variable		Value
Text::align		CENTER
Text::fontSize	80% of height
hover color		130% brightness of original
press color		70% brightness of original
*/
class Button: public GameObject{
protected:
	Text textObj;
	Rect rectObj;
public:
	Color fillColor;
	Color& fontColor; //refers to textObj
	double& borderSize; //refers to rectObj
	Color& borderColor; //refers to rectObj

	std::function<void()> action; ///action() is executed when the button is clicked.

	Button(Vec2 pos, Vec2 size, std::string text, Color fontColor, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	virtual void render() const override;

	//change the color according to the states(hover, held)
	virtual void updateHook() override;
	virtual void onClick(MouseButton button, Vec2) override;

	//setters and getters
	///action() is executed when the button is clicked.
	Button& setFontColor(Color fontColor){ textObj.fontColor = fontColor; return *this; }
	Button& setBorderSize(double borderSize){ rectObj.borderSize = borderSize; return *this; }
	Button& setBorderColor(Color borderColor){ rectObj.borderColor = borderColor; return *this; }

	Color getFontColor() const{ return textObj.fontColor; }
	double getBorderSize() const{ return rectObj.borderSize; }
	Color getBorderColor() const{ return rectObj.borderColor; }

};

#endif