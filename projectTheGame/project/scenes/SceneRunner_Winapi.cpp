#include "SceneRunner_Winapi.h"
#include "../project.h"
#include <stdexcept>
#include <iostream>
#include <stdlib.h>

SceneRunner_Winapi::SceneRunner_Winapi(int fps):
	SceneRunner(fps),
	graphicsBuffer(nullptr){
		QueryPerformanceFrequency(&this->tickFreq);
		QueryPerformanceCounter(&this->startTick);
}


void SceneRunner_Winapi::run(){
	MSG msg;
	double lastDisplayUpdateSec = this->getSec();
	while(!this->getTerminated()){
		//If the scene is changed, re-initialize stuffs.
		if(this->newScene!=nullptr){
			this->scene = this->newScene;
			this->newScene = nullptr;
			this->lastUpdateSec = this->getSec();
		}

		//handle system events.
		while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)!=0){
			if(GetMessage(&msg, NULL, 0, 0)==-1)
				throw std::runtime_error("Fatal error: fail to GetMessage() :'(");
			if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		//for getDeltaSec(). This is to ensure that event handlers of GameObject to receive getDeltaSec() uniformly in a frame.
		this->secondsSpentOnPreviousFrame = this->getSec()-this->lastUpdateSec;
		this->handleEvents();
		this->updateScene();
		if(rand()%10==0)
			std::cout <<"fps:" << (1/this->secondsSpentOnPreviousFrame) <<std::endl;

		//for getDeltaSec() of the next frame.
		this->lastUpdateSec += this->secondsSpentOnPreviousFrame;

		//update display(frame-limited)
		if( this->getSec()-lastDisplayUpdateSec > 1.0/this->getFps() ){
			lastDisplayUpdateSec = this->getSec();
			InvalidateRgn(hWnd, NULL, FALSE);
		}

		//Sleep(1); //sleep for a millsecond to reduce the CPU load. Comment out this line for smoother gameplay.
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
	graphicsBuffer.Clear(Gdiplus::Color(255, 255, 255, 255));
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
	return this->secondsSpentOnPreviousFrame;
}
