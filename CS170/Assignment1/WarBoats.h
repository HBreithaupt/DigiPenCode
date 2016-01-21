////////////////////////////////////////////////////////////////////////////////
#ifndef WARBOATS_H
#define WARBOATS_H
////////////////////////////////////////////////////////////////////////////////


/*****************************************************************************/
/* !
\file WarBoats.h
\author      Haven Breithaupt
\par DP email: h.breithaupt@digipen.edu
\par Course: CS170
\par Assignment #1
\date   2/2/2015

\brief contains struct definitions Point, Boat and ShotStats; also includes
  function prototypes and enums necessary for the program.
*/
/*****************************************************************************/
namespace CS170
{
  namespace WarBoats
  {
    struct Ocean;  // Forward declaration

    enum Orientation { oHORIZONTAL, oVERTICAL };
    enum ShotResult { srHIT, srMISS, srDUPLICATE, srSUNK, srILLEGAL };
    enum DamageType { dtOK = 0, dtBLOWNUP = -1 };
    enum BoatPlacement { bpACCEPTED, bpREJECTED };

    struct Point
    {
      int x;
      int y;
    };

    struct Boat
    {
      int hits;                 // Hits taken so far
      int ID;                   // Unique ID 
      Orientation orientation;  // Horizontal/Vertical
      Point position;           // x-y coordinate (left-top)
    };

    struct ShotStats
    {
      int hits;
      int misses;
      int duplicates;
      int sunk;
    };

      // The interface
    Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants);
    void DestroyOcean(Ocean *theOcean);
    ShotResult TakeShot(Ocean &ocean, const Point &coordinate);
    BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat);
    ShotStats GetShotStats(const Ocean &ocean);

      // Provided
    void DumpOcean(const Ocean &ocean, int width = 4, bool extraline = false, 
                   bool showboats = true);

  } // namespace WarBoats

} // namespace CS170

#endif // WARBOATS_H
////////////////////////////////////////////////////////////////////////////////
