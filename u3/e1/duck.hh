#ifndef DUCK_HH
#define DUCK_HH


#include "bird.hh"

class Duck : public Bird
{
public:
	Duck(std::string const &name) : Bird(name) {}
	void speak(std::ostream& os) const;
	
	~Duck() {delete this;}
};

#endif
