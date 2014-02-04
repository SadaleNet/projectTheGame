#include "Scene.h"
#include <windows.h>

void Scene::handleEvents(){
	/*
		if(isMouseMoved()){
			EventData mouseMove = MouseData(mouse.getX(), mouse.getY());
			for(auto& it: gameObjects){
				it->trigger(MOUSE_MOVE, mouseMove);
			}
		}
	*/
	POINT tempMousePos;
	if (GetCursorPos(&tempMousePos)){
		ScreenToClient(hWnd, &tempMousePos);
		Vec2 mousePos;
		mousePos.x = tempMousePos.x;
		mousePos.y = tempMousePos.y;
		if( this->mousePos != mousePos ){
			this->mousePos = mousePos;
			/*for(auto& i: gameObjects){
				i.trigger(MOUSE_MOVE, mouseMove);
			}*/
			for( GameObjectIt it = gameObjects.begin(); it != gameObjects.end(); it++ ){
				MouseEvent me; me.button = NA; me.pos=this->mousePos;
				(*it)->trigger(MOUSE_MOVE, me);
			}
		}
	}
}