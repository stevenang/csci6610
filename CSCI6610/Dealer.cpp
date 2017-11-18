/*==============================================================================
 *                                                                    Dealer.cpp
 * Author      : Steven Kho Ang
 * Version     : Created on November 17, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is an actual implementation file for Dealer class
 *
 * Dealer()             Default Constructor
 * Dealer()             Constructor
 * isHitting()          Determine whether the dealer will hit or not
 * void lose()          Print dealer lose message to the console
 * toString()           String representation of the dealer's information
 * void win()           Print dealer winning message to the console
 *
 * ostream &operator<< (ostream &os, const Dealer &player)
 *                              Overload the operator<<
 *
 *==============================================================================
 */
#include "Dealer.hpp"

Dealer::Dealer() {
    this->name = "";
    this->isComputer = false;
}

Dealer::Dealer(const string &name, bool isComputer) {
    this->name = name;
    this->isComputer = isComputer;
}

bool Dealer::isHitting() const {
    return (getTotal() <= 16);
}

void Dealer::lose() const {
    cout << "Dealer Lose." << endl;
}

string Dealer::toString(bool showAll) const {

    string result = "";

    result.append("Dealer ");
    result.append(this->name);
    result.append(". Current hand: ");
    result.append(allCardToString(true, showAll));

    return result;
}

void Dealer::win() const {
    cout << "Dealer Win!!!" << endl;
}