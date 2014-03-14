#include "TextBox.h"
#include "../utils/utils.h"
#include <ctype.h>
#include <math.h>

TextBox::TextBox(Vec2 pos, Vec2 size, Color fontColor, Color fillColor, double borderSize, Color borderColor)
	:GameObject(pos, size, true, true, false),
	button(nullptr),
	textObj(Vec2(0,0), size, "", int(size.y*0.8), fontColor, Text::LEFT),
	rectObj(Vec2(0,0), size, fillColor, borderSize, borderColor),
	fillColor(fillColor),
	secret(false),
	fontColor(textObj.fontColor),
	borderSize(rectObj.borderSize),
	borderColor(rectObj.borderColor){
	textObj.setParent(this);
	rectObj.setParent(this);
}

void TextBox::updateHook(){
	if(this->isFocused()){
		this->rectObj.fillColor = Color(
									MIN(1.0, this->fillColor.r*1.3),
									MIN(1.0, this->fillColor.g*1.3),
									MIN(1.0, this->fillColor.b*1.3),
									this->fillColor.a
								);
	}else{
		this->rectObj.fillColor = this->fillColor;
	}

	std::string renderStr = this->secret?std::string(this->text.size(), '*'):this->text;
	//simulate blanking cursor by appending '_' to the text sometimes.
	if( this->isFocused() && fmod(this->getScene()->getSec(), 0.5) > 0.25 )
		this->textObj.text = renderStr+'_';
	else
		this->textObj.text = renderStr;
}

void TextBox::render() const{
	this->rectObj.render();
	this->textObj.render();
}

void TextBox::onKeyUp(char key){
	if(this->isFocused()){
		switch(key){
			case '\b':	if(this->text.size()>0){ this->text.pop_back(); }	break;
			case '\n':	this->button->action();								break;
			case '<':	/*TODO: unimplemented*/								break;
			case '>':	/*TODO: unimplemented*/								break;
			default:
				if( isprint(key) || key==' ' )
					this->text.push_back(key);
		}
	}
}
