#include "SceneRunner_Winapi.h"
#include "../project.h"
#include <stdexcept>
#include <iostream>

SceneRunner_Winapi::SceneRunner_Winapi(int fps):SceneRunner(fps),graphicsBuffer(nullptr){
	QueryPerformanceFrequency(&this->tickFreq);
	QueryPerformanceCounter(&this->startTick);
	lastUpdateSec = 0.0;
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
		this->handleEvents();
		this->updateScene();
		//wait a while
		Sleep(static_cast<DWORD>(1000.0/this->getFps()));

		//for getDeltaSec()
		lastUpdateSec = this->getSec();
		//update display
		InvalidateRgn(hWnd, NULL, FALSE);
	}
	/// Runs Scene methods repeatively until teminate() is called by the scene.
}

void SceneRunner_Winapi::render(){
	//initialize double buffering
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	Bitmap buffer(clientRect.right, clientRect.bottom);
	Graphics graphicsBuffer(&buffer);
	this->graphicsBuffer = &graphicsBuffer;

	//second buffer ready. Clear the buffer and let the scene draw something on it.
	graphicsBuffer.Clear(Color(255, 255, 255, 255));
	this->renderScene();

	//copy stuff from the new buffer to the old one
	Graphics graphics(hdc);
	graphics.DrawImage(&buffer, 0, 0);
}

/*Getter method(s)*/
double SceneRunner_Winapi::getSec() const{
	LARGE_INTEGER currentTick;
	QueryPerformanceCounter(&currentTick);
	return static_cast<double>(currentTick.QuadPart-this->startTick.QuadPart)/this->tickFreq.QuadPart;
}
double SceneRunner_Winapi::getDeltaSec() const{
	return this->getSec()-this->lastUpdateSec;
}
