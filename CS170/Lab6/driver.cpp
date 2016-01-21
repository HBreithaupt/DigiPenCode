#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstdlib>  // atoi
#include "List.h"

void TestAdd()
{
  std::cout << "\n******************** TestAdd ********************\n";

  CS170::ListLab::List list1;
  CS170::ListLab::List list2; 
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  size_t size = sizeof(numbers) / sizeof(*numbers);

    // Create two lists
  for (size_t i = 0; i < size; i++)
  {
    list1.AddToEnd(numbers[i]);
    list2.AddToFront(numbers[i]);

    std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
    std::cout << list1 << std::endl;
    std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
    std::cout << list2 << std::endl;
    std::cout << std::endl;
  }
}

void TestFind()
{
  std::cout << "\n******************** TestFind ********************\n";

  CS170::ListLab::List list1;
  const int numbers[] = {
                         22, 23, 38, 94, 56, 34, 
                         67, 56, 88, 19, 10, 59
                        };
  size_t size = sizeof(numbers) / sizeof(*numbers);
  for (size_t i = 0; i < size; i++)
    list1.AddToEnd(numbers[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

    // Find an existing value
  int value = 56;
  CS170::ListLab::Node *node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << value << " was not found.\n";

  value = 22;
  node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << value << " was not found.\n";

  value = 59;
  node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << value << " was not found.\n";

    // Find a non-existant value
  value = 123;
  node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << value << " was not found.\n";

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
}

void TestDelete1()
{
  std::cout << "\n******************** TestDelete1 ********************\n";

  CS170::ListLab::List list1;
  const int numbers[] = {
                         22, 23, 38, 94, 56, 34, 
                         67, 56, 88, 19, 10, 59
                        };
  size_t size = sizeof(numbers) / sizeof(*numbers);
  for (size_t i = 0; i < size; i++)
    list1.AddToEnd(numbers[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  list1.Delete(56);
  std::cout << "Deleting: 56 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  list1.Delete(22);
  std::cout << "Deleting: 22 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  list1.Delete(59);
  std::cout << "Deleting: 59 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  list1.Delete(99);
  std::cout << "Deleting: 99 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  {
    const int numbers[] = {
                           23, 38, 94, 34, 
                           67, 56, 88, 19, 10
                          };
    size_t size = sizeof(numbers) / sizeof(*numbers);
    for (size_t i = 0; i < size; i++)
    {
      list1.Delete(numbers[i]);
      std::cout << "Deleting: " << numbers[i] << " (" << std::setw(2) 
                << list1.Count() << " nodes): ";
      std::cout << list1 << std::endl;
    }
    list1.Delete(99);
    std::cout << "Deleting: 99 (" << std::setw(2) << list1.Count() << " nodes): ";
    std::cout << list1 << std::endl;
  }
}

void TestDelete2()
{
  std::cout << "\n******************** TestDelete2 ********************\n";

  CS170::ListLab::List list1;
  const int numbers1[] = {
                         22, 23, 38, 94, 56, 34, 
                         67, 56, 88, 19, 10, 59
                        };
  size_t size1 = sizeof(numbers1) / sizeof(*numbers1);
  for (size_t i = 0; i < size1; i++)
    list1.AddToEnd(numbers1[i]);

  CS170::ListLab::List list2;
  const int numbers2[] = {
                         94, 23, 56, 22, 56, 19, 
                         67, 38, 34, 59
                        };
  size_t size2 = sizeof(numbers2) / sizeof(*numbers2);
  for (size_t i = 0; i < size2; i++)
    list2.AddToEnd(numbers2[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;

  list1.Delete(list2);
  std::cout << "List1 after deleting list2 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;
}

void TestConcat()
{
  std::cout << "\n******************** TestConcat ********************\n";

  CS170::ListLab::List list1;
  CS170::ListLab::List list2; 
  const int numbers1[] = {12, 34, 21, 56, 38, 94, 23};
  const int numbers2[] = {67, 56, 88, 19, 59, 10, 17};

  size_t size1 = sizeof(numbers1) / sizeof(*numbers1);
  size_t size2 = sizeof(numbers2) / sizeof(*numbers2);

  for (size_t i = 0; i < size1; i++)
    list1.AddToEnd(numbers1[i]);

  for (size_t i = 0; i < size2; i++)
    list2.AddToEnd(numbers2[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;

  std::cout << "Adding both lists (" << std::setw(2) << list1.Count() << " nodes): ";
  list1.Concat(list2);

  std::cout << list1 << std::endl;
}

void TestInsert1()
{
  std::cout << "\n******************** TestInsert1 ********************\n";

  CS170::ListLab::List list1;
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  for (int i = 0; i < 5; i++)
  {
    list1.AddToEnd(numbers[i]);
    std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
    std::cout << list1 << std::endl;
    std::cout << std::endl;
  }

  std::cout << "Inserting... 91 at position 3\n";
  list1.Insert(91, 3);
  std::cout << list1 << std::endl;
  std::cout << "Inserting... 92 at position 0\n";
  list1.Insert(92, 0);
  std::cout << list1 << std::endl;
  std::cout << "Inserting... 93 at position 7\n";
  list1.Insert(93, 7);
  std::cout << list1 << std::endl;
  std::cout << "Inserting... 94 at position 9\n";
  list1.Insert(94, 9);
  std::cout << list1 << std::endl;
}

void TestInsert2()
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

int main(int argc, char **argv)
{
  size_t test = 0;
  size_t count;
  void (*fp[])() = {
                     TestAdd,     /*  1 */
                     TestFind,    /*  2 */
                     TestInsert1, /*  3 */
                     TestInsert2, /*  4 */
                     TestConcat,  /*  5 */
                     TestDelete1, /*  6 */
                     TestDelete2, /*  7 */
                   };

  count = sizeof(fp) / sizeof(*fp);

  if (argc > 1)
    test = (size_t)std::atoi(argv[1]);

  if (test > count)
    test = 0;

  if (test)
    fp[test - 1]();
  else
  {
    for (size_t i = 0; i < count; i++)
      fp[i]();
  }

  return 0;
}
