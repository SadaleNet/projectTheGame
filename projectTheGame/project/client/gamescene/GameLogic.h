#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "Deck.h"
#include <functional>

#define TARGET_NUM 12

/** @brief A struct containing the number of items and silver merits that a player own. */
struct Player{
	int items[CARD_ITEM_TYPES_NUM];
	int silverMeritNum;

	//ctor
	Player():silverMeritNum(0){
		for(int i=0;i<sizeof(items)/sizeof(*items);i++)
			items[i] = 0;
	}
};

enum GameStatus{
	GAME_IN_PROCESS,
	GAME_TIED,
	GAME_WON
};

class GameDb; //forwad declaration

/** @brief A class that contains the logic of the game */
class GameLogic{
	Deck deck;
	GameDb* gameDb;
	std::vector<Player> players;
	int turn;
	int currentPlayerIndex;
	bool winOn4;

	GameStatus gameStatus;
	int winner;
	void nextTurn(); //Go to next turn.
	/// @return	returns true if uncollected cards are lost, false else.
	bool isLost();
public:
	//hook functions, mostly for GUI.
	std::function<void(Card)> drawCardHook;
	std::function<void(std::vector<Player>, Card)> collectCardHook; //called one-by-one. Param: old state, collected cards

	std::function<void()> lostHook, nextTurnHook, gameEndHook;

	/**	@param	userList	contain a list of username and password
		@param	winOn4		Win when 4 silver merit is obtained.
		@param	reuse		Reuse card when there is not enough cards
	*/
	GameLogic(GameDb* gameDb, bool winOn4, bool reuse);

	/// @brief	draw a card for the current player
	Card drawCard();
	/// @brief	collect cards for the current player. Then start the turn of another player.
	std::vector<Card> collectCards();

	/// @return	If someone have won the game, return the index of the winner. Return -1 else.
	int getWinner() const;
	///@return uncollected cards
	std::vector<Card> getUncollectedCards() const;
	/// @return	true if the deck is empty, false else.
	bool isDeckEmpty() const;
	/// @return	number of cards in the deck
	int getCardsNum() const;

	//Trivial getters
	int getCurrentPlayerIndex() const;
	Player getCurrentPlayer();
	std::vector<Player> getPlayers();
	GameStatus getGameStatus() const;

	/**
		@brief	For manual testing, prints output to std::cerr
	*/
	static void test();
};

#endif
