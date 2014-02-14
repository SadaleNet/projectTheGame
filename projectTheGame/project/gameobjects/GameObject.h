class GameObject;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../utils/Mat33.h"
#include "../utils/Vec2.h"
#include "../utils/Color.h"
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
	GameObject* parent;

	//Parent	Chilren		Result
	//true		true		both hidden
	//true		false		both hidden
	//false		true		hidden children, visible parent.
	//false		false		both visible
	//hidden object are not rendered and does NOT handle event, except update() and onStep().
	bool hidden;

	//the scene that this object is in
	Scene* scene;
	friend Scene;

protected:

public:
	Vec2 pos;
	Vec2 vel; //velocity
	Vec2 size;

	GameObject(Vec2 pos, Vec2 size);

	virtual void render() const = 0;

	bool isCollide(const GameObject& b) const;
	bool isCollide(const Vec2& p) const;

	//setters and getters
	GameObject& setParent(GameObject* parent){ this->parent = parent; return *this; }
	GameObject& setScene(Scene* scene){ this->scene = scene; return *this; }

	//absolution pos/vel : position/velocity that considers the position of the parent.
	Vec2 getAbsPos() const{ return (parent==nullptr?this->pos:(this->pos+parent->getAbsPos())); }
	Vec2 getAbsVel() const{ return (parent==nullptr?this->vel:(this->vel+parent->getAbsVel())); }
	const GameObject* getParent() const{ return this->parent; }

	const Scene* getScene() const{ return (parent==nullptr?this->scene:parent->getScene()); }
	Scene* getSceneVariable() const{ return (parent==nullptr?this->scene:parent->getSceneVariable()); }
	
	GameObject& hide(){ this->hidden = true; return *this; }
	GameObject& show(){ this->hidden = false; return *this; }
	bool isHidden() const{ return ((parent==nullptr||this->hidden)?this->hidden:parent->isHidden()); }

	void destroy();

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