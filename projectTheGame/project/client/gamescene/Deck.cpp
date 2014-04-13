#include "Deck.h"
#include <cstdlib>
#include <cassert>
#include <ctime>

Deck::Deck(bool reuse):
	reuse(reuse),
	lost(false){
	//Intialize card deck
	for(int i=CARD_APPLE; i<CARD_ITEM_TYPES_NUM; i++){
		for(int j=0; j<5; j++)
			this->cards.push_back(Card(i, 2));
		for(int j=0; j<4; j++)
			this->cards.push_back(Card(i, 4));
		for(int j=0; j<4; j++)
			this->cards.push_back(Card(i, 6));
	}
	srand(static_cast<unsigned int>(time(NULL)));
}

Card Deck::drawCard(){
	assert(this->drawnCards.size()<4); //ensure that the card already drawn is less than 4
	assert(!this->lost);
	assert(!this->isEmpty());

	//Decide a card to be drawn
	Card drawnCard = Card(0, 0);
	if(this->cards.size()>0){
		std::vector<Card>::iterator drawnCardIt = this->cards.begin()+rand()%this->cards.size();
		drawnCard = *drawnCardIt;
		this->cards.erase(drawnCardIt); //remove the drawn card from the deck
	}else{
		std::vector<Card>::iterator drawnCardIt = this->lostCards.begin()+rand()%this->lostCards.size();
		drawnCard = *drawnCardIt;
		this->lostCards.erase(drawnCardIt); //remove the drawn card from the deck
	}

	//There is a chance the the card magically turns into a character card.
	if(rand()%50==0){
		switch(rand()%3){
			case 0:	drawnCard = Card(CARD_WLCHAN, 0);	break;
			case 1:	drawnCard = Card(CARD_NOBEL, 0);	break;
			case 2:	drawnCard = Card(CARD_EINSTEIN, 0);	break;
		}
	}

	//Check whether it is busted.
	for(std::vector<Card>::iterator it=this->drawnCards.begin(); it!=this->drawnCards.end(); it++){
		//Busted! Push all values into this->bustedCards then return
		if(drawnCard.type == it->type){
			for(std::vector<Card>::iterator jt=this->drawnCards.begin(); jt!=this->drawnCards.end(); jt++)
				this->lostCards.push_back(*jt);
			this->drawnCards.clear();
			this->lost = true;
			return drawnCard;
		}
	}

	//draw card from the deck
	this->drawnCards.push_back(drawnCard);
	return this->drawnCards.back();
}

std::vector<Card> Deck::collectCards(){
	assert(!this->lost);
	std::vector<Card> ret = this->drawnCards;
	this->drawnCards.clear();
	return ret;
}

bool Deck::isLost(){
	//clear the this->busted flag then return the old value of this->busted.
	bool ret = this->lost;
	this->lost = false;
	return ret;
}

bool Deck::isEmpty() const{
	if(this->cards.size()>0)
		return false;
	if(this->reuse&&this->lostCards.size()>0)
		return false;
	return true;
}

#include <iostream>
void Deck::test(){
	Deck deck = Deck(true);
	int cardsOwned = 0;
	while(!deck.isEmpty()){
		Card card = deck.drawCard();
		bool busted = deck.isLost();
		std::cerr <<"Drawn card: " <<card.type <<',' <<card.quantity <<std::endl;
		
		cardsOwned++;
		if(busted){
			cardsOwned = 0;
			std::cerr <<"^^^Lost :'( ^^^" <<std::endl;
		}else if(cardsOwned==4){
			cardsOwned = 0;
			deck.collectCards();
			std::cerr <<"^^^Collected^^^" <<std::endl;
		}
	}
}
