#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstdlib>  // atoi, rand
#include "List.h"
#include "PRNG.h"

int RandomInt(unsigned low, unsigned high)
{
  return static_cast<int>(CS170::Utils::rand() % (high - low + 1) + low);
}

void Swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

void Shuffle(int *array, unsigned count)
{
  for (unsigned int i = 0; i < count; i++)
  {
    int r = RandomInt(i, count - 1);
    Swap(array[i], array[r]);
  }
}

void TestInsert2(void)
{
  std::cout << "\n******************** TestInsert2 ********************\n";

  CS170::ListLab::List list1;
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  size_t size = sizeof(numbers) / sizeof(*numbers);

  for (size_t i = 0; i < size; i++)
  {
    list1.Insert(numbers[i]);

    std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes) ";
    std::cout << "Inserting " << std::setw(2) << numbers[i] << ": ";
    std::cout << list1 << std::endl;
  }
}

void TestDuplicates(const int numbers1[], int size1)
{
  CS170::ListLab::List list1;

  for (int i = 0; i < size1; i++)
    list1.Insert(numbers1[i]);
 
  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  std::cout << "Duplicates removed: ";
  std::cout << list1.RemoveDuplicates() << std::endl;
  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
}

void TestDuplicates1(void)
{
  std::cout << "\n******************** TestDuplicates1 ********************\n";

  const int numbers1[] = {12, 34, 12, 24, 12, 12, 27, 34, 12, 12, 88, 27, 59, 12, 27, 12};
  int size1 = static_cast<int>(sizeof(numbers1) / sizeof(*numbers1));

  TestDuplicates(numbers1, size1);
}

void TestDuplicates2(void)
{
  std::cout << "\n******************** TestDuplicates2 ********************\n";

  const int numbers1[] = {12, 12, 12, 12, 12, 12, 12, 12};
  int size1 = static_cast<int>(sizeof(numbers1) / sizeof(*numbers1));

  TestDuplicates(numbers1, size1);
}

void TestDuplicates3(void)
{
  std::cout << "\n******************** TestDuplicates3 ********************\n";

  const int numbers1[] = {12, 17, 5, 10, 4, 11, 9, 8};
  int size1 = static_cast<int>(sizeof(numbers1) / sizeof(*numbers1));

  TestDuplicates(numbers1, size1);
}

void TestDuplicates4(void)
{
  std::cout << "\n******************** TestDuplicates4 ********************\n";

  const int numbers1[] = {5};
  int size1 = static_cast<int>(sizeof(numbers1) / sizeof(*numbers1));

  TestDuplicates(numbers1, size1);
}

void TestDuplicates5(void)
{
  std::cout << "\n******************** TestDuplicates5 ********************\n";

  const int numbers1[] = {5, 1};
  int size1 = static_cast<int>(sizeof(numbers1) / sizeof(*numbers1));

  TestDuplicates(numbers1, size1);
}

void TestDuplicates6(void)
{
  std::cout << "\n******************** TestDuplicates6 ********************\n";

  const int numbers1[] = {5, 1};

  TestDuplicates(numbers1, 0);
}

void TestDuplicates7(void)
{
  std::cout << "\n******************** TestDuplicates7 ********************\n";

  CS170::ListLab::List list1;
  const int size = 10000;

  for (int i = 0; i < size; i++)
    list1.Insert(RandomInt(1, 9));
 
  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): \n";
  //std::cout << list1 << std::endl;

  std::cout << "Duplicates removed: ";
  std::cout << list1.RemoveDuplicates() << std::endl;
  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
}

int main(int argc, char **argv)
{
  //TestInsert2(); 

  size_t test_num = 0;
  if (argc > 1)
    test_num = static_cast<size_t>(std::atoi(argv[1]));

  typedef void (*Test)(void);
  Test Tests[] = {
                    TestDuplicates1, // Test 1
                    TestDuplicates2, // Test 2
                    TestDuplicates3, // Test 3
                    TestDuplicates4, // Test 4
                    TestDuplicates5, // Test 5
                    TestDuplicates6, // Test 6
                    TestDuplicates7, // Test 7
                 };

  size_t num = sizeof(Tests) / sizeof(*Tests);
  if (test_num == 0)
  {
    for (size_t i = 0; i < num; i++)
      Tests[i]();
  }
  else if (test_num > 0 && test_num <= num)
    Tests[test_num - 1]();
  
  return 0;
}
