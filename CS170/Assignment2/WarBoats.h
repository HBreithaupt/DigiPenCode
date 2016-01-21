////////////////////////////////////////////////////////////////////////////////
#ifndef WARBOATS_H
#define WARBOATS_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{
  namespace WarBoats
  {
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

  } // namespace WarBoats

} // namespace CS170

#endif // WARBOATS_H
////////////////////////////////////////////////////////////////////////////////
