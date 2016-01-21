#include <iostream>
#include "List.h"

void TestPushFront()
{
  std::cout << "TestPushFront..." << std::endl;

  int size = 5;
  CS170::List list;
  for (int i = 1; i <= size; i++)
    list.push_front(i);

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestPushBack()
{
  std::cout << "TestPushBack..." << std::endl;

  int size = 5;
  CS170::List list;
  for (int i = 1; i <= size; i++)
    list.push_back(i);

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestPushFrontBack()
{
  std::cout << "TestPushFrontBack..." << std::endl;

  int size = 10;
  CS170::List list;
  for (int i = 1; i <= size; i++)
  {
    list.push_front(i);
    list.push_back(i * 5);
  }

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestPopFront()
{
  std::cout << "TestPopFront..." << std::endl;

  int size = 5;
  CS170::List list;
  for (int i = 1; i <= size; i++)
    list.push_front(i);

  std::cout << list;
  while (!list.empty())
  {
    int item = list.pop_front();
    std::cout << "First item was: " << item << std::endl;
    std::cout << "New list:";
    std::cout << list;
    std::cout << "Items in the list: " << list.size() << std::endl;
  }
  std::cout << std::endl;
}

void TestArray1()
{
  std::cout << "TestArray1..." << std::endl;

  int array[] = {4, 7, 12, 5, 9, 23, 7, 11, 15, 2};
  int size = static_cast<int>(sizeof(array) / sizeof(*array));

    // Construct from array
  CS170::List list(array, size);

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestArray2()
{
  std::cout << "TestArray2..." << std::endl;

  const int array[] = {4, 7, 12, 5, 9, 23, 7, 11, 15, 2};
  int size = static_cast<int>(sizeof(array) / sizeof(*array));

    // Construct from array
  CS170::List list(array, size);

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestCopyConstructor1()
{
  std::cout << "TestCopyConstructor1..." << std::endl;
  int size = 10;
  CS170::List list1;
  for (int i = 1; i <= size; i++)
    list1.push_front(i * 3);

  std::cout << "List 1: ";
  std::cout << list1;

  CS170::List list2(list1);
  std::cout << "List 2: ";
  std::cout << list2;

  std::cout << std::endl;
}

void TestCopyConstructor2()
{
  std::cout << "TestCopyConstructor2..." << std::endl;
  int size = 10;
  CS170::List list1;
  for (int i = 1; i <= size; i++)
    list1.push_front(i * 3);

  std::cout << "List 1: ";
  std::cout << list1;

  const CS170::List list2(list1);
  std::cout << "List 2: ";
  std::cout << list2;

  if (list2.empty())
    std::cout << "List 2 is empty\n";
  else
    std::cout << "List 2 is not empty\n";

  std::cout << "Items in List2: ";
  std::cout << list2.size();
  std::cout << std::endl;
  
  std::cout << std::endl;
}

void TestAssignment1()
{
  std::cout << "TestAssignment1..." << std::endl;
  int size = 10;
  CS170::List list1, list2;
  for (int i = 1; i <= size; i++)
    list1.push_front(i * 2);

  std::cout << "Before assignment:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;

  list2 = list1;
  std::cout << "After assignment:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;

  std::cout << std::endl;
}

void TestAssignment2()
{
  std::cout << "TestAssignment2..." << std::endl;
  int size = 10;
  CS170::List list1, list2, list3;
  for (int i = 1; i <= size; i++)
    list1.push_front(i * 2);

  std::cout << "Before assignment:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;
  std::cout << "List 3: ";
  std::cout << list3;

  list3 = list2 = list1;
  std::cout << "After assignment:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;
  std::cout << "List 3: ";
  std::cout << list3;

  std::cout << std::endl;
}

void TestAddition1()
{
  std::cout << "TestAddition1..." << std::endl;

  int size = 5;
  CS170::List list1, list2;
  for (int i = 1; i <= size; i++)
  {
    list1.push_front(i);
    list2.push_front(i * 10);
  }

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;

  CS170::List list3;
  list3 = list1 + list2;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;
  std::cout << "List 3: ";
  std::cout << list3;
  std::cout << std::endl;
}

void TestAddition2()
{
  std::cout << "TestAddition2..." << std::endl;

  int size = 5;
  CS170::List list1, list2;
  for (int i = 1; i <= size; i++)
  {
    list1.push_front(i);
    list2.push_front(i * 10);
  }

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;

  const CS170::List list3(list1 + list2);
  std::cout << "List 3: ";
  std::cout << list3;

  CS170::List list4;
  list4 = list1 + list2 + list3;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 4: ";
  std::cout << list4;
  std::cout << "Items in the list: " << list4.size() << std::endl;
  std::cout << std::endl;
}

void TestAddAssign1()
{
  std::cout << "TestAddAssign1..." << std::endl;

  int size = 5;
  CS170::List list1, list2;
  for (int i = 1; i <= size; i++)
  {
    list1.push_front(i);
    list2.push_front(i * 10);
  }

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;

  list1 += list2;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;
  std::cout << "Items in the list: " << list1.size() << std::endl;
  std::cout << std::endl;
}

void TestAddAssign2()
{
  std::cout << "TestAddAssign2..." << std::endl;

  int size = 5;
  CS170::List list1, list2;
  for (int i = 1; i <= size; i++)
    list1.push_front(i);

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;

  list1 += list2;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;
  std::cout << "Items in the list: " << list1.size() << std::endl;
  std::cout << std::endl;
}

void TestAddAssign3()
{
  std::cout << "TestAddAssign3..." << std::endl;

  int size = 5;
  CS170::List list1, list2;
  for (int i = 1; i <= size; i++)
    list1.push_front(i);

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;

  list2 += list1;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;
  std::cout << "Items in the list: " << list1.size() << std::endl;
  std::cout << std::endl;
}

void TestAddAssign4()
{
  std::cout << "TestAddAssign4..." << std::endl;

  int size = 5;
  CS170::List list1, list2, list3;
  for (int i = 1; i <= size; i++)
  {
    list1.push_front(i);
    list2.push_front(i * 2);
    list3.push_front(i * 5);
  }

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;
  std::cout << "List 3: ";
  std::cout << list3;

  list1 += list2 += list3;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1: ";
  std::cout << list1;
  std::cout << "List 2: ";
  std::cout << list2;
  std::cout << "List 3: ";
  std::cout << list3;
  std::cout << "Items in the list: " << list1.size() << std::endl;
  std::cout << std::endl;
}

void TestSubscript1()
{
  std::cout << "TestSubscript1..." << std::endl;

  int size = 10;
  CS170::List list1;
  for (int i = 1; i <= size; i++)
    list1.push_back(i);

  std::cout << "list[0] = " << list1[0] << std::endl;
  std::cout << "list[5] = " << list1[5] << std::endl;
  std::cout << "list[9] = " << list1[9] << std::endl;
  std::cout << std::endl;
}

void TestSubscript2()
{
  std::cout << "TestSubscript2..." << std::endl;

  int size = 10;
  CS170::List list1;
  for (int i = 1; i <= size; i++)
    list1.push_back(i);

  std::cout << "Original list:\n";
  std::cout << list1;

  list1[0] = 10;
  list1[5] = 20;
  list1[9] = 30;
  list1[7] = list1[2];

  std::cout << "Modified list:\n";
  std::cout << list1;

  std::cout << std::endl;
}

int main()
{
  try {
    TestPushFront();
  }
  catch (...) {
    std::cout << "***TestPushFront revealed something bad in the List class" << std::endl;
  }

  try {
    TestPushBack();
  }
  catch (...) {
    std::cout << "***TestPushBack revealed something bad in the List class" << std::endl;
  }

  try {
    TestPushFrontBack();
  }
  catch (...) {
    std::cout << "***TestPushFrontBack revealed something bad in the List class" << std::endl;
  }

  try {
    TestPopFront();
  }
  catch (...) {
    std::cout << "***TestPopFront revealed something bad in the List class" << std::endl;
  }

  try {
    TestArray1();
  }
  catch (...) {
    std::cout << "***TestArray1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestArray2();
  }
  catch (...) {
    std::cout << "***TestArray2 revealed something bad in the List class" << std::endl;
  }

  try {
    TestCopyConstructor1();
  }
  catch (...) {
    std::cout << "***TestCopyConstructor1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestCopyConstructor2();
  }
  catch (...) {
    std::cout << "***TestCopyConstructor2 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAssignment1();
  }
  catch (...) {
    std::cout << "***TestAssignment1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAssignment2();
  }
  catch (...) {
    std::cout << "***TestAssignment2 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddAssign1();
  }
  catch (...) {
    std::cout << "***TestAddAssign1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddAssign2();
  }
  catch (...) {
    std::cout << "***TestAddAssign2 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddAssign3();
  }
  catch (...) {
    std::cout << "***TestAddAssign3 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddAssign4();
  }
  catch (...) {
    std::cout << "***TestAddAssign4 revealed something bad in the List class" << std::endl;
  }

  try {
    TestSubscript1();
  }
  catch (...) {
    std::cout << "***TestSubscript1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestSubscript2();
  }
  catch (...) {
    std::cout << "***TestSubscript2 revealed something bad in the List class" << std::endl;
  }

  std::cout << "============================================\n";
  std::cout << "Total number of Lists created: ";
  std::cout << CS170::List::list_count();
  std::cout << std::endl;
  std::cout << "============================================\n";
  std::cout << std::endl;

  try {
    TestAddition1();
  }
  catch (...) {
    std::cout << "***TestAddition1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddition2();
  }
  catch (...) {
    std::cout << "***TestAddition2 revealed something bad in the List class" << std::endl;
  }

  std::cout << "============================================\n";
  std::cout << "Total number of Lists created: ";
  std::cout << CS170::List::list_count();
  std::cout << std::endl;
  std::cout << "============================================\n";
  std::cout << std::endl;
  
  std::cout << "============================================\n";
  std::cout << "Total number of nodes alive: ";
  std::cout << CS170::List::node_count();
  std::cout << std::endl;
  std::cout << "============================================\n";
  std::cout << std::endl;

  return 0;
}

