#include <iostream> // cout, endl
#include <iomanip>  // setw

#include "WarBoats.h"
#include "PRNG.h"

void PrintShotResult(const CS170::WarBoats::ShotResult &sr)
{
  const char *strings[] = {"HIT", "MISS", "DUPLICATE", "SUNK", "ILLEGAL"};
  std::cout << strings[static_cast<int>(sr)] << std::endl;
  //if (sr == CS170::WarBoats::srSUNK)
  //  std::cout << "*************************************************\n";
}

void PrintStats(const CS170::WarBoats::ShotStats &stats)
{
  std::cout << "      Hits: " << std::setw(3) << stats.hits << std::endl;
  std::cout << "    Misses: " << std::setw(3) << stats.misses << std::endl;
  std::cout << "Duplicates: " << std::setw(3) << stats.duplicates << std::endl;
  std::cout << "Boats Sunk: " << std::setw(3) << stats.sunk << std::endl;
}

void TakeAShot(CS170::WarBoats::Ocean &ocean, const CS170::WarBoats::Point& pt)
{
  CS170::WarBoats::ShotResult sr;
  std::cout << "Shot: " << pt.x << ", " << pt.y << "  ";
  sr = CS170::WarBoats::TakeShot(ocean, pt);
  PrintShotResult(sr);
  PrintStats(GetShotStats(ocean));
  CS170::WarBoats::DumpOcean(ocean);
  std::cout << std::endl;
}

void test_rect(int num_boats, int xsize, int ysize, 
               bool show_sunk = true, bool show_all = false)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

  CS170::WarBoats::Ocean *theOcean;
  theOcean = CS170::WarBoats::CreateOcean(num_boats, xsize, ysize);
  CS170::WarBoats::Ocean &ocean = *theOcean;

    // Place the boats randomly in the ocean
  int boats_placed = 0;
  while (boats_placed < num_boats)
  {
    CS170::WarBoats::Boat boat;

    //boat.hits = 0;
    boat.ID = boats_placed + 1;
    CS170::WarBoats::BoatPlacement bp;
    do
    {
        // Pick a random orientation
      boat.orientation = CS170::Utils::Random(0, 1)
                                 ? CS170::WarBoats::oHORIZONTAL
                                 : CS170::WarBoats::oVERTICAL;

        // Pick a random location
      CS170::WarBoats::Point location;
      location.x = CS170::Utils::Random(0, xsize - 1);
      location.y = CS170::Utils::Random(0, ysize - 1);
      boat.position = location;

        // Place the boat
      bp = CS170::WarBoats::PlaceBoat(ocean, boat);

    }while (bp == CS170::WarBoats::bpREJECTED);

    //CS170::WarBoats::DumpOcean(ocean);
    //std::cout << std::endl;
    boats_placed++;
  }
  std::cout << "Boats placed:\n";
  CS170::WarBoats::DumpOcean(ocean);
  std::cout << std::endl;

    // Try to sink the boats with random shots
  while (num_boats > 0)
  {
    CS170::WarBoats::ShotResult sr;
    do
    {
      CS170::WarBoats::Point coordinate;
      coordinate.x = CS170::Utils::Random(0, xsize - 1);
      coordinate.y = CS170::Utils::Random(0, ysize - 1);
      //std::cout << "target: " << coordinate.x << ", " 
      //          << coordinate.y << std::endl;

      sr = CS170::WarBoats::TakeShot(ocean, coordinate);
    } while (sr == CS170::WarBoats::srDUPLICATE);

      // Sunk a boat
    if (sr == CS170::WarBoats::srSUNK)
      num_boats--;

    if (show_all)
    {
      PrintShotResult(sr);
      PrintStats(GetShotStats(ocean));
      CS170::WarBoats::DumpOcean(ocean, 4, false);
      std::cout << std::endl;
    }
    else if ( (sr == CS170::WarBoats::srSUNK) && show_sunk)
    {
      PrintShotResult(sr);
      PrintStats(GetShotStats(ocean));
      CS170::WarBoats::DumpOcean(ocean, 4, false);
      std::cout << std::endl;
    }
  }
  std::cout << "Final board:\n";
  PrintStats(GetShotStats(ocean));
  CS170::WarBoats::DumpOcean(ocean, 4, false);
  std::cout << std::endl;
  CS170::WarBoats::DestroyOcean(theOcean);
}

int main(void)
{
  // usage: test_rect(boats, xsize, ysize, show_sunk, show_all)

  //test_rect(5, 10, 10, false, false);
  //test_rect(5, 10, 10, true, false);
  //test_rect(5, 10, 10, true, true);

  //test_rect(5, 8, 12, false, false);
  //test_rect(5, 8, 12, true, false);
  //test_rect(5, 8, 12, true, true);
  
  test_rect(99, 30, 30, false, false);
  //test_rect(99, 30, 30, true, false);
  //test_rect(99, 30, 30, true, true);
  
  return 0;
}
