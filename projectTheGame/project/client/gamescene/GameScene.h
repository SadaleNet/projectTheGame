class GameScene;
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "../../scenes/SceneRunner.h"
#include "../../scenes/Scene.h"
#include "../GameDb.h"
#include <string>

struct Player;
struct Card;

class GameScene: public Scene{
private:
	void gameEnd();
	void removeCardsOnPanel();
	void initTurn();
	void collectCard(std::vector<Player> oldStates, Card card);
	void cardsLost();
	void drawCard(Card card);
	//@param	itemType	CARD_ITEM_TYPES_NUM means silver merit.
	void showDeltaItem(int playerIndex, int itemType, int oldNum, int newNum);
	void updateDeckCardsNum();
	void processAi();
public:
	GameScene(SceneRunner* const sceneRunner, std::shared_ptr<GameDb> gameDb, bool winOn4, bool reuseLost);
};

#endif
