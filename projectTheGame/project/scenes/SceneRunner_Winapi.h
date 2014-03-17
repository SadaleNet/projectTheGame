class SceneRunner_Winapi;
#ifndef SCENERUNNER_WINAPI_H
#define SCENERUNNER_WINAPI_H

#include "Scene.h"
#include "SceneRunner.h"
#include <memory>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <memory>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

/**	@brief	WinAPI implementation of SceneRunner.<br>
			Overrides pure abstract method of SceneRunner.<br>
*/
class SceneRunner_Winapi : public SceneRunner{
private:
	LARGE_INTEGER tickFreq, startTick; ///used by getSec() and getDeltaSec()
	double secondsSpentOnPreviousFrame, lastUpdateSec; ///used by getDeltaSec()
	Graphics* graphicsBuffer;

	//for double buffering
	std::shared_ptr<Bitmap> internalGraphicsBuffer;
public:
	SceneRunner_Winapi(int fps=60);
	
	virtual void run(); /// Runs Scene methods repeatively until teminate() is called by the scene.
	virtual void render();

	//setters and getters
	virtual double getSec() const override;
	virtual double getDeltaSec() const override;
	Graphics& getBuffer() const{ return *graphicsBuffer; }
};

#endif
