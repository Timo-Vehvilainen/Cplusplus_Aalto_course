#include "board.hh"

  /*
                              ---Constructor---

      -Initializes the board to be empty full of NULL pointers, afterwhich
       it puts in the pieces according to the appropriate starting position 
    */

    Board::Board (const startingPosition start = CLASSIC) {
        initializeGrid();
        setStartingPosition(start);
    }

    Board::~Board() {
        for (size_t row = 0; row < 8; row++) {
            for (size_t col = 0; col < 10; col++) {
               Piece* square = grid[row][col];
               if (square != NULL)
                    delete square;
            }
        } 
    }

    /*
                                ---isOccupied---

        -Checks if the parametre square is empty or if there is a piece there

    PARAMETRES:
        - The row and column of the square in question.

    RETURNS:
        - A boolean value, which is TRUE is the square is occupied, FALSE otherwise
    */
    
    bool Board::isOccupied(const size_t row, const size_t column) const{
        if (grid[row][column] != NULL)
            return true;
        return false;
    }

     /*
                              ---isOutOfBounds---

        -Checks if the parametre square is outside the boundaries of the board

    PARAMETRES:
        -The row and column of the square in question.

    RETURNS:
        - A boolean value, which is TRUE is the square is out of bounds,
          FALSE otherwise.
    */

    bool Board::isOutOfBounds(const size_t row, const size_t column) const{
        return (row >= 8 || column >= 10);
    }

    /*                      ---rotateCw & rotateCcw---

        -Turns the piece in the specified square 
         clockwise or counterclockwise, respectively.

    PARAMETRES:
        -The row and column of the square in question.
    */

    void Board::rotateCw(const size_t row, const size_t column) {
        assert (grid[row][column] != NULL);
        return ((grid[row][column])->rotateCw());
    }

    void Board::rotateCcw(const size_t row, const size_t column) {
        assert (grid[row][column] != NULL);
        return ((grid[row][column])->rotateCcw());
    }

    /*
                                ---movePiece---

        -This function will move a piece from one square to another, given that
        a few conditions are met. Any of the following things will cause the
        function the fail and not move any piece:
            -The square is empty.
            -The piece trying to be moved is a Sphinx
            -The required movement is more than 1 square in distance
        -The function will also fail an assert-test, if any of the coordinate values
        are outside the boundaries of the board.

    PARAMETRES:
        -row1 and col1, the source square from which to move the piece
        -row2 and col2, the target square to which the piece should be moved.

    RETURNS:
        -A boolean value depending on whether the movement was successfull.
         If no move was made, this value is FALSE. Otherwise it is TRUE
         
    */

    bool Board::movePiece (const size_t row1, const size_t col1,            \
                            const size_t row2, const size_t col2) {
        assert (row1 < 8 && row2 < 8 && col1 < 10 && col2 < 10);
        if (grid[row1][col1] != NULL && (grid[row1][row2])->type != "Sphinx") {
            if ((std::max(row1, row2) - std::min(row1, row2)) <= 1 && \
                 (std::max(col1, col2) - std::min(col1, col2)) <= 1) {
                if (!isOccupied(row2, col2)) {
                    grid[row2][col2] = grid[row1][col1];
                    grid[row1][col1] = NULL;
                    return true;
                }
            }
        }
        return false;
    }
    /*
                                ---switchPieces---

        -This function will switch a piece from one square to another, given that
        a few conditions are met. Any of the following things will cause the
        function the fail and not move any piece:
            -Either the source or the target square is empty.
            -The piece in the source square trying to be moved is not a Scarab.
            -The required movement is more than 1 square in distance
        -The function will also fail an assert-test, if any of the coordinate values
        are outside the boundaries of the board.

    PARAMETRES:
        -row1 and col1, the source square from which to switch the Scarab
        -row2 and col2, the target square to which the Scarab should be switched.

    RETURNS:
        -A boolean value depending on whether the switch was successfull.
         If no switch was made, this value is FALSE. Otherwise it is TRUE.
         
    */

    bool Board::switchPieces (const size_t row1, const size_t col1,         \
                             const size_t row2, const size_t col2) {
        assert (row1 < 8 && row2 < 8 && col1 < 10 && col2 < 10);
        if ((grid[row1][col1] != NULL) && (grid[row2][col2] != NULL)) {
            if ((grid[row1][col1])->type == "Scarab") {
                if ((std::max(row1, row2) - std::min(row1, row2)) <= 1 && \
                    (std::max(col1, col2) - std::min(col1, col2)) <= 1) {
                    Piece* tempPtr = grid[row1][col1];
                    grid[row1][col1] = grid[row2][col2];
                    grid[row2][col2] = tempPtr;
                    return true; 
                }
            }
        }
        return false;
    }
    
    /*
                                ---fireLaser---

         -This function handles the entire laser shooting event from start
          to finish. It shoots the laser from the Sphinx of the parametre color,
          and guides the laser until it either kills a piece or goes off the
          board. This function also handles discarding any dead pieces.

     PARAMETRES:
        -The color of the Sphinx which is supposed to fire the laser
    */

    void Board::fireLaser(const Color color) {
        
        std::vector <std::pair<size_t, size_t> > deadPieces;
        std::vector <Laser*> lasers;
        
        
        //The color check is done within the Sphinx's shootLaser-function   
        
        lasers.push_back(grid[0][0]->shootLaser(color));
        for (auto laserIt = lasers.begin(); laserIt != lasers.end(); laserIt++) {
            while (advance(*laserIt)) {
                size_t hitRow = (*laserIt)->row;
                size_t hitCol = (*laserIt)->col;
                Piece* hitPiece = grid[hitRow][hitCol];
                
        //If the beam hits a Beamsplitter, it adds a new laser to list of lasers
        //to be fired this round.
        
                if (hitPiece->type == "Beamsplitter") 
                     lasers.push_back(new Laser(hitRow, hitCol, (*laserIt)->direction));

        //Pieces that die (ie. return a TRUE value from their isHit-function) 
        //are added to a list of dead pieces, which are
        //removed later. This is because of the Beamsplitter piece, which can
        //cause multiple pieces to die within one firing. The piece will not be added
        //to the list if it is already dead.
        
                if (hitPiece->isHit(*laserIt)) {                                
                    if (std::find(deadPieces.begin(), deadPieces.end(),         \
                    std::pair<size_t, size_t>(hitRow, hitCol)) == deadPieces.end()) {
                            deadPieces.push_back(std::pair<size_t, size_t>(hitRow, hitCol));
                    }
                }
            }    
        }
        
        //Remove dead pieces from the board
        for (auto deadIt = deadPieces.begin(); deadIt != deadPieces.end(); deadIt++) 
            delete (grid[deadIt->first][deadIt->second]);
    }
    
    /*
                    ---intializeGrid---
                    
        -A private helper function used to initialize the board grid to
         be empty before inserting any pieces.
    */
    
    void Board::initializeGrid() {
        for (size_t row = 0; row < 8; row++) {
            for (size_t col = 0; col < 10; col++)
                grid[row].push_back(NULL);
        }
        return;
    }

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
    void Board::setStartingPosition(const startingPosition start = CLASSIC) {
        std::ifstream pos;
        if (start == IMHOTEP)
            pos.open("imhotep.txt");
        else if (start == DYNASTY)
            pos.open("dynasty.txt");
        else
            pos.open("classic.txt");
        size_t row;
        size_t col;
        size_t dir;
        size_t color;
        std::string next; 
        for (size_t counter = 0; counter < 24; counter++) {
            pos >> row;
            pos >> col;
            pos >> color;
            pos >> dir;
            pos >> next;
            if (next == "Sphinx")
                grid[row][col] = new Sphinx((Direction) dir, (Color) color);
            else if (next == "Anubis")
                grid[row][col] = new Anubis((Direction) dir, (Color) color);
            else if (next == "Pyramid")
                grid[row][col] = new Pyramid((Direction) dir, (Color) color);
            else if (next == "Scarab")
                grid[row][col] = new Scarab((Direction) dir, (Color) color);
            else if (next == "Pharaoh")
                grid[row][col] = new Pharaoh((Direction) dir, (Color) color);
        }
        pos.close();
    }

    /*                             ---advance---

        -Advances the laser beam on the board one square at a time,
         until it either collides with a piece or goes off the board.

     RETURNS:
        -A boolean value indicating whether the laserbeam hit a piece or it
         went off the board. This value is TRUE if it collided with a piece,
         and FALSE if it ran off the board.
    */
    
    bool Board::advance(Laser* laser) const{
        while (true) {
            laser->takeStep();
            if (isOutOfBounds(laser->row, laser->col))
                return false;
            else if (isOccupied(laser->row, laser->col))
                return true;
        }
        return false;
    }

