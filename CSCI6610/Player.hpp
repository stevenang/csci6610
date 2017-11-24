/*==============================================================================
 *                                                                    Player.hpp
 * Author      : Steven Kho Ang
 * Version     : Created on November 17, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is an abstreact class uses as a base class for
 * BlackJackPlayer and Dealer
 *
 * Player()                     Default Constructor
 * Player(const string& name,   Constructor
 *          bool isComputer)
 * allCardToString()            String representation of user hand's card
 * void bust()                  a method to make an announcement that
 *                              user is busted.
 * bool isBlackJacj()           Check whether the user is BlackJack or not
 * getTotal()			        Return a total value of the cards in the vector.
 * virtual bool isHitting()     Methods which returns playser decision whether
 *                              Hit or not.
 * bool isBusted()              a method return a boolean to determine whether
 *                              if user is bust or not
 * bool isHighCard()            Check whether the first card is high card nor not
 *
 *==============================================================================
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include "Hand.hpp"
#include <string>

using namespace std;

class Player : Hand {



public:

    Player();
    Player(const string& name, bool isComputer);
    string allCardToString(bool isDealer, bool showAll) const;
    void addCardToHand(Card* card) { addCard(card); }
    void bust() const;
    int getFirstCardValue() const;
    string getName() const { return this->name; }
    int getStatus() const { return status; }
    int getTotal() const;
    bool isBlackJack() const;
    bool isBusted();
    bool isFirstCardHighCard() const;
    vector <Card*> getCardsFromHand() { return getCards(); }
    void clearHands() { clearHand(); }
    virtual ~Player();

    enum statusType {NOT_STARTED, HITTING, STANDING, BUSTED, SURRENDER};

protected:
    string name;
    bool isComputer;
    int status = Player::NOT_STARTED;

};

#endif /* PLAYER_HPP_ */
