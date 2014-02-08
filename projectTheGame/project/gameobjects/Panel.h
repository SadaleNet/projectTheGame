class Panel;

#ifndef PANEL_H
#define PANEL_H

#include "GameObject.h"
#include "Rect.h"

/**	@brief	Panel -- used for grouping GameObjects
			The position and velocity of its children is relative to that of Panel.
*/
class Panel: public GameObject{
private:
	std::vector<std::shared_ptr<GameObject>> children;
protected:
	Rect rectObj;
public:
	Panel(Vec2 pos, Vec2 size, Color fillColor, double borderSize=3, Color borderColor=Color(0,0,0,1));

	//invoke children[each].update()
	virtual void render() const override;

	///set scene of children to current scene
	virtual void onSceneAdded() override;
	///set scene of children to current nullptr
	virtual void onSceneRemoved() override;

	//setters and getters
	Panel& setFillColor(Color fillColor){ rectObj.setFillColor(fillColor); return *this; }
	Panel& setBorderSize(double borderSize){ rectObj.setBorderSize(borderSize); return *this; }
	Panel& setBorderColor(Color borderColor){ rectObj.setBorderColor(borderColor); return *this; }
	
	Color getFillColor() const{ return rectObj.getFillColor(); }
	double getBorderSize() const{ return rectObj.getBorderSize(); }
	Color getBorderColor() const{ return rectObj.getBorderColor(); }

	//children manipulation functions

	Panel& add(GameObject* child);
	Panel& remove(GameObject* child);
	//forwards to children
	std::vector<std::shared_ptr<GameObject>>::iterator begin(GameObject* child);
	std::vector<std::shared_ptr<GameObject>>::iterator end(GameObject* child);
};

#endif