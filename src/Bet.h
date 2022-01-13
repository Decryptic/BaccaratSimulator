/*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Bet.h
 *
*/

#ifndef BET
#define BET

using namespace std;

class Bet {
    public:
        enum class Bets { Player, Banker, Tie };
        double bet;
        Bets on;
};

#endif
