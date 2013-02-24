#include "Card.hpp"
#include "Cards.hpp"
#include "Hand.hpp"
#include "Draws.hpp"
#include "CardSet.hpp"
#include "Wins.hpp"

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	Cards cards[2];

	cards[0] = Cards(5);
	cards[0].push(Card(13, Card::SuitClubs));
	cards[0].push(Card(3, Card::SuitClubs));
	cards[0].push(Card(5, Card::SuitClubs));
	cards[0].push(Card(8, Card::SuitClubs));

	cards[1] = Cards(5);
	cards[1].push(Card(12, Card::SuitSpades));
	cards[1].push(Card(3, Card::SuitSpades));
	cards[1].push(Card(5, Card::SuitSpades));
	cards[1].push(Card(8, Card::SuitSpades));

	CardSet exclude;

	for(int i=0; i<2; i++) {
		exclude.add(cards[i]);
	}

	int *counts[2];
	for(int i=0; i<2; i++) {
		cout << "Cards (" << i << "): " << cards[i] << endl;

		counts[i] = new int[Hand::NumTypes];
		Draws::counts(cards[i], exclude, counts[i]);

		int total = 0;
		for(int j=0; j<Hand::NumTypes; j++) {
			total += counts[i][j];
		}

		cout << "Probabilities:" << endl;
		for(int j=1; j<Hand::NumTypes; j++) {
			Hand::Type type = (Hand::Type)j;
			int count = counts[i][j];
			if(count > 0) {
				cout << Hand::name(type) << ": " << count << " (" << std::setiosflags(std::ios_base::fixed) << std::setprecision(2) << (count * 100.0f / total) << "%)" << endl;
			}
		}
		cout << endl;
	}

	int wins[2];
	Wins::wins(2, cards, exclude, wins);

	int total = 0;
	for(int i=0; i<2; i++) {
		total += wins[i];
	}

	cout << "Player win percentages:" << endl;
	for(int i=0; i<2; i++) {
		cout << "  " << i << ": " << wins[i] << " (" << std::setiosflags(std::ios_base::fixed) << std::setprecision(2) << (wins[i] * 100.0f / total) << "%)" << endl;
	}

	return 0;
}