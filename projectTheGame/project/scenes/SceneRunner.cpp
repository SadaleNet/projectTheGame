#include "SceneRunner.h"
#include "../misc/testCases.h"
#include <iostream>

SceneRunner::SceneRunner(int fps){
	testCases();
	this->fps = fps;
	this->terminated = false;
}

void SceneRunner::handleEvents(){
	return this->scene->handleEvents();
}

void SceneRunner::renderScene(){
	this->scene->render();
}

void SceneRunner::updateScene(){
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
