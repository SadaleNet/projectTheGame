#include "Button.h"
#include "../utils/utils.h"

Button::Button(Vec2 pos, Vec2 size, std::string text, Color fontColor, Color fillColor, double borderSize, Color borderColor)
	:GameObject(pos, size),
	action(nullptr),
	textObj(Vec2(0,0), size, text, int(size.y*0.8), fontColor, Text::CENTER),
	rectObj(Vec2(0,0), size, fillColor, borderSize, borderColor),
	fillColor(fillColor){
	textObj.setParent(this);
	rectObj.setParent(this);
}

void Button::updateHook(){
	if(this->isHeld(::LEFT)){
		this->rectObj.setFillColor(Color( this->fillColor.r*0.7, this->fillColor.g*0.7, this->fillColor.b*0.7, this->fillColor.a ));
	}else if(this->isHovered()){
		this->rectObj.setFillColor(Color(
								MIN(1.0, this->fillColor.r*1.3),
								MIN(1.0, this->fillColor.g*1.3),
								MIN(1.0, this->fillColor.b*1.3),
								this->fillColor.a
							));
	}else{
		this->rectObj.setFillColor(this->fillColor);
	}
}

void Button::render() const{
	this->rectObj.render();
	this->textObj.render();
}

void Button::onClick(MouseButton button, Vec2){
	if(button==::LEFT && this->action){
		this->action();
	}
}
