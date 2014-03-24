#include "EmptyScene.h"
#include "../../project.h"
#include <string>

#include "../../gameobjects/include.h"
#include "../../misc/soundPlayer.h"
#include "../../misc/messageBox.h"
#include "../../db/UserDb.h"
#include "../../db/User.h"

EmptyScene::EmptyScene(SceneRunner* const sceneRunner)
	:Scene(sceneRunner){
	// All initialization code goes here. This includes constructing the GUI, defining actions, etc.
}