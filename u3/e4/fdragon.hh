#ifndef ELEC_AS_CPP_FDRAGON_HH
#define ELEC_AS_CPP_FDRAGON_HH

#include "dragon.hh"

class FantasyDragon : public Dragon
{
  public:
  
    /* Description:
     * ------------
     * Constructor of the FantasyDragon class.
     *
     * Parameters:
     * ------------
     * name: name of the dragon
     * age: age of the dragon
     * size: size of the dragon
     */
    FantasyDragon(std::string const& name, size_t age, size_t size);
  
    /* Description:
     * ------------
     * The eat function of the FantasyDragon class. FantasyDragons eat only Food which
     * type is either People or PeopleFood. Each eaten Food item increases the
     * FantasyDragon's size by one.
     *
     * The food that the FantasyDragon eats is removed from the parameter food list and
     * each time the FantasyDragon feasts upon something you should print information of
     * the Food that is being eaten to std::cout in the following format:
     *
     * Fantasy dragon ate: <Food's name>¶
     *
     * You should loop through the food list from beginning to end.
     *
     * Parameters:
     * ------------
     * food: a list of food containing possible edible items.
     *
     * Returns:
     * ------------
     * Nothing.
     */
    void eat(std::list<Food>& food);
    
    /* Description:
     * ------------
     * The hoard function of the FantasyDragon class. FantasyDragons hoard only Treasures which
     * type is Jewellery. Each hoarded Treasure is added to the FantasyDragon's treasures list
     * and is removed from the parameter treasures list.
     *
     * Each time the FantasyDragon hoards an item you should print information about the hoarded
     * item to std::cout in the following format:
     *
     * Fantasy dragon received: <Treasure's name>¶
     *
     * You should loop through the treasures list from beginning to end.
     *
     * Parameters:
     * ------------
     * treasures: a list of treasures containing possible hoardable items.
     *
     * Returns:
     * ------------
     * Nothing.
     */
    void hoard(std::list<Treasure>& treasures);
    
    /* Description:
     * ------------
     * The clone function of the FantasyDragon class. This function creates an exact copy of the 
     * FantasyDragon. The copy also has all the same Treasures that the original FantasyDragon had.
     *
     * Parameters:
     * ------------
     * None.
     *
     * Returns:
     * ------------
     * A pointer to a dynamically allocated copy of the FantasyDragon.
     */
    FantasyDragon* clone() const;
};

#endif

