#include "aviary.hh"

void Aviary::addBird(Bird* bird) {
	//if (bird == NULL)
		//throw (std::logic_error);
	birds.push_back(bird);
	return;
}

void Aviary::speakAll(std::ostream& os) const {
	vector<Bird*>::iterator Iter;
	for (Iter = birds.begin(); Iter != birds.end(); Iter++) 
		(*Iter).speak();
	return;
}

sizeType Aviary::size(){
	return amount;
}

const Bird* Aviary::operator[] (sizeType num) const {
	if (num > size)
		throw (std::out_of_range);
	return vector[num];
}

Bird* Aviary::operator[] (sizeType num) {
	if (num > size)
		throw (std::out_of_range);
	return vector[num];
}
