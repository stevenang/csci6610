/*
 * Deck.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: jayee
 */

#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<vector>
#include <ctime>
#pragma once;
#include "Deck.hpp"
#include "Card.hpp"


Deck::Deck() {
//Initialize the deck:
	fillDeck();
	//printDeck();
}

void Deck::fillDeck() {

	for (int n = 1; n <= 4; ++n) {
		SUIT_TYPE type;
		CARD_VALUE c;
		switch (n) {
		case 1:
			type = SUIT_TYPE::CLUB;
			break;
		case 2:
			type = SUIT_TYPE::HEART;
			break;
		case 3:
			type = SUIT_TYPE::SPADE;
			break;
		case 4:
			type = SUIT_TYPE::DIAMOND;
			break;
		}

		for (int i = 1; i <= 13; ++i) {
			switch (i) {
			case 1:
				c = CARD_VALUE::ACE;
				break;
			case 2:
				c = CARD_VALUE::TWO;
				break;
			case 3:
				c = CARD_VALUE::THREE;
				break;
			case 4:
				c = CARD_VALUE::FOUR;
				break;
			case 5:
				c = CARD_VALUE::FIVE;
				break;
			case 6:
				c = CARD_VALUE::SIX;
				break;
			case 7:
				c = CARD_VALUE::SEVEN;
				break;
			case 8:
				c = CARD_VALUE::EIGHT;
				break;
			case 9:
				c = CARD_VALUE::NINE;
				break;
			case 10:
				c = CARD_VALUE::TEN;
				break;
			case 11:
				c = CARD_VALUE::JACK;
				break;
			case 12:
				c = CARD_VALUE::QUEEN;
				break;
			case 13:
				c= CARD_VALUE::KING;
				break;
			}

			m_deck.push_back(new Card(type, c));
		}
	}

}

void Deck::printDeck(){
		cout<<"Total Deck Size:-"<<m_deck.size()<<endl;

		for (unsigned i=0; i<m_deck.size(); i++){
			cout << ' ' << m_deck.at(i)->getCardSuite()<<"--"<< m_deck.at(i)->getCardValue();
			cout << '\n';
		}
}

vector<Card*> Deck::getDeck(){
	return m_deck;
}

