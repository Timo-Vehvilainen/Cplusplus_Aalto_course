#include "card.hh"
#include "context.hh"
#include "deck.hh"
#include "player.hh"
#include "exception.hh"
#include "cardstore.hh"

#include <algorithm>

GameContext::GameContext(std::vector<Player*> playersPar, std::vector<const Card*> cards) : playerInTurn(0), storage(playersPar.size(), cards), activeCard(NULL)
{
   std::vector<Player*>::iterator it;
  for(it = playersPar.begin(); it != playersPar.end(); it++) {
  	PlayerEntry newEntry(*it);
  	players.push_back(newEntry);
  }
  for (auto it = players.begin(); it != players.end(); it++) {
  	setupTurnContext (*it);
  }
}

bool GameContext::endCondition() const
{
  if (players.size() < 4)  {
  	if (storage.countEmptyStacks() >= 3) {
	  	return true;
	}  else if (storage.countEmptyStacks() >= 4) {
  		return true;
  	}  else if (!storage.countCard(CardStore::get("Province"))){
  		return true;
  	}	
  }
  return false;
}

std::vector<TurnContext*> GameContext::getTargets(TurnContext& turn, bool attack)
{
  std::vector<TurnContext*> targets;
  for (auto iter = players.begin();iter != players.end();iter++)
    if (iter->player != turn.getPlayer() && (!attack || !iter->turnContext->attackProtection()))
      targets.push_back(iter->turnContext);
  return targets;
}

void GameContext::invokeEvent(const Card* card, const Player& playerPar, void (Player::*function)(const Card*, const Player&))
{
  std::vector<PlayerEntry>::iterator it;
  for(it = players.begin(); it != players.end(); it++) {
		(it->player->*function)(card, playerPar);
  }
}

void GameContext::invokeEvent(const Player& playerPar, void (Player::* function)(const Player&))
{
   std::vector<PlayerEntry>::iterator it;
  for(it = players.begin(); it != players.end(); it++) {
		(it->player->*function)(playerPar);
  }
}

void GameContext::endGame()
{
  std::vector<PlayerEntry>::iterator it;
  for(it = players.begin(); it != players.end(); it++) {
		delete it->turnContext;
		it->turnContext = NULL;
  }
}

std::map<const Player*, int> GameContext::countVictoryPoints() const
{
  std::map<const Player*, int> points;
  std::vector<PlayerEntry>::const_iterator it;
  for(it = players.begin(); it != players.end(); it++) {
		points.insert(std::pair <const Player*, int> (it->player, (it->deck).countVictoryPoints()));
  }
  return points;
}

size_t GameContext::nextPlayer(void)
{
  playerInTurn = (playerInTurn + 1) % players.size();
  players[playerInTurn].turn += 1;
  setupTurnContext(players[playerInTurn]);
  if (players[playerInTurn].turn >= 10000)
  	throw Exception::RuntimeError("Turn numbers are over the limit");
  return playerInTurn;
  
}

void GameContext::setupTurnContext(PlayerEntry& newPlayer) 
{
  delete (newPlayer.turnContext);
  newPlayer.turnContext = new TurnContext(*this, newPlayer.player, newPlayer.deck);
  
}
