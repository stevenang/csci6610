/*==============================================================================
 *                                                           BlackJackPlayer.hpp
 * Author      : Steven Kho Ang
 * Version     : 1.0
 * Created     : Created on November 17, 2017
 * Last Update:  Last Update on December 03, 2017
 * Copyright   : Copyright (c) 2017 STEVEN KHO ANG.
 *
 * This is an header file for  BlackJackPlayer class
 *
 * BlackJackPlayer()            Default Constructor
 * BlackJackPlayer(             Constructor
 *          const string& name,
 *          bool isComputer)
 * addWinCount()                Increment Win counter
 * addTieCount()                Increment Tie counter
 * addLoseCount()               Increment Lose counter
 * getLoseCount()               Return user's lose count
 * getStatistic()               String representation of user's game statistic
 * getTieCount()                Return user's tie count
 * getWinCount()                Return user's winning count
 * isHitting(int dealerCard)    Determine whether the user will hit or not
 * isStanding(int dealerCard)   Determine whether the user will stand or not
 * isSurrender(int dealerCard)  Determine whether the user will surrender or not
 * toString()                   String representation of the user's information
 *
 * ostream &operator<< (ostream &os, const BlackJackPalyer &player)
 *                              Overload the operator<<
 *
 *==============================================================================
 */
#ifndef BLACKJACKPLAYER_HPP_
#define BLACKJACKPLAYER_HPP_

#include "Player.hpp"
#include "Card.hpp"

class BlackJackPlayer: public Player {
public:
	BlackJackPlayer();
	BlackJackPlayer(const string& name, bool isComputer);
    void addWinCount() { this->winCount++; }
    void addTieCount() { this->tieCount++; }
    void addLoseCount() {this->loseCount++; }
    int getLoseCount() const { return this->loseCount; }
    string getStatistic() const;
    int getTieCount() const { return this->tieCount; }
    int getWinCount() const { return this->winCount; }
    bool isHitting(int dealerCard);
    bool isStanding(int dealerCard);
    bool isSurrender(int dealderCard);
    string toString() const;


    virtual ~BlackJackPlayer();

private:
    //int winCount = 0;
    //int loseCount = 0;
    //int tieCount = 0;
};

// Overloaded operator <<
ostream &operator<< (ostream &os, const BlackJackPlayer &player);

#endif /* BLACKJACKPLAYER_HPP_ */
