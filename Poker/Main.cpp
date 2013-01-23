#include "Card.hpp"
#include "Cards.hpp"
#include "Hand.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	Cards cards(5);

	cards.add(Card(1, Card::SuitHearts));
	cards.add(Card(1, Card::SuitClubs));
	cards.add(Card(2, Card::SuitHearts));
	cards.add(Card(4, Card::SuitClubs));
	cards.add(Card(3, Card::SuitHearts));

	Hand hand = Hand::identify(cards);

	cout << "Cards: " << cards << endl;
	cout << "Hand: " << hand << endl;
	return 0;
}