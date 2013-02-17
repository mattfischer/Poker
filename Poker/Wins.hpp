#ifndef WINS_HPP
#define WINS_HPP

#include "Hand.hpp"

class Wins {
public:
	static void wins(int numPlayers, int *counts[], int wins[]);

private:
	static void winsRecursive(int numPlayers, int *counts[], int wins[], Hand::Type types[], int player);
};

#endif