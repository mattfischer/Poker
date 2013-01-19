#include "Card.hpp"

const Card Card::None;

std::ostream &operator<<(std::ostream &o, const Card &card)
{
	const char *ranks[] = { "_", "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K" };
	const char *suits[] = { "_", "c", "h", "s", "d" };

	return o << ranks[card.rank()] << suits[card.suit()];
}