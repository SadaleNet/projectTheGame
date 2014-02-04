#include "SceneRunner_Winapi.h"
#include "../project.h"
#include <stdexcept>
#include <iostream>

SceneRunner_Winapi::SceneRunner_Winapi(Scene* scene, int fps):SceneRunner(scene,fps){
	QueryPerformanceFrequency(&this->tickFreq);
	QueryPerformanceCounter(&this->startTick);
}


void SceneRunner_Winapi::run(){
	//TODO: make use of http://gameprogrammingpatterns.com/game-loop.html
	MSG msg;
	while(!this->getTerminated()){
		while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)!=0){
			if(GetMessage(&msg, NULL, 0, 0)==-1)
				throw std::runtime_error("Fatal error: fail to GetMessage() :'(");
			if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		this->getScene()->handleEvents();
		//wait a while
		Sleep(static_cast<DWORD>(1000.0/this->getFps()));
		//update display
		InvalidateRgn(hWnd, NULL, FALSE);
	}
	/// Runs Scene methods repeatively until teminate() is called by the scene.
}

#include <objidl.h>
#include <gdiplus.h>
#include <string>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
void SceneRunner_Winapi::render(){
	this->getScene()->render();
}

/*Getter method(s)*/
double SceneRunner_Winapi::getSec() const{
	LARGE_INTEGER currentTick;
	QueryPerformanceCounter(&currentTick);
	return static_cast<double>(currentTick.QuadPart-this->startTick.QuadPart)/this->tickFreq.QuadPart;
}
