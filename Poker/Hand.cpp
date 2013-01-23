#include "Hand.hpp"

#include <algorithm>

Hand::Hand()
{
	mType = TypeNone;
	for(int i=0; i<5; i++) {
		mRanks[i] = Card::RankNone;
	}
}

Hand::Hand(Type type, Card::Rank ranks[5])
{
	mType = type;
	for(int i=0; i<5; i++) {
		mRanks[i] = ranks[i];
	}
}

struct RankDesc {
	Card::Rank rank;
	int count;

	bool operator<(const RankDesc &other)
	{
		return count < other.count;
	}
};

struct SuitDesc {
	Card::Suit suit;
	int count;

	bool operator<(const SuitDesc &other)
	{
		return count < other.count;
	}
};

static void countRanks(const Cards &cards, int counts[Card::NumRanks], Card::Suit suit = Card::SuitNone)
{
	for(int i=0; i<Card::NumRanks; i++) {
		counts[i] = 0;
	}

	for(unsigned int i=0; i<cards.size(); i++) {
		if(suit == Card::SuitNone || cards[i].suit() == suit) {
			counts[cards[i].rank()]++;
		}
	}
}

static void countSuits(const Cards &cards, int counts[Card::NumSuits])
{
	for(int i=0; i<Card::NumSuits; i++) {
		counts[i] = 0;
	}

	for(unsigned int i=0; i<cards.size(); i++) {
		counts[cards[i].suit()]++;
	}
}

static bool isSet(const int rankCounts[Card::NumRanks], int count, Card::Rank ranks[5])
{
	bool ret = false;
	for(int i=Card::RankAceHigh; i>Card::RankAce; i--) {
		Card::Rank rank = Card::aceLow(i);

		if(rankCounts[rank] >= count) {
			ret = true;
			ranks[0] = rank;

			int n = 0;
			int numKickers = 5 - count;
			for(int j=Card::RankAceHigh; j>Card::RankAce; j--) {
				Card::Rank kicker = Card::aceLow(j);
				if(rankCounts[kicker] != 0 && kicker != rank) {
					ranks[n + 1] = kicker;
					n++;
					if(n == numKickers) {
						break;
					}
				}
			}
			break;
		}
	}

	return ret;
}

static bool isTwoPair(const int rankCounts[Card::NumRanks], Card::Rank ranks[5])
{
	bool ret = false;
	int p = 0;

	for(int i=Card::RankAceHigh; i>Card::RankAce; i--) {
		Card::Rank rank = Card::aceLow(i);

		if(rankCounts[rank] > 1) {
			ranks[p++] = rank;
		}
	}

	if(p > 1) {
		ret = true;

		int n = 0;
		int numKickers = 1;
		for(int j=Card::RankAceHigh; j>Card::RankAce; j--) {
			Card::Rank kicker = Card::aceLow(j);
			if(rankCounts[kicker] != 0 && kicker != ranks[0] && kicker != ranks[1]) {
				ranks[n + 2] = kicker;
				n++;
				if(n == numKickers) {
					break;
				}
			}
		}
	}

	return ret;
}

static bool isStraight(const int rankCounts[Card::NumRanks], Card::Rank ranks[5])
{
	bool ret = false;
	for(int i=Card::RankAceHigh; i>Card::RankNone; i--) {
		int count = 0;
		for(int j=0; j<5; j++) {
			Card::Rank rank = Card::aceLow(i - j);

			if(rankCounts[rank] > 0) {
				count++;
			} else {
				break;
			}
		}

		if(count > 4) {
			ret = true;
			ranks[0] = Card::aceLow(i);
			break;
		}
	}

	return ret;
}

static bool isFlush(int suitCounts[Card::NumSuits], const Cards &cards, Card::Rank ranks[5])
{
	bool ret = false;
	Card::Suit suit;

	for(int i=1; i<Card::NumSuits; i++) {
		if(suitCounts[i] > 4) {
			suit = (Card::Suit)i;
			ret = true;
			break;
		}
	}

	if(ret) {
		Card::Rank *sortedRanks = new Card::Rank[cards.size()];
		int pos = 0;
		for(int i=0; i<cards.size(); i++) {
			sortedRanks[i] = Card::RankNone;
		}

		for(unsigned int i=0; i<cards.size(); i++) {
			if(cards[i].suit() == suit) {
				sortedRanks[pos++] = Card::aceHigh(cards[i].rank());
			}
		}

		std::sort(&sortedRanks[0], &sortedRanks[cards.size()]);

		for(int i=0; i<5; i++) {
			ranks[i] = Card::aceLow(sortedRanks[cards.size() - i - 1]);
		}

		delete[] sortedRanks;
	}
	return ret;
}

static bool isFullHouse(int rankCounts[Card::NumRanks], Card::Rank ranks[5])
{
	bool ret = false;
	bool found2 = false;
	bool found3 = false;
	for(int i=Card::RankAceHigh; i>Card::RankAce; i--) {
		Card::Rank rank = Card::aceLow(i);

		if(rankCounts[rank] > 2) {
			if(found3) {
				ranks[1] = rank;
				found2 = true;
			} else {
				ranks[0] = rank;
				found3 = true;
			}
		} else if(rankCounts[rank] > 1) {
			ranks[1] = rank;
			found2 = true;
		}

		if(found2 && found3) {
			ret = true;
			break;
		}
	}

	return ret;
}

static bool isStraightFlush(const Cards &cards, Card::Rank ranks[5])
{
	bool ret = false;
	int rankCounts[Card::NumRanks];

	for(int i=1; i<Card::NumSuits; i++) {
		countRanks(cards, rankCounts, (Card::Suit)i);
		if(isStraight(rankCounts, ranks)) {
			ret = true;
			break;
		}
	}

	return ret;
}

bool Hand::is(Type type, const Cards &cards, Card::Rank ranks[5], int rankCounts[Card::NumRanks], int suitCounts[Card::NumSuits])
{
	bool ret;
	int start;

	switch(type) {
		case Hand::TypeHighCard:
			ret = isSet(rankCounts, 1, ranks);
			break;

		case Hand::TypePair:
			ret = isSet(rankCounts, 2, ranks);
			break;

		case Hand::TypeTwoPair:
			ret = isTwoPair(rankCounts, ranks);
			break;

		case Hand::TypeThreeOfAKind:
			ret = isSet(rankCounts, 3, ranks);
			break;

		case Hand::TypeStraight:
			ret = isStraight(rankCounts, ranks);
			break;

		case Hand::TypeFlush:
			ret = isFlush(suitCounts, cards, ranks);
			break;

		case Hand::TypeFullHouse:
			ret = isFullHouse(rankCounts, ranks);
			break;

		case Hand::TypeFourOfAKind:
			ret = isSet(rankCounts, 4, ranks);
			break;

		case Hand::TypeStraightFlush:
			ret = isStraightFlush(cards, ranks);
			break;

		default:
			ret = false;
			break;
	}

	return ret;
}

bool Hand::is(Type type, const Cards &cards)
{
	int rankCounts[Card::NumRanks];
	int suitCounts[Card::NumSuits];

	countRanks(cards, rankCounts);
	countSuits(cards, suitCounts);

	Card::Rank ranks[5];
	return is(type, cards, ranks, rankCounts, suitCounts);
}

Hand Hand::identify(const Cards &cards)
{
	Hand ret;
	int rankCounts[Card::NumRanks];
	int suitCounts[Card::NumSuits];
	Hand::Type type = Hand::TypeNone;
	Card::Rank ranks[5];

	countRanks(cards, rankCounts);
	countSuits(cards, suitCounts);

	for(unsigned int i=Hand::TypeStraightFlush; i>Hand::TypeNone; i--) {
		if(is((Hand::Type)i, cards, ranks, rankCounts, suitCounts)) {
			type = (Hand::Type)i;
			break;
		}
	}

	ret = Hand(type, ranks);
	return ret;
}

std::ostream &operator<<(std::ostream &o, const Hand &hand)
{
	const char *names[] = { "None", "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush" };
	int rankCounts[] = { 0, 5, 4, 3, 1, 1, 5, 2, 2, 1 };

	o << names[hand.type()] << " (";
	for(int i=0; i<rankCounts[hand.type()]; i++) {
		o << hand.rank(i);
		if(i < rankCounts[hand.type()] - 1) {
			o << " ";
		}
	}
	o << ")";

	return o;
}