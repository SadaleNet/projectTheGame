#include "SceneRunner.h"
#include "../testCases.h"
#include <iostream>

void SceneRunner::handleEvents(){
	return this->scene->handleEvents();
}
void SceneRunner::render(){
	return this->scene->render();
}

SceneRunner::SceneRunner(Scene* scene, int fps){
	testCases();
	this->scene = std::shared_ptr<Scene>(scene);
	this->fps = fps;
	this->terminated = false;
	scene->parent = this;
}

void SceneRunner::setScene(std::shared_ptr<Scene> scene){
	this->scene = scene;
}

void SceneRunner::terminate(){
	this->terminated = true;
}

/*Setter and getters*/
void SceneRunner::setFps(int fps){ this->fps = fps; }
std::shared_ptr<Scene> SceneRunner::getScene() const{ return this->scene; };
bool SceneRunner::getTerminated() const{ return this->terminated; }
int SceneRunner::getFps() const{ return this->fps; }
