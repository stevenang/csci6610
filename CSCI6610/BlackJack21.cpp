//============================================================================
// Name        : BlackJack21.cpp
// Project     : Group Project Blackjack 21 Game App
// Author      : Parvathy Mohan
// Version     : Created on 11/24/2017
// Copyright   : This program can only be used for project grading purpose
// Description : Blackjack 21 game implementation in C++ using MVC design.
//				 BlackJack21.cpp is the controller class that integrates all
//				 header files and decides on the flow of the program and
//				 show UI to the controller. The game have five computer
//				 players, a dealer and a human player. It implements all rules
//				 of the game and plays the dealer and player objects.
//============================================================================

#include <iostream>
#include "BlackJackPlayer.hpp"
#include "Dealer.hpp"
#include "Decks.hpp"

using namespace std;

#define CONSOLE_WIDTH 100
#define COMP_PLAYERS_COUNT 5

const char* statuses[6] = {" ", "HIT", "STAND", "BUST", "SURRENDER",
		"WIN"};

//------------------Function prototypes start-----------------------------//

//Prints welcome message
void printWelcome();
//Print menu to hit, stand, surrender
void printMenu(Decks* currentDeck, BlackJackPlayer user);
//Print yes/no to continue
int isContinue();
//Print exit message
void printExit();
//serve cards to players around table
void serveCards(BlackJackPlayer players[], BlackJackPlayer* user,
		Dealer* dealer, Decks* currentDeck, int numOfCards);
//check if any of the computer player have a natural blackjack
void checkPlayersBlackJack(BlackJackPlayer players[], int numOfPlayers,
		vector<Player*>* winners);
//check if the human player has a natural blackjack
void checkUserBlackJack(BlackJackPlayer* user, vector<Player*>* winners);
//check if dealer have a natural blackjack, in case his first card is a high
//card
bool checkDealerBlackJack(Dealer* dealer, vector<Player*>* winners,
		BlackJackPlayer players[], int noOfPlayers, BlackJackPlayer* user);
//Prints table showing cards of players and dealer
void printUserTable(BlackJackPlayer players[],int numOfPlayers,
		Dealer dealer, bool isHiddenCard);
void printCard(BlackJackPlayer user);
//Get maximum number of cards any player got in a round.
int getNumOfCards(BlackJackPlayer players[], int numOfPlayers, Dealer dealer);
//Playing option for user wih hit/stand/surrender
void playUser(Decks* currentDeck, BlackJackPlayer* user);
//all computer users playing against dealer based on training logic
void playComputerUsers(BlackJackPlayer players[], int numOfPlayers,
		Dealer dealer, Decks* currentDeck, vector<Player*> winners);
//for each computer player, how to play, called from above function
bool playComputerUser(BlackJackPlayer* player, Dealer* dealer,
		Decks* currentDeck);
//Rules for dealer to play.
void playDealer(Decks* currentDeck, Dealer* dealer, BlackJackPlayer players[],
		int numOfPlayers, BlackJackPlayer* user);
//Print the status of a round of game (who the winner(s) are)
void printRoundStatus(vector<Player*> winners);
//find the winner among all players
void findWinner(Dealer* dealer, BlackJackPlayer players[], int numOfPlayers,
		BlackJackPlayer* user, vector<Player*> winners);
void printPlayerReport(BlackJackPlayer* player);
//Print status of each player under the card table - like stand/bust/win etc
void printPlayerStatus(BlackJackPlayer players[], int numOfPlayers,
		Dealer dealer);
//Clear the hand
void clearHand(BlackJackPlayer players[], int numOfPlayers,
		BlackJackPlayer* user, Dealer* dealer);

//------------------Function prototypes end---------------------------------/

/*
 * Main function where execution of the program starts
 * Input: None
 * Output: int (success/failure)
 */
int main() {
	setbuf(stdout, NULL);
	printWelcome();
	string username;
	cout << "Please enter your username:\n";
	getline(cin, username);
	cout << "\nHello " << username << ",Let us start the game.";
	cout << "\nAre you ready?";
	if(isContinue()){
		cout << "\033c";
		Dealer dealer("Dealer", true);
		//human user is referred as user and computer players are referred
		//as players everywhere.
		BlackJackPlayer player1("Player1", true);
		BlackJackPlayer player2("Player2", true);
		BlackJackPlayer player3("Player3", true);
		BlackJackPlayer player4("Player4", true);
		BlackJackPlayer player5("Player5", true);
		BlackJackPlayer user (username, false);
		BlackJackPlayer players[COMP_PLAYERS_COUNT] =
						{player1, player2, player3, player4, player5};
		cout << "\nDealer is shuffling your cards.\n";
		Decks currentDeck;
		currentDeck.shuffle();
		for(;;){
			serveCards(players, &user, &dealer, &currentDeck, 2);
			bool isHiddenCard = true;//For dealer second card, hidden or not
			cout << "\nHere is the card table.\n";
			printUserTable(players, COMP_PLAYERS_COUNT, dealer, isHiddenCard);
			printCard(user);
			//There could be more than one winner in case of ties
			vector<Player*> winners;
			//First check if any computer player have a natural blackjack
			checkPlayersBlackJack(players, COMP_PLAYERS_COUNT, &winners);
			//Next check if the human user have a natural blackjack
			checkUserBlackJack(&user, &winners);
			//Next check if dealer got a high card, if so, open the hidden card
			//to see if dealer got a natural blackjack
			//isHiddenCard is returned as False
			//in case the dealer had a high card
			isHiddenCard = checkDealerBlackJack(&dealer, &winners,
					players, COMP_PLAYERS_COUNT, &user);

			if(winners.size() > 0){//When there are already winners in first
				//round
				printUserTable(players, COMP_PLAYERS_COUNT,
										dealer, false);
				printCard(user);
				printRoundStatus(winners);
			}else{//else, continue playing
				//all computer players play
				playComputerUsers(players, COMP_PLAYERS_COUNT,
						dealer, &currentDeck, winners);
				cout << "\n\nAll other users are done, here is the card table!"
						<< endl;
				//human user play
				printUserTable(players, COMP_PLAYERS_COUNT,
						dealer, isHiddenCard);
				//printing all players status
				printPlayerStatus(players, COMP_PLAYERS_COUNT, dealer);
				if(user.getTotal() == 21){
					printCard(user);
					user.win();
					winners.push_back(&user);
				}else{
					cout << "\n";
					currentDeck.askQuestion();
					playUser(&currentDeck, &user);
				}
				//dealer's turn to play
				if(isHiddenCard){
					cout << "\nDealer open the face down card.";
					cout << "\nDealer got "
							<< dealer.getCardsFromHand().at(1)->toString();
					isHiddenCard= false;
				}
				playDealer(&currentDeck, &dealer, players,
						COMP_PLAYERS_COUNT, &user);
				printUserTable(players, COMP_PLAYERS_COUNT,
						dealer, isHiddenCard);
				printPlayerStatus(players, COMP_PLAYERS_COUNT, dealer);
				printCard(user);
				findWinner(&dealer, players, COMP_PLAYERS_COUNT,
							&user, winners);
			}
			cout << "\nWould you like to play another round? \n";
			cin.clear();
			cin.ignore(144, '\n');
			if(isContinue()){
				cout << "\033c";
				clearHand(players, COMP_PLAYERS_COUNT, &user, &dealer);
			}else{
				printPlayerReport(&user);
				break;
			}
		}
	}
	printExit();
	return 0;
}

/*
 * Get maximum number of cards any player got. This to decide how many rows
 * should be there in the table printed to show card table.
 * Input: array of players, number of players, dealer
 * Output: None
 *
 */
int getNumOfCards(BlackJackPlayer players[], int numOfPlayers, Dealer dealer){
	//2 servings of card per person default
	int cards = 2;
	for(int i=0; i<numOfPlayers; ++i){
		int currentSize = players[i].getCardsFromHand().size();
		if(currentSize > cards){
			cards = currentSize;
		}
	}
	int dealerCardSize = dealer.getCardsFromHand().size();
	return cards > dealerCardSize ? cards : dealerCardSize;
}

/*
 * To print the table showing cards for players and dealer
 * Input: players array, number of players, dealer, isHiddenCard for dealer
 * Output: None
 */
void printUserTable(BlackJackPlayer players[],int numOfPlayers,
		Dealer dealer, bool isHiddenCard){

	cout << "\n-" << setw(70) << setfill('-') << "-" ;
	cout << "\n" << setfill(' ') << setw(12)
			<< left << "Dealer" << setw(12)
			<< left << "Player1" <<  setw(12)
			<< left << "Player2"<< setw(12)
			<< left << "Player3" <<  setw(12)
			<< left << "Player4" << setw(12)
			<< left << "Player5";

	int size = getNumOfCards(players, numOfPlayers, dealer);
	cout << "\n-" << setw(70) << setfill('-') << "-" << "-";

	int player1Size = players[0].getCardsFromHand().size();
	int player2Size = players[1].getCardsFromHand().size();
	int player3Size = players[2].getCardsFromHand().size();
	int player4Size = players[3].getCardsFromHand().size();
	int player5Size = players[4].getCardsFromHand().size();
	int dealerSize = dealer.getCardsFromHand().size();

	for(int k=0; k<size; k++){
		cout << "\n" ;
		string dealerCard, player1Card, player2Card, player3Card,
		player4Card, player5Card;

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

/*
 * Prints player status below card table - stand/bust/win etc
 * Input: array of players, number of players, dealer
 * Output: None
 */
void printPlayerStatus(BlackJackPlayer players[], int numOfPlayers,
		Dealer dealer){

	cout << setfill(' ') << setw(13) <<left << statuses[dealer.getStatus()];
	for(int i=0; i<numOfPlayers; ++i){
		BlackJackPlayer* player = &players[i];
		cout << setfill(' ') << setw(13) << left
			 << statuses[player->getStatus()];
	}
	cout << "\n-" << setw(70) << setfill('-') << "-" << "-";
	cout << endl;
}

/*
 * Print card figure for user
 * Input: User
 * Output: None
 */
void printCard(BlackJackPlayer user){
		vector<Card*> cards = user.getCardsFromHand();
		cout << "\n" << user.getName() << " - Total : "
			 << user.getTotal();
		if(user.isBlackJack()){
			cout << " -- BLACKJACK";
		}else if(user.getTotal() == 21){
			cout << " -- WIN";
		}else if(user.getTotal() > 21){
			cout << " -- BUST";
		}
		cout << "\n";
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

/*
 * Print win/lose report at the end.
 * Input: Human user
 * Output: None
 */
void printPlayerReport(BlackJackPlayer* player){
	cout <<"\n";
	cout << setw(CONSOLE_WIDTH/3) << setfill('-') << " " << endl;
	cout << player->getName() << " Score Table:\n";
	cout << setw(CONSOLE_WIDTH/3) << setfill('-') << " " << endl;

	cout << "-" << setw(15) << setfill('-') << "-" << "-";
	cout << "\n|" << setw(7) << setfill(' ')
			<< "WIN" << "|" << setw(7) << "LOSE"
			<< "|";// << setw(7) << "TIE"
			//<< setw(1) << "|" ;
	cout << "\n-" << setw(15) << setfill('-') << "-" << "-";
	cout << "\n|" << setw(7) << setfill(' ')
					<< player->getWinCount() << "|"
					<< setw(7) << player->getLoseCount()
					<< "|"; //<< setw(7) << player->getTieCount()
					//<< setw(1) << "|" ;
	cout << "\n-" << setw(15) << setfill('-') << "-" << "-";
	cout << endl;

}

/*
 * Serves card to all players around the table
 * Input: all computer players, human player, dealer, currentDeck,
 * number of cards to be served.
 * Output: None
 */
void serveCards(BlackJackPlayer players[], BlackJackPlayer* user,
		Dealer* dealer, Decks* currentDeck, int numOfCards){

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

/*
 * Playing logic for all computer users based on training
 * Input: array of players, number of players, dealer, current deck,
 * vector of winner players
 * Output: None
 */
void playComputerUsers(BlackJackPlayer players[], int numOfPlayers,
		Dealer dealer, Decks* currentDeck, vector<Player*> winners){
	cout << "\n\nDealer playing with players clockwise :: " << endl;
	cout << setw(CONSOLE_WIDTH/2) << setfill('-') << " " << endl;
	for(int i=0; i<numOfPlayers; ++i){
		BlackJackPlayer* player;
		player = &players[i];
		if(playComputerUser(player, &dealer, currentDeck)){
			winners.push_back(player);
		}
	}
}

/*
 * Playing logic for one computer user based on training, called from
 * function above
 * Input: computer player, dealer, current deck
 * Output: Return if the player gets a blackjack
 */
bool playComputerUser(BlackJackPlayer* player, Dealer* dealer,
		Decks* currentDeck){
	bool isWinner = false;
	bool goAhead = true;
	//hitting logic in a loop until player stops hitting
	while(
		player->isHitting(dealer->getCardsFromHand().at(0)->getCardRank(false))
	){
		cout << "" << player->getName() << " decided to HIT.\n";
		vector<Card*> cards = currentDeck->giveCard(1);
		player->addCardToHand(cards.at(0));
		cout << "" << player->getName() << " was served card "
				<< cards.at(0)->getCardSuite() << cards.at(0)->getCardValue()
				<< "\n";
		if(player->isBusted()){
			player->bust();
			goAhead = false;
			break;
		}else if(player->getTotal() == 21){
			player->win();
			goAhead = false;
			isWinner = true;
			break;
		}
	}
	//if player is standing
	if(goAhead &&
	player->isStanding(dealer->getCardsFromHand().at(0)->getCardRank(false))){
		cout << "" << player->getName() << " decided to STAND.\n";
		goAhead = false;
	}
	//if player is surrendering
	if(goAhead &&
	player->isSurrender(dealer->getCardsFromHand().at(0)->getCardRank(false))){
		cout << "" << player->getName() << " decided to SURRENDER.\n";
		goAhead = false;
	}
	//in case the player card count does not fall under hit/stand/surrender
	if(goAhead){
		player->standing();
		goAhead = false;
	}

	return isWinner;
}

/*
 * Dealer playing following rules of Blackjack 21 game
 * Input: current deck, dealer, players list, number of player, user
 * Output: Is dealer a blackjack?
 */
void playDealer(Decks* currentDeck, Dealer* dealer,
		BlackJackPlayer players[], int numOfPlayers, BlackJackPlayer* user){
	//The rule is dealer cannot hit after total reach 17.
	while(dealer->getTotal() < 17){
		cout << "\nDealer have a total of " << dealer->getTotal() << ".";
		cout << "\nTaking next card from the deck.";
		vector<Card*> dealerCard = currentDeck->giveCard(1);
		dealer->addCardToHand(dealerCard.at(0));
		cout << "\nDealer got " << dealerCard.at(0)->getCardSuite()
		<< dealerCard.at(0)->getCardValue()<< ".\n";
		if(dealer->getTotal() == 21){
			cout << "\n";
			dealer->win();
		}else if(dealer->isBusted()){
			dealer->bust();
			dealer->lose();
		}
	}
	if(dealer->getStatus() != BlackJackPlayer::BUSTED
			&& dealer->getTotal() >= 17){
		cout << "\nDealer have a total of " << dealer->getTotal() << ".";
		cout << "\nDealer will STAND.\n";
		dealer->standing();
	}
}

/*
 * Human user playing, menu for decisions printed, based on key,
 * user can hit, stand or surrender.
 * Input: decks, user
 * Output: bool (if user is done with the round, user is done when he/she
 * busts or win or choose to exit/surrender/stand
 */
void playUser(Decks* currentDeck, BlackJackPlayer* user){
	printMenu(currentDeck, *user);
	char userDecision;
	cin >> userDecision;
	switch(toupper(userDecision)){
		case 'S':
			cout << user->getName() << " decided to STAND.\n";
			user->standing();
			break;
		case 'U':
			cout << user->getName() << " decided to SURRENDER.\n";
			user->surrender();
			break;
		case 'H':
			{
			vector<Card*> userCard = currentDeck->giveCard(1);
			user->addCardToHand(userCard.at(0));
			if(user->isBusted()){
				printCard(*user);
				cout <<"\n\n";
				user->bust();
			}else if(user->getTotal() == 21){
				cout <<"\n\n";
				user->win();
			}else{
				//recursion
				playUser(currentDeck, user);
			}
			break;
			}
		default:
			cout << "Sorry, wrong key!" << endl;
			//recursion
			playUser(currentDeck, user);
	}
}
/*
 * Find the winner of a round: if dealer bust, all other players who are not
 * busted/surrendered wins. Else, if dealer wins, all other players with no
 * 21 total lose. If no one has 21, all players with a total above dealer
 * are winners and below are losers.
 * Input: array of players, number of players, human user, list of winners
 * Output: None
 */
void findWinner(Dealer* dealer, BlackJackPlayer players[], int numOfPlayers,
		BlackJackPlayer* user, vector<Player*> winners){
	switch(dealer->getStatus()){
		case BlackJackPlayer::WIN:
		{//calculating winners when dealer has 21
			winners.push_back(dealer);
			//dealer got a natural blackjack
			for(int i=0; i < numOfPlayers; ++i){
				BlackJackPlayer* player = &players[i];
				if(player->getStatus() == BlackJackPlayer::WIN){
					winners.push_back(player);
				}
			}
			if(user->getStatus() == BlackJackPlayer::WIN){
				user->addWinCount();
				winners.push_back(user);
			}else if(user->getStatus() == BlackJackPlayer::BUSTED){
				user->addLoseCount();
			}else if(user->getStatus() != BlackJackPlayer::SURRENDER){
				//because lose count is already added for user when busted.
				user->addLoseCount();
			}
			break;
		}
		case BlackJackPlayer::BUSTED:
		{//calculating winners when dealer is busted
			for(int i=0; i < numOfPlayers; ++i){
				BlackJackPlayer* player = &players[i];
				if(player->getStatus() != BlackJackPlayer::BUSTED &&
						player->getStatus() != BlackJackPlayer::SURRENDER){
					winners.push_back(player);
				}
			}
			if(user->getStatus() == BlackJackPlayer::BUSTED){
				user->addLoseCount();
			}else if(user->getStatus() != BlackJackPlayer::SURRENDER){
				user->addWinCount();
				winners.push_back(user);
			}
			break;
		}
		case BlackJackPlayer::STANDING:
		{//calculating winners when dealer is standing, not busted/21.
			vector<Player*> losers;//gets all players with total less than
			//dealer's total
			vector<Player*> ties;//gets all players with total equal to winners
			int dealerTotal = dealer->getTotal();
			for(int i=0; i< COMP_PLAYERS_COUNT; i++){
				Player* player = &players[i];
				if(player->getStatus() == BlackJackPlayer::BUSTED
						|| player->getStatus() == BlackJackPlayer::SURRENDER){
					continue;
				}
				if(dealerTotal < player->getTotal()){
					winners.push_back(player);
				}else if(dealerTotal == player->getTotal()){
					ties.push_back(player);
				}else{
					losers.push_back(player);
				}
			}
			if(user->getStatus() == BlackJackPlayer::BUSTED){
				user->addLoseCount();
			}else if (user->getStatus() == BlackJackPlayer::SURRENDER){
				// do nothing
			}else{
				if(dealerTotal < user->getTotal()){
					user->addWinCount();
					winners.push_back(user);
				}else if(dealerTotal == user->getTotal()){
					user->addWinCount();
					ties.push_back(user);
				}else{
					user->addLoseCount();
					losers.push_back(user);
				}
			}
			if(winners.size() == 0){
				winners.push_back(dealer);
				if(ties.size()!=0){
					for(int i=0; i<ties.size(); i++){
						winners.push_back(ties.at(i));
					}
				}
			}
		}
	}
	printRoundStatus(winners);
}

/*
 * Prints the result of a round of game, who the winner is if any,
 * is there a tie between players/dealer etc.
 * Input: vector of winner players
 * Output: None
 */
void printRoundStatus(vector<Player*> winners){
	cout << "\n" << "Calculating results...";
	cout << "\n";
	cout << setw(CONSOLE_WIDTH/3) << setfill('-') << " " << endl;
	cout << "Results : " << endl;
	cout << setw(CONSOLE_WIDTH/3) << setfill('-') << " " << endl;
	if(winners.size() == 1){
		cout << "The winner is : " << winners.at(0)->getName();
	}else if(winners.size() > 1){
		string result = "\nIt is a tie between ";
		for(int i=0; i<winners.size();++i){
			result += winners.at(i)->getName();
			if((i+1) != winners.size()){
				result += " and ";
			}
			cout << "\n" << winners.at(i)->getName() << " wins.";
		}
	}
	cout << "\n";
	cout << setw(CONSOLE_WIDTH/3) << setfill('-') << " " << endl;
}

/*
 * Clear hand, erase card details of this round.
 * Input: Array of computer players, number of computer players,
 * human user, dealer
 * Output: None
 */
void clearHand(BlackJackPlayer players[], int numOfPlayers,
		BlackJackPlayer* user, Dealer* dealer){
	for(int i =0; i < numOfPlayers; ++i){
		BlackJackPlayer* player = &players[i];
		player->clearHands();
	}
	dealer->clearHands();
	user->clearHands();
}

/*
 * To check if any of the computer players have a natural blackjack.
 * Input: Array of players, number of players, list of winners if any
 * Output: None
 */
void checkPlayersBlackJack(BlackJackPlayer players[], int numOfPlayers,
		vector<Player*>* winners){
	for(int i=0; i<COMP_PLAYERS_COUNT; ++i){
		if(players[i].isBlackJack()){
			cout << "\n";
			players[i].win();
			cout << "\n" << players[i].getName() << " got a BLACKJACK!\n";
			winners->push_back(&players[i]);
		}
	}
}

/*
 * To check if the human player has a natural blackjack
 * Input: BlackJackPlayer, vector of winners
 * Output: None
 */
void checkUserBlackJack(BlackJackPlayer* user, vector<Player*>* winners){
	if(user->isBlackJack()){
		cout << "\n";
		user->win();
		cout << "\n" << user->getName() << " got a BLACKJACK!\n";
		user->addWinCount();
		winners->push_back(user);
	}
}

/*
 * Check if dealer got a high card and if so, see if dealer gets a natural
 * blackjack.
 * Input: dealer, isHiddenCard (second card of dealer), list of winners
 * Output: None
 */
bool checkDealerBlackJack(Dealer* dealer, vector<Player*>* winners,
		BlackJackPlayer players[], int noOfPlayers, BlackJackPlayer* user){
	bool isHiddenCard = true;
	if(dealer->isFirstCardHighCard()){
		cout << "\nDealer got "
				<< dealer->getCardsFromHand().at(0)->getCardSuite()
				<< dealer->getCardsFromHand().at(0)->getCardValue()
				<< " as the face up card.";
		cout << "\nDealer is going to open the face down card.";
		isHiddenCard = false;
		cout << "\nThe face down card is "
				<<  dealer->getCardsFromHand().at(1)->getCardSuite()
				<< dealer->getCardsFromHand().at(1)->getCardValue()
				<<".";
		cout << "\nChecking if the dealer got a natural blackjack.\n";
		if(dealer->isBlackJack()){
			cout << "Dealer is a Natural Blackjack.\n\n";
			dealer->win();
			winners->push_back(dealer);
			for(int i=0; i< noOfPlayers; ++i){
				BlackJackPlayer* player = &players[i];
				if(!player->isBlackJack()){
					player->lose();
					player->addLoseCount();
				}
			}
			if(!user->isBlackJack()){
				user->lose();
				user->addLoseCount();
			}
		}else{
			cout << "Dealer is NOT a Blackjack.\n";
			if(winners->size() > 0){
				dealer->lose();
			}
		}
	}else{
		if(winners->size() > 0){
			cout << "\nDealer is going to open the face down card.";
			isHiddenCard = false;
			cout << "\nThe face down card is "
					<<  dealer->getCardsFromHand().at(1)->getCardSuite()
					<< dealer->getCardsFromHand().at(1)->getCardValue()
					<<".";
			dealer->lose();
		}
	}
	return isHiddenCard;
}

/*
 * Prints welcome message
 * Input: None
 * Output: None
 */
void printWelcome(){
	cout << setw(CONSOLE_WIDTH) << setfill('*') << " " << endl;
	cout << setw(CONSOLE_WIDTH / 2) << setfill(' ')
			<< "Welcome to Blackjack 21 Game" << endl;
	cout << setw(CONSOLE_WIDTH) << setfill('-') << " " << endl;
	cout << setw(CONSOLE_WIDTH) << setfill(' ') << left << "Rules:" << endl;
	cout << setw(CONSOLE_WIDTH) << left << "You will be playing"
			" against the dealer." << endl;
	string displayStr = "There will be " +
				to_string(COMP_PLAYERS_COUNT) + " players "
						" apart from you in the table.";
	cout << setw(CONSOLE_WIDTH) << left << displayStr << endl;
	cout << setw(CONSOLE_WIDTH)
		 << left << "You may do card counting by calculating High card"
		 " probability strategy." << endl;
	cout << setw(CONSOLE_WIDTH)
		 << left << "The app will check your strategy through signals."
		 << endl;
	cout << setw(CONSOLE_WIDTH) << setfill('*') << " " << endl;
}

/*
 * Prints menu options for user to hit/stand/surrender
 * Input: BlackJack Player - Human user
 * Output: None
 */
void printMenu(Decks* currentDeck, BlackJackPlayer user){
	printCard(user);
	cout << "\n\n" << user.getName() << ", it is your turn.";
	cout << "\n\n";
	cout << "Your Options are:\n";
	cout << setw(15) << setfill(' ') << left << "HIT" << right << "STAND";
	cout << setw(15) <<  " " ;
	cout << setw(7) << setfill(' ') << right << "SURRENDER";
	cout << setw(15) <<  " " ;
	cout << "\n\n";
	cout << "Press H to HIT, S to Stand and U to Surrender.\n";
}

/*
 * Checks if user wants to continue or not
 * Input: None
 * Output: 1 or 0
 */
int isContinue(){
	cout << "\nPress Y to continue or any other key to exit.\n";
	char option;
	option = getchar();
	if(tolower(option) == 'y'){
		return 1;
	}else{
		return 0;
	}
}

/*
 * Print exit message
 * Input: None
 * Output: None
 */
void printExit(){
	cout << "\n";
	cout << setw(CONSOLE_WIDTH) << setfill('*') << "" << endl;
	cout << setw(CONSOLE_WIDTH / 2) << setfill(' ')
			<< "Thankyou for playing Blackjack 21 Game with us. See you again!"
			<< endl;
	cout << setw(CONSOLE_WIDTH) << setfill('*') << "" << endl;
}
