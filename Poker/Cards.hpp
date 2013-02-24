#ifndef CARDS_HPP
#define CARDS_HPP

#include "Card.hpp"

#include <vector>
#include <ostream>

class Cards {
public:
	Cards(unsigned int size = 0);

	int size() const { return mCards.size(); }
	int filled() const { return mFilled; }
	int empty() const { return mCards.size() - mFilled; }

	const Card &operator[](unsigned int n) const { return mCards[n]; }
	Card &operator[](unsigned int n) { return mCards[n]; }

	bool push(const Card &card);
	bool push(const Cards &cards);
	bool pop(int n = 1);

private:
	std::vector<Card> mCards;
	unsigned int mFilled;
};

std::ostream &operator<<(std::ostream &o, const Cards &cards);

#endif