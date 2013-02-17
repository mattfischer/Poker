#include "Wins.hpp"

void Wins::wins(int numPlayers, int *counts[], int wins[])
{
	Hand::Type *types = new Hand::Type[numPlayers];
	for(int i=0; i<numPlayers; i++) {
		wins[i] = 0;
	}

	winsRecursive(numPlayers, counts, wins, types, 0);
	delete[] types;
}

void Wins::winsRecursive(int numPlayers, int *counts[], int wins[], Hand::Type types[], int player)
{
	if(player == numPlayers) {
		Hand::Type maxType = Hand::TypeNone;
		int numOfType = 0;
		for(int i=0; i<numPlayers; i++) {
			if(types[i] > maxType) {
				maxType = types[i];
				numOfType = 1;
			} else if(types[i] == maxType) {
				numOfType++;
			}
		}

		int count = 1;
		for(int i=0; i<numPlayers; i++) {
			count *= counts[i][types[i]];
		}

		for(int i=0; i<numPlayers; i++) {
			if(types[i] == maxType) {
				wins[i] += count / numOfType;
			}
		}
	} else {
		for(int i=1; i<Hand::NumTypes; i++) {
			types[player] = (Hand::Type)i;
			winsRecursive(numPlayers, counts, wins, types, player + 1);
		}
	}
}