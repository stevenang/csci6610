/*==============================================================================
 *                                                                    Dealer.hpp
 * Author      : Steven Kho Ang
 * Version     : Created on November 17, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is an header file for  Delaer class¥
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

#ifndef CSCI6610_DEALER_HPP
#define CSCI6610_DEALER_HPP

#include "Player.hpp"
#include <string>

using namespace std;

class Dealer : public Player {

public:
    Dealer();
    Dealer(const string& name, bool isComputer);
    //bool isHitting() const override;
    void lose() const;
    string toString(bool showAll) const;
    void win() const;

private:
    string name;
    bool isComputer;
};


#endif //CSCI6610_DEALER_HPP
