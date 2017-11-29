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

const char* statuses[6] = {" ", "HIT", "STAND", "BUST", "SURRENDER", "WIN"};


void printWelcome();
void printUserTable(BlackJackPlayer players[], Dealer dealer, int numOfPlayers, bool isHiddenCard);
void printCard(BlackJackPlayer user);
void printMenu(BlackJackPlayer user);
int printYesOrNo();
void printExit();
int getNumOfRounds(BlackJackPlayer players[], int numOfPlayers, Dealer dealer);
void serveCards(BlackJackPlayer players[], BlackJackPlayer* user, Dealer* dealer, Decks* currentDeck, int numOfCards);
void playComputerUsers(BlackJackPlayer players[], int numOfPlayers, Dealer dealer, Decks* currentDeck, vector<Player*> winners);
bool playComputerUser(BlackJackPlayer* player, Dealer* dealer, Decks* currentDeck);
bool playDealer(Decks* currentDeck, Dealer* dealer, BlackJackPlayer players[], int numOfPlayers, BlackJackPlayer* user);
void printRoundStatus(vector<Player*> winners);
void findWinner(Dealer* dealer, BlackJackPlayer players[], int numOfPlayers, BlackJackPlayer* user, vector<Player*> winners);
void printPlayerReport(BlackJackPlayer* player);
void printPlayerStatus(BlackJackPlayer players[], int numOfPlayers, Dealer dealer);

int main() {
	setbuf(stdout, NULL);
	printWelcome();
	string username;
	cout << "Please enter your username:\n";
	getline(cin, username);
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
		//revisit
		for(;;){
			serveCards(players, &user, &dealer, &currentDeck, 2);
			bool isHiddenCard = true;//For dealer second card, hidden or not
			cout << "\nHere is the card table.\n";
			printUserTable(players, dealer, 5, isHiddenCard);
			printCard(user);
			//Step 1: is any player natural blackjack?
			vector<Player*> winners;
			for(int i=0; i<5; ++i){
				if(players[i].isBlackJack()){
					cout << "\n";
					players[i].win();
					winners.push_back(&players[i]);
				}
			}
			if(user.isBlackJack()){
				cout << "\n";
				user.win();
				winners.push_back(&user);
			}
			//Step 2: Check if the dealer has a high card?
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
				cout << "\nChecking if the dealer got a natural blackjack.\n";
				if(dealer.isBlackJack()){
					cout << "Dealer is a Natural Blackjack.\n";
					cout << "dealer name is :: " << dealer.getName();
					winners.push_back(&dealer);
				}else{
					cout << "Dealer is NOT a Blackjack.\n";
				}
			}

			if(winners.size() != 0){
				printRoundStatus(winners);
			}else{
				playComputerUsers(players, 5, dealer, &currentDeck, winners);
				cout << "\n\nAll other users are done, here is the card table!" << endl;
				printUserTable(players, dealer, 5, isHiddenCard);
				printPlayerStatus(players, 5, dealer);
				if(user.getTotal() == 21){
					user.win();
					winners.push_back(&user);
				}else{
					bool isUserDone = false;
					while(!isUserDone){
						printMenu(user);
						char userDecision;
						cin >> userDecision;
						if(userDecision == 'H'){
							vector<Card*> userCard = currentDeck.giveCard(1);
							user.addCardToHand(userCard.at(0));
							if(user.isBusted()){
								printCard(user);
								cout <<"\n\n";
								user.bust();
								user.lose();
								isUserDone = true;
							}else if(user.getTotal() == 21){
								cout <<"\n\n";
								user.win();
								isUserDone = true;
							}
						}else if (userDecision == 'S'){
							cout << user.getName() << " decided to STAND.\n";
							isUserDone = true;
						}else if (userDecision == 'Q'){
							cout << user.getName() << " decided to QUIT.\n";
							isUserDone = true;
						}else if (userDecision == 'U'){
							cout << user.getName() << " decided to SURRENDER.\n";
						//	user.surrender();
							isUserDone = true;
						}else{
							cout << "\nSorry, your key is incorrect.\n";
						}
					}
				}
				//dealer's turn to play
				if(playDealer(&currentDeck, &dealer, players, 5, &user)){
					winners.push_back(&dealer);
				}
				if(winners.size() != 0 ){
					printRoundStatus(winners);
				}else{
					findWinner(&dealer, players, 5, &user, winners);
				}
			}
			cout << "\nWould you like to play another round? \n";
			getchar();
			if(printYesOrNo()){
				for(int i =0; i < 5; ++i){
					players[i].clearHands();
				}
				dealer.clearHands();
				user.clearHands();
			}else{
				printPlayerReport(&user);
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
	cout << "\n-" << setw(70) << setfill('-') << "-" ;
	cout << "\n" << setfill(' ') << setw(12)
			<< left << "Dealer" << setw(12)
			<< left << "Player1" <<  setw(12)
			<< left << "Player2"<< setw(12)
			<< left << "Player3" <<  setw(12)
			<< left << "Player4" << setw(12)
			<< left << "Player5";
	//TODO: change it to max player card size?
	//need a function for it, where? hand or here?
	int size = getNumOfRounds(players, numOfPlayers, dealer);
	//cout << "Size is " << size;
	cout << "\n-" << setw(70) << setfill('-') << "-" << "-";
	//TODO: Will the player count be always 5?
	int player1Size = players[0].getCardsFromHand().size();
	int player2Size = players[1].getCardsFromHand().size();
	int player3Size = players[2].getCardsFromHand().size();
	int player4Size = players[3].getCardsFromHand().size();
	int player5Size = players[4].getCardsFromHand().size();
	int dealerSize = dealer.getCardsFromHand().size();
	for(unsigned k=0; k<size; k++){
		cout << "\n" ;
		string dealerCard, player1Card, player2Card, player3Card, player4Card, player5Card;
		if(k==1 && isHiddenCard){
			dealerCard = "--";//For Hidden second card
			cout << setfill(' ') << setw(13) << left << dealerCard;
		}else if(k < dealerSize){
			dealerCard = dealer.getCardsFromHand().at(k)->getCardSuite() +
					dealer.getCardsFromHand().at(k)->getCardValue();
			cout << setfill(' ') << setw(15) << left << dealerCard;
		}else{
			dealerCard = "";
			cout << setfill(' ') << setw(13) << left << dealerCard;
		}
		if(k >= player1Size){
			player1Card = "";
			cout   << setw(13) <<left << player1Card;
		}else{
			player1Card = players[0].getCardsFromHand().at(k)->getCardSuite() +
						players[0].getCardsFromHand().at(k)->getCardValue();
			cout   << setw(15) <<left << player1Card;
		}
		if(k >= player2Size){
			player2Card = "";
			cout <<left  << setw(13) <<left << player2Card;
		}else{
			player2Card = players[1].getCardsFromHand().at(k)->getCardSuite() +
						players[1].getCardsFromHand().at(k)->getCardValue();
			cout <<left  << setw(15) <<left << player2Card;
		}
		if(k >= player3Size){
			player3Card = "";
			cout <<left  << setw(13) <<left <<
					player3Card;
		}else{
			player3Card = players[2].getCardsFromHand().at(k)->getCardSuite() +
						players[2].getCardsFromHand().at(k)->getCardValue();
			cout <<left  << setw(15) <<left <<
					player3Card;
		}
		if(k >= player4Size){
			player4Card = "";
			cout <<left  << setw(13) <<left <<
					player4Card;
		}else{
			player4Card = players[3].getCardsFromHand().at(k)->getCardSuite() +
						players[3].getCardsFromHand().at(k)->getCardValue();
			cout <<left  << setw(15) <<left <<
					player4Card;
		}
		if(k >= player5Size){
			player5Card = "";
			cout <<left  << setw(13) <<left <<
						player5Card;
		}else{
			player5Card = players[4].getCardsFromHand().at(k)->getCardSuite() +
						players[4].getCardsFromHand().at(k)->getCardValue();
			cout <<left  << setw(15) <<left <<
									player5Card;
		}
	}
	cout << "\n-" << setw(70) << setfill('-') << "-" << "-";
	cout << endl;
}

void printPlayerStatus(BlackJackPlayer players[], int numOfPlayers, Dealer dealer){

	cout << setfill(' ') << setw(13) <<left << statuses[dealer.getStatus()];
	for(int i=0; i<numOfPlayers; ++i){
		BlackJackPlayer* player = &players[i];
		cout << setfill(' ') << setw(13) << left << statuses[player->getStatus()];
	}
	cout << "\n-" << setw(70) << setfill('-') << "-" << "-";
	cout << endl;
}

void printCard(BlackJackPlayer user){
		vector<Card*> cards = user.getCardsFromHand();
		cout << "\n" << user.getName() << " - Total : " << user.getTotal() << "\n";
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

void printMenu(BlackJackPlayer user){
	printCard(user);
	cout << "\n\n" << user.getName() << ", it is your turn.";
	cout << "\n\n";
	cout << "Your Options are:\n";
	cout << setw(15) << setfill(' ') << left << "HIT" << right << "STAND";
	cout << setw(15) <<  " " ;
	cout << setw(15) << setfill(' ') << left << "SPLIT" << right << "SURRENDER";
	cout << setw(15) <<  " " ;
	cout << "\n\n";
	cout << "Press H to HIT, S to Stand, P to Split and U to Surrender.\n";
	cout << "Press Q to Quit.\n";
}

int printYesOrNo(){
	cout << "\nPress Y to continue:\n";
	char option;
	option = getchar();
	//getchar();//for eclipse
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


void printPlayerReport(BlackJackPlayer* player){

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
					<< player->getWinCount() << "|"
					<< setw(7) << player->getLoseCount()
					<< "|" << setw(7) << player->getTieCount()
					<< setw(1) << "|" ;
	//}
	cout << "\n-" << setw(24) << setfill('-') << "-" << "-";
	cout << endl;

}

void serveCards(BlackJackPlayer players[], BlackJackPlayer* user, Dealer* dealer, Decks* currentDeck, int numOfCards){

	cout << "\nDealer is serving the cards.\n";
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

void playComputerUsers(BlackJackPlayer players[], int numOfPlayers, Dealer dealer, Decks* currentDeck, vector<Player*> winners){
	cout << "\n\nDealer playing with players clockwise :: " << endl;
	cout << setw(50) << setfill('-') << " " << endl;
	for(int i=0; i<numOfPlayers; ++i){
		BlackJackPlayer* player;
		player = &players[i];
		if(playComputerUser(player, &dealer, currentDeck)){
			winners.push_back(player);
		}
	}
}

bool playComputerUser(BlackJackPlayer* player, Dealer* dealer, Decks* currentDeck){
	cout << "\n";
	bool isWinner = false;
	bool goAhead = true;
	while(player->isHitting(dealer->getCardsFromHand().at(0)->getCardRank(false))){
		cout << "" << player->getName() << " decided to HIT.";
		vector<Card*> cards = currentDeck->giveCard(1);
		player->addCardToHand(cards.at(0));
		cout << "\n" << player->getName() << " was served card "
				<< cards.at(0)->getCardSuite() << cards.at(0)->getCardValue()
				<< "\n";
		if(player->isBusted()){
			player->bust();
			player->lose();
			goAhead = false;
			break;
		}else if(player->getTotal() == 21){
			player->win();
			goAhead = false;
			isWinner = true;
			break;
		}
	}
	if(goAhead && player->isStanding(dealer->getCardsFromHand().at(0)->getCardRank(false))){
		cout << "" << player->getName() << " decided to STAND.";
		goAhead = false;
	}
	if(goAhead && player->isSurrender(dealer->getCardsFromHand().at(0)->getCardRank(false))){
		cout << "" << player->getName() << " decided to SURRENDER.";
		goAhead = false;
	}
	return isWinner;
}

//TODO: Steven: 2 functions? isBlackJack and isNaturalBlackjack?

bool playDealer(Decks* currentDeck, Dealer* dealer, BlackJackPlayer players[], int numOfPlayers, BlackJackPlayer* user){
	//cout << "\nDealer have a total of " << dealer->getTotal()<< "\n";
	bool isWinner = false;
	while(dealer->getTotal() < 17){
		cout << "\nDealer have a total of " << dealer->getTotal() << "\n";
		cout << "\nTaking next card from the deck.\n";
		vector<Card*> dealerCard = currentDeck->giveCard(1);
		dealer->addCardToHand(dealerCard.at(0));
		cout << "\nDealer got " << dealerCard.at(0)->getCardSuite()
		<< dealerCard.at(0)->getCardValue()<< ".\n";
		if(dealer->getTotal() == 21){
			dealer->win();
			isWinner = true;
			//handle: all players who have no blackjack lose.
			for(int i=0; i <numOfPlayers; ++i){
				if(players[i].getTotal() != 21){
					players[i].lose();
				}
			}
			if(user->getTotal() != 21){
				user->lose();
			}
		}else if(dealer->isBusted()){
			dealer->bust();
			dealer->lose();
		}
	}
	if(dealer->getStatus() != BlackJackPlayer::BUSTED && dealer->getTotal() >= 17){
		cout << "\nDealer have a total of " << dealer->getTotal() << "\n";
		cout << "\nDealer will STAND.\n";
	}
	return isWinner;
}

void findWinner(Dealer* dealer, BlackJackPlayer players[], int numOfPlayers, BlackJackPlayer* user, vector<Player*> winners){
	numOfPlayers = numOfPlayers+2;//dealer and user
	Player* allPlayers[numOfPlayers];
	int i = 0;
	for(i=0; i < numOfPlayers-2; ++i){
		allPlayers[i] = &players[i];
	}
	allPlayers[i] = user;
	i = i+1;//revisit
	allPlayers[i] = dealer;
	int highestRank = 0;
	for(int i=0; i<numOfPlayers; ++i){
		if(allPlayers[i]->getStatus() == BlackJackPlayer::SURRENDER){
			continue;
		}
		int total = allPlayers[i]->getTotal();
		if(total<= 21  and total > highestRank){
			winners.clear();
			winners.push_back(allPlayers[i]);
			highestRank = total;
		}else if(total == highestRank){
			winners.push_back(allPlayers[i]);
		}
	}
	//revisit
	printRoundStatus(winners);
}

void printRoundStatus(vector<Player*> winners){
	cout << "\nResults : " << endl;
	if(winners.size() == 1){
		cout << "The winner is : " << winners.at(0)->getName();
	}else if(winners.size() > 1){
		cout << "It is a tie between ";
		for(int i=0; i<winners.size();++i){
			cout << winners.at(i)->getName();
			if((i+1) != winners.size()){
				cout << " and ";
			}
		}
	}
	cout << "\n";
}
