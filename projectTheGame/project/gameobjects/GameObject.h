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
protected:
	std::map<EventType, std::function<bool(EventData)>> callbackList;
	Mat33 trans; //transformation
	Shape shape;

	std::vector<std::shared_ptr<GameObject>> children;
	GameObject* parent;

public:
	//event handling functions
	GameObject& on(EventType eventType, const std::function<bool(EventData)>& callback);
	GameObject& trigger(EventType eventType);
	GameObject& off(EventType eventType);

	//children manipulation functions
	GameObject& add(GameObject* child);
	GameObject& remove(GameObject* child);
	std::vector<std::shared_ptr<GameObject>>::iterator begin(GameObject* child);
	std::vector<std::shared_ptr<GameObject>>::iterator end(GameObject* child);


	//forwards to Shape
	virtual GameObject& render() const = 0;

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