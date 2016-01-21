#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstdlib>  // atoi
#include "List.h"

#if 0
static void TestInsert2()
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
#endif

static void TestMerge(const int numbers1[], const int numbers2[], size_t size1, size_t size2)
{
  CS170::ListLab::List list1;
  CS170::ListLab::List list2;

    // Get the numbers into a sorted list
  for (size_t i = 0; i < size1; i++)
    list1.Insert(numbers1[i]);
 
    // Get the numbers into a sorted list
  for (size_t i = 0; i < size2; i++)
    list2.Insert(numbers2[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;

  std::cout << "Merge list2 into list1:\n";
  list1.Merge(list2);
  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;
}

static void TestMerge1()
{
  std::cout << "\n******************** TestMerge1 ********************\n";

  const int numbers1[] = {12, 70, 21};
  const int numbers2[] = {67, 23, 88};
                        
  size_t size1 = sizeof(numbers1) / sizeof(*numbers1);
  size_t size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

static void TestMerge2()
{
  std::cout << "\n******************** TestMerge2 ********************\n";

  const int numbers1[] = {12, 34, 21, 56, 38, 94, 27, 22};
  const int numbers2[] = {67, 23, 88, 19, 59, 10, 17, 30};
                        
  size_t size1 = sizeof(numbers1) / sizeof(*numbers1);
  size_t size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

static void TestMerge3()
{
  std::cout << "\n******************** TestMerge3 ********************\n";

  const int numbers1[] = {12, 34, 21, 56};
  const int numbers2[] = {67, 23, 88, 19, 59, 10, 17, 30};
                        
  size_t size1 = sizeof(numbers1) / sizeof(*numbers1);
  size_t size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

static void TestMerge4()
{
  std::cout << "\n******************** TestMerge4 ********************\n";

  const int numbers1[] = {12, 34, 21, 56, 38, 94, 27, 22};
  const int numbers2[] = {67, 23, 88};
                        
  size_t size1 = sizeof(numbers1) / sizeof(*numbers1);
  size_t size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

static void TestMerge5()
{
  std::cout << "\n******************** TestMerge5 ********************\n";

  const int numbers1[] = {12, 34, 21, 56, 38, 94, 27, 22};
  const int numbers2[] = {0};
                        
  size_t size1 = sizeof(numbers1) / sizeof(*numbers1);

  TestMerge(numbers1, numbers2, size1, 0);
}

static void TestMerge6()
{
  std::cout << "\n******************** TestMerge6 ********************\n";

  const int numbers1[] = {0};
  const int numbers2[] = {67, 23, 88, 19, 59, 10, 17, 30};
                        
  size_t size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, 0, size2);
}

static void TestMerge7()
{
  std::cout << "\n******************** TestMerge7 ********************\n";

  const int numbers1[] = {12, 34, 12, 56, 12, 12, 27, 22};
  const int numbers2[] = {12, 12, 88, 12, 59, 12, 17, 12};
                        
  size_t size1 = sizeof(numbers1) / sizeof(*numbers1);
  size_t size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

static void TestMerge8()
{
  std::cout << "\n******************** TestMerge8 ********************\n";

  const int numbers1[] = {12, 70, 21, 55, 56, 20, 21, 12, 12, 8, 43};
                        
  size_t size1 = sizeof(numbers1) / sizeof(*numbers1);

  std::cout << "Merging a list into itself...\n";
  TestMerge(numbers1, numbers1, size1, size1);
}

int main(int argc, char **argv)
{
  //TestInsert2();
  //return 0;

  size_t test_num = 0;
  if (argc > 1)
    test_num = static_cast<size_t>(std::atoi(argv[1]));

  typedef void (*Test)();
  Test Tests[] = {
                    TestMerge1, // Test 1
                    TestMerge2, // Test 2
                    TestMerge3, // Test 3
                    TestMerge4, // Test 4
                    TestMerge5, // Test 5 
                    TestMerge6, // Test 6
                    TestMerge7, // Test 7
                    TestMerge8  // Test 8
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
