class CheckBox;

#ifndef CHECK_BOX_H
#define CHECK_BOX_H

#include "GameObject.h"
#include "Button.h"
#include "Text.h"
#include <string>

/** @brief	A class for a check box
@note
CheckBox has a Button and Text<br>
The following variables are automatically calculated/are fixed, and cannot be changed:<br>
<table>
<tr><td>Text::align		</td><td>LEFT	</td></tr>
<tr><td>Text::fontSize	</td><td>80% of height	</td></tr>
</table>
*/
class CheckBox: public GameObject{
private:
	static const int PADDING = 5;
protected:
	Button buttonObj;
	Text textObj;
public:
	Color fillColor; ///used to calculate buttonObj.fillColor when this object is hovered, clicked, etc.
	bool checked; ///whether the checkbox is checked
	Color& fontColor; ///refers to textObj
	std::string& text; ///label of the textObj
	double& borderSize; ///refers to buttonObj
	Color& borderColor; ///refers to buttonObj

	CheckBox(Vec2 pos, Vec2 size, std::string text, Color fontColor, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	virtual void render() const override;

	///change color if focused
	virtual void updateHook() override;

	virtual void onClick(MouseButton button, Vec2);
};

#endif