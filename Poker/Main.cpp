#include "Card.hpp"
#include "Cards.hpp"
#include "Hand.hpp"
#include "Draws.hpp"
#include "CardSet.hpp"

#include <iomanip>
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

	int perm = 1;
	for(int i=0; i<cards.empty(); i++) {
		perm *= (i + 1);
	}

	int total = 1;
	int num = Card::NumCards - cards.filled();
	for(int i=0; i<cards.empty(); i++) {
		total *= num;
		num--;
	}
	total /= perm;

	cout << "Probabilities:" << endl;
	for(int i=1; i<Hand::NumTypes; i++) {
		Hand::Type type = (Hand::Type)i;
		int count = Draws::numDraws(cards, exclude, type);
		cout << Hand::name(type) << ": " << std::setiosflags(std::ios_base::fixed) << std::setprecision(2) << (count * 100.0f / total) << "%" << endl;
	}
	cout << endl;

	Hand nut = Draws::nut(cards, exclude);
	cout << "Nut hand: " << nut << endl;

	return 0;
}