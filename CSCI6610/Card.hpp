//============================================================================
// Name        : Card.hpp
// Project	   : Final Project Blackjack 21 Game App
// Author      : Parvathy Mohan
// Version     : Created on 11/14/2017
// Copyright   : This program can only be used for project grading purpose
// Description : Class representing a card in the game.
//============================================================================

#ifndef CARD_HPP_
#define CARD_HPP_

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum SUIT_TYPE {SPADE, CLUB, HEART, DIAMOND};
enum CARD_VALUE {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ACE,
	JACK, QUEEN, KING
};

class Card{
private:
	string cardSuit;
	char cardValue;
public:
	//Constructor with no arguments
	Card();
	//Constructor with arguments
	Card(SUIT_TYPE cardSuit, CARD_VALUE cardValue);
	//constructor with string card suit and char card value
	Card(string cardSuit, char cardValue);
	//get card suite
	string getCardSuite() const {return cardSuit;}
	//get card value
	char getCardValue() const {return cardValue;}
	//get card score/rank
	int getCardRank(bool isAceSpCase) const;
	//print card format
	void printCard() const;
	//returns card suit and value
	string toString() const;
};
#endif /* CARD_HPP_ */
