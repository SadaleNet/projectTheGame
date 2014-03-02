class Panel;

#ifndef PANEL_H
#define PANEL_H

#include "GameObject.h"
#include "Rect.h"

/**	@brief	A class for grouping GameObjects<br>
			The position and velocity of its children is relative to that of Panel.<br>
			Can optionally have a border and background color for the Panel.
*/
class Panel: public GameObject{
private:
	std::vector<GameObject*> children;
protected:
	Rect rectObj; ///for border and background color
public:
	Color& fillColor; ///refers to rectObj.fillColor
	double& borderSize; ///refers to rectObj.borderSize
	Color& borderColor; ///refers to rectObj.borderColor

	/**
	*/
	Panel(Vec2 pos, Vec2 size, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	///invoke children[each].update()
	virtual void render() const override;

	///set scene of children to current scene
	virtual void onSceneAdded() override;
	///set scene of children to current nullptr
	virtual void onSceneRemoved() override;

	///append a child to children list
	Panel& add(GameObject* child);
	///remove a child from children list
	Panel& remove(GameObject* child);

	///@return begin iterator of children
	std::vector<GameObject*>::iterator begin();
	///@return end iterator of children
	std::vector<GameObject*>::iterator end();
};

#endif