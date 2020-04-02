#include "cardstore.hh"
#include "context.hh"
#include "deck.hh"
#include <utility>

/* (due exercise 1):
 * ----------------------
 * Initialize the singleton CardStore object here. This initializes the
 * CardStore class' private static object variable.
 */
CardStore CardStore::object = CardStore();

 
const Card* CardStore::get(const std::string& cardName) 
{
 	std::map<std::string, Card*>::iterator it = (object.cards).find(cardName);
 	if (it == (object.cards).end())
 		throw Exception::LogicError ("Card name not found!");
 	return it->second;
}

void CardStore::add(Card* cardPtr)
{
	//std::pair <std::string, Card*> cardPair(cardPtr->name, cardPtr);
	if (!(((object.cards).insert(std::pair <std::string, Card*> (cardPtr->name, cardPtr))).second))
		throw Exception::LogicError ("Card already in deck!");
	return;
}
 
CardStore::CardStore() 
{
  loadCards();
}

CardStore::~CardStore()
{
  for (std::map<std::string, Card*>::iterator it = (object.cards).begin(); it != (object.cards).end(); it++) 
  	delete (it->second);
}
