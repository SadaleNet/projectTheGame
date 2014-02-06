class SceneRunner;
#ifndef SCENERUNNER_H
#define SCENERUNNER_H

#include "Scene.h"
#include <memory>

class SceneRunner{
private:
	std::shared_ptr<Scene> scene;
	double second;
	int fps;
	bool terminated;

protected:
	SceneRunner(int fps);
	//forwards to scene. Since these methods are private in Scene, and only SceneRunner is a friend of Scene,
	//subclasses of SceneRunner need these forwarding methods to access the methods in Scene.
	void handleEvents();

	void renderScene();
	void updateScene();

public:
	template <class SceneType>
	void setScene(){
		this->scene = std::shared_ptr<Scene>(new SceneType(this));
	}

	template <class SceneRunnerType, class SceneType>
	static SceneRunnerType* instantiate(int fps=60){
		SceneRunnerType* ret = new SceneRunnerType(fps);
		ret->setScene<SceneType>();
		return ret;
	}

	virtual void run() = 0;
	void terminate();
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
