#ifndef ELEC_AS_CPP_GCOURSE_HH
#define ELEC_AS_CPP_GCOURSE_HH

#include <vector>
#include <map>
#include <iostream>

#include "ghole.hh"
#include "gplayer.hh"

/* ENUMERATION:
 * ------------
 * Possible tee colors. The colors go from easiest to hardest, i.e. the red tee
 * is the easiest and the white tee is the hardest.
 */
typedef enum TeeColor {
    RED,
    BLUE,
    YELLOW,
    WHITE
} TeeColor;


/* CLASS: GolfCourse
 * -----------------
 * The class describes one golf course, and contains information necessary for
 * the score calculation.
 */
class GolfCourse {

public:
    /* DESCRIPTION:
     * ------------
     * Constructor for the GolfCourse class. Creates a new GolfCourse object.
     *
     * PARAMETERS:
     * ------------
     * const std::string& name: the name of the golf course.
     *
     * const std::vector<GolfHole>& holes: a vector containing the holes of
     * the golf course.
     *
     * const std::map<std::pair<Gender, TeeColor>,
     * 				  std::pair<double, size_t>>& difficulty: a map, which
     * maps a pair of Gender and TeeColor to the corresponding pair of
     * cr and slope. These values are used to calculate the course handicap
     * in the GolfScoreCard class.
     *
     * RETURNS:
     * ------------
     * Nothing.
     */
    GolfCourse(const std::string& name, const std::vector<GolfHole>& holes,
            const std::map<std::pair<Gender, TeeColor>, std::pair<double, size_t> >& difficulty);


    /* DESCRIPTION:
     * ------------
     * Constructor for the class. This is an empty, already implemented, constructor.
     * You do not need to worry about this.
     *
     * PARAMETERS:
     * ------------
     * Nothing.
     *
     * RETURNS:
     * ------------
     * Nothing.
     */
    GolfCourse() { }


    /* DESCRIPTION:
     * ------------
     * The function returns the name of the golf course.
     *
     * PARAMETERS:
     * ------------
     * Nothing.
     *
     * RETURNS:
     * ------------
     * The name of the golf course as a string.
     */
    const std::string& getName() const;


    /* DESCRIPTION:
     * ------------
     * The function returns the vector containing the holes of the golf course.
     *
     * PARAMETERS:
     * ------------
     * Nothing.
     *
     * RETURNS:
     * ------------
     * The vector containing the holes of the golf course.
     */
    const std::vector<GolfHole>& getHoles() const;


    /* DESCRIPTION:
     * ------------
     * The function returns the course par.
     *
     * The course par is calculated by accumulating (hint) all the par values
     * of the golf course's golf holes.
     *
     * PARAMETERS:
     * ------------
     * Nothing.
     *
     * RETURNS:
     * ------------
     * The course par of the golf course as a size_t.
     */
    size_t getPar() const;


    /* DESCRIPTION:
     * ------------
     * The function returns the pair containing the cr and slope values, matching
     * to the parameter gender and tee color.
     *
     * The information is stored in the map named difficulty. You should form a
     * pair of the parameter values and use that pair to find the corresponding
     * cr and slope values from the map.
     *
     * NOTE: you can assume that a corresponding cr and slope value is in the map.
     *       In case it's not, the behaviour is undefined.
     *
     * PARAMETERS:
     * ------------
     * Gender gender: the gender.
     * TeeColor teeColor: the tee color.
     *
     * RETURNS:
     * ------------
     * A pair containing the cr - slope values for the parameter gender and tee color.
     */
    const std::pair<double, size_t>& getDifficulty(Gender gender, TeeColor teeColor) const;


    /* DESCRIPTION:
     * ------------
     * Overload for the input stream, >> -operator. The function is used to read
     * the information of the GolfCourse from the input stream.
     *
     * The format of the data in the input stream can be found in the
     * courseFileFormat.txt file.
     *
     * An example file called sarfvik.txt is also provided.
     *
     * PARAMETERS:
     * ------------
     * std::istream& in: the input stream where to read from.
     * GolfCourse& course: the object where to store the data.
     *
     * RETURNS:
     * ------------
     * The parameter input stream.
     */
    friend std::istream& operator>> (std::istream& in, GolfCourse& course);

private:

    // The name of the golf course
    std::string name;

    // The golf holes in the golf course. Please note that the holes ARE NOT
    // ordered by the hcp.
    std::vector<GolfHole> holes;

    // A map, which maps the gender and tee color to a pair of cr (course rating)
    // and slope. The cr and slope values effect the calculation of the course
    // handicap.
    std::map<std::pair<Gender, TeeColor>, std::pair<double, size_t> > difficulty;
};

#endif
