#include "Deck.h"
#include <cstdlib>

Deck::Deck(){
	this->busted = false;
	for(int i=CARD_APPLE; i<CARD_ITEM_TYPES_NUM; i++){
		for(int j=0; j<5; j++)
			this->cards.push_back(Card(i, 2));
		for(int j=0; j<4; j++)
			this->cards.push_back(Card(i, 4));
		for(int j=0; j<4; j++)
			this->cards.push_back(Card(i, 6));
	}
}

void Deck::drawCard(){
	const int drawnId = rand()%this->drawnCards.size();
	this->cards.erase(this->cards.begin()+drawnId);
	this->drawnCards.push_back(this->drawnCards[drawnId]);
}