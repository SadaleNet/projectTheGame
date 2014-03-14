class SceneRunner;
#ifndef SCENE_RUNNER_H
#define SCENE_RUNNER_H

#include "Scene.h"
#include <memory>

/** 
	@brief	Contain a Scene. Use to control the game like performing scene-switching, runs the game and terminate the game.<br>
			This is an abstract class to be overridden by library-specific classes.
	@note	1. handleEvents, renderScene and updateScene forwards to scene.<br>
			Since these methods are private in Scene, and only SceneRunner is a friend of Scene,<br>
			subclasses of SceneRunner need these forwarding methods to access the methods in Scene.

			2. The relationship between SceneRunner and Scene is a state pattern in GoF design pattern.
*/
class SceneRunner{
private:
	double second; ///seconds elasped since the SceneRunner is constructed
	int fps; ///Display refresh per second. **NOT** frame per second. This game runs in as high fps as possible. Naming it fps is due to legacy issue.
	bool terminated; ///If true, this sceneRunner is terminated and will exit soon.

protected:
	std::shared_ptr<Scene> scene; ///The scene that is currently being used
	std::shared_ptr<Scene> newScene; ///If != nullptr, this is the scene to be switched in next frame.

	///@param	fps	Display refresh per second. **NOT** frame per second.
	SceneRunner(int fps);

	void handleEvents();

	void renderScene();
	void updateScene();

public:
	///@brief	change the current scene
	void setScene(Scene* scene){
		this->newScene = std::shared_ptr<Scene>(scene);
	}

	template <class SceneRunnerType, class SceneType>
	static SceneRunnerType* instantiate(int fps=60){
		SceneRunnerType* ret = new SceneRunnerType(fps);
		ret->setScene(new SceneType(ret));
		return ret;
	}

	/**@brief	A blocking function that runs the scene.<br>
				Similar to main loop in procedurel programming.<br>
				Runs until terminate() is called.
	*/
	virtual void run() = 0;
	void terminate(); //terminate the rnu()

	//setter and getters
	void setFps(int fps);
	virtual double getSec() const = 0;
	virtual double getDeltaSec() const = 0;
	std::shared_ptr<Scene> getScene() const;
	bool getTerminated() const;
	int getFps() const;

	//Do something(e.g. handling double buffering) and forwards to scene.
	virtual void render() = 0;
};

#endif
