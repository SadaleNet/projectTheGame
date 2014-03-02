#include "SceneRunner.h"
#include "../misc/testCases.h"
#include <iostream>

SceneRunner::SceneRunner(int fps){
	testCases();
	this->newScene = nullptr;
	this->fps = fps;
	this->terminated = false;
}

void SceneRunner::handleEvents(){
	if(this->scene==nullptr)
		return;
	return this->scene->handleEvents();
}

void SceneRunner::renderScene(){
	if(this->scene==nullptr)
		return;
	this->scene->render();
}

void SceneRunner::updateScene(){
	if(this->scene==nullptr)
		return;
	this->scene->update();
}

void SceneRunner::terminate(){
	this->terminated = true;
}

/*Setter and getters*/
void SceneRunner::setFps(int fps){ this->fps = fps; }
std::shared_ptr<Scene> SceneRunner::getScene() const{ return this->scene; };
bool SceneRunner::getTerminated() const{ return this->terminated; }
int SceneRunner::getFps() const{ return this->fps; }
