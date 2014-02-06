#ifndef RECT_H
#define RECT_H
#include "GameObject.h"
#include "../utils/Color.h"

class Rect: public GameObject{
protected:
	Color fillColor;
	double borderSize;
	Color borderColor;
public:
	Rect(Vec2 pos, Vec2 size, Color fillColor, double borderSize=0.0, Color borderColor=Color(0,0,0,0));
	virtual void render() const;
};

#endif