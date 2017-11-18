/*==============================================================================
 *                                                                      Hand.hpp
 * Author      : Steven Kho Ang
 * Version     : Created on November 17, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is a header class of Hand class
 * Hand class will provides the following methods:
 *
 * Hand()				Default Constructor
 * addCard(Card* card)	adding card to vector
 * cleanHand()			Reinitialize the vector
 * hasAce()				Return whether there is ACE in current hand
 * isEmpty()			Return whether the current hand is empty or not
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
    virtual ~Hand();
    void addCard(Card* card);
    void clearHand();
    int getTotalNoOfCards() const { return this->cardsVector.size(); }
    bool hasAce() const { return ace; }
    bool isEmpty() const;

protected:
    vector<Card*> cardsVector;
    bool ace;

};

#endif /* HAND_HPP_ */
