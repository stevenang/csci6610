/*
 * Deck.hpp
 *
 *  Created on: Nov 18, 2017
 *      Author: jayee
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


class Deck {
private:
	vector<Card*> m_deck;

public:
	Deck();

	void fillDeck();
	void clearDeck();
	void printDeck();
	vector<Card*> getDeck();
};

#endif /* DECK_HPP_ */
