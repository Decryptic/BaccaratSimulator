# BaccaratSimulator
Simulate playing thousands of Baccarat hands in an instant.

I wrote this software while working on my Computer Science degree at the University of Hawaii Hilo in July 2021. The assignment was to create a simulation, any simulation. I chose to create a simulation of what it would be like to play thousands of hands at a Baccarat table, and I chose to create the simulation in C++.

When you run the program, you will be given two options: play a game, or run a simulation.

![](https://github.com/Decryptic/BaccaratSimulator/blob/main/img/0baccaratPlaySetup.png)

Playing a game looks like the image below, where the number of players are selected with a given balance, then each player can place on the outcome of the hand: either player, banker or tie. Then a hand is dealt, and the players are either debited or credited.

Sample hand 1:
![](https://github.com/Decryptic/BaccaratSimulator/blob/main/img/1baccaratPlayHand0.png)

Sample hand 2:
![](https://github.com/Decryptic/BaccaratSimulator/blob/main/img/2baccaratPlayHand1.png)

Option two, running a simulation, looks like what is pictured below. Only one player plays against the house in a simultion. Once initial balances are chosen, then the betting strategy is selected: player, banker, tie, or some combination. Also, the players bet amount must be selected: either constant, all-in on every hand, or random. A stats class was added to keep track of how the player is doing throughout the course of the game. The simulation then runs until the maximum hands is played, otherwise until the the player goes broke. At the end of the simulation, it shows how many hands were played, how much the player had at their peak, and how much they have at the end.

Setting up a simulation:
![](https://github.com/Decryptic/BaccaratSimulator/blob/main/img/3baccaratSimulateSetup.png)

Repeating a simulation:
![](https://github.com/Decryptic/BaccaratSimulator/blob/main/img/4baccaratSimulations.png)
