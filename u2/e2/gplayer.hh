#ifndef ELEC_AS_CPP_GPLAYER_HH
#define ELEC_AS_CPP_GPLAYER_HH

#include <string>
#include <iostream>

/* ENUMERATION:
 * ------------
 * These are the possible values for the player's gender.
 */
typedef enum Gender {
    MALE,
    FEMALE
} Gender;


/* CLASS: GolfPlayer
 * ------------------
 * The class describes one golf player. Each player has a name, gender, handicap
 * and id. The id is defined by the static variable idCounter in the class. The
 * idCounter is increased each time a GolfPlayer object is created.
 *
 * The id of a new player is always initialized to the current value of the
 * idCounter.
 */
class GolfPlayer {

public:
   /* DESCRIPTION:
    * ------------
    * Constructor for the GolfPlayer class. Creates a new GolfPlayer object.
    *
    * PARAMETERS:
    * ------------
    * const std::string& name: name of the golf player.
    * Gender gender: gender of the golf player (see the enumerations at the top).
    * double handicap: the handicap of the player, has a default value of 54.0.
    *
    * RETURNS:
    * ------------
    * Nothing.
    */
    GolfPlayer(const std::string& name, Gender gender, double handicap = 54.0);


   /* DESCRIPTION:
    * ------------
    * The function returns the name of the golf player.
    *
    * PARAMETERS:
    * ------------
    * Nothing.
    *
    * RETURNS:
    * ------------
    * The name of the golf player as a string.
    */
    const std::string& getName() const;


   /* DESCRIPTION:
    * ------------
    * The function returns the gender of the golf player.
    *
    * PARAMETERS:
    * ------------
    * Nothing.
    *
    * RETURNS:
    * ------------
    * The gender of the golf player.
    */
    Gender getGender() const;


   /* DESCRIPTION:
    * ------------
    * The function returns the handicap of the golf player.
    *
    * PARAMETERS:
    * ------------
    * Nothing.
    *
    * RETURNS:
    * ------------
    * The function returns the handicap of the golf player as a double.
    */
    double getHandicap() const;


   /* DESCRIPTION:
    * ------------
    * The function sets the golf player's handicap to the parameter value.
    *
    * PARAMETERS:
    * ------------
    * double newHandicap: the new value for the golf player's handicap.
    *
    * RETURNS:
    * ------------
    * Nothing.
    */
    void setHandicap(double newHandicap);


    /* DESCRIPTION:
    * ------------
    * The function returns the id of the golf player.
    *
    * PARAMETERS:
    * ------------
    * Nothing.
    *
    * RETURNS:
    * ------------
    * The id of the golf player as a size_t.
    */
    size_t getId() const;


    /* DESCRIPTION:
    * ------------
    * Overload for the output stream, << -operator.
    *
    * The function prints the parameter player's information to the parameter
    * output stream, in the following format:
    *
    * Player information:
    * Id: <player's id>
    * Name: <player's name>
    * Gender: <player's gender as a string either male or female>
    * Handicap: <player's handicap>
    *
    * For example:
    *
    * Player information:
    * Id: 0
    * Name: Petteri Koivumaki
    * Gender: male
    * Handicap: 7.5
    *
    * NOTE: Use the default formatting for the palyer's handicap (double) value.
    * NOTE: There is NO new line after the last line
    *
    * PARAMETERS:
    * ------------
    * std::ostream& out: the output stream where the information is printed.
    * const GolfPlayer& player: the player to be printed.
    *
    * RETURNS:
    * ------------
    * The parameter output stream.
    */
    friend std::ostream& operator<< (std::ostream& out, const GolfPlayer& player);

private:
    std::string name;   // The name of the player
    Gender gender;      // The gender of the player (see the enumerations at the top)
    double handicap;    // The player's handicap
    size_t id;          // The unique id of the player

    // A static counter which is used to assign each golf player a unique id.
    // The counter is increased each time a player object is created. A new
    // player object's id is always the idCounters current value.
    static size_t idCounter;
};

#endif
