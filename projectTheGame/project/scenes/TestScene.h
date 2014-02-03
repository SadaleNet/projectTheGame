class TestScene;
#ifndef TESTSCENE_H
#define TESTSCENE_H
#include "SceneRunner.h"
#include "Scene.h"
#include <string>

class TestScene : public Scene{
private:
	std::wstring* paintMessage;
public:
	TestScene(std::wstring* paintMessage);
	virtual void handleEvents() override;
	virtual void update() override;
	virtual void render() override;
};

#endif
