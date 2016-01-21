/*****************************************************************************/
/*!
\file   Sudoku.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS280
\par assignment 3
\date 10/15/15

\brief
  Header file for sudoku solver with function prototypes.

*/
/*****************************************************************************/

//---------------------------------------------------------------------------
#ifndef SUDOKUH
#define SUDOKUH
//---------------------------------------------------------------------------
#include <cstddef> // size_t
#include <vector> // std::vector
#include <algorithm> // sort, unique

/*! sudoku solver class */
class Sudoku
{
  public:
      /*! Used by the callback function */
    enum MessageType
    {
      MSG_STARTING,      ///< the board is setup, ready to go
      MSG_FINISHED_OK,   ///< finished and found a solution
      MSG_FINISHED_FAIL, ///< finished but no solution found
      MSG_ABORT_CHECK,   ///< checking to see if algorithm should continue
      MSG_PLACING,       ///< placing a symbol on the board
      MSG_REMOVING       ///< removing a symbol (back-tracking)
    };

      /*! 1-9 for 9x9, A-P for 16x16, A-Y for 25x25 */
    enum SymbolType {SYM_NUMBER, SYM_LETTER};

      /*! what to replace '.' with when filling out the board */
    const static char EMPTY_CHAR = ' ';

      /*! Implemented in the client and called during the search for a solution */
    typedef bool (*SUDOKU_CALLBACK)
      (const Sudoku& sudoku, // the Sudoku object itself
       const char *board,    // one-dimensional array of symbols
       MessageType message,  // type of message
       size_t move,          // the move number
       int basesize,         // 3, 4, 5, etc. (for 9x9, 16x16, 25x25, etc.)
       int index,            // index of current cell
       char value,           // symbol (value) in current cell
       int *dup_indexes      // index of each duplicate sorted from lowest
                             // index to highest. -1 means no conflict.
                             // max of 3 duplicates.
      );

      /*! statistics tracker for the object */
    struct SudokuStats
    {
      int basesize;      ///< 3, 4, 5, etc.
      int placed;        ///< the number of values the algorithm has placed 
      size_t moves;      ///< total number of values that have been tried
      size_t backtracks; ///< total number of times the algorithm backtracked
      SudokuStats() : basesize(0), placed(0), moves(0), backtracks(0) {}
    };

      // Constructor
    Sudoku(int basesize, SymbolType stype = SYM_NUMBER, SUDOKU_CALLBACK callback = 0);

      // Destructor
    ~Sudoku();

      // The client (driver) passed the board in the values parameter
    void SetupBoard(const char *values, int size);

      // Once the board is setup, this will start the search for the solution
    void Solve();

      // For debugging with the driver
    const char *GetBoard() const;
    SudokuStats GetStats() const;

  private:

    // Other private members

    /*! find conflicts for this index and value */
  void conflict(int index);

    /*! find the next empty cell */
  int find_next_empty(int index);
  
    /*! recursively solve the board */
  void place_value(int index);

  int check_row(int index);
  int check_column(int index);
  int check_neighbors(int index);

    /*! stats of the object */
	SudokuStats stats;
  
    /*! length of the sides of the board (basesize^2) */
  int length;
  
    /*! create one dimensional array for the board
    // for use in callback */
  char *board;

    /*! array to hold duplicates */
  int dupe_index[3];
	
    /*! callback function */
	SUDOKU_CALLBACK callback;

    /*! flag to indicate solution was found */
  bool finished;

    /*! starting value for the board (1 or A) */
  char starting_value;
  
    /*! ending value for the board */
  char ending_value;

    /*! index of the first empty cell */
  int first_empty;

};

#endif  // SUDOKUH
