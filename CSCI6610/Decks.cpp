/*
 * Decks.cpp
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
#include <utility>      // std::swap
#pragma once;
#include "Decks.hpp"
using namespace std;

Decks::Decks() {
//Initialize the deck:
	fillDecks();

}

void Decks::fillDecks() {
	for(int i=0;i<6;i++){
		deck_list.push_back(new Deck());
	}
	updateAllDeckCards();
}

void Decks::shuffle(){

	srand ( unsigned ( std::time(0) ) );

	int n = (all_deck.end()-all_deck.begin());
	for (unsigned i=n-1; i>0; --i) {
		swap (all_deck.begin()[i],all_deck.begin()[(rand()%i)+1]);
	}

	generateWhiteMagicNumber(); //After shuffle generate magic number for future shuffle

	cout<<"******************* AFTER shuffle:-********************************************************"<<endl;
	printAllDeckCards();
}

vector<Card*> Decks::getAllDeckCards(){

	return all_deck;
}

void Decks::updateAllDeckCards(){

	for(unsigned i=0;i<deck_list.size();i++){

			vector<Card*> n_deck= deck_list.at(i)->getDeck();

			for(unsigned j=0;j<n_deck.size();j++){
				//cout << ' ' << n_deck.at(j)->getCardSuite()<<"--"<< n_deck.at(j)->getCardValue();
				//cout << '\n';
				all_deck.push_back(n_deck.at(j));
			}
		}
}

vector<Card*> Decks::giveCard(int numberOfCards){

 vector<Card*> cards;
 cout<<"numberOfCards to give:-"<<numberOfCards<<endl;
 int range = (all_deck.size()-numberOfCards);
 for(int i = all_deck.size()-1;i>=range;i--){
	 if(i == white_magic) shuffle();
	 cards.push_back(all_deck.at(i));
	 all_deck.erase(all_deck.end() - 1);
 }

 cout<<"Given to player cards:-\n";
 for(unsigned n=0;n<cards.size();n++){
 	 cout<<""<<cards.at(n)->getCardSuite()<<"--"<<cards.at(n)->getCardValue()<<endl;
  }

 return cards;

}

void Decks::printAllDeckCards(){

	cout<<"All Decks cards size:-"<<all_deck.size()<<endl;

	for (unsigned k=0; k<all_deck.size(); k++) {
			cout << ' ' << all_deck.at(k)->getCardSuite() << "--"<< all_deck.at(k)->getCardValue();
			cout << '\n';
		}
}

void Decks::generateWhiteMagicNumber(){
	white_magic = rand()%all_deck.size() - 1;
	cout<<white_magic<<endl;
}
