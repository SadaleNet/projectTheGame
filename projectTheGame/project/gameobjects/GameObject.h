class GameObject;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../utils/Vec2.h"
#include "../utils/Color.h"
#include "../scenes/Scene.h"
#include "../misc/eventData.h"
#include <map>
#include <vector>
#include <memory>
#include <functional>
#include <cassert>

typedef std::vector<std::shared_ptr<GameObject>>::iterator GameObjectIt;
typedef std::vector<std::shared_ptr<GameObject>>::const_iterator GameObjectConstIt;

/**	@brief	An abstract class of all objects in game.<br>
			Defines basic properties like position, velocity and size.<br>
			Defines basic methods like even handling methods, render() and collision detection methods
	@note	Issue with this class: a) Assumes rectangular objects b) strongly coupled with Scene
*/
class GameObject{
private:
	//mouse states
	bool hovered, focused;
	bool held[MOUSE_KEY_NUM];
	GameObject* parent;

	
	/**	@brief	Decide whether hide the object or not:<br>
		<table>
		<tr><td>Parent</td>	<td>Chilren</td>	<td>Result</td></tr>
		<tr><td>true</td>	<td>true</td>		<td>both hidden</td></tr>
		<tr><td>true</td>	<td>false</td>		<td>both hidden</td></tr>
		<tr><td>false</td>	<td>true</td>		<td>hidden children, visible parent</td></tr>
		<tr><td>false</td>	<td>false</td>		<td>both visible</td></tr>
		</table>
		hidden object are not rendered and does NOT handle event, except update() and onStep().
		@note	To avoid confusion, this variable is private. Always use hide(), show() and isHidden() to access this variable.
	*/
	bool hidden;

	///the scene that this object is in
	Scene* scene;
	friend Scene;

public:
	Vec2 pos; ///position. If parent!=nullptr, then this is the relative position to the parent
	Vec2 vel; ///velocity. If parent!=nullptr, then this is the relative velocity to the parent
	Vec2 size;

	GameObject(Vec2 pos, Vec2 size);

	virtual void render() const{};

	bool isCollide(const GameObject& b) const;
	bool isCollide(const Vec2& p) const;

	/**********************
	**setters and getters**
	***********************/
	GameObject& setParent(GameObject* parent){ this->parent = parent; return *this; }
	GameObject& setScene(Scene* scene){ this->scene = scene; return *this; }

	/** getAbsPos, getAbsVel
		@return	position/velocity relative to the scene.
	*/
	Vec2 getAbsPos() const{ return (parent==nullptr?this->pos:(this->pos+parent->getAbsPos())); }
	Vec2 getAbsVel() const{ return (parent==nullptr?this->vel:(this->vel+parent->getAbsVel())); }
	const GameObject* getParent() const{ return this->parent; }

	const Scene* getScene() const{ return (parent==nullptr?this->scene:parent->getScene()); }
	Scene* getSceneVariable() const{ return (parent==nullptr?this->scene:parent->getSceneVariable()); }
	
	GameObject& hide(){ this->hidden = true; return *this; }
	GameObject& show(){ this->hidden = false; return *this; }
	bool isHidden() const{ return ((parent==nullptr||this->hidden)?this->hidden:parent->isHidden()); }

	void destroy();

	/**************************************************
	**event handllers, to be overridden by subclasses**
	**************************************************/
	virtual void onMouseMove(Vec2){} //triggered when mouse is moved, regardless of states
	virtual void onMouseDown(MouseButton, Vec2){} //triggered when mouse key is down AND the object is hovered
	virtual void onMouseUp(MouseButton, Vec2){} //triggered when ( the object is held AND ( mouse key is up OR the mouse leaves ) )
	virtual void onClick(MouseButton, Vec2){}  //triggered when ( the object is held AND mouse key is up )
	virtual void onMouseIn(Vec2){} //triggered when the object is just hovered
	virtual void onMouseOut(Vec2){} //triggered when the object is just unhovered
	/**	onKeyDown(char key), onKeyUp(char key)<br>
		@param key the key pressed in UPPER CASE. lower case keys are used to represent non-alphanumeric keys as shown in the table below:<br>
		<table>
		<tr><td>virtual key	</td>	<td>real key	</td></tr>
		<tr><td>	\\b		</td>	<td>backspace	</td></tr>
		<tr><td>	\\t		</td>	<td>tab			</td></tr>
		<tr><td>	\\n		</td>	<td>enter		</td></tr>
		<tr><td>	^		</td>	<td>up			</td></tr>
		<tr><td>	v		</td>	<td>down		</td></tr>
		<tr><td>	\<		</td>	<td>left		</td></tr>
		<tr><td>	\>		</td>	<td>right		</td></tr>
		</table>
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

	/********************************
	**mouse-related state functions**
	********************************/
	bool isHovered() const{ return this->hovered; }
	bool isHeld(MouseButton button) const{ return this->held[button]; }
	bool isFocused() const{ return this->focused; }
	
};

#endif