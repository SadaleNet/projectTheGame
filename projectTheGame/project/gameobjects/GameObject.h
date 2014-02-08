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

typedef std::vector<std::shared_ptr<GameObject>>::iterator GameObjectIt;
typedef std::vector<std::shared_ptr<GameObject>>::const_iterator GameObjectConstIt;

/// class GameObject - Problems: a) Assumes rectangular objects b) strongly coupled with Scene
class GameObject{
private:
	//mouse states
	bool hovered, focused;
	bool held[MOUSE_KEY_NUM];
	const GameObject* parent;

	//the scene that this object is in
	Scene* scene;
	friend Scene;

protected:
	Vec2 pos;
	Vec2 vel; //velocity
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
	GameObject& setParent(const GameObject* parent){ this->parent = parent; return *this; }
	GameObject& setScene(Scene* scene){ this->scene = scene; return *this; }
	
	Vec2 getPos() const{ return this->pos; }
	Vec2 getVel() const{ return this->vel; }
	//absolution pos/vel : position/velocity that considers the position of the parent.
	Vec2 getAbsPos() const{ return (parent==nullptr?this->pos:(this->pos+parent->getAbsPos())); }
	Vec2 getAbsVel() const{ return (parent==nullptr?this->vel:(this->vel+parent->getAbsVel())); }
	Vec2 getSize() const{ return this->size; }
	const GameObject* getParent() const{ return this->parent; }

	const Scene* getScene() const{ return (parent==nullptr?this->scene:parent->getScene()); }
	Scene* getSceneVariable() const{ return (parent==nullptr?this->scene:parent->getSceneVariable()); }

	//event handllers, to be overridden by subclasses.
	virtual void onMouseMove(Vec2){} //triggered when mouse is moved, regardless of states
	virtual void onMouseDown(MouseButton, Vec2){} //triggered when mouse key is down AND the object is hovered
	virtual void onMouseUp(MouseButton, Vec2){} //triggered when ( the object is held AND ( mouse key is up OR the mouse leaves ) )
	virtual void onClick(MouseButton, Vec2){}  //triggered when ( the object is held AND mouse key is up )
	virtual void onMouseIn(Vec2){} //triggered when the object is just hovered
	virtual void onMouseOut(Vec2){} //triggered when the object is just unhovered
	/**	onKeyDown(char key), onKeyUp(char key)
		Note: char key is the key pressed in UPPER CASE. lower case keys are used to represent non-alphanumeric keys as shown in the table below:
		virtual key		real key
		\b				backspace
		\t				tab
		\n				enter
		^				up
		v				down
		<				left
		>				right
	*/
	virtual void onKeyDown(char key){} //triggered when a keyboard key is pressed, regardless of states
	virtual void onKeyUp(char key){} //triggered when a keyboard key is released, regardless of states
	virtual void onFocus(){} //triggered when the object is clicked
	virtual void onBlur(){} //triggered when mouse is clicked and is not on the object.
	virtual void onCollide(const GameObject&){} //triggered when this object collides with another object.

	virtual void onStep(){} //triggered by GameObject::update(), to be overridden by the client
	virtual void onSceneAdded(){} //triggered by Scene::add()
	virtual void onSceneRemoved(){} //triggered by Scene::remove()

	virtual void updateHook(){} //triggered by GameObject::update(), to be overridden by the library
	void update(); //triggered by SceneRunner::run, NOT overridable.

	//mouse-related state functions
	bool isHovered() const{ return this->hovered; }
	bool isHeld(MouseButton button) const{ return this->held[button]; }
	bool isFocused() const{ return this->focused; }
	
};

#endif