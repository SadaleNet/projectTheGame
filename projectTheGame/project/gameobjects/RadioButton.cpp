#include "RadioButton.h"
#include "Panel.h"

RadioButton::RadioButton(Vec2 pos, Vec2 size, std::string text, Color fontColor, Color fillColor, double borderSize, Color borderColor)
	:CheckBox(pos, size, text, fontColor, fillColor, borderSize, borderColor){
}

void RadioButton::onClick(MouseButton button, Vec2){
	if(button==::LEFT){
		const Panel* panel = dynamic_cast<const Panel*>(this->getParent());
		if(panel!=nullptr){
			for(std::vector<GameObject*>::const_iterator it=panel->begin(); it!=panel->end(); it++){
				RadioButton* radioButton = dynamic_cast<RadioButton*>(*it);
				if(radioButton==nullptr)
					continue;
				radioButton->checked = false;
			}
		}
		this->checked = true;
	}
}
