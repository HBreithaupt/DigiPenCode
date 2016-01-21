#include <iostream> // cout, endl
#include <iomanip>  // setw
#include "List.h"

void TestAdd(void)
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
    list1.PrintList();
    std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
    list2.PrintList();
    std::cout << std::endl;
  }
}

void TestFind(void)
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
  list1.PrintList();

    // Find an existing value
  int value = 56;
  CS170::ListLab::Node *node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n";

  value = 22;
  node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n";

  value = 59;
  node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n";

    // Find a non-existant value
  value = 123;
  node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << value << " was not found.\n";

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  list1.PrintList();
}

void TestInsert1(void)
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
    list1.PrintList();
    std::cout << std::endl;
  }

  std::cout << "Inserting... 91 at position 3\n";
  list1.Insert(91, 3);
  list1.PrintList();
  std::cout << "Inserting... 92 at position 0\n";
  list1.Insert(92, 0);
  list1.PrintList();
  std::cout << "Inserting... 93 at position 7\n";
  list1.Insert(93, 7);
  list1.PrintList();
  std::cout << "Inserting... 94 at position 9\n";
  list1.Insert(94, 9);
  list1.PrintList();
}

int main(void)
{
  TestAdd();
  TestFind();
  TestInsert1();
}
