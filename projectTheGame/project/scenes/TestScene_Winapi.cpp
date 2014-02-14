#include "TestScene.h"
#include "../project.h"
#include <objidl.h>
#include <gdiplus.h>
#include <string>
#pragma comment (lib,"Gdiplus.lib")

#include "../gameobjects/include.h"
#include "../misc/soundPlayer.h"

TestScene::TestScene(const SceneRunner* sceneRunner)
	:Scene(sceneRunner){

	GameObject* rect = new Rect(Vec2(100, 100), Vec2(50, 50), Color(0.5, 1.0, 0.5, 1.0), 5, Color(1.0, 0.5, 0.5, 1.0));
	rect->vel += Vec2(5, 5);
	//this->add(rect);

	SpriteObject* spriteObject = new SpriteObject(Vec2(200, 200), Vec2(50, 50), "./assets/test.png", Vec2(5, 5), Vec2(10, 10));
	spriteObject->vel += Vec2(20, 0);
	//this->add(spriteObject);

	Text* text = new Text(Vec2(30, 30), Vec2(200, 200), "Hi!", 20);
	text->vel += Vec2(0, 30);
	//this->add(text);

	Button* button = new Button(Vec2(400, 400), Vec2(100, 30), "Button", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	button->action = [=](){ button->vel -= Vec2(0, -10); playSfx("./assets/coin.wav"); };
	button->vel += Vec2(0, -30);
	//this->add(button);

	TextBox* textBox = new TextBox(Vec2(100, 400), Vec2(400, 30), Color(1,1,0,1), Color(0.7,0.7,0.5,1));
	textBox->setButton(button);
	//this->add(textBox);

	Panel* panel = new Panel(Vec2(200, 200), Vec2(200, 200), Color(0.5,0.7,0.5,1));
	panel->vel += Vec2(-10, -10);
	panel->add(rect);
	panel->add(spriteObject);
	panel->add(text);
	panel->add(button);
	panel->add(textBox);
	this->add(panel);

	Timer* timer = new Timer([=](){ text->text = "haha!"; }, 1.5);
	this->add(timer);

	GameObject* animatedRect = new Rect(Vec2(100, 300), Vec2(25, 25), Color(1.0, 0.8, 0.5, 1.0), 5, Color(1.0, 1.0, 0.5, 1.0));
	this->add(animatedRect);
	this->add( new Animator<Vec2>(animatedRect->pos, 2.0, Vec2(100,300), 5.0, Vec2(300,100)) );

	playBgm("./assets/testBgm.wav");
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