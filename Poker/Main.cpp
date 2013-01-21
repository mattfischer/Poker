#include "Card.hpp"
#include "Cards.hpp"
#include "Hand.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	Cards cards(5);

	cards.add(Card(9, Card::SuitSpades));
	cards.add(Card(11, Card::SuitSpades));
	cards.add(Card(12, Card::SuitSpades));
	cards.add(Card(13, Card::SuitSpades));
	cards.add(Card(1, Card::SuitSpades));

	Hand hand = Hand::identify(cards);

	return 0;
}