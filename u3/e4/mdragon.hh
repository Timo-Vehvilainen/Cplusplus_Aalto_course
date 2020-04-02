#ifndef ELEC_AS_CPP_MDRAGON_HH
#define ELEC_AS_CPP_MDRAGON_HH

#include "dragon.hh"

class MagicDragon : public Dragon
{
  public:
    MagicDragon(std::string const& name, size_t age, size_t size);
    
    void eat(std::list<Food>& food);
    void hoard(std::list<Treasure>& treasures);
    MagicDragon* clone() const;
};

#endif