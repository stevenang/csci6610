/*============================================================================
 *Name        : Decks.cpp
 *Project	  : Final Project Blackjack 21 console game
 *Author      : Jayeeta Banerjee
 *Version     : Created on 11/18/2017
 *Copyright   : Prohobited
 *Description : It introduces the implementation of all methods from the class
                of decks.
 *=============================================================================
*/
#include <typeinfo>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<vector>
#include <ctime>
#include <utility>      // std::swap. it is used while shuffling the whole decks
#include "Decks.hpp"
using namespace std;

//------------------------------------------------------------------------------
//this method will call 'fillDecks()' to create a decks
Decks::Decks()
{
//Initialize the deck:
	fillDecks();

}

/*------------------------------------------------------------------------------
 * This method create a full decks with 6X52= 312 cards. It will call another
 * method 'updateAllDeckCards()' to insert each card in the decks. Vector method
 * 'push_back' and new is used in this method. 'all_deck.size()' is used to
 * determine the number of total cards
 */


void Decks::fillDecks()
{
	//cout<<"\nTotal Card before:-"<<all_deck.size()<<endl;
	for(int i=0;i<6;i++)
	{
		deck_list.push_back(new Deck());
	}
	updateAllDeckCards();
	totalCard = all_deck.size();
	//cout<<"Total Card:-"<<totalCard<<endl;
}

/*------------------------------------------------------------------------------
 * This method is used to shuffle decks. 'srand' is used to shuffle in different
 * variation. Variable n(integer) to store the number after subtracting decks
 * end and begin position values. Using a reverse for loop to swap it
 * randomly. After shuffling a white magic card number is generating by calling
 * 'generateWhiteMagicNumber()' this method for future shuffle.
 *
 */

void Decks::shuffle()
{

	srand ( unsigned ( std::time(0) ) );

	int n = (all_deck.end()-all_deck.begin());
	for (unsigned i=n-1; i>0; --i)
	{
		swap (all_deck.begin()[i],all_deck.begin()[(rand()%i)+1]);
	}
	if(all_deck.size() > 1){
		//cout<<"size"<<all_deck.size();
		generateWhiteMagicNumber(); //After shuffle generate magic number for future shuffle
	}


	//cout<<"******************* AFTER shuffle:-*********************************"
			//"***********************"<<endl;
	//printAllDeckCards();
}

/*------------------------------------------------------------------------------
 * This method will return the full deck of cards while calling.
 */

vector<Card*> Decks::getAllDeckCards()
{

	return all_deck;
}

/*------------------------------------------------------------------------------
 * This method will clear the decks if needed. It will clear both 'all_deck' and
 * 'all_deck'. After decks are clear it will call again 'fillDecks()' to fill
 * decks for future use.
 */

void Decks::clearDecks()
{
	all_deck.clear();
	all_deck.clear();
	totalCard= all_deck.size();
	//cout<<all_deck.size();
	//cout<<"total card"<<totalCard;
	fillDecks();

}

/*------------------------------------------------------------------------------
 * This method will update the decks cards. Iterating through total deck_list(6)
 * it will call 'getDeck()'. Then it will iterate through the whole deck to fill
 * it with cards. push back operation is used for that.
 */

void Decks::updateAllDeckCards()
{
	//cout<<"deck_list.size():- "<<deck_list.size();
	for(unsigned i=0;i<deck_list.size();i++)
	{

			vector<Card*> n_deck= deck_list.at(i)->getDeck();

			for(unsigned j=0;j<n_deck.size();j++)
			{
				//cout << ' ' << n_deck.at(j)->getCardSuite()<<"--"<<
				//n_deck.at(j)->getCardValue();
				//cout << '\n';
				all_deck.push_back(n_deck.at(j));
			}
		}
}

/*------------------------------------------------------------------------------
 * This method is used to give card as needed. It will return vector of cards.
 * It also keeps a track of decks size and number of cards after giving. A for
 * loop is used to iterate whole deck. If the magic number is hit while giving
 * card it will again call 'shuffle()' to shuffle again. ' all_deck.erase' is
 * used to erase each vector while giving card. After giving card if deck size
 * is zero it will call 'clearDecks()' to refresh it and refill again.
 */

vector<Card*> Decks::giveCard(int numberOfCards)
{

 vector<Card*> cards;
 //cout<<"numberOfCards to give:-"<<numberOfCards<<endl;
 int range = (all_deck.size()-numberOfCards);
 for(int i = all_deck.size()-1;i>=range;i--)
 {
	 if(i == white_magic) shuffle();
	 cards.push_back(all_deck.at(i));
	 all_deck.erase(all_deck.end() - 1);
 }

 //cout<<"Given to player cards:-\n";
 //for(unsigned n=0;n<cards.size();n++){
 	 //cout<<""<<cards.at(n)->getCardSuite()<<"--"<<cards.at(n)->getCardValue()
 			 //<<endl;
  //}
 //cout<<"******"<<totalCard<<"---"<<all_deck.size()<<endl;

 if(all_deck.size()==0)
 {
	 //cout<<"all_deck.size() is zero";
	 clearDecks();
 }


 return cards;

}

/*This function is necessary for testing purpose to check whether the number of
 * cards type of cards are same as real world calculation or not.
 */
void Decks::printAllDeckCards()
{

	cout<<"All Decks cards size:-"<<all_deck.size()<<endl;

	for (unsigned k=0; k<all_deck.size(); k++)
	{
			cout << ' ' << all_deck.at(k)->getCardSuite() << "--"<<
					all_deck.at(k)->getCardValue();
			cout << '\n';
		}
}

/*------------------------------------------------------------------------------
 * This method is used to train the users. It will calculate the total no of
 * high cards percentage in whole decks. While giving cards percentages of high
 * cards is changing. Based on the range of different percentages a secret word
 * is generated. This method will return the secret word to check whether users
 * answer is correct or not.
 */

string Decks::getHighCardPercentage()
{
	double count=0.00;
	int noOfCard=(int)all_deck.size();

	for (unsigned k=0; k<all_deck.size(); k++)
	{
				char cardVal = all_deck.at(k)->getCardValue();
				if(cardVal=='T' || cardVal=='J' || cardVal=='Q' || cardVal=='K'
						|| cardVal=='A')
				{
					//cout<<cardVal;
					count++;
				}
		}
	//cout <<"\nTotal High Cards:-"<<count<<"--"<<all_deck.size()<<"--"
			//<<(count / noOfCard)<<'\n';
	double percentage = ((count/noOfCard) * 100);
	//cout<<"Percentage:-"<<percentage<<endl;
	string secretWord;

	if(percentage>1.00 && percentage <=15.00)
	{
		cout<<"cocktails";
		secretWord="cocktails";
	}
	else if(percentage>15.00 && percentage <=24.00)
	{
		cout<<"coke";
		secretWord="coke";
	}
	else if(percentage>24.00 && percentage <=37.00)
	{
		cout<<"tea";
		secretWord="tea";
	}
	else if(percentage>37.00 && percentage <=45.00)
	{
		cout<<"coffee";
		secretWord="coffee";
	}
	else if(percentage>45.00 && percentage <=60.00)
	{
		cout<<"soda";
		secretWord="soda";
	}
	else if(percentage>60.00 && percentage <=75.00)
	{
		cout<<"juice";
		secretWord="juice";
	}
	else
	{
		cout<<"water";
	    secretWord="water";
	}

	return secretWord;

}

/*------------------------------------------------------------------------------
 * This method only generate the white magic number to shuffle again. 'rand' is
 * used to generate a random number between whole deck size.
 */

void Decks::generateWhiteMagicNumber()
{
	white_magic = rand()%all_deck.size() - 1;
	cout<<"magic:-"<<white_magic<<endl;
}

/*------------------------------------------------------------------------------
 * This method will show the menu items for questions answer round in training
 * section. Using switch case statement it will match 'userInput' number with
 * corresponding answer(userInputValue). It will return 'userInputValue'
 */

string Decks::showMenuItems()
{

		int userInput;
		string userInputValue;

		cout<<"Which drink do you like to prefer ?"<<"\n";
		cout<<"Please select from options below."<<"\n";
		cout<<"Press 1 for coke."<<"\n";
		cout<<"Press 2 for tea."<<"\n";
		cout<<"Press 3 for coffee."<<"\n";
		cout<<"Press 4 for soda."<<"\n";
		cout<<"Press 5 for juice."<<"\n";
		cout<<"Press 6 for water."<<"\n";
		cout<<"Press 7 for cocktails."<<"\n";

		fflush( stdout );
		cin>>userInput;
		cin.clear();
		cin.ignore(144,'\n');

		switch(userInput)
		{

		case 1:
			userInputValue = "coke";
			break;
		case 2:
			userInputValue = "tea";
			break;
		case 3:
			userInputValue = "coffee";
			break;
		case 4:
			userInputValue = "soda";
			break;
		case 5:
			userInputValue = "juice";
			break;
		case 6:
			userInputValue = "water";
			break;
		case 7:
			userInputValue = "cocktails";
			break;
		default:
			cout<<"Wrong option !... Please try again!"<<endl;
			showMenuItems();

		}

	return userInputValue;
}

/*------------------------------------------------------------------------------
 * This method will call 'showMenuItems' to ask a question to user. The user
 * input will be compared with the secretWord to match the high card percentage.
 * It will generate output statement according to answer.
 */

void Decks::askQuestion()
{

	string userInputValue = showMenuItems();

	string secretWord = getHighCardPercentage();

	if(!userInputValue.compare(secretWord))//function returns 0 if strings are equal hence the '!'
	  cout << "\nThat's Great!.\n";
	else
	  cout << "\nHmm.. Bad Mood now :P \n";


}
