////////////////////////////////////////////////////////////////////////////////
#ifndef OCEAN_H
#define OCEAN_H
////////////////////////////////////////////////////////////////////////////////

/*****************************************************************************/
/*!
\file Ocean.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Assignment #2
\date  2-11-15

\brief
  Conatins the class Ocean to be used in Ocean.cpp.

*/
/*****************************************************************************/

#include "WarBoats.h"

namespace CS170
{
  namespace WarBoats
  {
    const int BOAT_LENGTH = 4;  // Length of a boat
    const int HIT_OFFSET = 100; // Add this to the boat ID

    class Ocean
    {
      public:
        
        // constructor
      Ocean(int num_boats, int x_quadrants, int y_quadrants);
      
        //destructor
      ~Ocean();
        
           // Provided
        const int *GetGrid(void) const;
        Point GetDimensions(void) const;
      
        //places boat on the board    
      BoatPlacement PlaceBoat(const Boat& boat);
      
        //takes a shot on the board
      ShotResult TakeShot(const Point &coordinate);
      
        //returns shot results
      ShotStats GetShotStats() const;

      private:
        int *grid_;        // The 2D ocean
        int x_quadrants_;  // Ocean size along x-axis
        int y_quadrants_;  // Ocean size along y-axis
        int num_boats_;    //number of boats
        Boat *boats_;      // holds the boats on the board
        ShotStats stats_;  // tracks stats of the shots
        
        
        
    }; // class Ocean

  } // namespace WarBoats

} // namespace CS170

#endif // OCEAN_H
////////////////////////////////////////////////////////////////////////////////
