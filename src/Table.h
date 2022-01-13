/*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Table.h
 *
*/

#ifndef TABLE
#define TABLE

#include <ostream>
#include <vector>

#include "Bet.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"

#define DEFAULT_PLAYER_COUNT 1
#define DEFAULT_MINIMUM_BET 25

using namespace std;

class Table {
    public:
        Table() : Table(DEFAULT_PLAYER_COUNT, DEFAULT_MINIMUM_BET) {}
        Table(unsigned int nplayers, unsigned int _minimum) {
            minimum = _minimum;
            deck = new Deck();
            banker = new Player();
            players = new vector<Player*>();
            if (nplayers < 1)
                nplayers = 1;
            for (int i = 0; i < nplayers; i++)
                players->push_back(new Player());
            bankerHand = new vector<Card*>();
            playerHand = new vector<Card*>();
        }
        ~Table() {
            delete banker;
            for (auto itr = players->begin(); itr != players->end(); itr++)
                delete *itr;
            delete players;
            delete bankerHand;
            delete playerHand;
            delete deck;
        }
        ostream& showBalances(ostream&) const;
        void debitBets(Bet::Bets);
        void clearHands();
        void deleteBets();
        void recordStats(); // phase iii
        void clearStats(); // phase iii
        Bet::Bets playHand();
        Deck *deck;
        Player *banker;
        vector<Player*> *players;
        vector<Card*> *bankerHand;
        vector<Card*> *playerHand;
        unsigned int minimum;
    private:
        unsigned int sumOfHand(vector<Card*>*);
};

#endif



