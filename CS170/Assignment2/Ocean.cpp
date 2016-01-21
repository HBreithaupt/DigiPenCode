/*****************************************************************************/
/*!
\file Ocean.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt@digipen.edu
\par Course: CS170
\par Assignment #2  
\date 2-11-15

\brief
  Converts assignment 1 to be contained in a class.


Hours spent on assignment: 1.5

Specific portions that gave you the most trouble: 
  - understanding function paramters to accomadate being in a class was
  a bit confusing at first
  
*/
/*****************************************************************************/

#include "WarBoats.h"
#include "Ocean.h"

namespace CS170
{

namespace WarBoats
{
  
  /***************************************************************************/
  /*!

  \brief
    Constructor to make the class.

  \param num_boats
    Number of boats to be on the board.
    
  \param x_quadrants
    Width of the board.
  
  \param y_quadrants
    Height of the board.

  */
  /***************************************************************************/
  Ocean::Ocean(int num_boats, int x_quadrants, int y_quadrants)
  {
      // allocate the grid
    grid_ =  new int[x_quadrants * y_quadrants];
    
      //initialize the grid
    for(int i = 0; i < x_quadrants * y_quadrants; i++)
    {
      grid_[i] = 0;
    }
    
      // save number of boats
    num_boats_ = num_boats;
    
      //allocate the boat array
    boats_ = new Boat[num_boats];
    
    
      //assign width and height of grid
    x_quadrants_ = x_quadrants;
    y_quadrants_ = y_quadrants;
    
      // initialize the boat array
    for(int i = 0; i < num_boats; i++)
    {
      boats_[i].hits = 0;
      boats_[i].ID = 0;
      boats_[i].position.x = 0;
      boats_[i].position.y = 0;
    }
    
      //initialize the memebers of ShotStats to 0
    stats_.hits = 0;
    stats_.misses = 0;
    stats_.duplicates = 0;
    stats_.sunk = 0;
    
  }
  
  
  /***************************************************************************/
  /*!

  \brief
    Places a boat on the board.

  \param boat
    A constant reference to a boat struct

  \return
    bpACCEPTED if boat placement is ok, bpREJECTED if it is not.
  */
  /***************************************************************************/
  BoatPlacement Ocean::PlaceBoat(const Boat& boat)
  {
      
        // y cooridinate of the boat piece given
      int relative_y = boat.position.y;
      
        // x coordinate of boat piece given
      int relative_x = boat.position.x;
      
        // width of the board
      int grid_width = x_quadrants_;
      
        // boat is vertical
      if(boat.orientation == oVERTICAL)
      {
          // is the top piece on the board
        if(boat.position.y >= 0 && boat.position.y <= y_quadrants_)
        {
            // is the top piece on the board
          if(boat.position.x >= 0 && boat.position.x <= x_quadrants_)
          {
              //is the bootom piece on the board
            if(boat.position.y + 3 < y_quadrants_)
            {
                //count safe spots
              int safe_spots_v = 0;
              
                //checks all spots to see if theyre empty
              for(int i = 0; i < BOAT_LENGTH; i++)
              {
                if(grid_[(relative_y + i) * grid_width + relative_x] == 0)
                  safe_spots_v++;
                
                 //if all spots are empty write to the grid and return accepted
                if (safe_spots_v == BOAT_LENGTH)
                {
                    //writes to grid the boat id
                  for(int write_v = 0; write_v <= 3; write_v++)
                              grid_[(relative_y + write_v) * grid_width 
                              + relative_x] = boat.ID;
                  return bpACCEPTED;
                }
                  
              }
            }
          }
        }
      }
        
        //if the boat is horizontal
      if(boat.orientation == oHORIZONTAL)
      {
          //is the leftmost piece's x-coord on the board?
        if(boat.position.x >= 0 && boat.position.x <= x_quadrants_)
        {
            //is the leftmost piece's y-coord on the board?
          if(boat.position.y >= 0 && boat.position.y <= y_quadrants_)
          {
              //is the rightmost piece on the board?
            if(boat.position.x + 3 < x_quadrants_)
            {
                //counts safe spots
              int safe_spots_h = 0;
              
                //check all pieces on the grid to see if the spaces are empty
              for(int j = 0; j < BOAT_LENGTH; j++)
              {
                  //if nothing is here keep checking
                if (grid_[relative_y * grid_width + (relative_x + j)] == 0)
                  safe_spots_h++;
                
                  // all spaces are empty write to the grid and return accepted
                if (safe_spots_h == BOAT_LENGTH)
                {
                    //writes to the grid the boat id
                  for (int write_h = 0; write_h <= 3; write_h++)
                            grid_[relative_y * grid_width + 
                            (relative_x + write_h)] = boat.ID;
                  return bpACCEPTED;
                }
              }
            }
          }
        }
      }
      
        //boat placement was invalid
      return bpREJECTED;
  }

  /***************************************************************************/
  /*!

  \brief
    Takes a shit on the board.

  \param coordinate
    A constant reference to a point structure.

  \return
    Results can be HIT, MISS, DUPLICATE, SUNK, ILLEGAL for the result of the 
    shot.
  */
  /***************************************************************************/
  ShotResult Ocean::TakeShot(const Point &coordinate)
  {
    //coordinate is not on grid
      if (coordinate.x < 0 || coordinate.y < 0)
        return srILLEGAL;
      
        //shot is off board
      if (coordinate.x > x_quadrants_ || coordinate.y > y_quadrants_)
        return srILLEGAL;
      
        //index formula for grid array
      int grid_index = coordinate.y * x_quadrants_ + coordinate.x;
      
        //grab value of the board
      int grid_value = grid_[grid_index];
      
        //you missed
      if (grid_value == dtOK)
      {
        stats_.misses++;
        grid_[grid_index] = -1;
        return srMISS;
      }
      
        //you hit a boat
      if (grid_value > dtOK && grid_value <= num_boats_)
      {
        grid_[grid_index] += 100;
        stats_.hits++;
        boats_[grid_value - 1].hits++;
        
          // checks if the boat has been sunk
        if(boats_[grid_value - 1].hits == BOAT_LENGTH)
        {
          stats_.sunk++;
          return srSUNK;
        }
          
          // you hit a boat
        return srHIT;
      }
      
        //duplicate
      if (grid_value == dtBLOWNUP || grid_value > HIT_OFFSET)
      {
        stats_.duplicates++;
        return srDUPLICATE;
      }
      
        // if for some reason no conditions are validated then return illegal
      return srILLEGAL;
  }
  
  /***************************************************************************/
  /*!

  \brief
    Returns the results of the shots you've taken in this session.

  \return
    How results of the shots you've taken.
  */
  /***************************************************************************/
  ShotStats Ocean::GetShotStats() const
  {
      //return shot results
    return stats_; 
  }
  
  /***************************************************************************/
  /*!

  \brief
    Gets the grid values of the board.

  \return
    The grid array with the values from the game session.
  */
  /***************************************************************************/
  const int *Ocean::GetGrid(void) const
  {
    return grid_;
  }
  
  /***************************************************************************/
  /*!

  \brief
    Makes a point struct with the dimensions of the grid.

  \return
    A point struct the if the dimensions of the grid.
  */
  /***************************************************************************/
  Point Ocean::GetDimensions(void) const
  {
    Point pt = {x_quadrants_, y_quadrants_};
    return pt;
  }
  
  /***************************************************************************/
  /*!

  \brief
    Destructor of the class that deletes all allocated memory.

  */
  /***************************************************************************/
  Ocean::~Ocean()
  {
      //delete dynamic allocated arrays within the class
    delete [] grid_;
    delete [] boats_;
  }
  

} // namespace WarBoats

} // namespace CS170

