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

	cards.push(Card(1, Card::SuitSpades));
	cards.push(Card(2, Card::SuitClubs));
	cards.push(Card(3, Card::SuitClubs));

	cout << "Cards: " << cards << endl;

	std::vector<Card> available;
	available.push_back(Card(4, Card::SuitSpades));
	available.push_back(Card(5, Card::SuitSpades));
	available.push_back(Card(6, Card::SuitSpades));
	available.push_back(Card(4, Card::SuitHearts));

	cout << "Available: ";
	for(int i=0; i<available.size(); i++) {
		cout << available[i] << " ";
	}
	cout << endl;

	cout << "Num Draws: " << Draws::numDraws(Hand::TypeStraight, cards, available) << endl;

	std::vector<Cards> draws = Draws::draws(Hand::TypeStraight, cards, available);

	cout << "Draws: " << endl;
	for(int i=0; i<draws.size(); i++) {
		cout << "  " << draws[i] << endl;
	}

	return 0;
}