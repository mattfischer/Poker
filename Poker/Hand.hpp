#ifndef HAND_HPP
#define HAND_HPP

#include "Card.hpp"
#include "Cards.hpp"

class Hand {
public:
	enum Type {
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

	Hand(Type type, Card::Rank rank0 = Card::RankNone, Card::Rank rank1 = Card::RankNone);

	static bool is(Type type, const Cards &cards);

private:
	Type mType;
	Card::Rank mRanks[2];
};

#endif