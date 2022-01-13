/*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Stats.h
 *
*/

#ifndef STATS
#define STATS

using namespace std;

class Stats {
    public:
        Stats() : Stats(0, 0, 0) {}
        Stats(int _balance, int _wins, int _losses) {
            balance = _balance;
            wins    = _wins;
            losses  = _losses;
        }
        int balance, wins, losses;
};

#endif



