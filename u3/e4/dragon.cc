#include "dragon.hh"


Dragon::Dragon (std::string const &name, size_t age, size_t size) : name(name), age(age), size(size) {}

const std::string& Dragon::getName() const {
	return name;
}

size_t Dragon::getAge() const {
	return age;
}

size_t Dragon::getSize() const {
	return size;
}

const std::list<Treasure>& Dragon::getTreasures() const {
	return treasures;
}

std::ostream& operator<<(std::ostream& os, Dragon const& dragon) {
	os << "Dragon named: " << dragon.getName();
	os << ", age: " << dragon.getAge();
	os << ", size: " << dragon.getSize() << std::endl;
	os << "Treasures:" << std::endl;

	std::list<Treasure> treasures = dragon.getTreasures();
	std::list<Treasure>::const_iterator iter;
	for (iter = treasures.begin(); iter != treasures.end(); iter++) 
		os << iter->name << std::endl;
	return os;
}

DragonCave::DragonCave() {}

DragonCave::~DragonCave() {
	std::list<Dragon*>::iterator iter;
	for(iter = dragons.begin(); iter != dragons.end(); iter++)
		delete (*iter);
	dragons.clear();
}

const std::list<Dragon*>& DragonCave::getDragons() const {
	return dragons;
}

void DragonCave::accommodateDragon(Dragon* dragon) {
	dragons.push_back(dragon);
	return;
}

void DragonCave::evictDragon(const std::string& str) {
	std::list<Dragon*>::iterator iter;
	for(iter = dragons.begin(); iter != dragons.end(); iter++) {
		if ((*iter)->getName() == str) {
			dragons.erase(iter);
			break;
		}
	}
}

std::ostream& operator<<(std::ostream& os, DragonCave const& cave) {
	os << "DragonCave dwellers:" << std::endl;

	std::list<Dragon*> dragons = cave.getDragons();
	std::list<Dragon*>::const_iterator iter;
	for (iter = dragons.begin(); iter != dragons.end(); iter++)
		os << std::endl << *(*iter);
	return os;
}
