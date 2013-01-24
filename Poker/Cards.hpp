#ifndef CARDS_HPP
#define CARDS_HPP

#include "Card.hpp"

#include <ostream>

class Cards {
public:
	Cards(unsigned int size);
	Cards(const Cards &other);
	~Cards();

	int size() const { return mSize; }
	int filled() const { return mFilled; }
	int empty() const { return mSize - mFilled; }

	const Card &operator[](unsigned int n) const { return mCards[n]; }
	Card &operator[](unsigned int n) { return mCards[n]; }

	bool push(const Card &card);
	bool push(const Cards &cards);
	bool pop(int n = 1);

private:
	Card *mCards;
	unsigned int mSize;
	unsigned int mFilled;
};

std::ostream &operator<<(std::ostream &o, const Cards &cards);

#endif