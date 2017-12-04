/*
 * Decks.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: jayee
 */
#include <typeinfo>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<vector>
#include <ctime>
#include <utility>      // std::swap
#include "Decks.hpp"
using namespace std;

Decks::Decks()
{
//Initialize the deck:
	fillDecks();

}

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

vector<Card*> Decks::getAllDeckCards()
{

	return all_deck;
}

void Decks::clearDecks()
{
	all_deck.clear();
	deck_list.clear();
	totalCard= all_deck.size();
	//cout<<all_deck.size();
	//cout<<"total card"<<totalCard;
	fillDecks();

}

void Decks::updateAllDeckCards()
{
	//cout<<"deck_list.size():- "<<deck_list.size();
	for(unsigned i=0;i<deck_list.size();i++)
	{

			vector<Card*> n_deck= deck_list.at(i)->getDeck();

			for(unsigned j=0;j<n_deck.size();j++)
			{
				//cout << ' ' << n_deck.at(j)->getCardSuite()<<"--"<<
				n_deck.at(j)->getCardValue();
				//cout << '\n';
				all_deck.push_back(n_deck.at(j));
			}
		}
}

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

void Decks::generateWhiteMagicNumber()
{
	white_magic = rand()%all_deck.size() - 1;
	//cout<<"magic:-"<<white_magic<<endl;
}

string Decks::showMenuItems()
{

		int userInput;
		string userInputValue;

		cout<<"Which drink do you prefer ?"<<"\n";
		cout<<"please select from options below."<<"\n";
		cout<<"press 1 for coke."<<"\n";
		cout<<"press 2 for tea."<<"\n";
		cout<<"press 3 for coffee."<<"\n";
		cout<<"press 4 for soda."<<"\n";
		cout<<"press 5 for juice."<<"\n";
		cout<<"press 6 for water."<<"\n";
		cout<<"press 7 for cocktails."<<"\n";

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

void Decks::askQuestion()
{

	string userInputValue = showMenuItems();

	string secretWord = getHighCardPercentage();

	if(!userInputValue.compare(secretWord))//function returns 0 if strings are equal hence the '!'
	  cout << "\nThat's Great!.\n";
	else
	  cout << "\nHmm.. Bad Mood now :P \n";


}
