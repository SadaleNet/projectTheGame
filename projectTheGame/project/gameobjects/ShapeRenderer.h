class IShapeRenderer;
class ShapeRenderer;

#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include "Shape.h"

class IShapeRenderer{};
/**
	@brief Base class of shape renderers
			For example, a rectangle can be rendered as a bitmap or as lines.
			In that case, this class can be subclassed by LineRenderer and BitmapRenderer.
*/
class ShapeRenderer: private IShapeRenderer{
private:
	const Shape& shape;
public:
	ShapeRenderer(const Shape& shape);
	virtual ShapeRenderer& render() const = 0;
};

/**
	@brief Base class of shape renderers decorator.
			Examlpes of shape renderers decorator: BorderRenderer, ColorFilterRenderer
*/
class ShapeRendererDecorator: private IShapeRenderer{
	const IShapeRenderer& shapeRenderer;
	ShapeRendererDecorator(const IShapeRenderer& shapeRenderer);
	virtual ShapeRenderer& render() const = 0;
};

#endif