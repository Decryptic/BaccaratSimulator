/*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Deck.h
 *
*/

#ifndef DECK
#define DECK

#include <vector>

#include "Card.h"

#define DEFAULT_DECK_COUNT 6
#define DEFAULT_SHUFFLE_COUNT 8

using namespace std;

class Deck {
    public:
        Deck() : Deck(DEFAULT_DECK_COUNT, DEFAULT_SHUFFLE_COUNT) {}
        Deck(unsigned int _ndecks, unsigned int _nshuffles) {
            ndecks = 1;
            if (_ndecks > 0)
                ndecks = _ndecks;
            nshuffles = 1;
            if (_nshuffles > 0)
                nshuffles = _nshuffles;
            deck = new vector<Card*>();
            discarded = new vector<Card*>();
            
            populateDeck();
            shuffle();
        }
        ~Deck() {
            for (auto itr = deck->begin(); itr != deck->end(); itr++)
                delete *itr;
            for (auto itr = discarded->begin(); itr != discarded->end(); itr++)
                delete *itr;
            delete deck, discarded;
        }
        Card* pop();
        void shuffle();
        unsigned int size() const {
            return deck->size();
        }
        int count() const;
    private:
        unsigned int ndecks;
        unsigned int nshuffles;
        vector<Card*> *deck;
        vector<Card*> *discarded;
        void populateDeck();
};

#endif


