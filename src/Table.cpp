/*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Table.cpp
 *
 * Phase III Changelog:
 * Added a recordStats() function, which is
 * meant to be called after every call to
 * playHand(), similar to debitBets() and
 * clearHands().
 *
*/

#include "Table.h"

using namespace std;

Bet::Bets Table::playHand() {
    if (deck->size() < 6)
        deck->shuffle();
    playerHand->push_back(deck->pop());
    bankerHand->push_back(deck->pop());
    playerHand->push_back(deck->pop());
    bankerHand->push_back(deck->pop());
    unsigned int bankerSum = sumOfHand(bankerHand);
    unsigned int playerSum = sumOfHand(playerHand);
    if (bankerSum == 8 || bankerSum == 9 || playerSum == 8 || playerSum == 9) {
        if (bankerSum > playerSum)
            return Bet::Bets::Banker;
        if (playerSum > bankerSum)
            return Bet::Bets::Player;
        return Bet::Bets::Tie;
    }
    bool playerDraws = playerSum < 6;
    if (playerDraws)
        playerHand->push_back(deck->pop());
    else if (bankerSum < 6)
        bankerHand->push_back(deck->pop());
    
    if (playerDraws) {
        int plcv = playerHand->back()->value(); // player's last card's value
        if (plcv == 0 || plcv == 1 || plcv == 9) {
            if (bankerSum < 4)
                bankerHand->push_back(deck->pop());
        }
        else if (plcv == 8) {
            if (bankerSum < 3)
                bankerHand->push_back(deck->pop());
        }
        else if (plcv == 6 || plcv == 7) {
            if (bankerSum < 7)
                bankerHand->push_back(deck->pop());
        }
        else if (plcv == 4 || plcv == 5) {
            if (bankerSum < 6)
                bankerHand->push_back(deck->pop());
        }
        else if (plcv == 2 || plcv == 3) {
            if (bankerSum < 5)
                bankerHand->push_back(deck->pop());
        }
    }
    
    bankerSum = sumOfHand(bankerHand);
    playerSum = sumOfHand(playerHand);
    if (bankerSum > playerSum)
        return Bet::Bets::Banker;
    if (playerSum > bankerSum)
        return Bet::Bets::Player;
    return Bet::Bets::Tie;
}

unsigned int Table::sumOfHand(vector<Card*> *hand) {
    unsigned int sum = 0;
    for (auto itr = hand->begin(); itr != hand->end(); itr++) {
        sum += (*itr)->value();
    }
    return sum % 10;
}

void Table::debitBets(Bet::Bets winner) {
    for (auto itrP = players->begin(); itrP != players->end(); itrP++) { // player iterator
        for (auto itrB = (*itrP)->bets->begin(); itrB != (*itrP)->bets->end(); itrB++) { // bet iterator
            double value = (*itrB)->bet;
            if ((*itrB)->on == winner) {
                if (winner == Bet::Bets::Tie) {
                    value = (*itrB)->bet * 8;
                }
                else if (winner == Bet::Bets::Banker) {
                    value = (*itrB)->bet * 0.95;
                }
                banker->balance -= value; // debit banker
                (*itrP)->balance += value; // credit player
                (*itrP)->wins++;
                banker->losses++; // phase iii addition
            }
            else if (winner != Bet::Bets::Tie) {
                (*itrP)->balance -= value; // debit player
                banker->balance += value; // credit banker
                (*itrP)->losses++;
                banker->wins++; // phase iii addition
            }
        }
    }
}

void Table::deleteBets() {
    for (auto itr0 = players->begin(); itr0 != players->end(); itr0++) {
        for (auto itr1 = (*itr0)->bets->begin(); itr1 != (*itr0)->bets->end(); itr1++)
            delete *itr1;
        (*itr0)->bets->clear();
    }
}

void Table::clearHands() {
    bankerHand->clear();
    playerHand->clear();
}

ostream& Table::showBalances(ostream &out) const {
    out << "Banker: $" << banker->balance << endl;
    for (int i = 0; i < players->size(); i++) {
        out << "Player" << i+1 << ": $" << players->at(i)->balance << endl;
    }
    return out;
}

void Table::recordStats() {
    banker->recordStat();
    for (auto itr = players->begin(); itr != players->end(); itr++) {
        (*itr)->recordStat();
    }
}

void Table::clearStats() {
    banker->clearStats();
    for (auto itr = players->begin(); itr != players->end(); itr++) {
        (*itr)->clearStats();
    }
}




