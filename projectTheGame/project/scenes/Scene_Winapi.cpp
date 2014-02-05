#include "Scene.h"
#include "../project.h"
#include <windows.h>

#define EACH_GAME_OBJECT(_identifier) \
	GameObjectIt it = gameObjects.begin();\
	for( ; it != gameObjects.end(); it++ ){\
		GameObject* _identifier = (*it).get();

#define END_EACH }


void Scene::handleEvents(){
	POINT tempMousePos;
	if (GetCursorPos(&tempMousePos)){
		ScreenToClient(hWnd, &tempMousePos);
		Vec2 mousePos;
		mousePos.x = tempMousePos.x;
		mousePos.y = tempMousePos.y;
		if( this->mousePos != mousePos ){
			this->mousePos = mousePos;
			EACH_GAME_OBJECT(i)
				MouseEvent me; me.button = NA; me.pos=this->mousePos;
				i->trigger(MOUSE_MOVE, me);
			END_EACH
		}
	}

	handleExtraEvents();
}

void Scene::render(){
	EACH_GAME_OBJECT(i)
		i->render();
	END_EACH
}