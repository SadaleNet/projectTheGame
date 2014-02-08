#include "TextBox.h"
#include "../utils/utils.h"
#include <ctype.h>
#include <math.h>

TextBox::TextBox(Vec2 pos, Vec2 size, Color fontColor, Color fillColor, double borderSize, Color borderColor)
	:GameObject(pos, size),
	button(nullptr),
	textObj(pos, size, "", int(size.y*0.8), fontColor, Text::LEFT),
	rectObj(pos, size, fillColor, borderSize, borderColor),
	fillColor(fillColor){
}

void TextBox::updateHook(){
	this->textObj.setPos(this->pos);
	this->rectObj.setPos(this->pos);
	this->textObj.setSize(this->size);
	this->rectObj.setSize(this->size);

	if(this->isFocused()){
		this->rectObj.setFillColor(Color(
								MIN(1.0, this->fillColor.r*1.3),
								MIN(1.0, this->fillColor.g*1.3),
								MIN(1.0, this->fillColor.b*1.3),
								this->fillColor.a
							));
	}else{
		this->rectObj.setFillColor(this->fillColor);
	}

	//simulate blanking cursor by appending '_' to the text sometimes.
	if( this->isFocused() && fmod(this->getScene()->getSec(), 0.5) > 0.25 )
		this->textObj.setText(this->text+'_');
	else
		this->textObj.setText(this->text);
}

void TextBox::onSceneAdded(){
	this->textObj.setScene(this->getScene());
	this->rectObj.setScene(this->getScene());
}

void TextBox::onSceneRemoved(){
	this->textObj.setScene(nullptr);
	this->rectObj.setScene(nullptr);
}

void TextBox::render() const{
	this->rectObj.render();
	this->textObj.render();
}

void TextBox::onKeyUp(char key){
	if(this->isFocused()){
		switch(key){
			case '\b':	if(this->text.size()>0){ this->text.pop_back(); }	break;
			case '\n':	this->getButton()->getAction()();					break;
			case '<':	/*TODO: unimplemented*/								break;
			case '>':	/*TODO: unimplemented*/								break;
			default:
				if( isprint(key) || key==' ' )
					this->text.push_back(key);
		}
	}
}
