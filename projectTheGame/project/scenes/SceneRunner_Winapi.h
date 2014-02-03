class SceneRunner_Winapi;
#ifndef SCENERUNNER_WINAPI_H
#define SCENERUNNER_WINAPI_H

#include "Scene.h"
#include <memory>
#include <windows.h>

class SceneRunner_Winapi : public SceneRunner{
private:
	LARGE_INTEGER tickFreq, startTick;
public:
	SceneRunner_Winapi(Scene* scene, int fps=60);
	
	virtual void run(); /// Runs Scene methods repeatively until teminate() is called by the scene.
	void render();
	virtual double getSec() const;
};

#endif
