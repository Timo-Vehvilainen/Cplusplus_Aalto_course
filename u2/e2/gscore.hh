#ifndef ELEC_AS_CPP_GSCORE_HH
#define ELEC_AS_CPP_GSCORE_HH

#include "gcourse.hh"
#include <iostream>

/* CLASS: GolfScoreCard
 * --------------------
 * The GolfScoreCard class describes a score card for one game of golf. Each
 * game has 18 holes.
 */
class GolfScoreCard {

public:

    /* DESCRIPTION:
     * ------------
     * Constructor for the GolfScoreCard class. Creates a new GolfScoreCard object.
     *
     * PARAMETERS:
     * ------------
     * const GolfPlayer& player: the player who this score card belongs to.
     * const GolfCourse& course: the golf course where the game was played.
     *
     * RETURNS:
     * ------------
     * Nothing.
     */
    GolfScoreCard(const GolfPlayer& player, const GolfCourse& course, TeeColor teeColor);


   /* DESCRIPTION:
    * ------------
    * The function returns the player, whose score card this is.
    *
    * PARAMETERS:
    * ------------
    * Nothing.
    *
    * RETURNS:
    * ------------
    * The GolfPlayer object related to the score card.
    */
    const GolfPlayer& getPlayer() const;


    /* DESCRIPTION:
     * ------------
     * The function returns the golf course where the game was played at.
     *
     * PARAMETERS:
     * ------------
     * Nothing.
     *
     * RETURNS:
     * ------------
     * The GolfCourse object related to the score card.
     */
    const GolfCourse& getCourse() const;


    /* DESCRIPTION:
     * ------------
     * The function returns the tee color, where the player played from.
     *
     * PARAMETERS:
     * ------------
     * Nothing.
     *
     * RETURNS:
     * ------------
     * The tee color the player played from.
     */
    TeeColor getTeeColor() const;


    /* DESCRIPTION:
     * ------------
     * The function appends one result to the resultsPerHole vector.
     *
     * In case there are already 18 results in the vector, the function
     * does nothing.
     *
     * PARAMETERS:
     * ------------
     * size_t result: the new result for one hole.
     *
     * RETURNS:
     * ------------
     * Nothing.
     */
    void addResult(size_t result);


    /* DESCRIPTION:
     * ------------
     * The function returns the vector of results per hole.
     *
     * PARAMETERS:
     * ------------
     * Nothing.
     *
     * RETURNS:
     * ------------
     * The vector containing the hole by hole results (resultsPerHole).
     */
    const std::vector<size_t>& getResultsPerHole() const;


   /* DESCRIPTION:
    * ------------
    * The function calculates the points received per hole and returns
    * them in a vector. The indexing of the points must match the indexing
    * of the holes in the golf course and the resultsPerHole vector.
    *
    * Now for the hard part. The hole by hole results are calculated as
    * follows:
    *
    * 1. Calculate the course handicap, the formula for the course handicap is:
    *
    *    Course handicap = player handicap * (slope / 113) + (cr - course par).
    *
    *    You can get the player handicap from the player. The values for slope
    *    and cr (course rating) can be found by using the getDifficulty function
    *    with the player's gender and the score card's tee color. Course par is
    *    simply and accumulation of the par of all the course's holes' pars.
    *
    *    NOTE: The course handicap is initially a floating point value, which
    *    should be rounded naturally. The course handicap may also be negative.
    *
    *  2. The resulting course handicap (an integer) signifies additional strokes 
    *     the player may take during the game. These strokes are then divided and 
    *     added to the pars of each hole for the Golf course.
    *
    *     The strokes are divided evenly, e.g. a course handicap of 18 gives each 
    *     hole one additional stroke to the par, 36 gives each hole two additional 
    *     strokes to the par.
    *  
    *     When dividing less than 18 additional strokes, usually as the remainder 
    *     of a larger course handicap, the strokes are added in the order of hole 
    *     difficulty, starting from the most difficult hole, i.e. the hole with 
    *     hcp 1.
    *
    *     For negative course handicaps, the strokes are removed from the pars of
    *     the holes in the order of decreasing difficulty, starting from the least 
    *     difficult hole, i.e. the hole with hcp 18.
    *
    * Now you should have a vector with the player's own par per hole. Next you
    * should use this vector to calculate the points per hole.
    *
    * The points received for one hole is calculated as follows:
    *
    * 1. If the player meets his/her own par (calculated above), he/she receives
    *    2 points for the hole.
    *
    * 2. Each each stroke over the player's own par reduces the score by one,
    *    to a minimum of zero.
    *
    * 3. Each stroke less than the player's own par adds the score by one.
    *
    * 4. If the result for the hole is zero strokes, the score is automatically zero,
    *    meaning that the player gave up during that hole.
    *
    * PARAMETERS:
    * ------------
    * Nothing.
    *
    * RETURNS:
    * ------------
    * A vector containing the points per hole.
    */
    std::vector<size_t> getPointsPerHole() const;


   /* DESCRIPTION:
    * ------------
    * The function accumulates the points received per hole, to one single
    * number, that represents the total points of the player.
    *
    * PARAMETERS:
    * ------------
    * Nothing.
    *
    * RETURNS:
    * ------------
    * The total points received in all of the holes as a size_t.
    */
    size_t getTotalPoints() const;


   /* DESCRIPTION:
    * ------------
    * Overload for the output stream, << -operator.
    *
    * The function prints the score information to the output stream in the
    * following format:
    *
    * Player information:
    * Id: <player's id>
    * Name: <player's name>
    * Gender: <player's gender as a string, either male or female>
    * Handicap: <player's handicap>
    * Course: <course name>
    * Tee color: <tee color as a string either, red, blue, yellow or white>
    * Hole <id>: <hole par>/<hole hcp>/<player's hole result>/<player's points for the hole>
    * .
    * .
    * Hole <id>: <hole par>/<hole hcp>/<player's hole result>/<player's points for the hole>
    * Total points: <player's total points>
    *
    * NOTE: If the result for the hole is 0, a "-" is printed instead of the
    *       number 0.
    *
    * NOTE: There is NO new line after the last line.
    *
    * NOTE: See the main program's example output in the example.txt for
    *       further reference.
    *
    * PARAMETERS:
    * ------------
    * std::ostream& out: the output stream where to print.
    * const GolfScoreCard& scoreCard: the score card to print.
    *
    * RETURNS:
    * ------------
    * The parameter output stream.
    */
    friend std::ostream& operator<< (std::ostream& out, const GolfScoreCard& scoreCard);

private:
    const GolfPlayer& player;   // The player who this score card belongs to
    const GolfCourse& course;   // The golf course where the game was played
    TeeColor teeColor;          // The tee color where the player played from

    // A vector containing the results for each hole. The results are in the same
    // order as the holes in the GolfCourse. Note that the holes ARE NOT ordered
    // by the hcp (and neither are the results).
    std::vector<size_t> resultsPerHole;
};


#endif
