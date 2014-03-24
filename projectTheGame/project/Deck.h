#include <vector>
#include <string>

#ifndef DECK_H
#define DECK_H

/** Define the type of cards */
enum CardType {
	CARD_APPLE,
	CARD_PEAR,
	CARD_CARROT,
	CARD_NUT,
	CARD_MARX,
	CARD_NOBEL,
	CARD_EINSTEIN,

	CARD_ITEM_TYPES_NUM=CARD_NUT+1
};

/** A class that define the type of card with quantity */
struct Card{
	const CardType type;
	const int quantity;
	Card(const CardType& type, const int& quantity):type(type),quantity(){}
};

class Deck{
	std::vector<Card> cards; ///store available cards
	std::vector<Card> bustedCards; ///store all cards that is busted
	std::vector<Card> drawnCards; ///store cards that is drawn cards but not collected
	bool busted;
public:
	Deck();
	void drawCard();
	void collectCards();
	bool isBusted() const;
};

#endif