/*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Card.h
 *
*/

#ifndef CARD
#define CARD

#include <ostream>
#include <string>

using namespace std;

class Card {
    public:
        enum class Suit { Clubs, Diamonds, Hearts, Spades };
        enum class Face { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
        Card() : Card(Face::Ace, Suit::Spades) {}
        Card(Face _face, Suit _suit) {
            face = _face;
            suit = _suit;
        }
        int value() const; // face value
        int count() const; // count value
        friend ostream& operator<<(ostream &out, const Card &card) {
		out << card.show();
		return out;
	}
	string show() const;
	string showSuit() const;
	string showFace() const;
    private:
        Suit suit;
        Face face;
};

#endif


