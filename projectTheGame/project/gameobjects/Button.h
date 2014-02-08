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
private:
	std::function<void()> action;
protected:
	Text textObj;
	Rect rectObj;
	Color fillColor;
public:
	Button(Vec2 pos, Vec2 size, std::string text, Color fontColor, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	virtual void render() const override;

	virtual void updateHook() override;
	virtual void onSceneAdded() override;
	virtual void onSceneRemoved() override;
	virtual void onClick(MouseButton button, Vec2) override;

	//setters and getters
	Button& setAction(std::function<void()> action){ this->action = action; return *this; }
	Button& setFontColor(Color fontColor){ textObj.setFontColor(fontColor); return *this; }
	Button& setFillColor(Color fillColor){ this->fillColor = fillColor; return *this; }
	Button& setBorderSize(double borderSize){ rectObj.setBorderSize(borderSize); return *this; }
	Button& setBorderColor(Color borderColor){ rectObj.setBorderColor(borderColor); return *this; }
	
	std::function<void()> getAction(){ return action; }
	Color getFontColor() const{ return textObj.getFontColor(); }
	Color getFillColor() const{ return fillColor; }
	double getBorderSize() const{ return rectObj.getBorderSize(); }
	Color getBorderColor() const{ return rectObj.getBorderColor(); }

};

#endif