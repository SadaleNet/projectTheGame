class GameObject;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../utils/Mat33.h"
#include "../utils/Vec2.h"
#include "../scenes/eventData.h"
#include "Shape.h"
#include "ShapeRenderer.h"
#include <map>
#include <vector>
#include <memory>
#include <functional>

/// class GameObject - Problems: a) Assumes rectangular objects b) strongly coupled with Scene
class GameObject{
private:
	//callback: return true to propagate to parent(default), false else.
	std::map<EventType, std::function<bool(EventData)>> callbackList;
	std::vector<std::shared_ptr<GameObject>> children;
	GameObject* parent;
	std::shared_ptr<ShapeRenderer> renderer;

protected:
	Mat33 trans; //local transformation
	Mat33 gTrans; //global transformation
	std::shared_ptr<Shape> shape;

public:
	GameObject();
	GameObject& setShape(Shape* shape);
	GameObject& setRenderer(ShapeRenderer* renderer);

	//event handling functions. TODO: If this framework scales, move event handling stuffs to else where?
	GameObject& on(EventType eventType, const std::function<bool(EventData)>& callback);
	GameObject& trigger(EventType eventType, EventData eventData);
	GameObject& off(EventType eventType);

	void update();
	void render() const;

	//children manipulation functions, TODO: unimplemented.
	GameObject& add(GameObject* child);
	GameObject& remove(GameObject* child);
	std::vector<std::shared_ptr<GameObject>>::iterator begin(GameObject* child);
	std::vector<std::shared_ptr<GameObject>>::iterator end(GameObject* child);


	//forwards to Shape
	bool isCollide(const Shape& b) const;
	bool isCollide(const Vec2& p) const;

	//getters
	const Mat33& getTrans() const;
	const Mat33& getGTrans() const;

	/*
	GameObject setPos (setPos pos);
	GameObject setSize (Vec2 size);
	GameObject setScale (double scale);
	GameObject setRot (double rot);
	Vec2 getPos () const;
	Vec2 getSize () const;
	double getScale () const;
	double getRot () const;
	bool isCollide (GameObject other);
	bool isCollide (Vec2 other);
	virtual GameObject render () const = 0;
	*/
};

#endif