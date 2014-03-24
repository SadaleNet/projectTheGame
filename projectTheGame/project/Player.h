#ifndef PLAYER_H
#define PLAYER_H
#include "Deck.h"

class Player{
	int items[CARD_ITEM_TYPES_NUM];
	int silverMeritNum;
	std::string name;
	Deck* deck const;
	std::function<void()> drawHook;
	std::function<void()> collectHook;
public:
	Player(const std::string& name, Deck* deck const, const std::function<void()>& drawHook, const std::function<void()>& collectHook);
	void drawCard();
	void collectCards();
	bool isBusted() const;
	int getSilverMeritNum() const;
	int getItemNum(CardType itemType);

};

#endif