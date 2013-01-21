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

static void countRanks(const Cards &cards, int counts[Card::NumRanks])
{
	for(int i=0; i<Card::NumRanks; i++) {
		counts[i] = 0;
	}

	for(unsigned int i=0; i<cards.size(); i++) {
		counts[cards[i].rank()]++;
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
	for(int i=Card::RankAceHigh; i>Card::RankNone; i--) {
		Card::Rank rank = Card::aceLow(i);

		if(rankCounts[rank] >= count) {
			ret = true;
			ranks[0] = rank;
			break;
		}
	}

	return ret;
}

static bool isTwoPair(const int rankCounts[Card::NumRanks], Card::Rank ranks[5])
{
	bool ret = false;
	int p = 0;

	for(int i=Card::RankAceHigh; i>Card::RankNone; i--) {
		Card::Rank rank = Card::aceLow(i);

		if(rankCounts[rank] > 1) {
			ranks[p++] = rank;
		}
	}

	if(p > 1) {
		ret = true;
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
	for(int i=Card::RankAceHigh; i>Card::RankNone; i--) {
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

static bool isStraightFlush(const Cards &cards, int rankCounts[Card::NumRanks], Card::Rank ranks[5])
{
	bool ret = false;

	if(isStraight(rankCounts, ranks)) {
		int start = (ranks[0] == Card::RankAce) ? 10 : ranks[0] - 4;
		int suitCounts[Card::NumSuits];
		for(int i=1; i<Card::NumSuits; i++) {
			suitCounts[i] = 0;
		}

		for(int i=0; i<cards.size(); i++) {
			int pos = cards[i].rank() - start;
			if(cards[i].rank() == Card::RankAce && start == 10) {
				pos = 4;
			}

			if(pos >= 0 && pos < 5) {
				suitCounts[cards[i].suit()]++;
				if(suitCounts[cards[i].suit()] == 5) {
					ret = true;
					break;
				}
			}
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
			ret = (cards.size() > 0);
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
			ret = isStraightFlush(cards, rankCounts, ranks);
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