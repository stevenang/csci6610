/*==============================================================================
 *                                                                    Dealer.cpp
 * Author      : Steven Kho Ang
 * Version     : 1.0
 * Created     : Created on November 17, 2017
 * Last Update:  Last Update on December 03, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is an implementation of the Dealer class
 *
 * Dealer()                     Default Constructor
 * Dealer(const string&, bool)  Constructor
 * isHitting()                  Determine whether the dealer will hit or not
 * isStanding()                 Determine whether the dealer will stand or not
 * lose()                       Print dealer lose message to the console
 * toString()                   String representation of the dealer's information
 * win()                        Print dealer winning message to the console
 *
 * ostream &operator<< (ostream &os, const Dealer &player)
 *                              Overload the operator<<
 *
 *==============================================================================
 */

#include "Dealer.hpp"

/**
 * Default Constructor
 */
Dealer::Dealer() {
    this->name = "";
    this->isComputer = false;
}

/**
 * Constructor
 * @param name         Dealer's name
 * @param isComputer   A boolean value indicate whether the dealer is
 *                     computer or not. (Always true)
 */
Dealer::Dealer(const string &name, bool isComputer) {
    this->name = name;
    this->isComputer = isComputer;
}

/**
 * if the total is 16 or under, he must take a card.
 * He must continue to take cards until the total is 17 or more,
 * at which point the dealer must stand.
 */
bool Dealer::isHitting() const {
    return (getTotal() <= 16);
}

/**
 * if the total is 16 or under, he must take a card.
 * He must continue to take cards until the total is 17 or more,
 * at which point the dealer must stand.
 */
bool Dealer::isStanding() const {
	return (getTotal() >= 17);
}

/**
 * Print out a lose message.
 */
void Dealer::lose() const {
    cout << "Dealer Lose." << endl;
}

/**
 * Print Dealer's information which will return the following:
 * 1.  Deal;er's name
 * 2.  Dealer's all cards.
 */
string Dealer::toString(bool showAll) const {

    string result = "";

    result.append("Dealer ");
    result.append(this->name);
    result.append(". Current hand: ");
    result.append(allCardToString(true, showAll));

    return result;
}

/**
 * Print out Winning message
 */
void Dealer::win() {
	this->status = Player::WIN;
    cout << "Dealer Win!!!" << endl;
}
