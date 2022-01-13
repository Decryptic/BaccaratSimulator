/*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Deck.cpp
 *
*/

#include <time.h>

#include "Deck.h"

using namespace std;

void Deck::populateDeck() {
    Card::Face faces[] = {
        Card::Face::Ace,
        Card::Face::Two,
        Card::Face::Three,
        Card::Face::Four,
        Card::Face::Five,
        Card::Face::Six,
        Card::Face::Seven,
        Card::Face::Eight,
        Card::Face::Nine,
        Card::Face::Ten,
        Card::Face::Jack,
        Card::Face::Queen,
        Card::Face::King
    };
    Card::Suit suits[] = {
        Card::Suit::Clubs,
        Card::Suit::Diamonds,
        Card::Suit::Hearts,
        Card::Suit::Spades
    };
    for (int i = 0; i < ndecks; i++) {
        for (int j = 0; j < 13; j++) {
            for (int k = 0; k < 4; k++) {
                deck->push_back(new Card(faces[j], suits[k]));
            }
        }
    }
}

void Deck::shuffle() {
    srand(time(NULL) + clock());
    while (discarded->size() > 0) {
        deck->push_back(discarded->back());
        discarded->pop_back();
    }
    for (int i = 0; i < nshuffles; i++) {
        int randomIndex;
        while (deck->size() > 0) {
            randomIndex = rand() % deck->size();
            discarded->push_back(deck->at(randomIndex));
            deck->erase(deck->begin() + randomIndex);
        }
        while (discarded->size() > 0) {
            randomIndex = rand() % discarded->size();
            deck->push_back(discarded->at(randomIndex));
            discarded->erase(discarded->begin() + randomIndex);
        }
    }
}

Card* Deck::pop() {
    if (size() == 0)
        return NULL;
    Card *dealt = deck->back();
    deck->pop_back();
    discarded->push_back(dealt);
    return dealt;
}

int Deck::count() const {
    int count = 0;
    for (auto itr = discarded->begin(); itr != discarded->end(); itr++) {
        count += (*itr)->count();
    }
    return count;
}



