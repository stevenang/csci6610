/*============================================================================
 *Name        : Deck.cpp
 *Project	  : Final Project Blackjack 21 console game
 *Author      : Jayeeta Banerjee
 *Version     : Created on 11/18/2017
 *Copyright   : Prohobited
 *Description : It introduces the implementation of all methods from the class
                of deck.
 *=============================================================================
*/

#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<vector>
#include <ctime>
#include "Deck.hpp"
#include "Card.hpp"

//-----------------------------------------------------------------------------
//this method will call method 'fillDeck()' to create a deck
Deck::Deck()
{
//Initialize the deck:
	fillDeck();
	//printDeck(); // for testing the whole deck of 52 cards.
}

/*------------------------------------------------------------------------------
 * The method is used to fill the deck. It is generating four suit types and
 * 13 card values. Using 'push_back' and 'new' the deck is being filled with
 * 13*4 = 52 cards. 'switch case' is used for suite type and card values.
  */

void Deck::fillDeck()
{

	for (int n = 1; n <= 4; ++n) // for loop for 4 types of card
	{
		SUIT_TYPE type;
		CARD_VALUE c;
		switch (n)
		{
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

		for (int i = 1; i <= 13; ++i) //for loop on card values
		{
			switch (i)
			{
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

/*-----------------------------------------------------------------------------
 * Method 'printDeck()' to print the whole deck of cards. It is needed for
 * testing purpose. It is iterating through the whole deck and print the card
 * value and card suite.
 */
void Deck::printDeck()
{
		cout<<"Total Deck Size:-"<<m_deck.size()<<endl;

		for (unsigned i=0; i<m_deck.size(); i++)
		{
			cout << ' ' << m_deck.at(i)->getCardSuite()<<"--"<<
					m_deck.at(i)->getCardValue();
			cout << '\n';
		}
}

/*------------------------------------------------------------------------------
*This method to clear the deck if needed.It will call 'fillDeck()' again to fill
*the deck. 'clear()' is used to clean vector.
*/
void Deck::clearDeck()
{
	m_deck.clear();
	fillDeck();

	}

/*------------------------------------------------------------------------------
 * Method 'getDeck()' to return the whole vector of deck while calling
 */

vector<Card*> Deck::getDeck()
{
	return m_deck;
}

