#ifndef ELEC_AS_CPP_DRAGON_HH
#define ELEC_AS_CPP_DRAGON_HH

#include <string>
#include <list>
#include <iostream>

/* Enumeration types for the different treasures */
enum TreasureType
{
  Jewellery,
  Wisdom,
  Potions
};

/* Implementation of Treasure */
struct Treasure
{
  TreasureType type;
  std::string name;
};

/* Enumeration types for the different foods */
enum FoodType
{
  PeopleFood,
  People,
  Herbs
};

/* Implementation of Food */
struct Food
{
  FoodType type;
  std::string name;
};

class Dragon
{
  /* Description:
   * ------------
   * An abstract class that describes a Dragon. The Fantasy-, Chinese- and MagicDragon
   * classes inherit this class. Each Dragon object has a name (std::string), 
   * age (size_t), size (size_t) and a list of Treasure objects that the Dragon has
   * hoarded.
   */
public:

  /* Functions:
   * ------------
   * The constructor takes the Dragon's name (std::string const&), age (size_t) and 
   * size (size_t) as a parameter and intializes them to the parameter values.
   */
	Dragon (std::string const &name, size_t age, size_t size);

  /* getName: the function returns a constant reference to the Dragon's name and takes
   * no parameters. This function does not change the state of the Dragon object, i.e.
   * the function should be const.
   */
	const std::string& getName() const;
   
  /* getAge: the function returns the Dragon's age as a size_t and takes no parameters. 
   * This function does not change the state of the Dragon object, i.e. the function 
   * should be const.
   */
	size_t getAge() const;
   
  /* getSize: the function returns the Dragon's size as a size_t and takes no parameters.
   * This function does not change the state of the Dragon object, i.e. the function 
   * should be const.
   */
	size_t getSize() const;
   
  /* getTreasures: the function returns a constant reference to the Dragon's treasures list
   * and takes no parameters. This function does not change the state of the Dragon object, 
   * i.e. the function should be const.
   */
	const std::list<Treasure>& getTreasures() const;
   
  /* clone: a pure virtual function, which returns a Dragon* and takes no parameters. This
   * function does not change the state of the Dragon object, i.e. the function should be 
   * const.
   */
	virtual Dragon* clone() const = 0;
   
  /* eat: a pure virtual function, which returns nothing and takes a reference to a list of
   * Food objects as a parameter.
   */
	virtual void eat(std::list<Food> &) = 0;
   
  /* hoard: a pure virtual function, which returns nothing and takes a reference to a list of
   * Treasure objects as a parameter.
   */
	virtual void hoard(std::list<Treasure> &) = 0;

protected:

   /* Other:
   * ------------
   * The class has the following protected members, which means they are accessible to classes
   * which inherit this class: name (std::string), age (size_t), size (size_t), treasures 
   * (std::list<Treasure>).
   */
   std::string name;
   size_t age;
   size_t size;
   std::list<Treasure> treasures;
};

/* Description:
 * ------------
 * An overloaded << stream operator for printing Dragons to parameter ostreams.
 * The dragon should be printed to the parameter ostream in the following format:
 *
 * Dragon named: <Dragon's name>, age: <Dragon's age>, size: <Dragon's size>¶
 * Treasures:¶
 * <First Treasure's name in the Dragon's treasures list>¶
 * <Second Treasure's name in the Dragon's treasures list>¶
 * .
 * .
 * .
 * <Last Treasure's name in the Dragon's treasures list>¶
 *
 * Parameters:
 * ------------
 * os: the output stream where the information about the Dragon is printed.
 * dragon: the Dragon which information should be printed.
 *
 * Returns:
 * ------------
 * The parameter output stream.
 *
 */
std::ostream& operator<<(std::ostream& os, Dragon const& dragon);

class DragonCave
{
  /* Description:
   * ------------
   * The DragonCave class is a sort of storage class for Dragons. The class
   * stores pointers of Dragon objects in a list. The class allows basic
   * manipulation of the Dragon pointer list through the functions described
   * below.
   */

public:

   /* Functions:
   * -----------
   * The DragonCave class has a parameterless constructor. 
   * The destructor of the DragonCave class deletes all the Dragons in the
   * the DragonCave's Dragon* list.
   */
	DragonCave();

   	~DragonCave();
   	
  /* getDragons: the function returns a const reference to the DragonCave's
   * list of Dragon pointers. The function takes no parameters and does not change 
   * the DragonCave's state, i.e. the function should be const.
   */
	const std::list<Dragon*>& getDragons() const;
   
  /* accommodateDragon: takes a Dragon* as a parameter and adds it to the end of
   * the DragonCave's Dragon pointer list. The function returns nothing.
   */
	void accommodateDragon(Dragon*);
   
   /* evictDragon: takes a Dragon's name as a const string reference as a parameter.
   * Tries to find a dragon with a matching name from the DragonCaves Dragon pointer
   * list. Erases the first Dragon pointer with a matching name from the list. If
   * there is no Dragon with a matching name in the list the function does nothing.
   * Note that the function only erases the pointer from the list, but DOES NOT delete
   * the Dragon object. The function returns nothing.
   */
   	void evictDragon(const std::string&);

private:

  /* Other:
   * -----------
   * The class obviously has a list of Dragon* as a private member. This class is not
   * copyable (also means not assignable), so copy and assignment operations for this
   * class should be prevented.
   *
   */
  	std::list<Dragon*> dragons; 

  	DragonCave (const DragonCave&);
  	
  	DragonCave operator= (const DragonCave&);
};

/* Description:
 * ------------
 * An overloaded << stream operator for printing DragonCaves to parameter ostreams.
 * The DragonCave should be printed to the parameter ostream in the following format:
 *
 * DragonCave dwellers:¶
 * ¶
 * <First Dragon in the dragons list>
 * ¶
 * <Second Dragon in the dragons list>
 * ¶
 * .
 * .
 * .
 * ¶
 * <Last Dragon in the dragons list>
 *
 * NOTE: The dragons in the dragon list are printed in the same format as the overloaded
 *       << stream operator for Dragons prints them. Note the line changes between each 
 *       individual Dragon.
 *
 * Parameters:
 * ------------
 * os: the output stream where the information about the DragonCave is printed.
 * cave: the DragonCave which information should be printed.
 *
 * Returns:
 * ------------
 * The parameter output stream.
 */
std::ostream& operator<<(std::ostream& os, DragonCave const& cave);

#endif
