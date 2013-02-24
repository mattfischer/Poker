#include "Wins.hpp"
#include "Draws.hpp"

#include <vector>

std::vector<int> Wins::wins(const std::vector<Cards> &cards, const CardSet &exclude)
{
	std::vector<std::vector<int> > counts(cards.size());
	std::vector<Hand::Type> types(cards.size());
	std::vector<int> wins(cards.size());

	for(int i=0; i<cards.size(); i++) {
		wins[i] = 0;
		counts[i] = Draws::counts(cards[i], exclude);
	}

	winsRecursive(cards, exclude, wins, counts, types, 0);

	return wins;
}

void Wins::winsRecursive(const std::vector<Cards> &cards, const CardSet &exclude, std::vector<int> &wins, const std::vector<std::vector<int> > &counts, std::vector<Hand::Type> &types, int player)
{
	if(player == cards.size()) {
		Hand::Type maxType = Hand::TypeNone;
		int numOfType = 0;
		for(int i=0; i<types.size(); i++) {
			if(types[i] > maxType) {
				maxType = types[i];
				numOfType = 1;
			} else if(types[i] == maxType) {
				numOfType++;
			}
		}

		if(numOfType == 1) {
			int count = 1;
			for(int i=0; i<counts.size(); i++) {
				count *= counts[i][types[i]];
			}

			for(int i=0; i<types.size(); i++) {
				if(types[i] == maxType) {
					wins[i] += count;
				}
			}
		} else {
			rankWins(cards, exclude, wins, counts, types, maxType);
		}
	} else {
		for(int i=1; i<Hand::NumTypes; i++) {
			if(counts[player][i] > 0) {
				types[player] = (Hand::Type)i;
				winsRecursive(cards, exclude, wins, counts, types, player + 1);
			}
		}
	}
}

void Wins::rankWins(const std::vector<Cards> &cards, const CardSet &exclude, std::vector<int> &wins, const std::vector<std::vector<int> > &counts, const std::vector<Hand::Type> &types, Hand::Type type)
{
	std::vector<std::vector<int> > rankCounts(cards.size());
	for(int i=0; i<cards.size(); i++) {
		if(types[i] == type) {
			rankCounts[i] = Draws::rankCounts(cards[i], exclude, type);
		}
	}

	std::vector<Card::Rank> ranks(cards.size());
	rankWinsRecursive(rankCounts, counts, types, type, wins, ranks, 0);
}

void Wins::rankWinsRecursive(const std::vector<std::vector<int> > &rankCounts, const std::vector<std::vector<int> > &counts, const std::vector<Hand::Type> &types, Hand::Type type, std::vector<int> &wins, std::vector<Card::Rank> &ranks, int player)
{
	if(player == rankCounts.size()) {
		Card::Rank maxRank = Card::RankNone;
		int numOfRank = 0;
		for(int i=0; i<ranks.size(); i++) {
			if(Card::aceHigh(ranks[i]) > Card::aceHigh(maxRank)) {
				maxRank = ranks[i];
				numOfRank = 1;
			} else if(ranks[i] == maxRank) {
				numOfRank++;
			}
		}

		int count = 1;
		for(int i=0; i<rankCounts.size(); i++) {
			if(types[i] == type) {
				count *= rankCounts[i][ranks[i]];
			} else {
				count *= counts[i][types[i]];
			}
		}

		for(int i=0; i<rankCounts.size(); i++) {
			if(types[i] == type && ranks[i] == maxRank) {
				wins[i] += count / numOfRank;
			}
		}
	} else {
		if(types[player] == type) {
			for(int i=1; i<Card::RankAceHigh; i++) {
				if(rankCounts[player][i] > 0) {
					ranks[player] = (Card::Rank)i;
					rankWinsRecursive(rankCounts, counts, types, type, wins, ranks, player + 1);
				}
			}
		} else {
			rankWinsRecursive(rankCounts, counts, types, type, wins, ranks, player + 1);
		}
	}
}
