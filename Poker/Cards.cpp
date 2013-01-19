#include "Cards.hpp"

bool Cards::add(const Card &card)
{
	for(unsigned int i=0; i<mSize; i++) {
		if(mCards[i] == Card::None) {
			mCards[i] = card;
			return true;
		}
	}

	return false;
}

std::ostream &operator<<(std::ostream &o, const Cards &cards)
{
	for(unsigned int i=0; i<cards.size(); i++) {
		o << cards[i];
		if(i < cards.size() - 1) {
			o << " ";
		}
	}

	return o;
}