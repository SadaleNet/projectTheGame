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
	//forwards to scene. Since these methods are private in Scene, and only SceneRunner is a friend of Scene,
	//subclasses of SceneRunner need these methods to access the methods in Scene.
	void handleEvents();

public:
	SceneRunner(Scene* scene, int fps=60);
	void setScene(std::shared_ptr<Scene> scene);

	virtual void run() = 0; /// Runs Scene methods repeatively until teminate() is called by the scene.
	void terminate();
	void setFps(int fps);
	virtual double getSec() const = 0;
	std::shared_ptr<Scene> getScene() const;
	bool getTerminated() const;
	int getFps() const;

	//forwards to scene.
	void render();
};

#endif
