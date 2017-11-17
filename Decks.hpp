/*
 * Decks.hpp
 *
 *  Created on: Nov 16, 2017
 *      Author: jayee
 */

#ifndef DECKS_HPP_
#define DECKS_HPP_
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<vector>
#include <ctime>
#pragma once;
#include "Card.hpp"
using namespace std;
class Decks{
private:
	vector <Card> decks;
	int cardIndex;
	int noOfCardsLeft;
	int numDecks;
	int randShuffleNo; //for white card

public:
	Decks();
	Decks(int numDecks = 0);
	void shuffleDecks();
	void fillDecks();
	void giveCard();
	void insertWhiteCard();
	const Card& dealCard();
	int getrandShuffleNo() const{return randShuffleNo;}
	int getnumDecks() const{return numDecks;}
	int getIndex() const{return cardIndex;}
	int getnoOfCardsLeft() const{return noOfCardsLeft;}
	ostream &operator<< (ostream &os, const Decks &deck);
};




#endif /* DECKS_HPP_ */
