class GameObject;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../utils/Mat33.h"
#include "../utils/Vec2.h"
#include "../scenes/eventData.h"
#include "../scenes/Scene.h"
#include <map>
#include <vector>
#include <memory>
#include <functional>

/// class GameObject - Problems: a) Assumes rectangular objects b) strongly coupled with Scene
class GameObject{
private:
	std::vector<std::shared_ptr<GameObject>> children;
	//GameObject* parent; //TODO: unimplemented
	Scene* scene;
	friend Scene;

protected:
	Vec2 pos;
	Vec2 vel;
	Vec2 size;

	const Scene* getScene() const{ return this->scene; }

public:
	GameObject(Vec2 pos, Vec2 size);

	virtual void onStep(){}
	virtual void onMouseMove(Vec2){}
	virtual void onMouseDown(MouseButton, Vec2){}
	virtual void onMouseUp(MouseButton, Vec2){}
	virtual void onKeyDown(char key){}
	virtual void onKeyUp(char key){}
	virtual void onClick(MouseButton, Vec2){}
	virtual void onFocus(){}
	virtual void onBlur(){}
	virtual void update();
	virtual void render() const = 0;

	bool isCollide(const GameObject& b) const;
	bool isCollide(const Vec2& p) const;

	//setters and getters
	GameObject& setPos(const Vec2& pos){ this->pos = pos; return *this; }
	GameObject& setVel(const Vec2& vel){ this->vel = vel; return *this; }
	GameObject& addVel(const Vec2& vel){ this->vel += vel; return *this; }
	GameObject& setSize(const Vec2& size){ this->size = size; return *this; }

	Vec2 getPos() const{ return this->pos; }
	Vec2 getVel() const{ return this->vel; }
	Vec2 getSize() const{ return this->size; }

	//children manipulation functions, TODO: unimplemented.
	/*GameObject& add(GameObject* child);
	GameObject& remove(GameObject* child);
	std::vector<std::shared_ptr<GameObject>>::iterator begin(GameObject* child);
	std::vector<std::shared_ptr<GameObject>>::iterator end(GameObject* child);*/
	
};

#endif