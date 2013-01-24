#include "Card.hpp"
#include "Cards.hpp"
#include "Hand.hpp"
#include "Draws.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	Cards cards(5);

	cards.push(Card(1, Card::SuitClubs));
	cards.push(Card(3, Card::SuitClubs));

	cout << "Cards: " << cards << endl;

	std::vector<Card> available;
	available.push_back(Card(3, Card::SuitSpades));
	available.push_back(Card(5, Card::SuitSpades));
	available.push_back(Card(6, Card::SuitSpades));
	available.push_back(Card(5, Card::SuitClubs));

	cout << "Available: ";
	for(int i=0; i<available.size(); i++) {
		cout << available[i] << " ";
	}
	cout << endl;

	Hand nut = Draws::nut(cards, available);
	cout << "Nut hand: " << nut << endl;

	return 0;
}