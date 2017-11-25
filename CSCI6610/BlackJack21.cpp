//============================================================================
// Name        : BlackJack21.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "Card.hpp"
#include "Player.hpp"
#include "BlackJackPlayer.hpp"
#include "Dealer.hpp"
#include "Decks.hpp"
#define CONSOLE_WIDTH 100

const char* statuses[5] = {"NOT_STARTED", "HITTING", "STANDING", "BUSTED", "SURRENDER"};//"WIN", "LOSE", "TIE"};


void printWelcome();
void printUserTable(BlackJackPlayer players[], Dealer dealer, int numOfPlayers, bool isHiddenCard);
//void printUserCard(vector<Card*> userCards);
void printCard(vector<Card*> cards);
void printMenu(string username);
int printYesOrNo();
void printExit();
//void printPlayerStatus(BlackJackPlayer player, int noOfHands);
int getNumOfRounds(BlackJackPlayer players[], int numOfPlayers, Dealer dealer);
void serveCards(BlackJackPlayer players[], BlackJackPlayer* user, Dealer* dealer, Decks* currentDeck, int numOfCards);
void printHandDetails(BlackJackPlayer players[], int numOfPlayers, Dealer dealer, BlackJackPlayer user, bool isHiddenCard);
void playComputerUsers(BlackJackPlayer players[], int numOfPlayers, Dealer dealer, Decks* currentDeck);
void playComputerUser(BlackJackPlayer* player, Dealer* dealer, Decks* currentDeck);
void playDealer(Decks* currentDeck, Dealer* dealer, BlackJackPlayer players[], int numOfPlayers, BlackJackPlayer* user);
void printRoundStatus(BlackJackPlayer players[], int numOfPlayers,
		Dealer dealer, BlackJackPlayer user);
void findWinner(Dealer* dealer, BlackJackPlayer players[], int numOfPlayers, BlackJackPlayer* user);

int main() {
	setbuf(stdout, NULL);
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
		BlackJackPlayer player1("Player1", true);
		BlackJackPlayer player2("Player2", true);
		BlackJackPlayer player3("Player3", true);
		BlackJackPlayer player4("Player4", true);
		BlackJackPlayer player5("Player5", true);
		BlackJackPlayer user (username, false);
		BlackJackPlayer players[5] = {player1, player2, player3, player4, player5};
		cout << "\nDealer is shuffling your cards.\n";
		Decks currentDeck;
		currentDeck.shuffle();
		//TODO:check with team:Does the order of giving matter?
		//currentDeck.giveCard(2);
		//TODO: check with Jay, return type Card would be enuf?
		//TODO: where will user sit? order matters?
		//TODO: setter for cards vector?
		serveCards(players, &user, &dealer, &currentDeck, 2);
		//TODO: order of giving card should be P1 to P6 to Dealer
		cout << "\nHere is the card table.\n";
		//TODO: check with jay on card printing
		//TODO: check with team how to represent hidden
		//TODO: Case 1: Check if Dealer got an Ace
		bool isHiddenCard = true;
		printHandDetails(players, 5, dealer, user, isHiddenCard);

		for(;;){
			bool isNextRound = false;
			bool isExit = false;
			bool isPlayRound = false;
			bool isDealerRound = false;
			bool isUserStand = false;
			if(dealer.isFirstCardHighCard()){
				cout << "\nDealer got " << dealer.getCardsFromHand().at(0)->getCardSuite()
						<< dealer.getCardsFromHand().at(0)->getCardValue()
						<< " as the face up card.\n";
				cout << "\nDealer is going to open the face down card.\n";
				isHiddenCard = false;
				cout << "\nThe face down card is "
						<<  dealer.getCardsFromHand().at(1)->getCardSuite()
						<< dealer.getCardsFromHand().at(1)->getCardValue()
						<<".\n";
				cout << "\nChecking if the dealer got a natural blackjack.\n"
						<< " " << dealer.isBlackJack();
				if(dealer.isBlackJack()){
					string tie_players = "";
					for(int i=0; i<5; ++i){
						if(players[i].isBlackJack()){//TODO:Steven check
							//players[i].tie();
							tie_players += players[i].getName() + ",";
						}
					}
					if(user.isBlackJack()){
						tie_players += user.getName() + ",";
					}
					if(tie_players == ""){
						dealer.win();
						for(int i=0; i<5; ++i){
							players[i].lose();
						}
						user.lose();
					}else{
						cout << "\nIt is a tie between "
							 << tie_players << " and Dealer.\n";
					}
					isNextRound = true;
				}else{
					cout << "\nDealer did not get a natural blackjack.\n";
					//TODO: Order - check with team
					playComputerUsers(players, 5, dealer, &currentDeck);
					isDealerRound = true;
					isPlayRound = true;
				}
			}else{
				isPlayRound = true;
			}

			if(isPlayRound){
				playComputerUsers(players, 5, dealer, &currentDeck);
				isDealerRound = true;
				//TODO: Order check
				printMenu(user.getName());
				char userDecision;
				cin >> userDecision;
				if (userDecision == 'H')
					{
						vector<Card*> userCard = currentDeck.giveCard(1);
						user.addCardToHand(userCard.at(0));
						if(user.isBusted()){
							printHandDetails(players, 5, dealer, user, isHiddenCard);
							user.bust();
							isNextRound = true;
						}
					}
				else if (userDecision == 'S')
					{
						isUserStand = true;
					}
				else if (userDecision == 'Q')
					{
						isExit = true;
					}
				else
					{
						cout << "\nSorry, your key is incorrect.\n";
					}
			}
			if(isDealerRound){
				//dealerPlay
				playDealer(&currentDeck, &dealer, players, 5, &user);
				isNextRound = true;
			}
			if(isExit){
				cout << user.getStatistic();//TODO: Steven check : change the content to table
				break;
			}else if(isNextRound){
				printRoundStatus(players, 5, dealer, user);
				cout << "\nPress Y to continue playing.\n";
				char choice;
				cin >> choice;
				if(tolower(choice) == 'y'){
					for(int i=0; i<5; ++i){
						players[i].clearHands();
					}
					dealer.clearHands();
					user.clearHands();
					serveCards(players, &user, &dealer, &currentDeck, 2);
					printHandDetails(players, 5, dealer, user, isHiddenCard);
				}else{
					cout << user.getStatistic();//TODO:Steven check
					break;
				}
			}else{
				printHandDetails(players, 5, dealer, user, isHiddenCard);
			}
		}
	}
	printExit();
	return 0;
}

void printHandDetails(BlackJackPlayer players[], int numOfPlayers, Dealer dealer, BlackJackPlayer user, bool isHiddenCard){
	printUserTable(players, dealer, numOfPlayers, isHiddenCard);
	cout << "\n" << user.getName() << "\n";
	//printUserCard(user.getCardsFromHand());
	printCard(user.getCardsFromHand());
	cout << "\nTotal : " << user.getTotal() << "\n";
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

int getNumOfRounds(BlackJackPlayer players[], int numOfPlayers, Dealer dealer){

	int rounds = 2;
	for(int i=0; i<numOfPlayers; ++i){
		int currentSize = players[i].getCardsFromHand().size();
		if(currentSize > rounds){
			rounds = currentSize;
		}
	}
	int dealerCardSize = dealer.getCardsFromHand().size();
	return rounds > dealerCardSize ? rounds : dealerCardSize;
}

//TODO: Change to a 2D array? Ask for suggestions from team
void printUserTable(BlackJackPlayer players[],
		Dealer dealer, int numOfPlayers, bool isHiddenCard){
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
	int size = getNumOfRounds(players, numOfPlayers, dealer);
	cout << "\n-" << setw(47) << setfill('-') << "-" << "-";
	//TODO: Will the player count be always 5?
	int player1Size = players[0].getCardsFromHand().size();
	int player2Size = players[1].getCardsFromHand().size();
	int player3Size = players[2].getCardsFromHand().size();
	int player4Size = players[3].getCardsFromHand().size();
	int player5Size = players[4].getCardsFromHand().size();
	int dealerSize = dealer.getCardsFromHand().size();
	for(unsigned k=0; k<size; k++){
		cout << "\n|" ;
		string dealerCard, player1Card, player2Card, player3Card, player4Card, player5Card;
		if(k==1 && isHiddenCard){
			dealerCard = "--";//For Hidden second card
		}else if(k < dealerSize){
			dealerCard = dealer.getCardsFromHand().at(k)->getCardSuite() +
					dealer.getCardsFromHand().at(k)->getCardValue();
		}else{
			dealerCard = "";
		}
		if(k >= player1Size){
			player1Card = "";
		}else{
			player1Card = players[0].getCardsFromHand().at(k)->getCardSuite() +
						players[0].getCardsFromHand().at(k)->getCardValue();
		}
		if(k >= player2Size){
			player2Card = "";
		}else{
			player2Card = players[1].getCardsFromHand().at(k)->getCardSuite() +
						players[1].getCardsFromHand().at(k)->getCardValue();
		}
		if(k >= player3Size){
			player3Card = "";
		}else{
			player3Card = players[2].getCardsFromHand().at(k)->getCardSuite() +
						players[2].getCardsFromHand().at(k)->getCardValue();
		}
		if(k >= player4Size){
			player4Card = "";
		}else{
			player4Card = players[3].getCardsFromHand().at(k)->getCardSuite() +
						players[3].getCardsFromHand().at(k)->getCardValue();
		}
		if(k >= player5Size){
			player5Card = "";
		}else{
			player5Card = players[4].getCardsFromHand().at(k)->getCardSuite() +
						players[4].getCardsFromHand().at(k)->getCardValue();
		}
		cout << setw(9) << setfill(' ') << dealerCard;
		cout << "|" << setw(9) <<
			player1Card
			<< "|" << setw(9) <<
			player2Card
			<< "|" << setw(9) <<
			player3Card
			<< "|" << setw(9) <<
			player4Card
			<< "|" << setw(9) <<
			player5Card
			<< setw(1) << "|" ;
	}
	cout << "\n-" << setw(47) << setfill('-') << "-" << "-";
	cout << endl;
}

//TODO: change logic here, remove unnecessary loop
/*void printUserCard(vector<Card*> userCards){
	int size = userCards.size();
	vector<Card> cards[size] = {};
	for(unsigned k=0; k<size; k++){
		Card card (userCards.at(k)->getCardSuite(),
			userCards.at(k)->getCardValue());
		cards[k] = card;
	}
	printCard(size, cards);
}*/

void printCard(vector<Card*> cards){
		int count = cards.size();
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
					cards.at(i)->getCardSuite() << cards.at(i)->getCardValue()
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

void printMenu(string username){
	cout << "\n\n" << username << ", it is your turn.";
	cout << "\n\n";
	cout << "Your Options are:\n";
	cout << setw(15) << setfill(' ') << left << "HIT" << right << "STAND";
	cout << setw(15) <<  " " ;
	cout << setw(7) << right << "SPLIT";
	cout << "\n\n";
	cout << "Press H to HIT, S to Stand and P to Split.\n";
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


/*void printPlayerStatus(BlackJackPlayer player, int noOfHands){
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

}*/
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

void serveCards(BlackJackPlayer players[], BlackJackPlayer* user, Dealer* dealer, Decks* currentDeck, int numOfCards){

	BlackJackPlayer* player1;
	player1 = &players[0];
	BlackJackPlayer* player2;
	player2 = &players[1];
	BlackJackPlayer* player3;
	player3 = &players[2];
	BlackJackPlayer* player4;
	player4 = &players[3];
	BlackJackPlayer* player5;
	player5 = &players[4];

	for(int i=0; i< numOfCards; ++i){
		vector<Card*> player1Cards = currentDeck->giveCard(1);
		player1->addCardToHand(player1Cards.at(0));
		vector<Card*> player2Cards = currentDeck->giveCard(1);
		player2->addCardToHand(player2Cards.at(0));
		vector<Card*> player3Cards = currentDeck->giveCard(1);
		player3->addCardToHand(player3Cards.at(0));
		vector<Card*> player4Cards = currentDeck->giveCard(1);
		player4->addCardToHand(player4Cards.at(0));
		vector<Card*> player5Cards = currentDeck->giveCard(1);
		player5->addCardToHand(player5Cards.at(0));
		vector<Card*> userCards = currentDeck->giveCard(1);
		user->addCardToHand(userCards.at(0));
		vector<Card*> dealerCards = currentDeck->giveCard(1);
		dealer->addCardToHand(dealerCards.at(0));
	}
}

void playComputerUsers(BlackJackPlayer players[], int numOfPlayers, Dealer dealer, Decks* currentDeck){

	for(int i=0; i<numOfPlayers; ++i){
		BlackJackPlayer* player;
		player = &players[i];
		playComputerUser(player, &dealer, currentDeck);
	}
}

void playComputerUser(BlackJackPlayer* player, Dealer* dealer, Decks* currentDeck){
	while(player->getStatus() != BlackJackPlayer::BUSTED &&
			player->getStatus() != BlackJackPlayer::STANDING){
			if(player->isHitting(dealer->getCardsFromHand().at(0)->getCardRank(false))){
				cout << "\n" << player->getName() << " decided to HIT.\n";
				vector<Card*> cards = currentDeck->giveCard(1);
				player->addCardToHand(cards.at(0));
				cout << "\n" << player->getName() << " was served card "
						<< cards.at(0)->getCardSuite() << cards.at(0)->getCardValue()
						<< "\n";
				if(player->isBusted()){
					player->bust();
				}else if(player->getTotal() == 21){
					player->win();
				}
			}else if(player->isStanding(dealer->getCardsFromHand().at(0)->getCardRank(false))){
				cout << "\n" << player->getName() << " decided to STAND.\n";
			}
		}
}

//TODO: Steven: 2 functions? isBlackJack and isNaturalBlackjack?

void playDealer(Decks* currentDeck, Dealer* dealer, BlackJackPlayer players[], int numOfPlayers, BlackJackPlayer* user){
	cout << "\nDealer have a total of " << (dealer->getTotal() < 17) << "\n";
	while(dealer->getTotal() < 17){
		cout << "\nDealer have a total of " << dealer->getTotal() << "\n";
		cout << "\nTaking next card from the deck.\n";
		vector<Card*> dealerCard = currentDeck->giveCard(1);
		dealer->addCardToHand(dealerCard.at(0));
		cout << "\nDealer got " << dealerCard.at(0)->getCardSuite()
		<< dealerCard.at(0)->getCardValue()<< ".\n";
		if(dealer->getTotal() > 21){
			dealer->win();
			for(int i=0; i<numOfPlayers;++i){
				if(players[i].getStatus() == BlackJackPlayer::STANDING){
					players[i].lose();
				}
			}
			if(user->getStatus() == BlackJackPlayer::STANDING){
				user->lose();
			}
		}else if(dealer->isBusted()){
			dealer->bust();
		}else if(dealer->getTotal() >= 17){
			cout << "\nDealer have a total of " << dealer->getTotal() << "\n";
			cout << "\nDealer will STAND.\n";
			findWinner(dealer, players, numOfPlayers, user);
		}
	}
}

void findWinner(Dealer* dealer, BlackJackPlayer players[], int numOfPlayers, BlackJackPlayer* user){
	Player* allPlayers[numOfPlayers+2];
	int i = 0;
	for(i=0; i < numOfPlayers; ++i){
		allPlayers[i] = &players[i];
	}
	allPlayers[++i] = user;
	allPlayers[++i] = dealer;
	int highestRank = 0;
	int winner;
	for(int i=0; i<numOfPlayers; ++i){
		if(allPlayers[i]->getTotal() > highestRank){
			winner = i;
		}
	}
	for(int i=0; i<numOfPlayers; ++i){
		if(i==winner){
		//	allPlayers[i]->win();
		}else{
		//	allPlayers[i]->lose();
		}
	}
}

void printRoundStatus(BlackJackPlayer players[], int numOfPlayers,
		Dealer dealer, BlackJackPlayer user){

		cout << "\n-" << setw(15) << setfill('-') << "-" << "-";
		cout << "\n|" << setw(7) << setfill(' ')
				<< "Player" << "|" << setw(7) << "Status"
				<< setw(1) << "|" ;
		cout << "\n-" << setw(24) << setfill('-') << "-" << "-";
		for(unsigned k=0; k<numOfPlayers; k++){
			cout << "\n|" << setw(7) << setfill(' ')
						<< players[k].getName() << "|"
						<< setw(7) << statuses[players[k].getStatus()]
						<< setw(1) << "|" ;
		}
		cout << "\n|" << setw(7) << setfill(' ')
					<< user.getName() << "|"
					<< setw(7) << statuses[user.getStatus()]
					<< setw(1) << "|" ;
		cout << "\n|" << setw(7) << setfill(' ')
					<< dealer.getName() << "|"
					<< setw(7) << statuses[dealer.getStatus()]
					<< setw(1) << "|" ;
		cout << "\n-" << setw(15) << setfill('-') << "-" << "-";
		cout << endl;
}
