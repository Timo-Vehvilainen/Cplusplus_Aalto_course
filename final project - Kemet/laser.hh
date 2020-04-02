/*
                TIMO VEHVILÄINEN
                    5.11.2012
*/

#ifndef LASER_HH
#define LASER_HH

/*
                           ***LASER CLASS***

       -Represents the laser travelling through the board and interacting
       with the pieces.
*/

class Laser {

public:

    /*
                           ---Constructor---

         -Initializes the coordinates and the direction of the laser beam. 
    */
    
    Laser (size_t row, size_t column, Direction direction) : 
    row(row), col(column), nextRow(row), nextCol(column), direction(direction) {
            takeStep();
    }

    /*
                                 ---takeStep---

         -This function advances the laser beam by one square, 
          and is used by the Board-class in its advance-function.
         -When initializing a laser or changing the direction, 
          it is used to merely assign the nextRow and nextCol
          to the right values.
    */
    
    void takeStep() {
        row = nextRow;
        col = nextCol;
        if (direction == UP) 
               nextRow--;
        else if (direction == DOWN)
                nextRow++;
        else if (direction == LEFT)
               nextCol++;
        else
               nextCol--;
        return;
    }

    /*
                        ---changeDirection---

        -This function is used by the mirrored pieces. 
        -It first changes the direction variable according 
         to where the laser should go next. 
        -Then it  nullifies the next square 
         the laser beam was anticipating to go to, 
         by setting them to the same values as the current location.
        -Lastly it used the takeStep-function to correctly reassing the
         next anticipated square to the desired direction.

     PARAMETRES:
        -The new desired direction variable
    */

    void changeDirection(Direction dir)  {
        direction = dir;
        nextRow = row;
        nextCol = col;
        takeStep();
        return;
    }

    //The coordinate variables for the laser beam, as well as the next
    //square the laser is supposed to go to according to its direction
    
    size_t row;
    size_t col;
    size_t nextRow;
    size_t nextCol;
    Direction direction;
};
#endif
