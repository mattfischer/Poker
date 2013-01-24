#ifndef DRAWS_HPP
#define DRAWS_HPP

#include "Cards.hpp"
#include "Hand.hpp"

#include <vector>

class Draws {
public:
	static std::vector<Cards> draws(const Cards &cards, const std::vector<Card> &available, Hand::Type type);
	static int numDraws(const Cards &cards, const std::vector<Card> &available, Hand::Type type);
	static Hand nut(const Cards &cards, const std::vector<Card> &available, Hand::Type type = Hand::TypeNone);

private:
	static std::vector<Cards> drawsRecursive(Cards &cards, const std::vector<Card> &available, Hand::Type type, int start);
	static int numDrawsRecursive(Cards &cards, const std::vector<Card> &available, Hand::Type type, int start);
};

#endif