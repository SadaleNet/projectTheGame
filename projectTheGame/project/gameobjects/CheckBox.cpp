#include "CheckBox.h"
#include "../utils/utils.h"
#include <ctype.h>
#include <math.h>

CheckBox::CheckBox(Vec2 pos, Vec2 size, std::string text, Color fontColor, Color fillColor, double borderSize, Color borderColor)
	:GameObject(pos, size, true, false, false),
	textObj(Vec2(size.y+PADDING, 0), size-Vec2(size.y+PADDING, 0), text, int(size.y*0.8), fontColor, Text::LEFT),
	buttonObj(Vec2(0,0), Vec2(size.y, size.y), "", fontColor, fillColor, borderSize, borderColor),
	fillColor(fillColor),
	checked(false),
	fontColor(textObj.fontColor),
	text(textObj.text),
	borderSize(buttonObj.borderSize),
	borderColor(buttonObj.borderColor){
	textObj.setParent(this);
	buttonObj.setParent(this);
	buttonObj.action = [=](){ this->checked = !this->checked; };
}

void CheckBox::updateHook(){
	//Set the brightness of the button
	if(this->isHeld(::LEFT)){
		this->buttonObj.fillColor = Color( this->fillColor.r*0.7, this->fillColor.g*0.7, this->fillColor.b*0.7, this->fillColor.a );
	}else if(this->isHovered()){
		this->buttonObj.fillColor = Color(
										MIN(1.0, this->fillColor.r*1.3),
										MIN(1.0, this->fillColor.g*1.3),
										MIN(1.0, this->fillColor.b*1.3),
										this->fillColor.a
									);
	}else{
		this->buttonObj.fillColor = this->fillColor;
	}
	this->buttonObj.updateHook(); //Note: this->buttonObj.isFocused() is always false.

	//Show the 'X' mark if the checkbox is checked
	if(this->checked)
		this->buttonObj.text = "X";
	else
		this->buttonObj.text = "";
}

void CheckBox::render() const{
	this->buttonObj.render();
	this->textObj.render();
}

void CheckBox::onClick(MouseButton button, Vec2){
	if(button==::LEFT)
		this->buttonObj.action();
}
