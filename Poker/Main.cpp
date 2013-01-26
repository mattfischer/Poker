#include "Card.hpp"
#include "Cards.hpp"
#include "Hand.hpp"
#include "Draws.hpp"
#include "CardSet.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	Cards cards(5);

	cards.push(Card(1, Card::SuitClubs));
	cards.push(Card(3, Card::SuitSpades));
	cards.push(Card(8, Card::SuitClubs));

	cout << "Cards: " << cards << endl;

	CardSet exclude;
	exclude.add(cards);

	Hand nut = Draws::nut(cards, exclude);
	cout << "Nut hand: " << nut << endl;

	return 0;
}