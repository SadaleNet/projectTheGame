#include "Scene.h"
#include "../project.h"
#include <windows.h>

#include <ctype.h>
#include <algorithm>

namespace{
	//Includes mouse key states and keyboard key states
	//0 means off/released, 1 means on/pressed
	//Relies on GetKeyState() Ref: http://msdn.microsoft.com/en-us/library/ms646301%28VS.85%29.aspx
	bool keyStates[0xFF];
}

void Scene::handleEvents(){
	//store old values
	Vec2 oldMousePos = this->mousePos;
	bool oldKeyStates[0xFF];
	for(int i=0;i<0xFF; i++)
		oldKeyStates[i] = keyStates[i];

	//fetch new values
	//fetch new mouse pos
	POINT newMousePos;
	if (GetCursorPos(&newMousePos)){
		ScreenToClient(hWnd, &newMousePos);
		this->mousePos.x = newMousePos.x;
		this->mousePos.y = newMousePos.y;
	}
	//fetch new key states
	for(int i=0;i<0xFF; i++)
		keyStates[i] = !!(GetKeyState(i)&0xF0);

	//find changes and trigger events

	{ //process mouse events

		//Initialize a clone of gameObject for processing mouse events
		std::vector<std::shared_ptr<GameObject>> gameObjectClone = this->gameObjects;
		//remove all objects without mouse event handling disbled.
		gameObjectClone.erase(
			std::remove_if(gameObjectClone.begin(), gameObjectClone.end(),
				[](std::shared_ptr<GameObject>& a){ return !a->detectMouseEvents; }
			), gameObjectClone.end()
		);

		//invoke GameObject::onMouseMove()
		if( this->mousePos != oldMousePos ){
			EACH_GAME_OBJECT_USE_CLONE(i, gameObjectClone)
				i->onMouseMove(this->mousePos);
			END_EACH
		}

		//invoke GameObject::onMouseIn(), GameObject::onMouseOut(), GameObject::onMouseUp()
		EACH_GAME_OBJECT_USE_CLONE(i, gameObjectClone)
			if(!i->hovered&&i->isCollide(this->mousePos)){
				i->hovered = true;
				i->onMouseIn(this->mousePos);
			}else if(i->hovered&&!i->isCollide(this->mousePos)){
				i->hovered = false;
				i->onMouseOut(this->mousePos);
				for(int mouseButton=0; mouseButton<MOUSE_KEY_NUM; mouseButton++){
					if(i->held[mouseButton]){
						i->held[mouseButton] = false;
						i->onMouseUp((MouseButton)mouseButton, this->mousePos);
					}
				}
			}
		END_EACH

		//invoke GameObject::held, GameObject::onMouseDown(), GameObject::onMouseUp(), GameObject::onFocus(), GameObject::onBlur()
		#define PROCESS_MOUSE_UP_DOWN(_winapiKey, _mouseButtonKey) \
		if(keyStates[_winapiKey]!=oldKeyStates[_winapiKey]){\
			EACH_GAME_OBJECT_USE_CLONE(i, gameObjectClone)\
				if(!keyStates[_winapiKey]&&_mouseButtonKey==::LEFT){\
					EACH_GAME_OBJECT_USE_CLONE(j, gameObjectClone)\
						if(j->focused && !j->isCollide(this->mousePos)){\
							j->onBlur();\
							j->focused = false;\
						}\
					END_EACH\
				}\
				if(i->isCollide(this->mousePos)){\
					if(i->hovered){\
						if(keyStates[_winapiKey]){\
							i->held[_mouseButtonKey] = true;\
							i->onMouseDown(_mouseButtonKey, this->mousePos);\
						}else{\
							i->held[_mouseButtonKey] = false;\
							i->onMouseUp(_mouseButtonKey, this->mousePos);\
							i->onClick(_mouseButtonKey, this->mousePos);\
							if(_mouseButtonKey==::LEFT){\
								i->focused = true;\
								i->onFocus();\
							}\
						}\
					}\
				}\
			END_EACH\
		}
		PROCESS_MOUSE_UP_DOWN(VK_LBUTTON, LEFT);
		PROCESS_MOUSE_UP_DOWN(VK_RBUTTON, RIGHT);
		PROCESS_MOUSE_UP_DOWN(VK_MBUTTON, MIDDLE);
		//TODO: unimplemented. seems that winapi handle these mouse buttons in a different way.
		//PROCESS_MOUSE_UP_DOWN(???, SCROLL_UP);
		//PROCESS_MOUSE_UP_DOWN(???, SCROLL_DOWN);
	} //end processing mouse events

	{ //process keyboard events
		
		//Initialize a clone of gameObject for processing keyboard events
		std::vector<std::shared_ptr<GameObject>> gameObjectClone = this->gameObjects;
		//remove all objects without mouse event handling disbled.
		gameObjectClone.erase(
			std::remove_if(gameObjectClone.begin(), gameObjectClone.end(),
				[](std::shared_ptr<GameObject>& a){ return !a->detectKeyEvents; }
			), gameObjectClone.end()
		);

		//invoke GameObject::onKeyDown(), GameObject::onKeyUp()
		#define PROCESS_KEY_EVENT(_winapiKey, _oursKey)\
			{\
			EACH_GAME_OBJECT_USE_CLONE(i, gameObjectClone)\
				if(keyStates[_winapiKey]!=oldKeyStates[_winapiKey]){\
					if(keyStates[_winapiKey])\
						i->onKeyDown(_oursKey);\
					else\
						i->onKeyUp(_oursKey);\
				}\
			END_EACH\
			}

		//winapi virtual key table: http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
		for(unsigned char key=0x00; key<0xFF; key++){
			if( isdigit(key) || isupper(key) || key=='\t' || key=='\b' || key==' ' ){
				PROCESS_KEY_EVENT(key, key);
			}
		}
		PROCESS_KEY_EVENT(VK_RETURN, '\n');
		PROCESS_KEY_EVENT(VK_LEFT, '<');
		PROCESS_KEY_EVENT(VK_RIGHT, '>');
		PROCESS_KEY_EVENT(VK_UP, '^');
		PROCESS_KEY_EVENT(VK_DOWN, 'v');
		PROCESS_KEY_EVENT(VK_OEM_1, ';');
		PROCESS_KEY_EVENT(VK_OEM_PLUS, '=');
		PROCESS_KEY_EVENT(VK_OEM_COMMA, ',');
		PROCESS_KEY_EVENT(VK_OEM_MINUS, '-');
		PROCESS_KEY_EVENT(VK_OEM_PERIOD, '.');
		PROCESS_KEY_EVENT(VK_OEM_2, '/');
		PROCESS_KEY_EVENT(VK_OEM_3, '`');
		PROCESS_KEY_EVENT(VK_OEM_4, '[');
		PROCESS_KEY_EVENT(VK_OEM_5, '\\');
		PROCESS_KEY_EVENT(VK_OEM_6, ']');
		PROCESS_KEY_EVENT(VK_OEM_7, '\'');
		PROCESS_KEY_EVENT(VK_NUMPAD0, '0');
		PROCESS_KEY_EVENT(VK_NUMPAD1, '1');
		PROCESS_KEY_EVENT(VK_NUMPAD2, '2');
		PROCESS_KEY_EVENT(VK_NUMPAD3, '3');
		PROCESS_KEY_EVENT(VK_NUMPAD4, '4');
		PROCESS_KEY_EVENT(VK_NUMPAD5, '5');
		PROCESS_KEY_EVENT(VK_NUMPAD6, '6');
		PROCESS_KEY_EVENT(VK_NUMPAD7, '7');
		PROCESS_KEY_EVENT(VK_NUMPAD8, '8');
		PROCESS_KEY_EVENT(VK_NUMPAD9, '9');
	} //end processing keyboard events

	//invoke collision events
	for( GameObjectIt it = gameObjects.begin(); it != gameObjects.end(); it++ ){
		GameObject* i = it->get();
		if(!i->detectCollisionEvents)
			continue;
		for( GameObjectIt jt = it+1; jt != gameObjects.end(); jt++ ){
			GameObject* j = jt->get();
			if(i->isCollide(*j)){
				i->onCollide(*j);
				j->onCollide(*i);
			}
		}
	}

	this->handleExtraEvents();
}