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
#include "Dealer.hpp"
#include "Decks.hpp"
#define CONSOLE_WIDTH 100

void printWelcome();
void printUserTable(BlackJackPalyer players[], Dealer dealer, int numOfPlayers);
void printUserCard(vector<Card*> userCards);
void printCard(int count, Card cards[]);
void printMenu();
int printYesOrNo();
void printExit();
void printPlayerStatus(BlackJackPalyer player, int noOfHands);

int main() {
	printWelcome();
	string username;
	cout << "Please enter your username:\n";
	getline(cin, username);
	//getchar();
	//getchar();
	cout << "\nHello " << username << ",Let us start the game.";
	cout << "\nAre you ready?";
	if(printYesOrNo()){
		Dealer dealer("Dealer", true);//TODO: check with Steven
		cout << "\nDealer is shuffling your cards.\n";
		Decks currentDeck;
		currentDeck.shuffle();
		//TODO:check with team:Does the order of giving matter?
		//currentDeck.giveCard(2);
		//TODO: check with Jay, return type Card would be enuf?
		//TODO: where will user sit? order matters?
		//TODO: setter for cards vector?
		BlackJackPalyer player1("Player1", true);
		vector<Card*> player1Cards = currentDeck.giveCard(2);
		player1.addCardToHand(player1Cards.at(0));
		player1.addCardToHand(player1Cards.at(1));
		BlackJackPalyer player2("Player2", true);
		vector<Card*> player2Cards = currentDeck.giveCard(2);
		player2.addCardToHand(player2Cards.at(0));
		player2.addCardToHand(player2Cards.at(1));
		BlackJackPalyer player3("Player3", true);
		vector<Card*> player3Cards = currentDeck.giveCard(2);
		player3.addCardToHand(player3Cards.at(0));
		player3.addCardToHand(player3Cards.at(1));
		BlackJackPalyer player4("Player4", true);
		vector<Card*> player4Cards = currentDeck.giveCard(2);
		player4.addCardToHand(player4Cards.at(0));
		player4.addCardToHand(player4Cards.at(1));
		BlackJackPalyer player5("Player5", true);
		vector<Card*> player5Cards = currentDeck.giveCard(2);
		player5.addCardToHand(player5Cards.at(0));
		player5.addCardToHand(player5Cards.at(1));
		vector<Card*> dealerCards = currentDeck.giveCard(2);
		dealer.addCardToHand(dealerCards.at(0));
		dealer.addCardToHand(dealerCards.at(1));

		BlackJackPalyer players[5] = {player1, player2, player3, player4, player5};
		//TODO: order of giving card should be P1 to P6 to Dealer
		BlackJackPalyer user (username, false);
		cout << "\nHere is the card table.\n";
		vector<Card*> userCards = currentDeck.giveCard(2);
		user.addCardToHand(userCards.at(0));
		user.addCardToHand(userCards.at(1));
		//TODO: check with jay on card printing
		//TODO: check with team how to represent hidden
		//TODO: Case 1: Check if Dealer got an Ace
		bool isUserBust = false;
		bool isExit = false;
		for(;;){
			printUserTable(players, dealer, 5);
			cout << "\n" << username << "\n";
			printUserCard(user.getCardsFromHand());
			cout << "\nTotal : " << user.getTotal() << "\n";
			printMenu();
			char userDecision;
			cin >> userDecision;
				if (userDecision == 'H')
					{
						vector<Card*> userCard = currentDeck.giveCard(1);
						user.addCardToHand(userCard.at(0));
						if(user.isBusted()){
							user.bust();
							isUserBust = true;
						}
					}
				else if (userDecision == 'S')
					{
						vector<Card*> dealerCard = currentDeck.giveCard(1);
						dealer.addCardToHand(dealerCard.at(0));
						if(dealer.isBlackJack()){
							dealer.win();
							isUserBust = true;
						}
					}
				else if (userDecision == 'Q')
					{
						isExit = true;
					}
				else
					{
						cout << "\nSorry, your key is incorrect.\n";
					}
			if(isExit){
				printPlayerStatus(user, 2);
				break;
			}
		}
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

//TODO: Change to a 2D array? Ask for suggestions from team
void printUserTable(BlackJackPalyer players[],
		Dealer dealer, int numOfPlayers){
	cout << "\n-" << setw(47) << setfill('-') << "-" << "-";
	cout << "\n|" << setw(7) << setfill(' ')
			<< "Dealer" << "|" << setw(7) << "Player1"
			<< "|" << setw(7) << "Player2"
			 << "|" << setw(7) << "Player3"
			 << "|" << setw(7) << "Player4"
			 << "|" << setw(7) << "Player5"
			<< setw(1) << "|" ;
	//TODO: change it to max player card size?
	//need a function for it, where? hand or here?
	int size = 2;//players[0].getCardsFromHand().size();
	cout << "\n-" << setw(47) << setfill('-') << "-" << "-";
	for(unsigned k=0; k<size; k++){
		cout << "\n|" ;
		string dealerCard = "";
		//if(k==1){
			//dealerCard = "HIDDEN";//For Hidden second card
		//}else{
			dealerCard = dealer.getCardsFromHand().at(k)->getCardSuite() +
					dealer.getCardsFromHand().at(k)->getCardValue();
		//}
		cout << setw(9) << setfill(' ') << dealerCard;
		cout << "|" << setw(9) <<
			players[0].getCardsFromHand().at(k)->getCardSuite() +
			players[0].getCardsFromHand().at(k)->getCardValue()
			<< "|" << setw(9) <<
			players[1].getCardsFromHand().at(k)->getCardSuite() +
			players[1].getCardsFromHand().at(k)->getCardValue()
			<< "|" << setw(9) <<
			players[2].getCardsFromHand().at(k)->getCardSuite() +
			players[2].getCardsFromHand().at(k)->getCardValue()
			<< "|" << setw(9) <<
			players[3].getCardsFromHand().at(k)->getCardSuite() +
			players[3].getCardsFromHand().at(k)->getCardValue()
			<< "|" << setw(9) <<
			players[4].getCardsFromHand().at(k)->getCardSuite() +
			players[4].getCardsFromHand().at(k)->getCardValue()
			<< setw(1) << "|" ;
	}
	cout << "\n-" << setw(47) << setfill('-') << "-" << "-";
	cout << endl;
}

//TODO: change logic here, remove unnecessary loop
void printUserCard(vector<Card*> userCards){
	int size = userCards.size();
	Card cards[size] = {};
	for(unsigned k=0; k<size; k++){
		Card card (userCards.at(k)->getCardSuite(),
			userCards.at(k)->getCardValue());
		cards[k] = card;
	}
	printCard(size, cards);
}

void printCard(int count, Card cards[]){
		for (int i=0; i< count; ++i){
			cout  << setw(7) << right << setfill('*') << "";
			cout << " ";
		}
		cout << "\n";
		for (int i=0; i< count; ++i){
			if(i!=0){
				cout << " ";
			}
			cout << "|" << setfill(' ');
			cout << setw(6) << setfill(' ') << right <<"|";
		}
		cout << "\n";
		for (int i=0; i< count; ++i){
			if(i!=0){
				cout << " ";
			}
			cout << "|";
			cout << setw(6) << setfill(' ') << left <<
					cards[i].getCardSuite() << cards[i].getCardValue()
					<<right <<"|";
		}
		cout << "\n";
		for (int i=0; i< count; ++i){
			if(i!=0){
				cout << " ";
			}
			cout << "|" << setfill(' ');
			cout << setw(6) << setfill(' ') << right <<"|";
		}
		cout << "\n";
		for (int i=0; i< count; ++i){
			cout  << setw(7) << right << setfill('*') << "";
			cout << " ";
		}
}

void printMenu(){
	cout << "\n\n";
	cout << "Your Options are:\n";
	cout << setw(15) << setfill(' ') << left << "HIT" << right << "STAND";
	cout << setw(15) <<  " " ;
	cout << setw(15) << left << "DOUBLE" << right << "SPLIT";
	cout << "\n\n";
	cout << "Press H to HIT, S to Stand, D to Double and P to Split.\n";
	cout << "Press Q to Quit.\n";
}

int printYesOrNo(){
	cout << "\nPress Y to continue:\n";
	char option;
	option = getchar();
	getchar();//for eclipse
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


void printPlayerStatus(BlackJackPalyer player, int noOfHands){
	//cout << "\n\nTotal hands played : " << noOfHands;
	cout << "\n-" << setw(24) << setfill('-') << "-" << "-";
	cout << "\n|" << setw(7) << setfill(' ')
			<< "WIN" << "|" << setw(7) << "LOSE"
			<< "|" << setw(7) << "TIE"
			<< setw(1) << "|" ;
	//TODO: change it to max player card size?
	//need a function for it, where? hand or here?
	cout << "\n-" << setw(24) << setfill('-') << "-" << "-";
	//for(unsigned k=0; k<noOfHands; k++){
		cout << "\n|" << setw(7) << setfill(' ')
					<< player.getWinCount() << "|"
					<< setw(7) << player.getLoseCount()
					<< "|" << setw(7) << player.getTieCount()
					<< setw(1) << "|" ;
	//}
	cout << "\n-" << setw(24) << setfill('-') << "-" << "-";
	cout << endl;

}
//TODO: Steven: Hand should have player-card mapping?
//Algorithm: 1) Check if dealer have a natural (21) in the first deal.
//I think this function should come in hand.
//int getTotalPoints(vector<Card*> playerCards): Get the playercard vector as input,
//get each card and call getCardRank in Card class and get total

//if dealer have he wins, if any of the player(s) also have, its a tie win between dealer and player(s)
//First if the up-card of dealer is Ace/Ten/J/K/Q, dealer can look whats his hidden card
//2) User decides Stand/Hit
//3) check if busted (above 21?)
//What is soft hand? Combination of Ace and another card(s) making a total of 17.

//Algorithm for Dealer:
//if total is 16 or under, hit, else 17 or more, stand (Doubt: Dealer must take Ace as 11 in all cases?)
