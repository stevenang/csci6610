//============================================================================
// Name        : CardGame.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "Card.hpp"
#include "Player.hpp"
#include "BlackJackPalyer.hpp"

#define CONSOLE_WIDTH 100

void printWelcome();
void printUserTable(BlackJackPalyer players[], int numOfPlayers);
void printUserCard();
void printCard(int count, Card cards[]);
void printMenu();
int printYesOrNo();
void printExit();

int main() {
	printWelcome();
	string username;
	cout << "Please enter your username:\n";
	getline(cin, username);
	cout << "Hello " << username << ",Let us start the game.\n";
	cout << "Are you game?\n";
	if(printYesOrNo()){
		BlackJackPalyer player1("Player1", true);
		BlackJackPalyer player2("Player2", true);
		BlackJackPalyer player3("Player3", true);
		BlackJackPalyer player4("Player4", true);
		BlackJackPalyer players[5] = {player1, player2, player3, player4};
		BlackJackPalyer user (username, false);
		printUserTable(players, 4);
		printUserCard();
		printMenu();
	}
	printExit();
	return 0;
}

void printWelcome(){
	cout << setw(CONSOLE_WIDTH) << setfill('*') << " " << endl;
	cout << setw(CONSOLE_WIDTH / 2) << setfill(' ')
			<< "Welcome to Blackjack 21 Game" << endl;
	cout << setw(CONSOLE_WIDTH) << setfill('-') << " " << endl;
	cout << setw(CONSOLE_WIDTH) << setfill(' ') << left << "Rules:" << endl;
	cout << setw(CONSOLE_WIDTH) << left << "You will be playing against 5 players." << endl;
	cout << setw(CONSOLE_WIDTH) << left << "You may do card counting using HiLo "
			"strategy." << endl;
	cout << setw(CONSOLE_WIDTH) << left << "The app will check your strategy through "
			"signals." << endl;
	cout << setw(CONSOLE_WIDTH) << setfill('*') << " " << endl;
}

void printUserTable(BlackJackPalyer players[], int numOfPlayers){
	cout << "\n|" << setw(39) << setfill('-') << "-" << "|";
		cout << "\n|" << setw(7) << setfill(' ')
				<< "Dealer" << "|" << setw(7) << "Player1"
				<< "|" << setw(7) << "Player2"
				 << "|" << setw(7) << "Player3"
				 << "|" << setw(7) << "Player4"
				<< setw(1) << "|" ;
		cout << "\n|" << setw(39) << setfill('-') << "-" << "|";
		for(int i = 0; i < 3; ++i){
			Card card1 (DIAMOND, KING);
			cout << "\n|" << setw(7) << setfill(' ')
							<< card1.getCardSuite() + card1.getCardValue()
							<< "|" << setw(7) <<
							card1.getCardSuite() + card1.getCardValue()
							<< "|" << setw(7) <<
							card1.getCardSuite() + card1.getCardValue()
							 << "|" << setw(7) <<
							 card1.getCardSuite() + card1.getCardValue()
							 << "|" << setw(7) <<
							 card1.getCardSuite() + card1.getCardValue()
							<< setw(1) << "|" ;
		}
		cout << "\n|" << setw(39) << setfill('-') << "-" << "|";
		cout << endl;
}

void printUserCard(){
	Card card1 {SPADE, ACE};
	Card card2 {SPADE, ACE};
	Card cards[21] = {card1, card2, card1, card2, card1, card2, card1, card2, card1, card2,
			card1, card2, card1, card2, card1, card2, card1, card2, card1, card2,
			card2};
	printCard(21, cards);
}

void printCard(int count, Card cards[]){
		for (int i=0; i< count; ++i){
			cout  << setw(6) << right << setfill('*') << " " ;
		}
		cout << "\n";
		for (int i=0; i< count; ++i){
			cout << "|" << setfill(' ');
			cout << setw(5) << setfill(' ') << right <<"|";
		}
		cout << "\n";
		for (int i=0; i< count; ++i){
			cout << "|";
			cout << setw(5) << setfill(' ') <<
					cards[i].getCardSuite() << cards[i].getCardValue()
					<<right <<"|";
		}
		cout << "\n";
		for (int i=0; i< count; ++i){
			cout << "|" << setfill(' ');
			cout << setw(5) << setfill(' ') << right <<"|";
		}
		cout << "\n";
		for (int i=0; i< count; ++i){
			cout  << setw(6) << right << setfill('*') << " " ;
		}
}

void printMenu(){
	cout << "\n\n";
	cout << setw(20) << setfill(' ') << left << "HIT" << right << "STAND";
	cout << setw(20) <<  " " ;
	cout << setw(20) << left << "DOUBLE" << right << "SPLIT";
	cout << "\n\n";
	cout << "Press H to HIT, S to Stand, D to Double and P to Split." << endl;
}

int printYesOrNo(){
	cout << "\nPress Y to continue:\n";
	char option;
	cin >> option;
	if(tolower(option) == 'y'){
		return 1;
	}else{
		return 0;
	}
}

void printExit(){
	cout << "\n";
	cout << setw(CONSOLE_WIDTH) << setfill('*') << "" << endl;
	cout << setw(CONSOLE_WIDTH / 2) << setfill(' ')
			<< "Thankyou for playing Blackjack 21 Game with us. See you again!"
			<< endl;
	cout << setw(CONSOLE_WIDTH) << setfill('*') << "" << endl;
}
