#ifndef BIRD_HH
#define BIRD_HH

#include <string>

#include <iostream>


// All member functions are implemented in this header file.
// There is no bird.cc.

class Bird {
public:
  
  
  
  // Constructor (explicit, we want to avoid implicit typecasts from string)
  explicit Bird(std::string const &name) : name(name)
  {}
  
  // We use implicit copy constructor and assignment operator.
  
  // Virtual - this class may be derived from
  virtual ~Bird() {}
  
  
  // All birds can fly, or at least the birds we are implementing
  // in this exercise.
  //
  // Notice that flying is not a const member function -
  // const birds cannot fly! They can only speak.
  
  void fly(std::ostream &os) { os << name << " flies!" << std::endl; }
  
  // How birds speak is defined by their genus (it is implemented in
  // the derived classes)
  
  virtual void speak(std::ostream &os) const = 0;
  
  // Returns the name of the bird.
  std::string getName() const
  {
    return name;
    }
  
private:
  std::string name;
  
};



#endif


