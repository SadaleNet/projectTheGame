#include "SceneRunner_Winapi.h"
#include "../project.h"
#include <stdexcept>
#include <iostream>

SceneRunner_Winapi::SceneRunner_Winapi(int fps):SceneRunner(fps),graphicsBuffer(nullptr){
	QueryPerformanceFrequency(&this->tickFreq);
	QueryPerformanceCounter(&this->startTick);
}


void SceneRunner_Winapi::run(){
	//TODO: make use of http://gameprogrammingpatterns.com/game-loop.html
	MSG msg;
	this->lastUpdateSec = this->getSec();
	double lastDisplayUpdateSec = this->getSec();
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

		//for getDeltaSec()
		this->lastUpdateSec = this->getSec();

		//update display(frame-limited)
		if( this->getSec()-lastDisplayUpdateSec > 1.0/this->getFps() ){
			lastDisplayUpdateSec = this->getSec();
			InvalidateRgn(hWnd, NULL, FALSE);
		}

		Sleep(1); //sleep for a millsecond to reduce the CPU load. Comment this line for smoother gameplay.
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
