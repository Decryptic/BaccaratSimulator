 /*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Card.cpp
 *
*/

#include "Card.h"

using namespace std;

int Card::value() const {
    switch (face) {
        case Face::Ace:
            return 1;
        case Face::Two:
            return 2;
        case Face::Three:
            return 3;
        case Face::Four:
            return 4;
        case Face::Five:
            return 5;
        case Face::Six:
            return 6;
        case Face::Seven:
            return 7;
        case Face::Eight:
            return 8;
        case Face::Nine:
            return 9;
    }
    return 0;
}

int Card::count() const {
    switch (face) {
        case Face::Ace:
            return 1;
        case Face::Two:
            return -1;
        case Face::Three:
            return -1;
        case Face::Four:
            return -1;
        case Face::Five:
            return -1;
        case Face::Six:
            return -1;
        case Face::Seven:
            return 0;
        case Face::Eight:
            return 0;
        case Face::Nine:
            return 0;
    }
    return 1;
}

string Card::show() const {
    return showFace() + " of " + showSuit();
}

string Card::showSuit() const {
    switch (suit) {
        case Suit::Clubs:
            return "Clubs";
        case Suit::Diamonds:
            return "Diamonds";
        case Suit::Hearts:
            return "Hearts";
        case Suit::Spades:
            return "Spades";
    }
    return "Suits";
}

string Card::showFace() const {
    switch (face) {
        case Face::Ace:
            return "Ace";
        case Face::Two:
            return "2";
        case Face::Three:
            return "3";
        case Face::Four:
            return "4";
        case Face::Five:
            return "5";
        case Face::Six:
            return "6";
        case Face::Seven:
            return "7";
        case Face::Eight:
            return "8";
        case Face::Nine:
            return "9";
        case Face::Ten:
            return "10";
        case Face::Jack:
            return "Jack";
        case Face::Queen:
            return "Queen";
        case Face::King:
            return "King";
    }
    return "Card";
}




