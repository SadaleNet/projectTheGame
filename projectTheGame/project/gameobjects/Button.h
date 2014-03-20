class Button;

#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"
#include "Rect.h"
#include "Text.h"

/**	@brief	A class for a clickable button. Optioanally with function executed on LMB clicked.

@note
Button has a Rect and Text<br>
The following variables are automatically calculated/are fixed, and cannot be changed:<br>
<table>
<tr><td>Variable		</td><td>Value	</td></tr>
<tr><td>Text::align		</td><td>CENTER	</td></tr>
<tr><td>Text::fontSize	</td><td>80% of height	</td></tr>
<tr><td>hover fillColor	</td><td>130% brightness of original fillColor</td></tr>
<tr><td>press fillColor	</td><td>70% brightness of original	fillColor</td></tr>
</table>
*/
class Button: public GameObject{
protected:
	Text textObj;
	Rect rectObj;
public:
	Color fillColor; ///used to calculate rectObj.fillColor when this object is hovered, clicked, etc.
	Color& fontColor; ///refers to textObj.fontColor
	std::string& text; ///refers to textObj.text
	double& borderSize; ///refers to rectObj.borderSize
	Color& borderColor; ///refers to rectObj.borderColor

	std::function<void()> action; ///action() is executed when the button is clicked.

	Button(Vec2 pos, Vec2 size, std::string text, Color fontColor, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	virtual void render() const override;

	///changes the color according to the states(hover, held)
	virtual void updateHook() override;
	///Execute action() if the button is clicked by left mouse button
	virtual void onClick(MouseButton button, Vec2) override;
};

#endif