#include "card.hh"
#include "turn.hh"
#include "deck.hh"
#include "context.hh"
#include "player.hh"
#include "cardstore.hh"

#include <algorithm>

TurnContext::TurnContext(GameContext& context, Player* player, Deck& deck) : gameContext(context), self(*player), deck(deck), shuffled(false), hand(deck.draw(shuffled, 5)), actions(1), buys(1), coin(0), phase(Interface::PHASE_PRE_TURN) {}
 
TurnContext::~TurnContext()
{
  discard(hand);
  discard(played);
}

bool TurnContext::selectCard(const Interface::CardSelection& options, bool optional)
{
  if (!optional && options.empty())
  	throw Exception::LogicError ("invalid parameters in TurnContext::selectCard");
  if (options.empty())
  	return false;
  if ((options.countSelected() == 1) && (!optional)) {
  	options.toggle(options.getSelectedIdx());
  	return true;
  }
  self.selectCard(*this, options, optional);
  if (!optional && (options.countSelected() != 1))
  	throw Exception::RuntimeError("Invalid selection in Turncontext::selectCard");
  return true;
}

size_t TurnContext::selectCards(const Interface::CardSelection& options, size_t min, size_t max)
{
  if (!options.validate())
  	throw Exception::LogicError ("Options are not valid in TurnContext::selectCards");
  if (min > options.size()) 
  	min = 0;
  if (max > options.size() || max < min) 
  	max = options.size();
  if (options.empty())
  	return 0;
  self.selectCards(*this, options, min, max);
  if (options.countSelected() < min || options.countSelected() > max)
  	throw Exception::RuntimeError ("Invalid number of selections in Turncontext::selectCards");
  return options.countSelected();
}

bool TurnContext::decide(enum Interface::Decision decision, const Card* card, const Player* owner)
{
  return (self.decide(*this, decision, card, owner));
}

void TurnContext::gainTrashed(const Card* card)
{
  gainCard(card, TurnContext::GAIN_DISCARD, false);
}

void TurnContext::trashRevealed(const Card* card)
{
  trashCard(card);
}

void TurnContext::trashLastPlayed()
{
  trashCard(played.back());
  played.pop_back();
}

const Card* TurnContext::revealCard()
{
  if (!deck.canDraw(shuffled))
    return NULL;
  else
    return deck.draw(shuffled, 1).front();
}

std::vector<const Card*> TurnContext::revealCards(size_t n)
{
  std::vector<const Card*> cards = deck.draw(shuffled, n);
  return cards;
}

void TurnContext::toHand(const std::vector<const Card*>& cards)
{
  std::copy(cards.begin(), cards.end(), std::back_inserter(hand));
}

void TurnContext::drawCards(size_t n)
{
  auto vec = deck.draw(shuffled, n);
  for (auto it = vec.begin(); it != vec.end(); it++)
  	hand.push_back(*it);
}

void TurnContext::playSelected(const Interface::CardSelection& selection)
{
   for (auto it = selection.rbegin(); it != selection.rend(); it++) {
   	if (it->selected) {
   		if (!((it->card)->validForPhase(phase)))
   			throw Exception::LogicError ("Card is invalid for phase in TurnContext::playSelected");
   		if (getPhase() == Interface::PHASE_ACTION) {
   			if (actions == 0)
   				throw Exception::LogicError ("No action phases left in playSelected");
   			else 
   				actions--;
   		}
   		hand.erase(hand.begin() + it->idx);
   		played.push_back(it->card);
   		playCard(it->card);
   	}	
   }
}

void TurnContext::playSelectedTwice(const Interface::CardSelection& selection)
{
  const Card* card = selection.getSelectedCard();
  if (!card->validForPhase(getPhase()))
    throw Exception::LogicError("TurnContext::playSelectedTwice Incorrect phase / play");
  hand.erase(hand.begin() + selection.getSelectedIdx());
  played.push_back(card);
  playCard(card);
  playCard(card);
}

void TurnContext::discardSelected(const Interface::CardSelection& selection)
{
  for (auto it = selection.rbegin(); it != selection.rend(); it++) {
  	if (it->selected) {
  		deck.discard(it->card);
  		hand.erase(hand.begin() + it->idx);
  	}
  }
}

void TurnContext::trashSelected(const Interface::CardSelection& selection)
{
  for (auto iter = selection.rbegin();iter != selection.rend();iter++) 
    if (iter->selected)
    {
      trashCard(iter->card);
      hand.erase(hand.begin() + iter->idx);
    }
}

void TurnContext::gainSelected(const Interface::CardSelection& selection, GainType gainType)
{
  gainCard(selection.getSelectedCard(), gainType);
}

void TurnContext::returnSelectedToDeck(const Interface::CardSelection& selection)
{
  deck.returnToDeck(selection.getSelectedCard());
  for (auto iter = selection.rbegin();iter != selection.rend();iter++)
    if (iter->selected)
      hand.erase(hand.begin() + iter->idx);
}

bool TurnContext::canDraw() const
{
  return (deck.canDraw(shuffled));
}

void TurnContext::discard(const std::vector<const Card*>& cards)
{
  deck.discard(cards);
}

void TurnContext::discard(const Card* card)
{
  deck.discard(card);
}

void TurnContext::discardEntireDeck()
{
  deck.discardEntireDeck();
}

void TurnContext::returnToDeck(const Card* card)
{
  deck.returnToDeck(card);
}

bool TurnContext::attackProtection()
{
  throw Exception::Unimplemented("exercise 4");
}

void TurnContext::buySelected(const Interface::CardSelection& selection)
{
  if (buys == 0)
  	throw Exception::LogicError ("No buys left in buySelected");
  if (selection.countSelected() == 0) {
  	buys = 0;
  	return;		
  }
  const Card* card = selection.getSelectedCard();
  if (coin < card->cost)
  	throw Exception::LogicError ("Not enough money left in buySelected");
  buys--;
  coin -= card->cost;
  gainCard(card);
  //discardSelected(selection);
}

void TurnContext::gainCard(const std::string& name, GainType gainType)
{
  gainCard(CardStore::get(name), gainType);
}

void TurnContext::gainCard(const Card* card, TurnContext::GainType gainType, bool fromStorage)
{
  // Do nothing if the card is not found in the storage
  if (fromStorage && !gameContext.storage.removeCard(card)) // Storage access
    return;
  if (gainType == GAIN_DISCARD)
    discard(card);
  else if (gainType == GAIN_HAND)
    hand.push_back(card);
  else if (gainType == GAIN_TOP_OF_DECK)
    deck.returnToDeck(card);
  gameContext.invokeEvent(card, self, &Player::onGain);
}

void TurnContext::trashCard(const Card* card)
{
  gameContext.invokeEvent(card, self, &Player::onTrash);
  gameContext.storage.trashCard(card); // Storage access
}

void TurnContext::playCard(const Card* card)
{
  gameContext.invokeEvent(card, self, &Player::onPlay);
  card->play(*this);
  gameContext.setActiveCard(NULL);
}

bool TurnContext::playReaction(const Cards::ReactionCard* card)
{
  gameContext.invokeEvent(card, self, &Player::onReact);
  return card->react(*this);
}
