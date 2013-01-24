#ifndef DRAWS_HPP
#define DRAWS_HPP

#include "Cards.hpp"
#include "Hand.hpp"

#include <vector>

class Draws {
public:
	static std::vector<Cards> draws(Hand::Type type, const Cards &cards, const std::vector<Card> &available);
	static int numDraws(Hand::Type type, const Cards &cards, const std::vector<Card> &available);

private:
	static std::vector<Cards> drawsRecursive(Hand::Type type, Cards &cards, const std::vector<Card> &available, int start);
	static int numDrawsRecursive(Hand::Type type, Cards &cards, const std::vector<Card> &available, int start);
};

#endif