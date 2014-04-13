#include <vector>
#include <string>

#ifndef DECK_H
#define DECK_H

#define CHARACTER_CARD_CHANCE 50 //The chance of having character card shown. 50 means 1 in 50, 100 means 1 in 100 and so on.
#define MAX_CARD_UNCOLLECTED 4

/** Define the type of cards */
enum CardType{
	CARD_APPLE,
	CARD_PEAR,
	CARD_CARROT,
	CARD_NUT,
	CARD_WLCHAN,
	CARD_NOBEL,
	CARD_EINSTEIN,

	CARD_ITEM_TYPES_NUM=CARD_NUT+1
};

/** A struct that define the type of card with quantity */
struct Card{
	CardType type;
	int quantity;
	Card(const int& type, const int& quantity):type((CardType)type),quantity(quantity){}
	Card& operator=(Card& b){
		this->type = b.type;
		this->quantity = b.quantity;
		return *this;
	}
};

class Deck{
	std::vector<Card> cards; ///store available cards
	std::vector<Card> lostCards; ///store all cards that is lost
	std::vector<Card> drawnCards; ///store cards that is drawn cards but not collected
	const bool reuse; ///Decide whether to reuse busted cards when there is not enough cards
	bool lost;
public:
	Deck(bool reuse);
	/** @brief	Draw a card from the deck.<br>
			If busted, the cards would be stored into this->bustedCards<br>
			If reuse is true, then when there is no cards in this->cards, the cards will be drawn from this->bustedCards instead.<br>
		@return	the card drawn
	*/
	Card drawCard();
	/**
		@brief	collect the drawn cards, then clear this->drawnCards
		@reutrn	the cards drawn
	*/
	std::vector<Card> collectCards();

	///@return number of uncollected cards
	int uncollectCardsNum() const;

	///@return true if the cards are lost(because of having the same kind of food in other uncollected cards), false else.
	bool isLost();

	///@return true if the card deck is empty, false else.
	bool isEmpty() const;
	
	/**
		@brief	For manual testing, prints output to std::cerr
	*/
	static void test();
};

#endif
