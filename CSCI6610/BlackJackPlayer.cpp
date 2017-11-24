/*==============================================================================
 *                                                           BlackJackPlayer.cpp
 * Author      : Steven Kho Ang
 * Version     : Created on November 17, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is an header file for  BlackJackPlayer class¥
 *
 * BlackJackPlayer()            Default Constructor
 * BlackJackPlayer(             Constructor
 *          const string& name,
 *          bool isComputer)
 * addWinCount()                Increament Win counter
 * addTieCount()                Increament Tie counter
 * addLoseCount()               Increament Lose counter
 * getLoseCount()               Return user's lose count
 * getStatistic()               String representation of user's game statictic
 * getTieCount()                Return user's tie count
 * getWinCount()                Return user's winning count
 * isHitting(int dealerCard)    Determine whether the user will hit or not
 * isStanding(int dealerCard)   Determine whether the user will stand or not
 * isSurrender(int dealerCard)  Determine whether the user will surrender or not
 * lose()                       Print user lose message to the console
 * win()                        Print user winning message to the console
 * toString()                   String representation of the user's information
 *
 * ostream &operator<< (ostream &os, const BlackJackPalyer &player)
 *                              Overload the operator<<
 *
 *==============================================================================
 */

#include "BlackJackPlayer.hpp"

BlackJackPlayer::BlackJackPlayer() {
    this->name = "";
    this->isComputer = false;
    this->winCount = 0;
    this->loseCount = 0;
    this->tieCount = 0;
}

/**
 * Constructor
 * @param name          Player's name
 * @param isComputer    Use to determine whether the use is computer or not.
 */
BlackJackPlayer::BlackJackPlayer(const string& name, bool isComputer){
    this->name = name;
    this->isComputer = isComputer;
    this->winCount = 0;
    this->loseCount = 0;
    this->tieCount = 0;
}

/**
 * String representation of user's game statictic
 * @return string - User's statistic
 */
string BlackJackPlayer::getStatistic() const {

    string result = "";

    result.append("Player " + this->name + ":\n");
    result.append("\tWin:\t" + to_string(this->getWinCount()) + ".\n");
    result.append("\tLose:\t" + to_string(this->getLoseCount()) + ".\n");
    result.append("\tTie:\t" + to_string(this->getTieCount()) + ".\n");

    return result;

}

/**
 * This method will determine whether the user will hit or not
 * http://www.blackjack.org/wp-content/uploads/2017/09/4-8-Decks-strategy-card-537x1030.png
 * based on the tutorial, the user will hit at the following conditions:
 *
 * 1.  If user's card total value is between 4 and 11.
 * 2.  If user's card total value is 12 and dealer's card value is
 *     either 2, 3, 7, 8, 9, 10, or A
 * 3.  If user's card total value is 13 or 14 and dealer's card value is
 *     either 7, 8, 9, 10, or A
 * 4.  If user's card total value is 15 and dealer's card value is
 *     either 7, 8, 9 or A (as 1)
 * 5.  if user's card total value is 16 and dealer's card value is
 *     either 7 or 8
 *
 * @return true if user can hit
 */
bool BlackJackPlayer::isHitting(int dealerCard)  {

	if ((getTotal() >= 4 && getTotal() <= 11) &&
			(dealerCard >=2 && dealerCard <= 11)) {
		this->status = BlackJackPlayer::HITTING;
		return true;
	}

	if ((getTotal() == 12) && ((dealerCard <=3) ||
			(dealerCard >= 7 && dealerCard << 11))) {
		this->status = BlackJackPlayer::HITTING;
		return true;
	}

	if ((getTotal() <= 14) && (dealerCard >=7 && dealerCard <= 11)) {
		this->status = BlackJackPlayer::HITTING;
		return true;
	}

	if ((getTotal() == 15) && ((dealerCard >=7 && dealerCard <= 9) ||
			dealerCard == 11 || dealerCard == 1)) {
		this->status = BlackJackPlayer::HITTING;
		return true;
	}

	if ((getTotal() == 16) && (dealerCard ==7 || dealerCard == 8)) {
		this->status = BlackJackPlayer::HITTING;
		return true;
	}

    return false;
}

/**
 * This method will determine whether the computer player should stand or not
 * Based on the tutorial, user should stand at the following conditions:
 *
 * 1.  if user'card is 12 and dealer's card is between 4 and 6
 * 2.  if user's card is between 13 and 16, and dealer's card is between
 *     2 and 6
 * 3.  if user's card is greater or equal than 17
 *
 * @return true when user can stand
 */
bool BlackJackPlayer::isStanding(int dealerCard) {

	if (getTotal() == 12 && (dealerCard >= 4 && dealerCard <= 6)) {
		this->status = BlackJackPlayer::STANDING;
		return true;
	}

	if ((getTotal() >= 13 && getTotal() <= 16) &&
			(dealerCard >= 2 && dealerCard <= 6)) {
		this->status = BlackJackPlayer::STANDING;
		return true;
	}

	if (getTotal() > 17) {
		return true;
	}

	return false;
}

/**
 * This method is to determine if the computer user should surrender or not.
 * Based on the tutorial, user should surrender at the following conditions:
 *
 * 1.  if the user card's total is 15 and dealer's card is 10
 * 2.  if the user card's total is 16 and dealer's card is 9, 10, or 11
 *
 * @return true when user needs to surrender
 */
bool BlackJackPlayer::isSurrender(int dealerCard) {

	if (getTotal() == 15 && (dealerCard == 10)) {
		this->status = BlackJackPlayer::SURRENDER;
		return true;
	}

	if (getTotal() == 16 && (dealerCard >= 9 && dealerCard <= 11)) {
		this->status = BlackJackPlayer::SURRENDER;
		return true;
	}

	return false;
}

/**
 * Print user lose message to the console
 */
void BlackJackPlayer::lose() {

	this->loseCount++;
    cout << "Player " + this->name + " lose." << endl;

}


void BlackJackPlayer::tie() {

	this->tieCount++;
    cout << "Player " + this->name + " tie." << endl;

}

/**
 * String representation of the user's information
 * @return string user's information
 */
string BlackJackPlayer::toString() const {

    string result = "";

    result.append("Player ");
    result.append(this->name);
    result.append(". Current hand: ");
    result.append(allCardToString(false, true));
    result.append(". Win: ");
    result.append(to_string(this->getWinCount()));
    result.append(". Lose: ");
    result.append(to_string(this->getLoseCount()));
    result.append(". Tie: ");
    result.append(to_string(this->getTieCount()));
    result.append(".");

    return result;

}

/**
 * Print user winning message to the console
 */
void BlackJackPlayer::win() {

	this->winCount++;
    cout << "Player " + this->name + " WIN!!!" << endl;

}

// Overloaded operator <<
ostream &operator<< (ostream &os, const BlackJackPlayer &player) {
    os << player.toString();

    return os;
}

BlackJackPlayer::~BlackJackPlayer() {
	// TODO Auto-generated destructor stub
}

