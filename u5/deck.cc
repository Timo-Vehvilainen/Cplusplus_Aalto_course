#include "deck.hh"
#include "cardstore.hh"

#include <algorithm>

Deck::Deck() 
{
  // Initial deck: 7 coppers and 3 estates
  for (size_t i = 0;i < 7;i++)
    discardDeck.push_back(CardStore::get("Copper"));
  for (size_t i = 0;i < 3;i++)
    discardDeck.push_back(CardStore::get("Estate"));
}

void Deck::discard(const Card* card)
{
  discardDeck.push_back(card);
}

void Deck::discard(const std::vector<const Card*>& cards)
{
  for (auto it = cards.begin(); it != cards.end(); it++)
  	discardDeck.push_back(*it);
}

void Deck::returnToDeck(const Card* card)
{
  drawDeck.push_front(card);
}

std::vector<const Card*> Deck::draw(bool& shuffledThisTurn, size_t n)
{
	std::vector<const Card*> deck;
	size_t deckSize = drawDeck.size();
	for (size_t i = 0; i < n; i++) {
	
		if (i == deckSize && shuffledThisTurn == false) {
			drawDeck = discardDeck;
			std::random_shuffle(drawDeck.begin(), drawDeck.end());
			discardDeck.clear();
		} else if (i == deckSize) {
			break;
		}	
		deck.push_back(drawDeck[0]);
		drawDeck.pop_front();
	}
	return deck;
}

void Deck::discardEntireDeck()
{
	size_t deckSize = drawDeck.size();
	for (size_t i = 0; i != deckSize; i++) {
		discardDeck.push_back(drawDeck[0]);
		drawDeck.pop_front();
	}
}

int Deck::countVictoryPoints() const
{
	int ret = 0;
	for (auto it1 = drawDeck.begin(); it1 != drawDeck.end(); it1++) {
		ret += (*it1)->getVictoryPoints(*this);
	}
	for (auto it2 = discardDeck.begin(); it2 != discardDeck.end(); it2++) {
		ret += (*it2)->getVictoryPoints(*this);
	}
  	return ret;
}

bool Deck::canDraw(bool shuffledThisTurn) const
{
  if ((drawDeck.size() != 0) || (discardDeck.size() != 0 && shuffledThisTurn == true))
  	return true;
  return false;
}

std::vector<const Card*> Deck::getCards() const
{
	std::vector<const Card*> ret;
	for (size_t i = 0; i != drawDeck.size(); i++) 
		ret.push_back(drawDeck[i]);
	for (size_t i = 0; i != discardDeck.size(); i++) 
		ret.push_back(discardDeck[i]);
	std::random_shuffle(ret.begin(), ret.end());
	return ret;
}
