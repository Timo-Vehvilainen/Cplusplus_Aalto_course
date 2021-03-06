#ifndef OWL_HH
#define OWL_HH

#include "bird.hh"

class Owl : public Bird
{
public:
	Owl(std::string const &name) : Bird(name) {}
	void speak(std::ostream& os) const;

	~Owl() {delete this;}

};

#endif
