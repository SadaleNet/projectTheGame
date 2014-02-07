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
#include <cassert>

/// class GameObject - Problems: a) Assumes rectangular objects b) strongly coupled with Scene
class GameObject{
private:
	std::vector<std::shared_ptr<GameObject>> children;
	//GameObject* parent; //TODO: move it to Panel
	//mouse states
	bool hovered, focused;
	bool held[MOUSE_KEY_NUM];
	Scene* scene;
	friend Scene;

protected:
	Vec2 pos;
	Vec2 vel;
	Vec2 size;

public:
	GameObject(Vec2 pos, Vec2 size);

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

	const Scene* getScene() const{ return this->scene; }
	Scene* getScene(){ return this->scene; }
	void setScene(Scene* scene){ this->scene = scene; }

	//event handllers
	virtual void onMouseMove(Vec2){} //triggered when mouse is moved, regardless of states
	virtual void onMouseDown(MouseButton, Vec2){} //triggered when mouse key is down AND the object is hovered
	virtual void onMouseUp(MouseButton, Vec2){} //triggered when ( the object is held AND ( mouse key is up OR the mouse leaves ) )
	virtual void onClick(MouseButton, Vec2){}  //triggered when ( the object is held AND mouse key is up )
	virtual void onMouseIn(Vec2){} //triggered when the object is just hovered
	virtual void onMouseOut(Vec2){} //triggered when the object is just unhovered
	virtual void onKeyDown(char key){} //triggered when a keyboard key is pressed, regardless of states
	virtual void onKeyUp(char key){} //triggered when a keyboard key is released, regardless of states
	virtual void onFocus(){}
	virtual void onBlur(){}
	virtual void update();

	virtual void onStep(){} //triggered by GameObject::update()
	virtual void onSceneAdded(){} //triggered by Scene::add()
	virtual void onSceneRemoved(){} //triggered by Scene::remove()

	//mouse-related state functions
	bool isHovered() const{ return this->hovered; }
	bool isHeld(MouseButton button) const{ return this->held[button]; }
	bool isFocused() const{ return this->focused; }

	//children manipulation functions, TODO: move them to Panel
	/*GameObject& add(GameObject* child);
	GameObject& remove(GameObject* child);
	std::vector<std::shared_ptr<GameObject>>::iterator begin(GameObject* child);
	std::vector<std::shared_ptr<GameObject>>::iterator end(GameObject* child);*/
	
};

#endif