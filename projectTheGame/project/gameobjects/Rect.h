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
	virtual void render() const override;

	//setters and getters
	Rect& setFillColor(Color fillColor){ this->fillColor = fillColor; return *this; }
	Rect& setBorderSize(double borderSize){ this->borderSize = borderSize; return *this; }
	Rect& setBorderColor(Color borderColor){ this->borderColor = borderColor; return *this; }

	Color getFillColor() const{ return fillColor; }
	double getBorderSize() const{ return borderSize; }
	Color getBorderColor() const{ return borderColor; }
};

#endif