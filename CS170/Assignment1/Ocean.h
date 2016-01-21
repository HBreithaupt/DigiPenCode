////////////////////////////////////////////////////////////////////////////////
#ifndef OCEAN_H
#define OCEAN_H
////////////////////////////////////////////////////////////////////////////////

/*****************************************************************************/
/* !
\file Ocean.h
\author      Haven Breithaupt
\par DP email: h.breithaupt@digipen.edu
\par Course: CS170
\par Assignment #1
\date  2/2/2015

\brief contains the struct definition of Ocean
*/
/*****************************************************************************/
#include "WarBoats.h" // ShotStats

namespace CS170
{
  namespace WarBoats
  {
      // The attributes of the ocean
    struct Ocean
    {
      int *grid;        // The 2D ocean 
      Boat *boats;      // The dynamic array of boats
      int num_boats;    // Number of boats in the ocean
      int x_quadrants;  // Ocean size along x-axis
      int y_quadrants;  // Ocean size along y-axis
      ShotStats stats;  // Status of the attack
    };
  } // namespace WarBoats
} // namespace CS170

#endif // OCEAN_H
////////////////////////////////////////////////////////////////////////////////
