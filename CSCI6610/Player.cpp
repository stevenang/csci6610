/*==============================================================================
 *                                                                    Player.cpp
 * Author      : Steven Kho Ang
 * Version     : 1.0
 * Created     : Created on November 17, 2017
 * Last Update:  Last Update on December 03, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is an implementation of the Player.hpp
 * Also a super class of BlackJackPlayer and Dealer
 *
 * Player()                     Default Constructor
 * Player(const string& name,   Constructor
 *          bool isComputer)
 * allCardToString(bool dealer) String representation of user hand's card
 * bust()                       Print out "Busted" message
 * getTotal()                   Get the total value of hand
 * getFirstCardValue()          Return the value of the first card of hand
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
 */
int Player::getTotal() const {

    int total = 0;

    // Get the total from the vector of cards
    vector<Card*>::const_iterator iter;
    int hard = 0;
    int soft = 0;

    for (iter = this->cardsVector.begin(); iter < this->cardsVector.end();
         ++ iter) {
    		soft = soft + (*iter)->getCardRank(false);
    }

    for (iter = this->cardsVector.begin(); iter < this->cardsVector.end();
             ++ iter) {
        	hard = hard + (*iter)->getCardRank(true);
    }

    if (soft == 21 || hard == 21) {
    		total = 21;
    } else if (soft <= hard) {
    		total = soft;
    } else {
    		total = hard;
    }

    return total;
}

/**
 * For Dealer use's only
 * This will return a first card of the hand.
 */
int Player::getFirstCardValue() const {
	// Get the total from the vector of cards
	vector<Card*>::const_iterator iter = this->cardsVector.begin();

	return (*iter)->getCardRank(false);

}

/**
 * A method to determine whether user has BlackJack or not
 * @return true when the total of card is 21 and number of card is 21
 */
bool Player::isBlackJack() {
    if ((getTotal() == 21) && (getTotalNoOfCards() == 2)) {
    		this->status = Player::WIN;
    		return true;
    }

    return false;
}

/**
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

/**
 * For Dealer used only
 * To check whether first card in hand is high card or not.
 */
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

/**
 * Print user is tie's message
 */
void Player::tie() {

	this->tieCount++;
    cout << "Player " + this->name + " tie." << endl;

}

/**
 * Print user winning message to the console
 */
void Player::win() {
	this->winCount++;
	this->status = Player::WIN;
    cout << "Player " + this->name + " WIN!!!" << endl;

}

/**
 * Default deconstructor.
 */
Player::~Player() {
    // TODO Auto-generated destructor stub
}
