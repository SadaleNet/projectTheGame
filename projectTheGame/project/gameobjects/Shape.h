class Shape;

#ifndef SHAPE_H
#define SHAPE_H

#include "../utils/Vec2.h"
#include "ShapeRenderer.h"
#include "GameObject.h"
#include <vector>
#include <memory>

class Shape{
private:
	GameObject* owner;
public:
	virtual bool isCollide(const GameObject& b) const = 0;
	virtual bool isCollide(const Vec2& p) const = 0;

};

class Polygon: public Shape{
private:
	std::vector<Vec2> points;
protected:
	Polygon& addPoint(const Vec2& p);
public:
	virtual bool isCollide(const GameObject& b) const;
	virtual bool isCollide(const Vec2& p) const;

	//forwards to points
	std::vector<Vec2>::iterator begin();
	std::vector<Vec2>::iterator end();
};

/* TODO: unimplemented.
class Circle: public Shape{
private:
	double radius;
protected:
	Circle& setRadius(const Vec2& p);
public:
	virtual bool isCollide(const GameObject& b) const final;
	virtual bool isCollide(const Vec2& p) const final;
};*/

#endif