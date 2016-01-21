#include <iostream> // cout, endl
#include <iomanip>  // setw

#include "WarBoats.h"
#include "Ocean.h"
#include "PRNG.h"

void Dump(const CS170::WarBoats::Ocean &ocean, int field_width = 4, bool extraline = false, bool showboats = true)
{
    // Get the size of the ocean
  int width = ocean.GetDimensions().x;
  int height = ocean.GetDimensions().y;

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      int value = ocean.GetGrid()[y * width + x];
      if ( (value > 0) && (value < CS170::WarBoats::HIT_OFFSET) && (showboats == false) )
        value = 0;
      std::cout << std::setw(field_width) << value;
    }
    std::cout << std::endl;
    if (extraline)
      std::cout << std::endl;
  }
}

void PrintShotResult(const CS170::WarBoats::ShotResult &sr)
{
  const char *strings[] = {"HIT", "MISS", "DUPLICATE", "SUNK", "ILLEGAL"};
  std::cout << strings[static_cast<int>(sr)] << std::endl;
  //if (sr == CS170::WarBoats::srSUNK)
  //  std::cout << "*************************************************\n";
}

void PrintStats(const CS170::WarBoats::Ocean &ocean)
{
  CS170::WarBoats::ShotStats stats = ocean.GetShotStats();
  std::cout << "      Hits: " << std::setw(3) << stats.hits << std::endl;
  std::cout << "    Misses: " << std::setw(3) << stats.misses << std::endl;
  std::cout << "Duplicates: " << std::setw(3) << stats.duplicates << std::endl;
  std::cout << "Boats Sunk: " << std::setw(3) << stats.sunk << std::endl;
}

void TakeAShot(CS170::WarBoats::Ocean &ocean, const CS170::WarBoats::Point& pt)
{
  CS170::WarBoats::ShotResult sr;
  std::cout << "Shot: " << pt.x << ", " << pt.y << "  ";
  sr = ocean.TakeShot(pt);
  PrintShotResult(sr);
  PrintStats(ocean);
  Dump(ocean);
  std::cout << std::endl;
}

void test0(void)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean
  int num_boats = 3;
  int xsize = 8;
  int ysize = 8;
  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize);

  std::cout << "The empty board" << std::endl;
  Dump(ocean);
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;
  CS170::WarBoats::BoatPlacement bp;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #2
  boat.ID = 2;
  location.x = 5;
  location.y = 1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #3
  boat.ID = 3;
  location.x = 0;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 4;
  location.x = 10;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 4;
  location.x = 2;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

      // Illegal placement
  boat.ID = 4;
  location.x = 5;
  location.y = 6;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  Dump(ocean, 4, true);
  std::cout << std::endl;
}

void test1(void)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean
  int num_boats = 3;
  int xsize = 8;
  int ysize = 8;
  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize);

  std::cout << "The empty board" << std::endl;
  Dump(ocean);
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean.PlaceBoat(boat);

    // Boat #2
  boat.ID = 2;
  location.x = 5;
  location.y = 1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  ocean.PlaceBoat(boat);

    // Boat #3
  boat.ID = 3;
  location.x = 0;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean.PlaceBoat(boat);

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  Dump(ocean);
  std::cout << std::endl;

  CS170::WarBoats::Point coordinate;

    // Illegal coordinate
  coordinate.x = 10;
  coordinate.y = 5;
  TakeAShot(ocean, coordinate);

    // HIT
  coordinate.x = 1;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // MISS
  coordinate.x = 5;
  coordinate.y = 7;
  TakeAShot(ocean, coordinate);

    // DUPLICATE
  coordinate.x = 1;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // HIT
  coordinate.x = 2;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // HIT
  coordinate.x = 3;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // SUNK
  coordinate.x = 4;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);
}

void test2(void)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean (check 100, 30x30)
  int num_boats = 5;
  int xsize = 10;
  int ysize = 10;

    // Use a pointer to an ocean and dynamically create it
  CS170::WarBoats::Ocean *ocean;
  ocean = new CS170::WarBoats::Ocean(num_boats, xsize, ysize);

  std::cout << "The empty board" << std::endl;
  Dump(*ocean);
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean->PlaceBoat(boat);

    // Boat #2
  boat.ID = 2;
  location.x = 5;
  location.y = 1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  ocean->PlaceBoat(boat);

    // Boat #3
  boat.ID = 3;
  location.x = 0;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean->PlaceBoat(boat);

    // Boat #4
  boat.ID = 4;
  location.x = 3;
  location.y = 8;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean->PlaceBoat(boat);

    // Boat #5
  boat.ID = 5;
  location.x = 9;
  location.y = 6;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  ocean->PlaceBoat(boat);

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  Dump(*ocean);
  std::cout << std::endl;

    // Try to sink the boats with random shots
  int shots = 0;
  while (num_boats > 0)
  {
    CS170::WarBoats::ShotResult sr;
    do
    {
      CS170::WarBoats::Point coordinate;
      coordinate.x = CS170::Utils::Random(0, xsize - 1);
      coordinate.y = CS170::Utils::Random(0, ysize - 1);
      std::cout << "Shot #"
                << ++shots
                << " at coordinate "
                << coordinate.x
                << ", "
                << coordinate.y
                << "  ";

      sr = ocean->TakeShot(coordinate);
      PrintShotResult(sr);
    } while (sr == CS170::WarBoats::srDUPLICATE);

      // Sunk a boat
    if (sr == CS170::WarBoats::srSUNK)
      num_boats--;

    //if (sr == CS170::WarBoats::srSUNK)
    {
      //PrintShotResult(sr);
      PrintStats(*ocean);
      Dump(*ocean);
      std::cout << std::endl;
    }
  }

  // Must delete the ocean "manually"
  delete ocean;
}

void test3(void)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean
  int num_boats = 1;
  int xsize = 5;
  int ysize = 5;

  CS170::WarBoats::Ocean *ocean;
  ocean = new CS170::WarBoats::Ocean(num_boats, xsize, ysize);

  std::cout << "The empty board" << std::endl;
  Dump(*ocean);
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;
  CS170::WarBoats::BoatPlacement bp;

    // Illegal placement
  boat.ID = 1;
  location.x = -1;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = -10;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 0;
  location.y = -1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 0;
  location.y = -10;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 6;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 100;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

      // Illegal placement
  boat.ID = 1;
  location.x = 0;
  location.y = 6;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 0;
  location.y = 100;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Legal placement
  boat.ID = 1;
  location.x = 0;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  Dump(*ocean, 4, true);
  std::cout << std::endl;

  CS170::WarBoats::Point coordinate;

    // Illegal coordinate
  coordinate.x = -1;
  coordinate.y = 0;
  TakeAShot(*ocean, coordinate);

  coordinate.x = -100;
  coordinate.y = 0;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 0;
  coordinate.y = -1;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 0;
  coordinate.y = -100;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 6;
  coordinate.y = 0;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 60;
  coordinate.y = 0;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 0;
  coordinate.y = 6;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 0;
  coordinate.y = 60;
  TakeAShot(*ocean, coordinate);

  delete ocean;
}

int main(void)
{
  test0();
  test1();
  test2();
  test3();
  return 0;
}
