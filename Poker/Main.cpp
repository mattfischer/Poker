#include "Card.hpp"
#include "Cards.hpp"
#include "Hand.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	Cards cards(5);

	cards.add(Card(9, Card::SuitHearts));
	cards.add(Card(9, Card::SuitSpades));
	cards.add(Card(13, Card::SuitSpades));
	cards.add(Card(1, Card::SuitSpades));
	cards.add(Card(1, Card::SuitSpades));

	Hand hand = Hand::identify(cards);

	cout << "Cards: " << cards << endl;
	cout << "Hand: " << hand << endl;
	return 0;
}