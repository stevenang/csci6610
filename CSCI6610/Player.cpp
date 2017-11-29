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

    int total = 0;

    // Get the total from the vector of cards
    vector<Card*>::const_iterator iter;
    for (iter = this->cardsVector.begin(); iter < this->cardsVector.end();
         ++ iter) {

        //if (total + (*iter)->getCardRank(true) <= 11) {
        //		total = total + (*iter)->getCardRank(true);
        //} else {
            total = total + (*iter)->getCardRank(false);
        //}

    }

    return total;
}

int Player::getFirstCardValue() const {
	// Get the total from the vector of cards
	vector<Card*>::const_iterator iter = this->cardsVector.begin();

	return (*iter)->getCardRank(false);

}

/**
 * isBlackJack()
 * A method to determine whether user has BlackJack or not
 *
 * @return true when the total of card is 21 and number of card is 2
 */
bool Player::isBlackJack() {
    if ((getTotal() == 21) && (getTotalNoOfCards() == 2)) {
    		this->status = Player::WIN;
    		return true;
    }

    return false;
}

/**
 * isBusted()
 * Check whether the user is busted or not
 * @return True when card's total is greater than 21.
 */
bool Player::isBusted() {

	if (getTotal() > 21) {
		this->status = Player::BUSTED;
		return true;
	}

    return false;
}

bool Player::isFirstCardHighCard() const {

	vector<Card*>::const_iterator iter = this->cardsVector.begin();

	if ((*iter)->getCardRank(false) == 10 ||
			(*iter)->getCardRank(false) == 11) {
		return true;
	}

	return false;

}


/**
 * Print user lose message to the console
 */
void Player::lose() {

	this->loseCount++;
    cout << "Player " + this->name + " lose." << endl;

}


void Player::tie() {

	this->tieCount++;
    cout << "Player " + this->name + " tie." << endl;

}

/**
 * Print user winning message to the console
 */
void Player::win() {

	this->winCount++;
    cout << "Player " + this->name + " WIN!!!" << endl;

}

Player::~Player() {
    // TODO Auto-generated destructor stub
}
