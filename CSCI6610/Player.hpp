/*==============================================================================
 *                                                                    Player.hpp
 * Author      : Steven Kho Ang
 * Version     : 1.0
 * Created     : Created on November 17, 2017
 * Last Update:  Last Update on December 03, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is a header class of the Player.cpp
 * Also a super class of BlackJackPlayer and Dealer
 *
 * Player()                     Default Constructor
 * Player(const string& name,   Constructor
 *          bool isComputer)
 * allCardToString(bool dealer) String representation of user hand's card
 * addCardToHand()              Add one card to your hand.
 * bust()                       Print out "Busted" message
 * clearHand()                  Clean player's hand at the end of each game.
 * getCardsFromHand()           Return player's hand
 * getFirstCardValue()          Return the value of the first card of hand
 * getName()                    Return player's name
 * getStatus()                  Return player's status
 * getTotal()                   Get the total value of hand
 * isBlackJacj()                Check whether the user is BlackJack or not
 * isBusted()                   a method return a boolean to determine whether
 *                              if user is bust or not
 * isFirstCardHighCard()        Determine of the first card of your hand is
 *                              high card (10, J, Q, K and A) or not
 * lose()                       Print out lose message
 * tie()                        Print out tie message
 * win()                        Print out win message
 * ~Player()                    Deconstructor
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
    void clearHands();
    vector <Card*> getCardsFromHand() { return getCards(); }
    int getFirstCardValue() const;
    string getName() const { return this->name; }
    int getStatus() const { return status; }
    int getTotal() const;
    void hitting() { this->status = Player::HITTING; }
    bool isBlackJack();
    bool isBusted();
    bool isFirstCardHighCard() const;
    void lose();
    void standing() { this->status = Player::STANDING; }
    void surrender() { this->status = Player::SURRENDER; }
    void tie();
    void win();
    virtual ~Player();

    enum statusType {NOT_STARTED, HITTING, STANDING, BUSTED, SURRENDER, WIN};

protected:
    string name;
    bool isComputer;
    int status = Player::NOT_STARTED;
    int winCount = 0;
    int loseCount = 0;
    int tieCount = 0;

};

#endif /* PLAYER_HPP_ */
