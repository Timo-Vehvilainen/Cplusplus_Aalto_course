#include "duck.hh"

void Duck::speak(std::ostream& os) const{
	os << (this->getName()) << ": QUACK" << std::endl;
	return;
}
