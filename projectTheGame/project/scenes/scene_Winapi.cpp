#include "Scene.h"
#include "../project.h"
#include <windows.h>

#include <ctype.h>

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

	//invoke GameObject::onMouseMove()
	if( this->mousePos != oldMousePos ){
		EACH_GAME_OBJECT(i)
			i->onMouseMove(this->mousePos);
		END_EACH
	}

	//invoke GameObject::onMouseIn(), GameObject::onMouseOut(), GameObject::onMouseUp()
	EACH_GAME_OBJECT(i)
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

	//invoke GameObject::held, GameObject::onMouseDown(), GameObject::onMouseUp()
	#define PROCESS_MOUSE_UP_DOWN(_winapiKey, _mouseButtonKey) \
	if(keyStates[_winapiKey]!=oldKeyStates[_winapiKey]){\
		EACH_GAME_OBJECT(i)\
			if(i->isCollide(this->mousePos)){\
				if(i->hovered){\
					if(keyStates[_winapiKey]){\
						i->held[_mouseButtonKey] = true;\
						i->onMouseDown(_mouseButtonKey, this->mousePos);\
					}else{\
						i->held[_mouseButtonKey] = false;\
						i->onMouseUp(_mouseButtonKey, this->mousePos);\
						i->onClick(_mouseButtonKey, this->mousePos);\
						EACH_GAME_OBJECT(j)\
							if(i->focused){\
								i->onBlur();\
								i->focused = false;\
							}\
						END_EACH\
						i->focused = true;\
						i->onFocus();\
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

	//invoke GameObject::onKeyDown(), GameObject::onKeyUp()
	
	for(unsigned char key=0x00; key<0xFF; key++){
		if( isdigit(key) || isupper(key) ){
			EACH_GAME_OBJECT(i)
				if(keyStates[key]!=oldKeyStates[key]){
					if(keyStates[key])
						i->onKeyDown(key);
					else
						i->onKeyUp(key);
				}
			END_EACH
		}
	}

	this->handleExtraEvents();
}