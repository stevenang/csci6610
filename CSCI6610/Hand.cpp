/*==============================================================================
 *                                                                      Hand.cpp
 * Author      : Steven Kho Ang
 * Version     : 1.0
 * Created     : Created on November 17, 2017
 * Last Update:  Last Update on December 03, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is an implementation of of Hand class
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

#include "Hand.hpp"

/**
 * Default Constructor
 * This will creat a vector with a capacity of 10
 */
Hand::Hand() {
    // This is to request change in capacity to vector;
    this->cardsVector.reserve(10);
}

/**
 * addCard
 * This will add the card to the vector
 */
void Hand::addCard(Card* card) {
    if (card->getCardValue() == 'A') {
        this->ace = true;
    }

    this->cardsVector.push_back(card);
}

/**
 * cleadHand
 * After each trun, user will call cleanHand to reinitialize the vector
 */
void Hand::clearHand() {
    // Clear the vector
    this->cardsVector.clear();
}

bool Hand::isEmpty() const {
    return this->cardsVector.empty();
}

Hand::~Hand() {
    this->clearHand();
}
