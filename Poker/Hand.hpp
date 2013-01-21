#ifndef HAND_HPP
#define HAND_HPP

#include "Card.hpp"
#include "Cards.hpp"

class Hand {
public:
	enum Type {
		TypeNone,
		TypeHighCard,
		TypePair,
		TypeTwoPair,
		TypeThreeOfAKind,
		TypeStraight,
		TypeFlush,
		TypeFullHouse,
		TypeFourOfAKind,
		TypeStraightFlush,
	};

	Hand();
	Hand(Type type, Card::Rank ranks[5]);

	static bool is(Type type, const Cards &cards, Card::Rank ranks[5], int rankCounts[Card::NumRanks], int suitCounts[Card::NumSuits]);
	static bool is(Type type, const Cards &cards);
	static Hand identify(const Cards &cards);

private:
	Type mType;
	Card::Rank mRanks[5];
};

#endif