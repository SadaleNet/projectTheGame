class TextBox;

#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "GameObject.h"
#include "Button.h"
#include "Rect.h"
#include "Text.h"
#include <string>

/** @brief	A class for a textbox
@note
TextBox has a Rect and Text<br>
The following variables are automatically calculated/are fixed, and cannot be changed:<br>
<table>
<tr><td>Variable		</td><td>Value	</td></tr>
<tr><td>Text::align		</td><td>LEFT	</td></tr>
<tr><td>Text::fontSize	</td><td>80% of height	</td></tr>
</table>
*/
class TextBox: public GameObject{
protected:
	Text textObj;
	Rect rectObj;
public:
	Button* button; ///button->action() is executed when enter is pressed while this textbox is focused.
	Color fillColor; ///used to calculate rectObj.fillColor when this object is hovered, clicked, etc.
	std::string text; ///text inside the textbox
	bool secret; ///If true, each character in the textbox would be shown as asterisk(*)
	Color& fontColor; ///refers to textObj
	double& borderSize; ///refers to rectObj
	Color& borderColor; ///refers to rectObj

	TextBox(Vec2 pos, Vec2 size, Color fontColor, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	virtual void render() const override;

	///change color if focused; simuilate blank cursor
	virtual void updateHook() override;
	///change the content of the textbox
	virtual void onKeyUp(char key) override;

};

#endif