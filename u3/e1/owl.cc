#include "owl.hh"

void Owl::speak(std::ostream& os) const{
	os << (this->getName()) << ": WHUU" << std::endl;
	return;
}
