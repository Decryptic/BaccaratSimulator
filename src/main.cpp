/*
 * Gage Swenson
 * Dr Edwards
 * CS 408
 * 9 June 2021
 *
 * Term Assignment Phase 2
 * Baccarat Simulation
 *
*/

#include <iostream>
#include <time.h>

#include "Bet.h"
#include "Table.h"

using namespace std;

Table* promptTable() {
    cout << "\nEnter minimum bet: $";
    int min;
    cin >> min;

    cout << "Enter number of players: ";
    int nplayers;
    cin >> nplayers;
    
    Table *table = new Table(nplayers, min);
    
    cout << "\nEnter balance for Banker: $";
    cin >> table->banker->balance;
    
    for (int i = 0; i < nplayers; i++) {
        cout << "Enter balance for Player" << i+1 << ": $";
        cin >> table->players->at(i)->balance;
    }
    
    return table;
}

void promptBets(Table *table) {
    for (int i = 0; i < table->players->size(); i++) {
        cout << "\nNumber of bets for Player" << i+1 << ": ";
        int bets;
        cin >> bets;
        if (bets > 3) {
            cout << "\nNo more than 3 bets per hand!" << endl;
            i--;
            continue;
        }
        for (int j = 0; j < bets; j++) {
            Bet *bet = new Bet();
            cout << "\nPlayer" << i+1 << ", Bet " << j+1 << ':' << endl;
            cout << "Bet on player, banker, or tie (p/b/t): ";
            string on;
            cin >> on;
            char c = tolower(on[0]);
            if (c == 'p') {
                bet->on = Bet::Bets::Player;
            }
            else if (c == 'b') {
                bet->on = Bet::Bets::Banker;
            }
            else if (c == 't') {
                bet->on = Bet::Bets::Tie;
            }
            else {
                cout << "\nInvalid selection, try again!" << endl;
                delete bet;
                j--;
                continue;
            }
            cout << "Bet amount: $";
            double amount;
            cin >> amount;
            if (amount < 0) {
                cout << "\nBet must be a non-negative number!" << endl;
                delete bet;
                j--;
                continue;
            }
            if (amount < table->minimum && amount != 0) {
                cout << "\nBet must be above the table minimum!" << endl;
                delete bet;
                j--;
                continue;
            }
            if (amount > table->players->at(i)->balance) {
                cout << "\nBet must not exceed your balance!" << endl;
                delete bet;
                j--;
                continue;
            }
            bet->bet = amount;
            table->players->at(i)->bets->push_back(bet);
        }
    }
}

void playBaccarat() {
    Table *table = promptTable();
    
    int decision;
    do {
        cout << "\n1. Play a hand." << endl;
        cout << "2. View balances." << endl;
        cout << "3. Quit." << endl;
        cout << "\nyour selection: ";
        cin >> decision;
        if (decision == 1) {
            promptBets(table);
            if (table->deck->size() < 6) {
                cout << "\nShuffling..." << endl;
                table->deck->shuffle();
            }
            Bet::Bets winner = table->playHand();
            cout << "\nPlayer draws:" << endl;
            for (auto itr = table->playerHand->begin(); itr != table->playerHand->end(); itr++)
                cout << **itr << endl;
            cout << "\nBanker draws:" << endl;
            for (auto itr = table->bankerHand->begin(); itr != table->bankerHand->end(); itr++)
                cout << **itr << endl;
            if (winner == Bet::Bets::Player)
                cout << "\nPlayer wins!" << endl;
            else if (winner == Bet::Bets::Banker)
                cout << "\nBanker wins!" << endl;
            else
                cout << "\nTie!" << endl;
            table->debitBets(winner);
            table->clearHands();
            table->deleteBets();
        }
        else if (decision == 2) {
            cout << endl;
            table->showBalances(cout);
        }
    } while (decision != 3 && table->banker->balance > 0);
    cout << "\nResults:" << endl;
    table->showBalances(cout);
    if (table->banker->balance <= 0)
        cout << "You beat the dealer." << endl;
    
    delete table;
}

int performSimulation(Table *table, int nhands, int betDecision, int proportion, int onDecision) {
    int i;
    for (i = 0; i < nhands || nhands == -1; i++) {
        srand(time(NULL) + clock());
        Bet *bet = new Bet();
        if (betDecision == 1)
            bet->bet = proportion;
        else if (betDecision == 2)
            bet->bet = 1 + (table->players->at(0)->balance-1) * proportion;
        else {
            bet->bet = (rand() % (int)table->players->at(0)->balance) + 1;
        }
        if (onDecision == 1)
            bet->on = Bet::Bets::Banker;
        else if (onDecision == 2)
            bet->on = Bet::Bets::Player;
        else if (onDecision == 3)
            bet->on = Bet::Bets::Tie;
        else if (onDecision == 4) {
            if (rand() % 2 == 1)
                bet->on = Bet::Bets::Banker;
            else
                bet->on = Bet::Bets::Player;
        }
        else if (onDecision == 5) {
            int r = rand() % 100;
            if (r < 2)
                bet->on = Bet::Bets::Tie;
            else if (r < 51)
                bet->on = Bet::Bets::Player;
            else
                bet->on = Bet::Bets::Banker;
        }
        else {
            int r = rand() % 3;
            if (r == 0)
                bet->on = Bet::Bets::Tie;
            else if (r == 1)
                bet->on = Bet::Bets::Player;
            else
                bet->on = Bet::Bets::Banker;
        }
        table->players->at(0)->bets->push_back(bet);
        Bet::Bets winner = table->playHand();
        table->debitBets(winner);
        table->recordStats();
        table->clearHands();
        table->deleteBets();
        if (table->players->at(0)->balance < 1 || table->banker->balance < 1)
            return i;
    }
    return i;
}

void runSimulation() {
    Table *table = new Table(1, 1); // 1 player, 1 dollar minimum
    int nhands;
    int betDecision;
    double proportion = 1; // either proportion of a dollar, or proportion of balance, based on betDecision
    int onDecision;
    int initialPlayerBalance;
    int initialBankerBalance;
    cout << "\nEnter initial balance for banker: $";
    cin >> initialBankerBalance;
    cout << "Enter initial balance for player: $";
    cin >> initialPlayerBalance;
    cout << "Enter maximum number of hands (-1 for no limit): ";
    cin >> nhands;
    cout << "\nChoose your strategy:" << endl;
    cout << "1. Constant bet." << endl;
    cout << "2. Variable bet." << endl;
    cout << "3. Random bet." << endl;
    cout << "\nyour selection: ";
    cin >> betDecision;
    if (betDecision == 1) {
        cout << "\nConstant bet amount: $";
        cin >> proportion;
    }
    else if (betDecision == 2) {
        cout << "\nProportion of balance: %";
        cin >> proportion;
    }
    else if (betDecision != 3)
        return;
    if (betDecision == 1 && proportion > table->players->at(0)->balance) {
        cout << "\nCan't bet more than player balance." << endl;
        return;
    }
    if (betDecision == 2) {
        proportion = proportion / 100;
        if (proportion > 1) {
            cout << "\nCan't bet more than player balance." << endl; 
            return;
        }
    }
    cout << "\nBet on:" << endl;
    cout << "1. Banker deterministic." << endl;
    cout << "2. Player deterministic." << endl;
    cout << "3. Tie deterministic." << endl;
    cout << "4. Player/banker 50/50 split." << endl;
    cout << "5. Player/banker/tie 49/49/2 split." << endl;
    cout << "6. Player/banker/tie 33/33/33 split." << endl;
    cout << "7. Exit." << endl;
    cout << "\nyour selection: ";
    cin >> onDecision;
    if (onDecision == 7)
        return;
    string repeat;
    do {
        double max = initialPlayerBalance;
        table->banker->balance = initialBankerBalance;
        table->players->at(0)->balance = initialPlayerBalance;
        int runs = performSimulation(table, nhands, betDecision, proportion, onDecision);
        for (int i = 0; i < table->players->at(0)->stats->size(); i++) {
            double balanceAt = table->players->at(0)->stats->at(i)->balance;
            if (balanceAt > max)
                max = balanceAt;
            //cout << i+1 << ": $" << balanceAt << endl;
        }
        if (table->players->at(0)-> balance < 1)
            cout << "\nPlayer went broke after ";
        else if (table->banker->balance < 1)
            cout << "\nBanker went broke after ";
        else
            cout << "\nAfter ";
        cout << runs+1 << " hands." << endl;
        cout << "The player's balance reached a high of $" << max << '.' << endl;
        table->showBalances(cout);
        table->clearStats();
        cout << "\nRepeat simulation (y/n): ";
        cin >> repeat;
    } while (tolower(repeat[0]) == 'y');
    delete table;
}

int main(int argc, char **argv) {
    cout << "\nWelcome to Baccarat" << endl;
    int decision = 0;
    do {
        cout << "\n1. Play a game." << endl;
        cout << "2. Run a simulation." << endl;
        cout << "3. Exit." << endl;
        cout << "\nyour selection: ";
        cin >> decision;
        if (decision == 1)
            playBaccarat();
        else if (decision == 2)
            runSimulation();
    } while (decision != 3);
    cout << endl;
    return 0;
}


