#include "Card.hpp"

const Card Card::None;

int Card::num() const
{
	return (mSuit - 1) * 13 + (mRank - 1);
}

Card Card::fromNum(int num)
{
	Suit suit = (Suit)(num / 13 + 1);
	Rank rank = (Rank)(num % 13 + 1);
	return Card(rank, suit);
}

std::ostream &operator<<(std::ostream &o, Card::Rank rank)
{
	const char *ranks[] = { "_", "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K" };

	return o << ranks[rank];
}

std::ostream &operator<<(std::ostream &o, Card::Suit suit)
{
	const char *suits[] = { "_", "c", "h", "s", "d" };

	return o << suits[suit];
}

std::ostream &operator<<(std::ostream &o, const Card &card)
{
	return o << card.rank() << card.suit();
}