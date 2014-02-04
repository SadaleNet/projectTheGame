#include "TestScene.h"
#include "../project.h"
#include <objidl.h>
#include <gdiplus.h>
#include <string>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

TestScene::TestScene(std::wstring* paintMessage){
	this->paintMessage = paintMessage;
}

void TestScene::handleEvents(){
	//TODO: a) move state-stuff to sceneRunner and make a getter for it.
	//      b) *paintMessage = ... should be called within a callback.
	POINT mousePos;
	if (GetCursorPos(&mousePos)){
		//std::cout <<(i++) <<std::endl;
		ScreenToClient(hWnd, &mousePos);
		*paintMessage = std::to_wstring(static_cast<long double>(mousePos.x))+L","+std::to_wstring(static_cast<long double>(mousePos.y))+L"; time:"+std::to_wstring(static_cast<long double>(this->parent->getSec()));
	}
}

void TestScene::render(){
	/*initialize a buffer for double buffering*/
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	Bitmap buffer(clientRect.right, clientRect.bottom);
	Graphics graphicsBuffer(&buffer);

	/*Draw stuffs here*/
	graphicsBuffer.Clear(Color(255, 255, 255, 255));
	Pen      pen(Color(255, 0, 0, 255));
	graphicsBuffer.DrawLine(&pen, 0, 0, 200, 100);

	SolidBrush  brush(Color(255, 0, 0, 255));
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF      pointF(10.0f, 20.0f);

	graphicsBuffer.DrawString(this->paintMessage->c_str(), -1, &font, pointF, &brush);

	/*copy stuff from the new buffer to the old one*/
	Graphics graphics(hdc);
	graphics.DrawImage(&buffer, 0, 0);
}