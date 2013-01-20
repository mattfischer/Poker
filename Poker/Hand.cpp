#include "Hand.hpp"

#include <algorithm>

Hand::Hand(Type type, Card::Rank rank0, Card::Rank rank1)
{
	mType = type;
	mRanks[0] = rank0;
	mRanks[1] = rank1;
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

static bool isSet(const int ranks[Card::NumRanks], int count)
{
	bool ret = false;
	for(int i=1; i<Card::NumRanks; i++) {
		if(ranks[i] >= count) {
			ret = true;
			break;
		}
	}

	return ret;
}

static bool isTwoPair(const int ranks[Card::NumRanks])
{
	bool ret = false;
	int count = 0;

	for(int i=1; i<Card::NumRanks; i++) {
		if(ranks[i] > 1) {
			count++;
		}
	}

	if(count > 1) {
		ret = true;
	}

	return ret;
}

static bool isStraight(const int ranks[Card::NumRanks], int &start)
{
	bool ret = false;
	for(int i=1; i<Card::NumRanks; i++) {
		int count = 0;
		for(int j=0; j<5; j++) {
			int pos = i + j;
			if(pos == Card::RankKing + 1) {
				pos = Card::RankAce;
			} else if(pos > Card::RankKing + 1) {
				break;
			}

			if(ranks[pos] > 0) {
				count++;
			} else {
				break;
			}
		}

		if(count > 4) {
			ret = true;
			start = i;
			break;
		} else if(count > 0) {
			i += count - 1;
		}
	}

	return ret;
}

static bool isStraight(int ranks[Card::NumRanks])
{
	int start;
	return isStraight(ranks, start);
}

static bool isFlush(int suits[Card::NumSuits])
{
	bool ret = false;
	for(int i=1; i<Card::NumSuits; i++) {
		if(suits[i] > 4) {
			ret = true;
			break;
		}
	}

	return ret;
}

static bool isFullHouse(int ranks[Card::NumRanks])
{
	bool ret = false;
	bool found2 = false;
	bool found3 = false;
	for(int i=1; i<Card::NumRanks; i++) {
		if(ranks[i] > 2) {
			if(found3) {
				found2 = true;
			} else {
				found3 = true;
			}
		} else if(ranks[i] > 1) {
			found2 = true;
		}

		if(found2 && found3) {
			ret = true;
			break;
		}
	}

	return ret;
}

static bool isStraightFlush(const Cards &cards, int ranks[Card::NumRanks])
{
	bool ret = false;
	int start;

	if(isStraight(ranks, start)) {
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

bool Hand::is(Type type, const Cards &cards)
{
	int ranks[Card::NumRanks];
	int suits[Card::NumSuits];
	bool ret;
	int start;

	countRanks(cards, ranks);
	countSuits(cards, suits);

	switch(type) {
		case Hand::TypeHighCard:
			ret = (cards.size() > 0);
			break;

		case Hand::TypePair:
			ret = isSet(ranks, 2);
			break;

		case Hand::TypeTwoPair:
			ret = isTwoPair(ranks);
			break;

		case Hand::TypeThreeOfAKind:
			ret = isSet(ranks, 3);
			break;

		case Hand::TypeStraight:
			ret = isStraight(ranks);
			break;

		case Hand::TypeFlush:
			ret = isFlush(suits);
			break;

		case Hand::TypeFullHouse:
			ret = isFullHouse(ranks);
			break;

		case Hand::TypeFourOfAKind:
			ret = isSet(ranks, 4);
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