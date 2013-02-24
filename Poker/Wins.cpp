#include "Wins.hpp"
#include "Draws.hpp"

void Wins::wins(int numPlayers, Cards cards[], CardSet exclude, int wins[])
{
	int **counts = new int*[numPlayers];
	Hand::Type *types = new Hand::Type[numPlayers];
	for(int i=0; i<numPlayers; i++) {
		wins[i] = 0;
		counts[i] = new int[Hand::NumTypes];
		Draws::counts(cards[i], exclude, counts[i]);
	}

	winsRecursive(numPlayers, cards, exclude, wins, counts, types, 0);
	delete[] types;
	for(int i=0; i<numPlayers; i++) {
		delete[] counts[i];
	}
	delete[] counts;
}

void Wins::winsRecursive(int numPlayers, Cards cards[], CardSet exclude, int wins[], int *counts[], Hand::Type types[], int player)
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

		if(numOfType == 1) {
			int count = 1;
			for(int i=0; i<numPlayers; i++) {
				count *= counts[i][types[i]];
			}

			for(int i=0; i<numPlayers; i++) {
				if(types[i] == maxType) {
					wins[i] += count;
				}
			}
		} else {
			int **rankCounts = new int*[numPlayers];
			int *counts2 = new int[numPlayers];
			for(int i=0; i<numPlayers; i++) {
				if(types[i] == maxType) {
					rankCounts[i] = new int[Card::NumRanks];
					Draws::rankCounts(cards[i], exclude, maxType, rankCounts[i]);
				} else {
					rankCounts[i] = 0;
					counts2[i] = counts[i][types[i]];
				}
			}
			rankWins(numPlayers, rankCounts, counts2, wins);
			for(int i=0; i<numPlayers; i++) {
				if(rankCounts[i]) {
					delete[] rankCounts[i];
				}
			}
			delete[] rankCounts;
			delete[] counts2;
		}
	} else {
		for(int i=1; i<Hand::NumTypes; i++) {
			if(counts[player][i] > 0) {
				types[player] = (Hand::Type)i;
				winsRecursive(numPlayers, cards, exclude, wins, counts, types, player + 1);
			}
		}
	}
}

void Wins::rankWins(int numPlayers, int *rankCounts[], int counts[], int wins[])
{
	Card::Rank *ranks = new Card::Rank[numPlayers];
	rankWinsRecursive(numPlayers, rankCounts, counts, wins, ranks, 0);
	delete[] ranks;
}

void Wins::rankWinsRecursive(int numPlayers, int *rankCounts[], int counts[], int wins[], Card::Rank ranks[], int player)
{
	if(player == numPlayers) {
		Card::Rank maxRank = Card::RankNone;
		int numOfRank = 0;
		for(int i=0; i<numPlayers; i++) {
			if(Card::aceHigh(ranks[i]) > Card::aceHigh(maxRank)) {
				maxRank = ranks[i];
				numOfRank = 1;
			} else if(ranks[i] == maxRank) {
				numOfRank++;
			}
		}

		int count = 1;
		for(int i=0; i<numPlayers; i++) {
			if(rankCounts[i]) {
				count *= rankCounts[i][ranks[i]];
			} else {
				count *= counts[i];
			}
		}

		for(int i=0; i<numPlayers; i++) {
			if(rankCounts[i]) {
				if(ranks[i] == maxRank) {
					wins[i] += count / numOfRank;
				}
			}
		}
	} else {
		if(rankCounts[player]) {
			for(int i=1; i<Card::RankAceHigh; i++) {
				if(rankCounts[player][i] > 0) {
					ranks[player] = (Card::Rank)i;
					rankWinsRecursive(numPlayers, rankCounts, counts, wins, ranks, player + 1);
				}
			}
		} else {
			rankWinsRecursive(numPlayers, rankCounts, counts, wins, ranks, player + 1);
		}
	}
}
