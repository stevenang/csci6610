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
 * isHitting(Dealer* dealer)    Determine whether the user will hit or not
 * lose()                       Print user lose message to the console
 * win()                        Print user winning message to the console
 * toString()                   String representation of the user's information
 *
 * ostream &operator<< (ostream &os, const BlackJackPalyer &player)
 *                              Overload the operator<<
 *
 *==============================================================================
 */
#include "BlackJackPalyer.hpp"

/**
 * Default Constructor.
 */
BlackJackPalyer::BlackJackPalyer() {
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
BlackJackPalyer::BlackJackPalyer(const string& name, bool isComputer){
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
string BlackJackPalyer::getStatistic() const {

    string result = "";

    result.append("Player " + this->name + ":\n");
    result.append("\tWin:\t" + to_string(this->getWinCount()) + ".\n");
    result.append("\tLose:\t" + to_string(this->getLoseCount()) + ".\n");
    result.append("\tTie:\t" + to_string(this->getTieCount()) + ".\n");

    return result;

}

/**
 * Determine whether the user will hit or not
 * http://www.blackjack.org/wp-content/uploads/2017/09/4-8-Decks-strategy-card-537x1030.png
 *
 * @return true if user want to hit
 */
bool BlackJackPalyer::isHitting() const {
    return true;
}

/**
 * Print user lose message to the console
 */
void BlackJackPalyer::lose() const {

    cout << "Player " + this->name + " lose." << endl;

}

/**
 * String representation of the user's information
 * @return string user's information
 */
string BlackJackPalyer::toString() const {

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
void BlackJackPalyer::win() const {

    cout << "Player " + this->name + " WIN!!!" << endl;

}

// Overloaded operator <<
ostream &operator<< (ostream &os, const BlackJackPalyer &player) {
    os << player.toString();

    return os;
}

BlackJackPalyer::~BlackJackPalyer() {

}

