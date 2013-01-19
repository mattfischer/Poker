#ifndef CARDS_HPP
#define CARDS_HPP

#include "Card.hpp"

#include <ostream>

class Cards {
public:
	Cards(unsigned int size) { mSize = size; mCards = new Card[size]; }
	~Cards() { delete[] mCards; }

	int size() const { return mSize; }
	const Card &operator[](unsigned int n) const { return mCards[n]; }
	Card &operator[](unsigned int n) { return mCards[n]; }

	bool add(const Card &card);

private:
	Card *mCards;
	unsigned int mSize;
};

std::ostream &operator<<(std::ostream &o, const Cards &cards);

#endif