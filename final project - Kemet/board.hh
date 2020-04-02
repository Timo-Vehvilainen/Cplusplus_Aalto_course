/*
            TIMO VEHVILÄINEN
            05.11.2012
*/

#ifndef BOARD_HH
#define BOARD_HH

#include <fstream>
#include <cassert>
#include <cstddef>
#include <algorithm>
#include <vector>

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum Color {
    RED,
    SILVER
};

enum startingPosition {
    CLASSIC,
    IMHOTEP,
    DYNASTY
};

#include "laser.hh"
#include "piece.hh"


/*
                           ***BOARD CLASS***

     -The board class governs all the main components in the game. 
      It knows the location of all the pieces, and takes care of the laser 
      travelling mechanics.
*/

class Board {

public:
    /*
                              ---Constructor---

      -Initializes the board to be empty full of NULL pointers, afterwhich
       it puts in the pieces according to the appropriate starting position 
    */

    Board (const startingPosition);

    /*
                                ---Destructor---
                                
       -Deletes all the allocated pointers to pieces on the board.
    */

    ~Board();

    /*
                                ---isOccupied---

        -Checks if the parametre square is empty or if there is a piece there

    PARAMETRES:
        - The row and column of the square in question.

    RETURNS:
        - A boolean value, which is TRUE is the square is occupied, FALSE otherwise
    */
    
    bool isOccupied(size_t row, size_t column) const;
    
     /*
                              ---isOutOfBounds---

        -Checks if the parametre square is outside the boundaries of the board

    PARAMETRES:
        -The row and column of the square in question.

    RETURNS:
        - A boolean value, which is TRUE is the square is out of bounds,
          FALSE otherwise.
    */

    bool isOutOfBounds(size_t row, size_t column) const;

    /*                      ---rotateCw & rotateCcw---

        -Turns the piece in the specified square 
         clockwise or counterclockwise, respectively.

    PARAMETRES:
        -The row and column of the square in question.
    */

    void rotateCw(size_t row, size_t column);

    void rotateCcw(size_t row, size_t column);

    /*
                                ---movePiece---

        -This function will move a piece from one square to another, given that
        a few conditions are met. Any of the following things will cause the
        function the fail and not move any piece:
            -The source square is empty.
            -The piece trying to be moved is a Sphinx
            -The required movement is more than 1 square in distance
        -The function will also fail an assert-test, if any of the coordinate values
        are outside the boundaries of the board.

    PARAMETRES:
        -row1 and col1, the source square from which to move the piece
        -row2 and col2, the target square to which the piece should be moved.

    RETURNS:
        -A boolean value depending on whether the movement was successfull.
         If no move was made, this value is FALSE. Otherwise it is TRUE.
    */

    bool movePiece (size_t row1, size_t col1, size_t row2, size_t col2);
    /*
                                ---switchPieces---

        -This is a special move for the Scarab and Beamsplitter pieces.
        -This function will switch a piece from one square to another, given that
        a few conditions are met. Any of the following things will cause the
        function the fail and not move any piece:
            -Either the source or the target square is empty.
            -The piece in the source square trying to be moved 
             is not a Scarab or a Beamsplitter.
            -The required movement is more than 1 square in distance
        -The function will also fail an assert-test, if any of the coordinate values
        are outside the boundaries of the board.

    PARAMETRES:
        -row1 and col1, the source square 
         from which to switch the Scarab/Beamsplitter
        -row2 and col2, the target square 
         to which the Scarab/Beamsplitter should be switched.

    RETURNS:
        -A boolean value depending on whether the switch was successfull.
         If no switch was made, this value is FALSE. Otherwise it is TRUE.
         
    */

    bool switchPieces (size_t row1, size_t col1, size_t row2, size_t col2);
    /*
                                ---fireLaser---

         -This function handles the entire laser shooting event from start
          to finish. It shoots the laser from the Sphinx of the parametre color,
          and guides the laser through all the relfections and/or splittings
          until all the lasers either kill a piece or goe off the
          board. This function also handles the discarding of any dead pieces.

     PARAMETRES:
        -The color of the Sphinx which is supposed to fire the laser.
         (ie. which player's turn it is.)
    */

    void fireLaser(Color color);
    
private:

// The 2-dimensional vector, which represents the gameboard

std::vector < std::vector<Piece*> > grid;


    /*
                    ---intializeGrid---
                    
        -A private helper function used to initialize the board grid to
         be empty before inserting any pieces.
    */
    
    void initializeGrid();

    /*
                    ---setStartingPosition---
                    
         -This private function places all the starting pieces in their
         appropriate places on the board. It reads the coordinates from
         a file, which has the information listed in the following way:

     <row number> <column number> <color number> <direction number> <Piece name>
     <row number> <column number> <color number> <direction number> <Piece name>
     ...

         so for example:

         0 0 1 2 Sphinx == A silver Sphinx facing downwards at row 0 column 0
    */
    void setStartingPosition(const startingPosition);

    /*                             ---advance---

        -Advances the laser beam on the board one square at a time,
         until it either collides with a piece or goes off the board.

     RETURNS:
        -A boolean value indicating whether the laserbeam hit a piece or it
         went off the board. This value is TRUE if it collided with a piece,
         and FALSE if it ran off the board.
    */
    
    bool advance(Laser* laser) const;

};


#endif
