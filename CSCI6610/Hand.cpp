/*==============================================================================
 *                                                                      Hand.hpp
 * Author      : Steven Kho Ang
 * Version     : Created on November 17, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is a header class for Hand.cpp
 * Hand class will provides the following methods:
 *
 * Hand()                   Default Constructor
 * addCard(Card* card)      adding card to vector
 * cleanHand()              Reinitialize the vector
 * hasAce()                 Determine whether there is an ACE in hand or not
 * isEmpty()                Determine whether the Hand has card or not
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

    vector <Card*>::iterator iter = this->cardsVector.begin();
    for (iter = this->cardsVector.begin(); iter != this->cardsVector.end();
         ++iter) {
        delete *iter;
        // This is to assign iter to null pointer.
    }

    // Clear the vector
    this->cardsVector.clear();
}

bool Hand::isEmpty() const {
    return this->cardsVector.empty();
}

Hand::~Hand() {
    this->clearHand();
}
