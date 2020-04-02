#ifndef ELEC_AS_CPP_CDRAGON_HH
#define ELEC_AS_CPP_CDRAGON_HH

#include "dragon.hh"

class ChineseDragon : public Dragon
{
  public:
  
    /* Description:
     * ------------
     * Constructor of the ChineseDragon class.
     *
     * Parameters:
     * ------------
     * name: name of the dragon
     * age: age of the dragon
     * size: size of the dragon
     */
    ChineseDragon(std::string const& name, size_t age, size_t size);
  
    /* Description:
     * ------------
     * The eat function of the ChineseDragon class. ChineseDragons eat only Food which
     * type is either Herbs or PeopleFood. Each eaten Food item increases the
     * ChineseDragon's size by one.
     *
     * The food that the ChineseDragon eats is removed from the parameter food list and
     * each time the ChineseDragon feasts upon something you should print information of
     * the Food that is being eaten to std::cout in the following format:
     *
     * Chinese dragon ate: <Food's name>¶
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
     * The hoard function of the ChineseDragon class. ChineseDragons hoard only Treasures which
     * type is Wisdom. Each hoarded Treasure is added to the ChineseDragon's treasures list
     * and is removed from the parameter treasures list.
     *
     * Each time the ChineseDragon hoards an item you should print information about the hoarded
     * item to std::cout in the following format:
     *
     * Chinese dragon received: <Treasure's name>¶
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
     * The clone function of the ChineseDragon class. This function creates an exact copy of the 
     * ChineseDragon. The copy also has all the same Treasures that the original ChineseDragon had.
     *
     * Parameters:
     * ------------
     * None.
     *
     * Returns:
     * ------------
     * A pointer to a dynamically allocated copy of the ChineseDragon.
     */
    ChineseDragon* clone() const;
};

#endif