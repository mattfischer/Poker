#ifndef DRAWS_HPP
#define DRAWS_HPP

#include "Cards.hpp"
#include "Hand.hpp"
#include "CardSet.hpp"

#include <vector>

class Draws {
public:
	static std::vector<Cards> draws(const Cards &cards, const CardSet &exclude, Hand::Type type);
	static int numDraws(const Cards &cards, const CardSet &exclude, Hand::Type type);
	static Hand nut(const Cards &cards, const CardSet &exclude, Hand::Type type = Hand::TypeNone);
	static void counts(const Cards &cards, const CardSet &exclude, int counts[Hand::NumTypes]);
	static void rankCounts(const Cards &cards, const CardSet &exclude, Hand::Type type, int counts[Card::NumRanks]);

private:
	static std::vector<Cards> drawsRecursive(Cards &cards, const CardSet &exclude, Hand::Type type, int start);
	static int numDrawsRecursive(Cards &cards, const CardSet &exclude, Hand::Type type, int start);
	static void countsRecursive(Cards &cards, const CardSet &exclude, int counts[Hand::NumTypes], int start);
	static void rankCountsRecursive(Cards &cards, const CardSet &exclude, Hand::Type type, int counts[Card::NumRanks], int start);
};

#endif