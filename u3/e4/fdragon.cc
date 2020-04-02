#include "fdragon.hh"

#include <string>
#include <list>
#include <iostream>

FantasyDragon::FantasyDragon(std::string const& name, size_t age, size_t size) : Dragon (name, age, size) {}

void FantasyDragon::eat(std::list<Food>& food) {
	for (std::list<Food>::iterator it = food.begin(); it != food.end();)
    if (it->type == People || it->type == PeopleFood) {
      	std::cout << "Fantasy dragon ate: " << it->name << std::endl;
      	it = food.erase(it);
      	size++;
    } else 
    	it++;
    return;
}

void FantasyDragon::hoard(std::list<Treasure>& treasures) {
	for (std::list<Treasure>::iterator it = treasures.begin(); it != treasures.end();)
		if (it->type == Jewellery) {
		  	std::cout << "Fantasy dragon received: " << it->name << std::endl;
		  	this->treasures.push_back(*it);
		  	it = treasures.erase(it);
		} else 
			it++;
	return;
}

FantasyDragon* FantasyDragon::clone() const {
	FantasyDragon* fdragon = new FantasyDragon(name, age, size);
  	fdragon->treasures = treasures;
  	return fdragon;
}
