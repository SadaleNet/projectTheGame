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
};

#endif
