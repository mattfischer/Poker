#include "Draws.hpp"

std::vector<Cards> Draws::draws(const Cards &cards, const CardSet &exclude, Hand::Type type)
{
	Cards mutableCards(cards);
	return drawsRecursive(mutableCards, exclude, type, 0);
}

std::vector<Cards> Draws::drawsRecursive(Cards &cards, const CardSet &exclude, Hand::Type type, int start)
{
	std::vector<Cards> ret;

	if(cards.empty() == 0) {
		if(Hand::identify(cards).type() == type) {
			ret.push_back(cards);
		}
	} else {
		for(int i=start; i<Card::NumCards; i++) {
			Card card = Card::fromNum(i);
			if(exclude.contains(card)) {
				continue;
			}

			cards.push(card);

			if(Hand::possible(type, cards)) {
				std::vector<Cards> draws = drawsRecursive(cards, exclude, type, i + 1);
				ret.insert(ret.end(), draws.begin(), draws.end());
			}

			cards.pop();
		}
	}

	return ret;
}

Hand Draws::nut(const Cards &cards, const CardSet &exclude, Hand::Type type)
{
	std::vector<Cards> nutDraws;

	if(type == Hand::TypeNone) {
		for(int i=Hand::TypeStraightFlush; i>Hand::TypeNone; i--) {
			type = (Hand::Type)i;
			nutDraws = draws(cards, exclude, type);
			if(nutDraws.size() > 0) {
				break;
			}
		}
	} else {
		nutDraws = draws(cards, exclude, type);
	}

	Hand ret;
	for(int i=0; i<nutDraws.size(); i++) {
		Hand hand = Hand::identify(nutDraws[i], type);
		if(hand > ret) {
			ret = hand;
		}
	}

	return ret;
}

std::vector<int> Draws::counts(const Cards &cards, const CardSet &exclude)
{
	std::vector<int> counts(Hand::NumTypes);
	for(int i=0; i<Hand::NumTypes; i++) {
		counts[i] = 0;
	}

	Cards mutableCards(cards);
	countsRecursive(mutableCards, exclude, counts, 0);

	return counts;
}

void Draws::countsRecursive(Cards &cards, const CardSet &exclude, std::vector<int> &counts, int start)
{
	if(cards.empty() == 0) {
		Hand hand = Hand::identify(cards);
		counts[hand.type()]++;
	} else {
		for(int i=start; i<Card::NumCards; i++) {
			Card card = Card::fromNum(i);
			if(exclude.contains(card)) {
				continue;
			}

			cards.push(card);
			countsRecursive(cards, exclude, counts, i + 1);
			cards.pop();
		}
	}
}

std::vector<int> Draws::rankCounts(const Cards &cards, const CardSet &exclude, Hand::Type type)
{
	std::vector<int> counts(Card::NumRanks);
	for(int i=0; i<Card::NumRanks; i++) {
		counts[i] = 0;
	}

	Cards mutableCards(cards);
	rankCountsRecursive(mutableCards, exclude, type, counts, 0);

	return counts;
}

void Draws::rankCountsRecursive(Cards &cards, const CardSet &exclude, Hand::Type type, std::vector<int> &counts, int start)
{
	if(cards.empty() == 0) {
		Hand hand = Hand::identify(cards);
		if(hand.type() == type) {
			counts[hand.rank(0)]++;
		}
	} else {
		for(int i=start; i<Card::NumCards; i++) {
			Card card = Card::fromNum(i);
			if(exclude.contains(card)) {
				continue;
			}

			cards.push(card);
			rankCountsRecursive(cards, exclude, type, counts, i + 1);
			cards.pop();
		}
	}
}
