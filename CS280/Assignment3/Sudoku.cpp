/*****************************************************************************/
/*!
\file        Sudoku.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS280
\par assignment 3
\date 10/15/15

\brief
  Implementation file of recursive brute force sudoku solver.


Hours spent on assignment: 12

Specific portions that gave you the most trouble: 
  Getting place value to work correctly. I still struggle grasping recursion 
  and why it works so getting that right and understanding it was difficult.
*/
/*****************************************************************************/

#include "Sudoku.h"

/*****************************************************************************/
/*!

\brief
  Constructor for Sudoku solver object.

\param basesize
  The number of elements per square. NOT entire length

\param stype
  The type of symbol being used for this object. Either numbers or letters.


\param callback
  Callback function defined by the client for debugging purposes.

*/
/*****************************************************************************/
Sudoku::Sudoku(int basesize, SymbolType stype, SUDOKU_CALLBACK callback) : 
  stats(), length(basesize * basesize), board(new char[length * length]), callback(callback), finished(false)
{
    // caclulate range of values for board based on symbol type
    // and board size
  if(stype == SYM_NUMBER)
  {
    starting_value ='1';
    ending_value = static_cast<char>('1' + (length - 1));
  }
  else
  {
    starting_value = 'A';
    ending_value = static_cast<char>('A' + (length - 1));
  }

    //set base size
  stats.basesize = basesize;
}

/*****************************************************************************/
/*!

\brief
  Destructor for obect.

*/
/*****************************************************************************/
Sudoku::~Sudoku()
{
    // delete the board
  delete [] board;
}
  
  
/*****************************************************************************/
/*!

\brief
  Load in the board values from text file provided.

\param values
  Pointer to values of the atarting board

\param size
  size of the board (basesize^4)

*/
/*****************************************************************************/
void Sudoku::SetupBoard(const char *values, int size)
{
    // copy values into array
  for(int i = 0; i < size; ++i)
	{
		if(values[i] == '.')
			board[i] = EMPTY_CHAR;
		else
    	board[i] = values[i];
	}
}

/*****************************************************************************/
/*!

\brief
  Solves the board by caliing place value to recursively finish the board.

*/
/*****************************************************************************/
void Sudoku::Solve()
{
		//send starting message
	callback(*this, 
					 board,
					 MSG_STARTING,
					 stats.moves, 
					 stats.basesize,
					 0,
					 board[0],
					 0);

    // find the first empty cell
	first_empty = find_next_empty(0);

    // start solving the board
  place_value(first_empty);
}

/*****************************************************************************/
/*!

\brief
  Check the values in a row of a given index for duplicates.

\param index
  The index of the board to check the row in.

\return
  The index of the first duplicate found. -1 if none were found.
*/
/*****************************************************************************/
int Sudoku::check_row(int index)
{ 
    // find the row we are in
  int row = index / length;

    // capture values in the row
  for(int i = row * length; i < length * (row +1); ++i)
  {
      // found a duplicate
    if(i != index && board[i] == board[index])
    {
        // return first duplicate found
      return i;
    }  
  }

    // return -1 for no duplicates found
  return -1;
}

/*****************************************************************************/
/*!

\brief
  Checks the column of the board of a certain index.

\param index
  The index of the board to check the column.

\return
  The index of the first duplicate found. -1 if none were found.
*/
/*****************************************************************************/
int Sudoku::check_column(int index)
{
    // find the colum we are in
  int column = index % length;
    
    // count number of iterations
  int count = 0;

    // check the column
  for(int i = column; count < length; ++count)
  {
      // found a duplicate
    if(i != index && board[i] == board[index])
    {
        // return first duplicate found
      return length * count + column;
    }

      // go one row down
    i += length;
  }

    // return -1 for no duplicates
  return -1;
}

/*****************************************************************************/
/*!

\brief
  Checks the neighbors of an index, the square around it, for duplicates.

\param index
  Index to check around.

\return
  The index of the first duplicate found. -1 if none were found.
*/
/*****************************************************************************/
int Sudoku::check_neighbors(int index)
{
 
   // find which row and column we are in
  int row = index / length;
  int column = index % length;

    // calculate the top left box of the neighborhood
  int top_left_row = stats.basesize * (row / stats.basesize);
  int top_left_col = stats.basesize * ( column / stats.basesize);

    // calculate bounds
  int max_row = stats.basesize * (top_left_row / stats.basesize + 1);
  int max_col = stats.basesize * ((top_left_col / stats.basesize) + 1);

    // check the neighbors
  for(int i = top_left_row; i < max_row; ++i)
  {
    for(int j = top_left_col; j < max_col; ++j)
    {
      int index_check = i * length + j;

        // found a duplicate
      if(index_check != index && board[index_check] == board[index])
      {
          // return first duplicate
        return i * length + j;
      }
    }
  }

    // return 
  return -1;
}

  // checks for conflictes given a certain position
/*****************************************************************************/
/*!

\brief
  Given an index check for conflicts around it (duplicate values).
  No specific return value but it will fill out member dupe_index with
  the results.

\param index
  The index to check.

*/
/*****************************************************************************/
void Sudoku::conflict(int index)
{
    // vector to hold duplicates temporarily
  std::vector<int> duplicates(3);

    // find any duplicates in the row
  duplicates[0] = check_row(index);

    // find any duplicates in the column
  duplicates[1] = check_column(index);

    // find any duplicates in the neighborhood
  duplicates[2] = check_neighbors(index);

    // sort the duplicates
  std::sort(duplicates.begin(), duplicates.end());

    // find duplicates found by two tests
    // ex [4      ]
    //    [  2  7 ]
    //    [6 1  8 ]
    // inserting 2 at (1,2)
    // would be flagged by both check_column and check_neighbors
  auto it = std::unique(duplicates.begin(), duplicates.end());


    // replace duplicates of the duplicates
  for(;it != duplicates.end(); ++it)
    *it = -1;

    // copy into dupe_index array for return
  for(size_t i = 0; i < 3; ++i)
    dupe_index[i] = duplicates[i];
}

/*****************************************************************************/
/*!

\brief
  Finds the next blank spot on the board.

\param index
  Index to start looking from.

\return
  Index of the next open cell.
*/
/*****************************************************************************/
int Sudoku::find_next_empty(int index)
{
    // find the next empty cell ( a space )
  for(int i = index; i < length * length; ++i)
  {
    if(board[i] == ' ')
      return i;
  }

  // didnt find an empty cell, means solution is found
  // return -1 as flag to indicate no more empty cells
  return -1;
}
  
/*****************************************************************************/
/*!

\brief
  Recursively solves the sudoku board by brute force. This function assumes
  the board is solvable. If given an impossible board it 'should' work but
  will take length^(# of empty spots at the start) to realize it, 
  (will never finish).

\param index
  Index to start testing values.

*/
/*****************************************************************************/
void Sudoku::place_value(int index)
{ 
    //start trying values
  for(char i = starting_value; i <= ending_value; ++i)
  {
      // increment number of moves
    ++stats.moves;

      // try a number
    board[index] = i;

      // look for conflicts
    conflict(index);

      // increment placed stats
    ++stats.placed;

      // send abort check message
    callback(*this,
             board,
             MSG_ABORT_CHECK,
             stats.moves,
             stats.basesize,
             index,
             board[index],
             dupe_index);

      // send placing message
    callback(*this,
             board,
             MSG_PLACING,
             stats.moves,
             stats.basesize,
             index,
             board[index],
             dupe_index);

      // no conflicts
    if(dupe_index[0] == -1 && dupe_index[1] == -1 && dupe_index[2] == -1)
    {
      // two situation:
        // 1) last piece was placed, solution found
        // 2) move to the next cell
        
        // find next empty cell    
      int next_cell = find_next_empty(index);
  
        // no more empty cells
      if(next_cell == -1)
      {
          // send msg finished ok
          callback(*this,
                   board, 
                   MSG_FINISHED_OK,
                   stats.moves,
                   stats.basesize,
                   index,
                   board[index],
                   dupe_index);

            // set flag to true to start unwinding
          finished = true;

            // return to previous call
          return;
      }
      else // move on the next cell
        place_value(next_cell);

        // once done or unsolvable board
        // keep returning to unwind the stack and exit out
      if(finished)
        return;
    }

      // remove value
    board[index] = ' ';
    
      // back track to previous cell
    --stats.placed;
    
      // send abort check message
    callback(*this,
             board,
             MSG_ABORT_CHECK,
             stats.moves,
             stats.basesize,
             index,
             i,
             dupe_index);

      // send removing message
    callback(*this,
             board,
             MSG_REMOVING,
             stats.moves,
             stats.basesize,
             index,
             i,
             dupe_index);  
  } 


  // got here with no solution, time to back up

    // remove the value
  board[index] = ' ';

  //--stats.placed;
  ++stats.backtracks;

    // go back to previous call to try more numbers
  return;
}

/*****************************************************************************/
/*!

\brief
  Returns the board in its current state.

\return
  Pointer to the board
*/
/*****************************************************************************/
const char* Sudoku::GetBoard() const
{
    // return the board
  return board;
}

/*****************************************************************************/
/*!

\brief
  Returns statistics of this object.

\return
  Statistics of the object.
*/
/*****************************************************************************/
Sudoku::SudokuStats Sudoku::GetStats() const
{
    // return stats
  return stats;
}

