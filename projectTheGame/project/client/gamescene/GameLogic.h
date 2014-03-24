#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "Deck.h"
#include "../../db/User.h"
#include <functional>

#define TARGET_NUM 12

struct Player{
	int items[CARD_ITEM_TYPES_NUM];
	int silverMeritNum;
	User user;

	//ctor
	Player(User user):
		silverMeritNum(silverMeritNum),
		user(user){
			for(int i=0;i<sizeof(items)/sizeof(*items);i++)
				items[i] = 0;
		}
};

enum GameStatus{
	GAME_IN_PROCESS,
	GAME_TIED,
	GAME_WON
};

class GameLogic{
	Deck deck;
	std::vector<Player> players;
	int turn;
	int currentPlayerIndex;
	bool winOn4;

	GameStatus gameStatus;
	int winner;
	void nextTurn(); //Go to next turn.
public:
	//hook functions, mostly for GUI.
	std::function<void(Card)> drawCardHook;
	std::function<void(Card)> collectCardHook; //called one-by-one.

	std::function<void()> lostHook, nextTurnHook, gameEndHook;

	/**	@param	userList	contain a list of username and password with `userNum` elements
		@param	userNum		see above
		@param	winOn4		Win when 4 silver merit is obtained.
		@param	reuse		Reuse card when there is not enough cards
	*/
	GameLogic(User* userList, int userNum, bool winOn4, bool reuse);

	/// @brief	draw a card for the current player
	Card drawCard();
	/// @brief	collect cards for the current player. Then start the turn of another player.
	std::vector<Card> collectCards();

	/** @return	If someone have won the game, return the index of the winner. Return -1 else. */
	int getWinner() const;
	bool isLost();

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
