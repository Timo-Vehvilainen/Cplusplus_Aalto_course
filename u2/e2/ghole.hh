#ifndef ELEC_AS_CPP_GHOLE_HH
#define ELEC_AS_CPP_GHOLE_HH

#include <cstddef>
#include <iostream>

/* CLASS: GolfHole
 * ---------------
 * The GolfHole class describes one golf hole. Each golf hole has a par value,
 * which describes the ideal result (number of swings) for the golf hole.
 *
 * Each golf hole also has a hcp (handicap) value, which describes the
 * difficulty of the golf hole in the golf course. The value from hcp is always
 * between 1 and 18.
 */
class GolfHole {

public:

    /* DESCRIPTION:
     * ------------
     * Constructor for the class. Creates a new GolfHole object.
     *
     * PARAMETERS:
     * ------------
     * size_t par: par of the golf hole.
     * size_t hcp: hcp of the golf hole (can be considered as the difficulty).
     *
     * RETURNS:
     * ------------
     * Nothing.
     */
    GolfHole(size_t par, size_t hcp);


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
    GolfHole() { }


    /* DESCRIPTION:
     * ------------
     * Returns the par of the golf hole.
     *
     * PARAMETERS:
     * ------------
     * Nothing.
     *
     * RETURNS:
     * ------------
     * The par of the golf hole as a size_t value.
     */
    size_t getPar() const;


    /* DESCRIPTION:
     * ------------
     * Returns the HCP of the golf hole.
     *
     * PARAMETERS:
     * ------------
     * Nothing.
     *
     * RETURNS:
     * ------------
     * The hcp of the golf hole as a size_t value.
     */
    size_t getHcp() const;


    /* DESCRIPTION:
     * ------------
     * Overload for the input stream, >> -operator. The function is used to read
     * the information of a GolfHole object from the input stream.
     *
     * The information is in the input stream in the following format:
     * <par> <hcp>
     *
     * PARAMETERS:
     * ------------
     * std::istream& in: the input stream to be read from.
     * GolfHole& hole: the GolfHole object where the information is stored.
     *
     * RETURNS:
     * ------------
     * The parameter input stream.
     */
    friend std::istream& operator>> (std::istream& in, GolfHole& hole);

private:

    size_t par;	// The par value of the golf hole
    size_t hcp;	// The hcp of the golf hole
};

#endif
