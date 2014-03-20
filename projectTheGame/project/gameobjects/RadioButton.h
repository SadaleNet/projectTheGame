class RadioBox;

#ifndef RADIO_BOX_H
#define RADIO_BOX_H

#include "GameObject.h"
#include "CheckBox.h"
#include <string>

/** @brief	A class for a radio button
@note
RadioButton is a subclass of Checkbox<br>
The difference is that clicking on RadioButton always selects it and deselects all other radio buttons in the same panel.
@see CheckBox
*/
class RadioButton: public CheckBox{
public:
	RadioButton(Vec2 pos, Vec2 size, std::string text, Color fontColor, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	virtual void onClick(MouseButton button, Vec2);
};

#endif