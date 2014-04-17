/**	@file	empty scene template to be copied

			To create a new scene, please do the following:<br>
			1. make a clone of `emptyscene` and rename it<br>
			2. rename the files cloned<br>
			3. in the files, rename replace `EmptyScene` with the name of your scene. Example: LoginScene, MenuScene, GameScene<br>
			4. modify `WhateverScene` from `#define INITIAL_SCENE WhateverScene` in project.cpp to the scene that you want it to be shown at the beginning. Also
					remember to add `#include client/yourscene/YourScene.h` in projet.cpp<br>
			5. in YourScene.cpp, add the initialization code. TestScene.cpp is a good example showing you what can be added there.<br>
			6. Finally, remove this comment.
*/
class EmptyScene;
#ifndef EMPTY_SCENE_H
#define EMPTY_SCENE_H

#include "../../scenes/SceneRunner.h"
#include "../../scenes/Scene.h"
#include <string>

/** @brief A template scene to be copied and modified */
class EmptyScene: public Scene{
public:
	EmptyScene(SceneRunner* const sceneRunner);
};

#endif