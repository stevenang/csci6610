/*============================================================================
 *Name        : Decks.hpp
 *Project	  : Final Project Blackjack 21 console game
 *Author      : Jayeeta Banerjee
 *Version     : Created on 11/18/2017
 *Copyright   : Prohobited
 *Description : Class representing decks of cards in blackjack game using
                vector of deck.
=============================================================================
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

/*Creating a class of Decks. It has private vectors 'deck_list' and 'all_deck'.
 * 'deck_list' represents the vector of Deck. 'all_deck' represents vector of
 * Card. It has two private integer variable 'white_magic' and 'totalCard'.
 * Public methods are 'fillDecks()', 'shuffle()', clearDecks(), giveCard(),
 * 'getAllDeckCards()', 'updateAllDeckCards()', 'printAllDeckCards()',
 * 'generateWhiteMagicNumber()', 'getHighCardPercentage()', 'askQuestion()',
 * 'showMenuItems()'.
 */

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
