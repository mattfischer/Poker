#ifndef WINS_HPP
#define WINS_HPP

#include "Hand.hpp"
#include "Cards.hpp"
#include "CardSet.hpp"

class Wins {
public:
	static void wins(int numPlayers, Cards *cards[], CardSet exclude, int wins[]);

private:
	static void winsRecursive(int numPlayers, Cards *cards[], CardSet exclude, int wins[], int *counts[], Hand::Type types[], int player);
	static void rankWins(int numPlayers, int *rankCounts[], int counts[], int wins[]);
	static void rankWinsRecursive(int numPlayers, int *rankCounts[], int counts[], int wins[], Card::Rank ranks[], int player);
};

#endif