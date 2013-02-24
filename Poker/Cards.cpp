#include "Cards.hpp"

Cards::Cards()
{
	mSize = 0;
	mFilled = 0;
}

Cards::Cards(unsigned int size)
{
	mSize = size;
	mFilled = 0;
	mCards.resize(size);
	for(int i=0; i<mSize; i++) {
		mCards[i] = Card::None;
	}
}

Cards::Cards(const Cards &other)
{
	mSize = other.mSize;
	mFilled = other.mFilled;
	mCards = other.mCards;
}

Cards &Cards::operator=(const Cards &other)
{
	mSize = other.mSize;
	mFilled = other.mFilled;
	mCards = other.mCards;

	return *this;
}

bool Cards::push(const Card &card)
{
	bool ret = false;

	if(mFilled < mSize) {
		mCards[mFilled] = card;
		mFilled++;
		ret = true;
	}

	return ret;
}

bool Cards::push(const Cards &cards)
{
	bool ret = true;
	for(int i=0; i<cards.filled(); i++) {
		bool pushed = push(cards[i]);
		if(!pushed) {
			ret = false;
			break;
		}
	}

	return ret;
}

bool Cards::pop(int n)
{
	bool ret = true;

	for(int i=0; i<n; i++) {
		if(mFilled == 0) {
			ret = false;
			break;
		} else {
			mFilled--;
			mCards[mFilled] = Card::None;
		}
	}

	return ret;
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