#include "List.h"
#include "PRNG.h"
#include <iostream> // cout, endl
#include <cstdlib>  // rand, atoi

// generate random numbers between low and high 
int RandomInt(int low, int high)
{
  int rnd = static_cast<int>(CS170::Utils::rand());
  int number = rnd % (high - low + 1) + low;
  return number;
}

// push_front, subscript
void TestStress1(int size)
{
  std::cout << "\nTestStress1..." << std::endl;

  CS170::List<int> list;
  for (int i = 1; i <= size; i++)
    list.push_front(RandomInt(1, 9));

  //std::cout << list;
  int sum = 0;
  for (int i = 0; i < size; i += 10)
    sum += list[i];
    
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << "Sum of 10%: " << sum << std::endl;
  std::cout << std::endl;
}

// push_front
void TestStress2(int size)
{
  std::cout << "\nTestStress2..." << std::endl;

  CS170::List<int> list;
  for (int i = 1; i <= size; i++)
    list.push_front(i);

  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

// push_front, rotate the items
void TestStress3(int size)
{
  std::cout << "\nTestStress3..." << std::endl;

  CS170::List<int> list;
  for (int i = 0; i < size; i++)
    list.push_front(RandomInt(1, 9));

  //std::cout << list;
  for (int i = 0; i < size; i++)
  {
    list.push_back(list.front());
    list.pop_front();
    //std::cout << list;
  }
  //std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

// push_front, subscript
void TestStress4(int size, int value)
{
  std::cout << "\nTestStress4..." << std::endl;

  CS170::List<int> list;
  for (int i = 0; i < size; i++)
    list.push_front(RandomInt(1, 9));

  //std::cout << list;
  int count = 0;
  for (int i = 0; i < size; i++)
  {
    if (list[i] == value)
      count++;
  }
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << "The number " << value << " appears " << count
            << " times in the list" <<  std::endl;

  std::cout << std::endl;
}

// push_front, subscript
void TestStress5(int size)
{
  std::cout << "\nTestStress5..." << std::endl;

  CS170::List<int> list;
  int low = 1, high = 9;
  for (int i = 0; i < size; i++)
    list.push_front(RandomInt(low, high));

  //std::cout << list;
  int total = 0;
  for (int i = 1; i <= high; i++)
  {
    int count = 0;
    for (int j = 0; j < size; j++)
      if (list[j] == i)
        count++;

    total += count;
    std::cout << "The number " << i << " appears " << count
              << " times in the list" <<  std::endl;
  }
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << "Items in the list: " << total << std::endl;

  std::cout << std::endl;
}

int main(int argc, char **argv)
{
  CS170::Utils::srand(1, 2);

  int test = 0;
  if (argc > 1)
    test = std::atoi(argv[1]);

  switch (test)
  {
    case 1:
      try {
        TestStress1(100000);
      }
      catch (...) {
        std::cout << "***TestStress1 revealed something bad in the List class" << std::endl;
      }
      break;

    case 2:
      try {
        TestStress2(1000000);
      }
      catch (...) {
        std::cout << "***TestStress2 revealed something bad in the List class" << std::endl;
      }
      break;

    case 3:
      try {
        TestStress3(1000000);
      }
      catch (...) {
        std::cout << "***TestStress3 revealed something bad in the List class" << std::endl;
      }
      break;

    case 4:
      try {
        TestStress4(50000, 3);
      }
      catch (...) {
        std::cout << "***TestStress4 revealed something bad in the List class" << std::endl;
      }
      break;

    case 5:
      try {
        TestStress5(10000);
      }
      catch (...) {
        std::cout << "***TestStress5 revealed something bad in the List class" << std::endl;
      }
      break;

    default:
        TestStress1(100000);
        TestStress2(1000000);
        TestStress3(1000000);
        TestStress4(50000, 3);
        TestStress5(10000);
      break;
  }


  std::cout << "============================================\n";
  std::cout << "Total number of Nodes in use: ";
  std::cout << CS170::List<int>::node_count();
  std::cout << std::endl;
  std::cout << "============================================\n";
  std::cout << std::endl;

  return 0;
}

