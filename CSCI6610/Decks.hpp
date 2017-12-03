/*
 * Decks.hpp
 *
 *  Created on: Nov 18, 2017
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
#include <utility>      // std::swap
#pragma once
#include "Deck.hpp"
using namespace std;

class Decks {
private:
	vector<Deck*> deck_list;
	vector<Card*> all_deck;
	int white_magic;
	int totalCard;

public:
	Decks();

	void fillDecks();
	void shuffle();
	void clearDecks();
	vector<Card*> giveCard(int numberOfCards);
	vector<Card*> getAllDeckCards();
	void updateAllDeckCards();
	void printAllDeckCards();
	void generateWhiteMagicNumber();
	string getHighCardPercentage();
	void askQuestion();
	string showMenuItems();
};

#endif /* DECKS_HPP_ */
