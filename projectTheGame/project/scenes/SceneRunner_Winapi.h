class SceneRunner_Winapi;
#ifndef SCENERUNNER_WINAPI_H
#define SCENERUNNER_WINAPI_H

#include "Scene.h"
#include "SceneRunner.h"
#include <memory>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

class SceneRunner_Winapi : public SceneRunner{
private:
	LARGE_INTEGER tickFreq, startTick;
	double lastUpdateSec;
	Graphics* graphicsBuffer;
public:
	SceneRunner_Winapi(int fps=60);
	
	virtual void run(); /// Runs Scene methods repeatively until teminate() is called by the scene.
	virtual void render();
	virtual double getSec() const override;
	virtual double getDeltaSec() const override;
	Graphics& getBuffer() const{ return *graphicsBuffer; }
};

#endif
