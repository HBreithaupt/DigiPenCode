/*****************************************************************************/
/*!
\file   Ocean.cpp
\author Haven Breithaupt
\par    email: h.breithaupt\@digipen.edu
\par    DigiPen login: h.breithaupt
\par    Course: CS170
\par    Assignment #1
\date   2/2/2015
\brief  
    This file ontains the functions to create a battleship like emulator
    
    Functions include:
      CreateOcean - create the board
      DestroyOcean - delete all components of the game
      TakeAShot - takes a shot and computes result
      PlaceBoat - places boats on the board
      GetShotStats - inform the player of their statisitics from the game
      
  Hours spent on this assignment: ~12

  Specific portions that gave you the most trouble: 
   - place boat had some interesting logic implementation
   - having to go back and initialize all components from Create Ocean to get
     rid of memory leaks
    
  
  
  
*/
/*****************************************************************************/

#include "WarBoats.h"
#include "Ocean.h"
#include <iostream> // cout, endl
#include <iomanip>  // setw

namespace CS170
{
  namespace WarBoats
  {
    const int BOAT_LENGTH = 4;  // Length of a boat
    const int HIT_OFFSET = 100; // Add this to the boat ID
    
    /*************************************************************************/

    /*!
    \fn Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants)

    \brief
      Creates a new Ocean to use for the game.

    \param num_boats
      Number of boats the player wants to place on the board.
      
    \param x_quadrants
      The width of the board.
    
    \param y_quadrants
      The height of the board.
      

    \return 
    */
    /*************************************************************************/
    Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants)
    {
        //dynamically created struct as the board
      Ocean *ocean = new Ocean;
        
        // assign num_boats in struct
      ocean->boats = new Boat[num_boats];
      
        //assign number of boats
      ocean->num_boats = num_boats;
      
        //assign width of the board in the struct
      ocean->x_quadrants = x_quadrants;
        
        //assign height of the board in the struct
      ocean->y_quadrants = y_quadrants;
      
        //create 2d array for the grid
      ocean->grid = new int[x_quadrants * y_quadrants];
      
        //initialize stats struct
      ocean->stats.hits = 0;
      ocean->stats.misses = 0;
      ocean->stats.duplicates = 0;
      ocean->stats.sunk = 0;
      
        //initialize the boats
      for(int boat_number = 1; boat_number <= num_boats; boat_number++)
      {
        ocean->boats[boat_number - 1].hits = 0;
        ocean->boats[boat_number - 1].ID = 0;
        ocean->boats[boat_number - 1].position.x = 0;
        ocean->boats[boat_number - 1].position.y = 0;
      }
      
        //initialize the grid
      for(int init_grid = 0; init_grid < x_quadrants * y_quadrants;init_grid++)
        ocean->grid[init_grid] = 0;
      
        //return pointer to the board struct
      return ocean;
    }

    /*************************************************************************/
    /*!
    \fn void DestroyOcean(Ocean *theOcean)

    \brief
      deletes the components of the game

    \param theOcean
      A pointer to the game board

    \return 
      N/A
    */
    /*************************************************************************/
    void DestroyOcean(Ocean *theOcean)
    {
        //delete the boat
      delete [] theOcean->boats; 
      
        //delete the grid array
      delete [] theOcean->grid;
      
        //delete the Ocean
      delete theOcean;
    }
    
    
    /*************************************************************************/
    /*!
    \fn ShotResult TakeShot(Ocean &ocean, const Point &coordinate)

    \brief
      Computes result of shot information given

    \param ocean
      a reference to a struct of the board.
      
    \param coordinate
      a reference to a struct containing the coordinates of the shot

    \return 
      possible returns depending on shot outcome: hit, miss, duplicate, illegal
      ship has been sunk
      
    */
    /*************************************************************************/
    ShotResult TakeShot(Ocean &ocean, const Point &coordinate)
    {
        //coordinate is not on grid
      if (coordinate.x < 0 || coordinate.y < 0)
        return srILLEGAL;
      
        //shot is off board
      if (coordinate.x > ocean.x_quadrants || coordinate.y > ocean.y_quadrants)
        return srILLEGAL;
      
        //index formula for grid array
      int grid_index = coordinate.y * ocean.x_quadrants + coordinate.x;
      
        //grab value of the board
      int grid_value = ocean.grid[grid_index];
      
        //you missed
      if (grid_value == dtOK)
      {
        ocean.stats.misses++;
        ocean.grid[grid_index] = -1;
        return srMISS;
      }
      
        //you hit a boat
      if (grid_value > dtOK && grid_value <= ocean.num_boats)
      {
        ocean.grid[grid_index] += 100;
        ocean.stats.hits++;
        ocean.boats[grid_value - 1].hits++;
        
          // checks if the boat has been sunk
        if(ocean.boats[grid_value - 1].hits == BOAT_LENGTH)
        {
          ocean.stats.sunk++;
          return srSUNK;
        }
          
          // you hit a boat
        return srHIT;
      }
      
        //duplicate
      if (grid_value == dtBLOWNUP || grid_value > HIT_OFFSET)
      {
        ocean.stats.duplicates++;
        return srDUPLICATE;
      }
      
        // if for some reason no conditions are validated then return illegal
      return srILLEGAL;
    }
    
    
    /*************************************************************************/
    /*!
    \fn BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat)

    \brief
      Validates if the boat placement requested is valid or invalid

    \param ocean
      A reference to a struct of the game board
      
    \param boat
      A struct containing information about the boat you wish to place

    \return 
      bpACCEPTED if boat can be placed, bpREJECTED if it cannot
    */
    /*************************************************************************/
    BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat)
    {
      
        // y cooridinate of the boat piece given
      int relative_y = boat.position.y;
      
        // x coordinate of boat piece given
      int relative_x = boat.position.x;
      
        // width of the board
      int grid_width = ocean.x_quadrants;
      
        // boat is vertical
      if(boat.orientation == oVERTICAL)
      {
          // is the top piece on the board
        if(boat.position.y >= 0 && boat.position.y <= ocean.y_quadrants)
        {
            // is the top piece on the board
          if(boat.position.x >= 0 && boat.position.x <= ocean.x_quadrants)
          {
              //is the bootom piece on the board
            if(boat.position.y + 3 < ocean.y_quadrants)
            {
                //count safe spots
              int safe_spots_v = 0;
              
                //checks all spots to see if theyre empty
              for(int i = 0; i <= 3; i++)
              {
                if(ocean.grid[(relative_y + i) * grid_width + relative_x] == 0)
                  safe_spots_v++;
                
                 //if all spots are empty write to the grid and return accepted
                if (safe_spots_v == BOAT_LENGTH)
                {
                    //writes to grid the boat id
                  for(int write_v = 0; write_v <= 3; write_v++)
                    ocean.grid[(relative_y + write_v) * grid_width 
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
        if(boat.position.x >= 0 && boat.position.x <= ocean.x_quadrants)
        {
            //is the leftmost piece's y-coord on the board?
          if(boat.position.y >= 0 && boat.position.y <= ocean.y_quadrants)
          {
              //is the rightmost piece on the board?
            if(boat.position.x + 3 < ocean.x_quadrants)
            {
                //counts safe spots
              int safe_spots_h = 0;
              
                //check all pieces on the grid to see if the spaces are empty
              for(int j = 0; j <= 3; j++)
              {
                  //if nothing is here keep checking
                if (ocean.grid[relative_y * grid_width + (relative_x + j)] == 0)
                  safe_spots_h++;
                
                  // all spaces are empty write to the grid and return accepted
                if (safe_spots_h == BOAT_LENGTH)
                {
                    //writes to the grid the boat id
                  for (int write_h = 0; write_h <= 3; write_h++)
                    ocean.grid[relative_y * grid_width + 
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
    
    
    /*************************************************************************/
    /*!
    \fn ShotStats GetShotStats(const Ocean &ocean)
    
    \brief
      returns the shot information from the current game
      
    \param ocean
      a reference to a struct that houses the stats
      

    \return 
      the struct containing the shot information
    */
    /*************************************************************************/
    ShotStats GetShotStats(const Ocean &ocean)
    {
        // return shot information
      return ocean.stats;
    }

    /*************************************************************************/
    /*!
      \brief
        Prints the grid (ocean) to the screen.
      
      \param ocean
        The Ocean to print
      
      \param field_width
        How much space each position takes when printed.
      
      \param extraline
        If true, an extra line is printed after each row. If false, no extra
        line is printed.
        
      \param showboats
        If true, the boats are shown in the output. (Debugging feature)
    */
    /*************************************************************************/
    void DumpOcean(const CS170::WarBoats::Ocean &ocean,
                                    int field_width, 
                                    bool extraline, 
                                    bool showboats)
    {
        // For each row
      for (int y = 0; y < ocean.y_quadrants; y++)
      {
          // For each column
        for (int x = 0; x < ocean.x_quadrants; x++)
        {
          int value = ocean.grid[y * ocean.x_quadrants + x];
    
            // Is it a boat?
          if ( (value > 0) && (value < HIT_OFFSET) && (showboats == false) )
            value = 0;
    
          std::cout << std::setw(field_width) << value;
        }
        std::cout << std::endl;
        if (extraline)
          std::cout << std::endl;
      }
    }

  } // namespace WarBoats
} // namespace CS170


