#ifndef CARD_HPP
#define CARD_HPP

#include <ostream>

class Card {
public:
	enum Suit {
		SuitNone,
		SuitClubs,
		SuitHearts,
		SuitSpades,
		SuitDiamonds,
		NumSuits
	};

	enum Rank {
		RankNone = 0,
		RankAce = 1,
		RankJack = 11,
		RankQueen = 12,
		RankKing = 13,
		NumRanks
	};

	Card() : mRank(RankNone), mSuit(SuitNone) {}
	Card(Rank rank, Suit suit) : mRank(rank), mSuit(suit) {}
	Card(int rank, Suit suit) : mRank((Rank)rank), mSuit(suit) {}

	bool operator==(const Card &other) const { return mSuit == other.mSuit && mRank == other.mRank; }
	bool operator!=(const Card &other) const { return !(*this == other); }
	
	Rank rank() const { return mRank; }
	Suit suit() const { return mSuit; }

	static const Card None;

private:
	Rank mRank;
	Suit mSuit;
};

std::ostream &operator<<(std::ostream &o, const Card &card);

#endif