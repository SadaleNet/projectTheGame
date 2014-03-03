#include "TestScene.h"
#include "../../project.h"
#include <string>

#include "../../gameobjects/include.h"
#include "../../misc/soundPlayer.h"

TestScene::TestScene(SceneRunner* const sceneRunner)
	:Scene(sceneRunner){

	GameObject* rect = new Rect(Vec2(100, 100), Vec2(50, 50), Color(0.5, 1.0, 0.5, 1.0), 5, Color(1.0, 0.5, 0.5, 1.0));
	rect->vel += Vec2(5, 5);
	//this->add(rect);

	SpriteObject* spriteObject = new SpriteObject(Vec2(200, 200), Vec2(50, 50), "./assets/test.png", Vec2(1, 0), Vec2(10, 10));
	spriteObject->vel += Vec2(20, 0);
	//this->add(spriteObject);

	AnimatedSprite* animatedSprite
		= new AnimatedSprite(Vec2(400, 200), Vec2(50, 50), "./assets/animation.png", Vec2(50, 50), 0.025, 4);
	//this->add(animatedSprite);
	Timer* changeAnimationTimer = new Timer([=](){ animatedSprite->tileIndex.y = 1; }, 5.0);
	this->add(changeAnimationTimer);

	Text* text = new Text(Vec2(30, 30), Vec2(200, 200), "Hi!", 20);
	text->vel += Vec2(0, 30);
	//this->add(text);

	Button* button = new Button(Vec2(400, 400), Vec2(100, 30), "Button", Color(1,1,0,1), Color(0.5,0.5,0.5,1));
	TextBox* textBox = new TextBox(Vec2(100, 400), Vec2(400, 30), Color(1,1,0,1), Color(0.7,0.7,0.5,1));

	button->action = [=](){
		button->vel -= Vec2(0, -10);
		playSfx("./assets/coin.wav");
		textBox->secret = !textBox->secret;
		this->getSceneRunner()->setScene<TestScene>();
	};
	button->vel += Vec2(0, -30);
	//this->add(button);

	textBox->button = button;
	//this->add(textBox);

	Panel* panel = new Panel(Vec2(200, 200), Vec2(200, 200), Color(0.5,0.7,0.5,1));
	panel->vel += Vec2(-10, -10);
	panel->add(rect);
	panel->add(spriteObject);
	panel->add(animatedSprite);
	panel->add(text);
	panel->add(button);
	panel->add(textBox);
	this->add(panel);

	Timer* timer = new Timer([=](){ text->text = "haha!"; }, 1.5);
	this->add(timer);

	Rect* animatedRect = new Rect(Vec2(100, 300), Vec2(25, 25), Color(1.0, 0.8, 0.5, 1.0), 5, Color(1.0, 1.0, 0.5, 1.0));
	this->add(animatedRect);
	this->add( new Animator<Vec2>(animatedRect->pos, 5.0, Vec2(300,100)) );
	this->add( new Animator<Color>(animatedRect->fillColor, 4.0, animatedRect->fillColor, 6.0, Color(0.0, 0.0, 1.0, 1.0)) );

	playBgm("./assets/testBgm.wav");
}