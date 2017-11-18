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
 * allCardToString(bool dealer) String representation of user hand's card
 * virtual bool isHitting()     Methods which returns playser decision whether
 *                              Hit or not.
 * bool isBlackJacj()           Check whether the user is BlackJack or not
 * bool isBusted()              a method return a boolean to determine whether
 *                              if user is bust or not
 * virtual bool isHitting()     Methods which returns playser decision whether
 *                              Hit or not.
 * void bust()                  a method to make an announcement that
 *                              user is busted.
 *
 *==============================================================================
 */

#include "Player.hpp"

/**
 * Default Constructor
 * This will initialized the following variables as follow:
 *      name = ""
 *      isComputer = false;
 *      ace = false
 */
Player::Player() {
    this->name = "";
    this->isComputer = false;
    this->ace = false;
}

/**
 * Constructor
 * This will initialized the variables
 *      name = name (player's name)
 *      isComputer = isComputer
 * @param name          Player's name
 * @param isComputer    Indicate whether this is computer player or not.
 */
Player::Player(const string &name, bool isComputer) {
    this->name = name;
    this->isComputer = isComputer;
    this->ace = false;
}


/**
 * String representation of user hand's card
 * @param isDealer Determine whether the player is dealer or not
 * @param showAll Determine whether to hide the first card or not.
 * @return string String representation of user hand's card
 */
string Player::allCardToString(bool isDealer, bool showAll) const {

    vector<Card*>::const_iterator iter;
    string result = "";
    int count = 0;

    if (this->cardsVector.empty()) {
        return "No Card in hand.";
    }

    for (iter=this->cardsVector.begin(); iter < this->cardsVector.end();
         ++iter) {

        result.append("[");

        if (isDealer && count == 0 && !showAll) {
            result.append("*");
            count++;
        } else {
            result.append(to_string((*iter)->getCardValue()));
        }

        result.append("]");

    }

    return result;

}


/**
 * bust()
 * A method which user used to announce he was busted.
 *      Example:    Player: Player 1 busted.
 */
void Player::bust() const {
    cout << "Player: " << this->name << " busted." << endl;
}

/**
 * Get the total value of hand
 * Iterate the cards and gets its numeric value 1-10
 * Then determine if there is an ACE by getting the Face value
 * If ACE exits in the hand, then check the total.
 * If total is less than or equal to 11, then the current total add 10
 */
int Player::getTotal() const {

    int total;
    bool isHandContainAce = false;

    // If there is nothing in hand, return 0;
    if (this->cardsVector.empty()) {
        return 0;
    }

    // If first card has value of 0, then means the card is faced down.
    // Also return 0
    // TODO Need to discuss
    if (this->cardsVector[0]->getCardValue() == '0') {
        return 0;
    }

    // Get the total from the vector of cards
    vector<Card*>::const_iterator iter;
    for (iter = this->cardsVector.begin(); iter < this->cardsVector.end();
         ++ iter) {
        // Todo Need to discuss with them
        total = total + (int)((*iter)->getCardValue());
    }

    // Check whether the hand contains ACE
    for (iter = this->cardsVector.begin(); iter < this->cardsVector.end();
         ++ iter) {
        // Todo Need to change this or add
        // if ((*iter)->getCardFaceValue() == Card::ACE) {
        //	isHandContainAce = true;
        //}
    }

    // If hand is low enough (not greater than 21), then treat ace as 10
    if (isHandContainAce && total <= 11) {
        total += 10;
    }

    return total;
}

/**
 * isBlackJack()
 * A method to determine whether user has BlackJack or not
 *
 * @return true when the total of card is 21 and number of card is 2
 */
bool Player::isBlackJack() const {
    return (getTotal() == 21) && (getTotalNoOfCards() == 2);
}

/**
 * isBusted()
 * Check whether the user is busted or not
 * @return True when card's total is greater than 21.
 */
bool Player::isBusted() const {
    return (getTotal() > 21);
}

Player::~Player() {
    // TODO Auto-generated destructor stub
}