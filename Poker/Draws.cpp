#include "Draws.hpp"

std::vector<Cards> Draws::draws(Hand::Type type, const Cards &cards, const std::vector<Card> &available)
{
	Cards mutableCards(cards);
	return drawsRecursive(type, mutableCards, available, 0);
}

std::vector<Cards> Draws::drawsRecursive(Hand::Type type, Cards &cards, const std::vector<Card> &available, int start)
{
	std::vector<Cards> ret;

	if(cards.empty() == 1) {
		for(int i=start; i<available.size(); i++) {
			Card card = available[i];
			cards.push(card);
			if(Hand::is(type, cards)) {
				Cards draw(1);
				draw.push(card);
				ret.push_back(draw);
			}
			cards.pop();
		}
	} else if(cards.empty() > 1) {
		for(int i=start; i<available.size(); i++) {
			Card card = available[i];
			cards.push(card);

			if(Hand::possible(type, cards)) {
				std::vector<Cards> draws = drawsRecursive(type, cards, available, i + 1);
				for(int j=0; j<draws.size(); j++) {
					Cards draw(draws[j].size() + 1);
					draw.push(card);
					draw.push(draws[j]);
					ret.push_back(draw);
				}
			}

			cards.pop();
		}
	}

	return ret;
}

int Draws::numDraws(Hand::Type type, const Cards &cards, const std::vector<Card> &available)
{
	Cards mutableCards(cards);
	return numDrawsRecursive(type, mutableCards, available, 0);
}

int Draws::numDrawsRecursive(Hand::Type type, Cards &cards, const std::vector<Card> &available, int start)
{
	int ret = 0;

	if(cards.empty() == 1) {
		for(int i=start; i<available.size(); i++) {
			Card card = available[i];
			cards.push(card);
			if(Hand::is(type, cards)) {
				ret++;
			}
			cards.pop();
		}
	} else if(cards.empty() > 1) {
		for(int i=start; i<available.size(); i++) {
			Card card = available[i];
			cards.push(card);

			if(Hand::possible(type, cards)) {
				ret += numDrawsRecursive(type, cards, available, i + 1);
			}

			cards.pop();
		}
	}

	return ret;
}
