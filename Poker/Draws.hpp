#ifndef DRAWS_HPP
#define DRAWS_HPP

#include "Cards.hpp"
#include "Hand.hpp"
#include "CardSet.hpp"

#include <vector>

class Draws {
public:
	static std::vector<Cards> draws(const Cards &cards, const CardSet &exclude, Hand::Type type);
	static Hand nut(const Cards &cards, const CardSet &exclude, Hand::Type type = Hand::TypeNone);
	static std::vector<int> counts(const Cards &cards, const CardSet &exclude);
	static std::vector<int> rankCounts(const Cards &cards, const CardSet &exclude, Hand::Type type);

private:
	static std::vector<Cards> drawsRecursive(Cards &cards, const CardSet &exclude, Hand::Type type, int start);
	static void countsRecursive(Cards &cards, const CardSet &exclude, std::vector<int> &counts, int start);
	static void rankCountsRecursive(Cards &cards, const CardSet &exclude, Hand::Type type, std::vector<int> &counts, int start);
};

#endif