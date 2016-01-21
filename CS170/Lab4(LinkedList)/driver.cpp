#include <iostream> // cout, endl
#include <iomanip>  // setw
#include "List.h"

int main(void)
{
  CS170::ListLab::Node *list1 = 0;
  CS170::ListLab::Node *list2 = 0; 
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  size_t size = sizeof(numbers) / sizeof(*numbers);

    // Create two lists
  for (size_t i = 0; i < size; i++)
  {
    CS170::ListLab::AddToEnd(&list1, numbers[i]);
    CS170::ListLab::AddToFront(&list2, numbers[i]);

    std::cout << "List1 (" << std::setw(2) << CS170::ListLab::Count(list1) << " nodes): ";
    CS170::ListLab::PrintList(list1);
    std::cout << "List2 (" << std::setw(2) << CS170::ListLab::Count(list2) << " nodes): ";
    CS170::ListLab::PrintList(list2);
    std::cout << std::endl;
  }

    // Find an existing value
  int value = 56;
  CS170::ListLab::Node *node = CS170::ListLab::FindItem(list1, value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n\n";
  //else
    //std::cout << "Value: " << node->number << " was not found.\n\n";

    // Find a non-existant value
  value = 123;
  node = CS170::ListLab::FindItem(list1, value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n\n";
  else
    std::cout << "Value: " << value << " was not found.\n\n";

    // Release the nodes
  CS170::ListLab::FreeList(list1);
  CS170::ListLab::FreeList(list2);

    // Inserting
  list1 = 0;
  for (int i = 0; i < 5; i++)
  {
    CS170::ListLab::AddToEnd(&list1, numbers[i]);
    std::cout << "List1 (" << std::setw(2) << CS170::ListLab::Count(list1) << " nodes): ";
    CS170::ListLab::PrintList(list1);
    std::cout << std::endl;
  }

  std::cout << "Inserting...\n";
  CS170::ListLab::Insert(&list1, 91, 3);
  CS170::ListLab::PrintList(list1);
  CS170::ListLab::Insert(&list1, 92, 0);
  CS170::ListLab::PrintList(list1);
  CS170::ListLab::Insert(&list1, 93, 7);
  CS170::ListLab::PrintList(list1);
  CS170::ListLab::Insert(&list1, 94, 9);
  CS170::ListLab::PrintList(list1);

  CS170::ListLab::FreeList(list1);

  return 0;
}
