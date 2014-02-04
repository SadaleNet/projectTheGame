class Shape;

#ifndef SHAPE_H
#define SHAPE_H

#include "../utils/Vec2.h"
#include "ShapeRenderer.h"
#include <vector>
#include <memory>

class Shape{
private:
	std::vector<Vec2> points;
	std::unique_ptr<ShapeRenderer> renderer;
protected:
	Shape& addPoint(const Vec2& p);
public:
	Shape& setRenderer(const ShapeRenderer&) const;

	bool isCollide(const Shape& b) const;
	bool isCollide(const Vec2& p) const;

	//forwards to renderer
	Shape& render() const;

	//forwards to points
	std::vector<Vec2>::const_iterator cbegin() const;
	std::vector<Vec2>::const_iterator cend() const;
};

#endif