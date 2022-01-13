/*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Player.h
 *
 * Phase III Changelog
 * Players now have a list of stats.
 * Also a function recordStat(), called
 * every hand, and clearStats(), called
 * at the end of every simulation.
 *
*/

#ifndef PLAYER
#define PLAYER

#include <vector>

#include "Bet.h"
#include "Stats.h"

#define DEFAULT_BALANCE 1000

using namespace std;

class Player {
    public:
        Player() : Player(DEFAULT_BALANCE) {}
        Player(double _balance) {
            balance = _balance;
            bets = new vector<Bet*>();
            stats = new vector<Stats*>();
            wins = losses = 0;
        }
        ~Player() {
            for (auto itr = bets->begin(); itr != bets->end(); itr++)
                delete *itr;
            clearStats();
            delete bets, stats;
        }
        void recordStat() { // phase iii
            stats->push_back(new Stats(balance, wins, losses));
        }
        void clearStats() { // phase iii
            for (auto itr = stats->begin(); itr != stats->end(); itr++)
                delete *itr;
            stats->clear();
        }
        double balance;
        vector<Bet*> *bets;
        vector<Stats*> *stats;
        unsigned int wins, losses;
};

#endif


