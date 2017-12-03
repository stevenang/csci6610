/*==============================================================================
 *                                                                      Hand.hpp
 * Author      : Steven Kho Ang
 * Version     : 1.0
 * Created     : Created on November 17, 2017
 * Last Update:  Last Update on December 03, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is a header class of Hand class
 * Hand class will provides the following methods:
 *
 * Hand()                Default Constructor
 * addCard(Card* card)   adding card to vector
 * cleanHand()           Reinitialize the vector
 * getCards()            Return a vector of cards
 * getTotalNoOfCards()   Return the number of cards in hand
 * hasAce()              Return whether there is ACE in current hand
 * isEmpty()             Return whether the current hand is empty or not
 * ~Hand()               Default deconstructor
 *
 *==============================================================================
 */

#ifndef HAND_HPP_
#define HAND_HPP_
#include "Card.hpp"
#include <string>
#include <vector>
using namespace std;

class Hand {

public:
    Hand();
    void addCard(Card* card);
    void clearHand();
    vector<Card*> getCards()const { return this->cardsVector; }
    int getTotalNoOfCards() const { return this->cardsVector.size(); }
    bool hasAce() const { return ace; }
    bool isEmpty() const;
    virtual ~Hand();

protected:
    vector<Card*> cardsVector;
    bool ace;

};

#endif /* HAND_HPP_ */
