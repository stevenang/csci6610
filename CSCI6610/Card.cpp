//============================================================================
// Name        : Card.cpp
// Project	   : Final Project Blackjack 21 Game App
// Author      : Parvathy Mohan
// Version     : Created on 11/15/2017
// Copyright   : This program can only be used for project grading purpose
// Description : Source implementation for a Card
//============================================================================
//#pragma once
#include "Card.hpp"

const char* cardSuites[4] = {"Spade", "Club", "Heart", "Diamond"};
constexpr char cardValues[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T',
		'A', 'J', 'Q', 'K'};

/*
 *Default no-arg constructor for Card
 *Input : None
 */
Card::Card(){
	cardSuit = "";
	cardValue = '\0';
}

/*
 * Constructor for Card with arguments
 * Input: cardSuit, cardValue
 */
Card::Card(SUIT_TYPE cardSuit, CARD_VALUE cardValue){
	this->cardSuit = cardSuites[cardSuit];
	this->cardValue = cardValues[cardValue];
}

/*
 * Returns the rank/point of each card value
 * Input: bool isAceSpCase (if not special case, Ace will return a value of 11
 * if special case, Ace will return 1
 * Output: int (Values corresponding to each card value.
 * Ex: For card K, it return rank 10
 */
int Card::getCardRank(bool isAceSpCase) const{
	switch(cardValue){
		case cardValues[TWO]:
			return 2;
		case cardValues[THREE]:
			return 3;
		case cardValues[FOUR]:
			return 4;
		case cardValues[FIVE]:
			return 5;
		case cardValues[SIX]:
			return 6;
		case cardValues[SEVEN]:
			return 7;
		case cardValues[EIGHT]:
			return 8;
		case cardValues[NINE]:
			return 9;
		case cardValues[TEN]:
			return 10;
		case cardValues[ACE]:
			if(isAceSpCase){
				return 1;
			}else{
				return 11;
			}
		case cardValues[JACK]:
			return 10;
		case cardValues[QUEEN]:
			return 10;
		case cardValues[KING]:
			return 10;
		default:
			return 0;
	}
}
/*
 * Print the card suit and value of the card
 * in the form of a card.
 * Input: None
 * Output: None
 */
void Card::printCard() const{
	cout << "\n|" << setw(75) << setfill('-') << "|";
	cout << "" << setw(50) << setfill('-') << endl;
	cout << "|";
	cout << "" << setw(48) << setfill('-') << " " ;
	cout << "|";
}
/*
 * Prints the card detail as a string
 * Input: None
 * Output: None
 */
void Card::toString() const{
	cout << "\n" << cardSuit << cardValue;
}

/*
 * Get the value of card for card counting
 * Input: None
 * Output: int (value would be 0, 1 or -1)
 */
int Card::getHiLoValue() const{
	int value = cardValue - '0';
	if(value >=2 && value <= 6){
		return +1;
	}else if(value >=7 && value <= 9){
		return 0;
	}else{
		return -1;
	}
}
