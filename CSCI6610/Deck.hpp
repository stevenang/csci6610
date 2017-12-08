/*============================================================================
 *Name        : Deck.hpp
 *Project	  : Final Project Blackjack 21 console game
 *Author      : Jayeeta Banerjee
 *Version     : Created on 11/18/2017
 *Copyright   : Prohobited
 *Description : Class representing a single deck of card in blackjack game using
                vector of card.
=============================================================================
*/

#ifndef DECK_HPP_
#define DECK_HPP_

#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<vector>
#include <ctime>
#pragma once
#include "Card.hpp"
using namespace std;
/*creating a class of 'Deck'. It will use 'Card.hpp' to fill the deck. Created
 * one private variable vector 'm_deck' and public functions 'fillDeck()',
 * 'clearDeck()', 'printDeck()' and 'getDeck()'.
 */

class Deck {
private:
	vector<Card*> m_deck;

public:
	Deck();

	void fillDeck(); // to fill this deck with cards
	void clearDeck();
	void printDeck();
	vector<Card*> getDeck(); //to use this deck
};

#endif /* DECK_HPP_ */
