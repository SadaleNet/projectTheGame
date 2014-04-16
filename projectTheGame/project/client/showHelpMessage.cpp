#include "../misc/messageBox.h"

void showHelpMessage(){
	showMessage(
	"This is a turn-based card game.\r\n"
	"* 52 supply card, with apple, pears, carrots or nuts.\r\n"
	"* For each kind of food: there are cards with 2, 4, or 6 food, where (2 foodsx5), (4 foodsx4), (6 foodsx4)\r\n"
	"* Per turn: a card is given. Player may a) draw more card(s) b) collect them.  Max: draw 4 cards.\r\n"
	"* In a turn: Same kind of food is drawn => the cards are lost.\r\n"
	"* Collect cards => all food shown on the cards are collected\r\n"
	"* Per kind of food: 12 foods = 1 silver merit\r\n"
	"* >12 foods => all food of the kind are lost\r\n"
	"* All card drawn OR 11 silver merits given out => player w/ most silver merit wins.\r\n"
	"* Available options: reuse lost cards, win on 4 silver merits.\r\n"
	"* Special cards:\r\n"
	"  * WL Chan = for each opponent: 1 random food is given\r\n"
	"  * Nobel = 1 silver merit\r\n"
	"  * Einstein: remove all your foods", "Rules");
}