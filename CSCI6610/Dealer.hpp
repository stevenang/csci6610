/*==============================================================================
 *                                                                    Dealer.hpp
 * Author      : Steven Kho Ang
 * Version     : 1.0
 * Created     : Created on November 17, 2017
 * Last Update:  Last Update on December 03, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is an header file for  Dealer class
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

#ifndef CSCI6610_DEALER_HPP
#define CSCI6610_DEALER_HPP

#include "Player.hpp"
#include <string>

using namespace std;

class Dealer : public Player {

public:
    Dealer();
    Dealer(const string& name, bool isComputer);
    bool isHitting() const;
    bool isStanding() const;
    void lose() const;
    string toString(bool showAll) const;
    void win() const;

private:
    bool isComputer;
};


#endif //CSCI6610_DEALER_HPP
