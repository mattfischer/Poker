#include "CardSet.hpp"

CardSet::CardSet()
{
	for(int i=0; i<Card::NumCards; i++) {
		mCards[i] = false;
	}
}

void CardSet::add(const Card &card)
{
	int num = card.num();
	if(num != -1) {
		mCards[num] = true;
	}
}

void CardSet::add(const Cards &cards)
{
	for(int i=0; i<cards.size(); i++) {
		add(cards[i]);
	}
}

bool CardSet::contains(const Card &card) const
{
	int num = card.num();
	if(num == -1) {
		return false;
	} else {
		return mCards[num];
	}
}