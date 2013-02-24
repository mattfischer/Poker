#ifndef WINS_HPP
#define WINS_HPP

#include "Hand.hpp"
#include "Cards.hpp"
#include "CardSet.hpp"

#include <vector>

class Wins {
public:
	static std::vector<int> wins(const std::vector<Cards> &cards, const CardSet &exclude);

private:
	static void winsRecursive(const std::vector<Cards> &cards, const CardSet &exclude, std::vector<int> &wins, const std::vector<std::vector<int> > &counts, std::vector<Hand::Type> &types, int player);
	static void rankWins(const std::vector<Cards> &cards, const CardSet &exclude, std::vector<int> &wins, const std::vector<std::vector<int> > &counts, const std::vector<Hand::Type> &types, Hand::Type type);
	static void rankWinsRecursive(const std::vector<std::vector<int> > &rankCounts, const std::vector<std::vector<int> > &counts, const std::vector<Hand::Type> &types, Hand::Type type, std::vector<int> &wins, std::vector<Card::Rank> &ranks, int player);
};

#endif