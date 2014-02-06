#include "TestScene.h"
#include "../project.h"
#include <objidl.h>
#include <gdiplus.h>
#include <string>
#pragma comment (lib,"Gdiplus.lib")

#include "../gameobjects/Rect.h"
#include "../utils/Vec2.h"

TestScene::TestScene(const SceneRunner* sceneRunner)
	:Scene(sceneRunner){
	GameObject* rect = new Rect(Vec2(100, 100), Vec2(50, 50), Color(0.5, 1.0, 0.5, 1.0));
	rect->addVel(Vec2(5, 5));
	this->add(rect);
}

/*void TestScene::render(){
	//initialize a buffer for double buffering
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	Bitmap buffer(clientRect.right, clientRect.bottom);
	Graphics graphicsBuffer(&buffer);

	//Draw stuffs here
	graphicsBuffer.Clear(Color(255, 255, 255, 255));
	Pen      pen(Color(255, 0, 0, 255));
	graphicsBuffer.DrawLine(&pen, 0, 0, 200, 100);

	SolidBrush  brush(Color(255, 0, 0, 255));
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF      pointF(10.0f, 20.0f);

	graphicsBuffer.DrawString(this->paintMessage->c_str(), -1, &font, pointF, &brush);

	//copy stuff from the new buffer to the old one
	Graphics graphics(hdc);
	graphics.DrawImage(&buffer, 0, 0);
}*/