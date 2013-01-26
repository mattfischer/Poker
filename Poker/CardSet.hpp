#ifndef CARD_SET_HPP
#define CARD_SET_HPP

#include "Card.hpp"
#include "Cards.hpp"

class CardSet {
public:
	CardSet();

	void add(const Card &card);
	void add(const Cards &cards);

	bool contains(const Card &card) const;

private:
	bool mCards[Card::NumCards];
};

#endif