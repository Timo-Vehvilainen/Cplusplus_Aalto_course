#include "cdragon.hh" 

#include <string>
#include <list>
#include <iostream>

ChineseDragon::ChineseDragon(std::string const& name, size_t age, size_t size) : Dragon (name, age, size) {}

void ChineseDragon::eat(std::list<Food>& food) {
	for (std::list<Food>::iterator it = food.begin(); it != food.end();)
    if (it->type == Herbs || it->type == PeopleFood) {
      	std::cout << "Chinese dragon ate: " << it->name << std::endl;
      	it = food.erase(it);
      	size++;
    } else 
    	it++;
    return;
}

void ChineseDragon::hoard(std::list<Treasure>& treasures) {
	for (std::list<Treasure>::iterator it = treasures.begin(); it != treasures.end();)
		if (it->type == Wisdom) {
		  	std::cout << "Chinese dragon received: " << it->name << std::endl;
		  	this->treasures.push_back(*it);
		  	it = treasures.erase(it);
		} else 
			it++;
	return;
}

ChineseDragon* ChineseDragon::clone() const {
	ChineseDragon* cdragon = new ChineseDragon(name, age, size);
  	cdragon->treasures = treasures;
  	return cdragon;
}
