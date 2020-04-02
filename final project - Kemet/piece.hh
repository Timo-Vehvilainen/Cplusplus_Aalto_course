/* 
        CREATED BY TIMO VEHVILÄINEN
        LAST UPDATED IN 5.11.2012
*/


#ifndef PIECE_HH
#define PIECE_HH

// The direction enum lists the 4 cardinal directions on the board, starting 
// with UP and going around clockwise


/*   
                         ***THE PIECE CLASS***

      -Is a parent class to all the specific subclasses for 
       all the specific pieces.
*/

class Piece {

public:
    /*  
                             ---Constructor---

        -Creates a new piece.

    PARAMETRES:
        - A Direction which the front of the piece is facing
        - The color of the piece, either red or silver
        - The type of the piece (always assigned implicitly, never explicitly)
    */
    
    Piece (Direction direction, Color color, std::string type) : 
    front(direction), color(color), type(type) {}
    
    /*  
                            ---isHit---

        -Implements the appropriate functionality when a piece is hit
        with a laser. With mirrored pieces it will reflect the laser accordingly.

    PARAMETRES:
        - A pointer to the laser beam which is hitting the piece. 

    RETURNS:
        - A boolean value indicating whether the piece dies in the process.
            This value is TRUE if the piece dies and should be eliminated by the board.
            It is FALSE otherwise.
    */

    virtual bool isHit (Laser*) const = 0;

    /*
                              ---rotateCw & rotateCcw---

             -Turn the piece clockwise or counterclockwise, respectively.
    */
    
    void rotateCw() {
        front = (Direction) ((front + 1) % 4);
        return;
    }

    void rotateCcw() {
        front = (Direction) ((front - 1) % 4);
        return;
    }

     /*                      ---shootLaser---

        -This function creates a new laser beam infront of the Sphinx.
        -It is up to the board to get the laser actually moving with its
         advance()-function.

    RETURNS:
        -The newly created laser object.
    */

    virtual Laser* shootLaser(const Color) const {
    	assert (type == "Sphinx");
    	Laser laser(1,1, UP);
    	Laser* laserPtr = &laser;
    	return laserPtr;
    }

       
    Direction front;
    Color color;
    std::string type;
};

/*
                               ***ANUBIS***

     The Anubis has basic maneuverability. When hit by a laser from the
     front, it absorbs the laser without taking any damage. If hit from any other 
     direction, it dies. 
*/

class Anubis : public Piece {

public:
    Anubis (Direction direction, Color color) : Piece(direction, color, "Anubis") {}
    
    bool isHit(Laser* laser) const {
    	bool dead = true;
        if (laser->direction == front)
            dead = false;
        delete laser;
        return dead;
    }
};

/*
                             ***PHARAOH***

       If the Pharaoh is hit from any direction, it dies. 
*/

class Pharaoh : public Piece {
public:
    Pharaoh (Direction direction, Color color) : Piece(direction, color, "Pharaoh") {}

    bool isHit (Laser* laser) const{
    	delete laser;
        return true;
    }
};

/*
                                ***SPHINX***

        The Sphinx cannot be killed. It has the functionality to shoot a laser.
*/

class Sphinx : public Piece {

public:
    Sphinx (Direction direction, Color color) : Piece(direction, color, "Sphinx") {}
    
    bool isHit (Laser* laser) const {
    	delete laser;
        return false;
    }
    
    Laser* shootLaser(const Color sphinxColor) const {
    	size_t row = 0;
    	size_t column = 0;
        if (sphinxColor == RED) {
            row = 7;
            column = 9;
        }
        Laser* laserPtr = new Laser(row, column, front);
        return laserPtr; 
    }
};

/*
                              ***PYRAMID***

        The Pyramid has one mirrored surface, which is angled at 45 degrees 
        between its front and its right side. It reflects a laser coming from its
        front to the right and vice versa. 
        When hit by a laser from the back or left, it dies.
*/

class Pyramid : public Piece {

public:
    Pyramid (Direction direction, Color color) : Piece(direction, color, "Pyramid") {}

    bool isHit (Laser* laser) const {
        if (laser->direction == front) 
            laser->changeDirection((Direction) ((front + 1) % 4));
        else if (laser->direction == ((Direction) ((front + 1) % 4)))
            laser->changeDirection (front);
        else {
        	delete laser;
            return true;
        }
        return false;
    }
};

/*
                                ***SCARAB***
                                
    The Scarab functions much like a pyramid, except that it also has a mirrored
    surface between it's backside and left side. As a consequence, this piece can
    never be killed, because it has no unmirrored sides.
*/

class Scarab : public Piece {

public:
     Scarab (Direction direction, Color color) : Piece(direction, color, "Scarab") {}
     
     bool isHit (Laser* laser) const {
        if (laser->direction == front) 
            laser->changeDirection((Direction)((front + 1) % 4));
         else if (laser->direction == ((Direction)((front + 1) % 4)))
            laser->changeDirection (front);
         else if (laser->direction == ((Direction)((front + 2) % 4)))
            laser->changeDirection((Direction)((front + 3) % 4));
         else
            laser->changeDirection((Direction)((front + 2) % 4));
         return false;
    }
};

/*
                             ***BEAMSPLITTER***
       
       -Gamewise, the Beamsplitter is much like a Scarab, in that it also has
        2 mirrored sides and cannot be killed. The major difference between the 2
        is that when hit with a laser, the Beamsplitter splits the laser into 2 
        lasers. One of the lasers is reflected by the mirror, while the other
        passes straight through.
       -Internally the Beamsplitter is also identical to the Scarab, except for a 
        different type string variable.
       -The type variable is used by the Board class in the fireLaser- function 
        to make a new laser when it hits a Beamsplitter.
*/

class Beamsplitter : public Piece {

public:
    Beamsplitter (Direction direction, Color color) : Piece(direction, color, "Beamsplitter") {}
    
    bool isHit (Laser* laser) const {
        if (laser->direction == front) 
            laser->changeDirection((Direction)((front + 1) % 4));
         else if (laser->direction == ((Direction)((front + 1) % 4)))
            laser->changeDirection (front);
         else if (laser->direction == ((Direction)((front + 2) % 4)))
            laser->changeDirection((Direction)((front + 3) % 4));
         else
            laser->changeDirection((Direction)((front + 2) % 4));
         return false;
    }
};
#endif
