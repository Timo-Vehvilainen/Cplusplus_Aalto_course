#include "mdragon.hh"

#include <string>
#include <list>
#include <iostream>

/* MagicDragon class functions */
MagicDragon::MagicDragon(std::string const& name, size_t age, size_t size) : Dragon(name, age, size) { }
    
void MagicDragon::eat(std::list<Food>& food)
{
  for (std::list<Food>::iterator it = food.begin(); it != food.end();)
    if (it->type == Herbs)
    {
      std::cout << "Magic dragon ate: " << it->name << std::endl;
      it = food.erase(it);
      size++;
    } else it++;
}

void MagicDragon::hoard(std::list<Treasure>& treasures)
{
  for (std::list<Treasure>::iterator it = treasures.begin(); it != treasures.end();)
    if (it->type == Potions)
    {
      std::cout << "Magic dragon received: " << it->name << std::endl;
      this->treasures.push_back(*it);
      it = treasures.erase(it);
    } else it++;
}

MagicDragon* MagicDragon::clone() const
{
  MagicDragon* mdragon = new MagicDragon(name, age, size);
  mdragon->treasures = treasures;
  
  return mdragon;
}