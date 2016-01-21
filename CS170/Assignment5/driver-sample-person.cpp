#include <iostream> // cout, endl
#include <cstdio>   // sprintf
#include <cstring>  // strcpy
#include "List.h"

const unsigned ID_LEN = 6;
struct Person
{
  char ID[ID_LEN + 1];
  char lastName[26];   
  char firstName[26];  
  float salary;        
  unsigned years;           
};

struct Person PEOPLE[] = 
{
  {"101000", "Last",       "First",        0,  0},
  {"101001", "Faith",      "Ian",      80000, 10},
  {"102001", "Tufnel",     "Nigel",    90000, 12},
  {"103001", "Savage",     "Viv",      50000,  4},
  {"104001", "Shrimpton",  "Mick",     50000,  4},
  {"105001", "Besser",     "Joe",      40000,  1},
  {"106001", "Smalls",     "Derek",    80000, 10},
  {"107001", "St.Hubbins", "David",    90000, 12},
  {"108001", "Fleckman",   "Bobbi",   120000,  8},
  {"109001", "Eton-Hogg",  "Denis",   250000, 22},
  {"110001", "Upham",      "Danny",    60000,  5},
  {"111001", "McLochness", "Ross",     60000,  5},
  {"112001", "Pudding",    "Ronnie",   50000,  2},
  {"113001", "Schindler",  "Danny",    60000,  3},
  {"114001", "Pettibone",  "Jeanine",  85000,  3},
  {"115001", "Fame",       "Duke",     95000,  8},
  {"116001", "Fufkin",     "Artie",    45000,  1},
  {"117001", "DiBergi",    "Marty",    15000,  7},
  {"118001", "Floyd",      "Pink",     25000,  6},
  {"119001", "Zeppelin",   "Led",      35000,  3},
  {"120001", "Mason",      "Nick",     15000,  7},
  {"121001", "Wright",     "Richard",  17000,  9},
  {"122001", "Waters",     "Roger",    10000,  3},
  {"123001", "Gilmore",    "David",    19000,  5}
};

Person **PersonRecs;

void FreePersonRecs()
{
  int count = static_cast<int>(sizeof(PEOPLE) / sizeof(*PEOPLE));

  for (int i = 0; i < count; i++)
    delete PersonRecs[i];

  delete[] PersonRecs;
}

void FillPersonRecs()
{
  int count = static_cast<int>(sizeof(PEOPLE) / sizeof(*PEOPLE));
  PersonRecs = (Person **) new Person[count];

  int index = 0;
  for (int i = 0; i < count; i++)
  {
    Person *person = new Person;
    std::strcpy(person->ID, PEOPLE[i].ID);
    std::strcpy(person->lastName, PEOPLE[i].lastName);
    std::strcpy(person->firstName, PEOPLE[i].firstName);
    person->salary = PEOPLE[i].salary;
    person->years = PEOPLE[i].years;
    PersonRecs[index++] = person;
  }
}

std::ostream& operator<<(std::ostream &os, const Person &person)
{
  char buffer[200];
  std::sprintf(buffer, "Key: %8s, Name: %12s, %12s    Salary:%7.0f, Years: %2d\n", 
                  person.ID, person.lastName, person.firstName, person.salary, 
                  person.years);
  os << buffer;
  return os;
}

void TestPushFront()
{
  std::cout << "TestPushFront..." << std::endl;

  int size = 5;
  CS170::List<Person> list;
  for (int i = 1; i <= size; i++)
    list.push_front(*PersonRecs[i]);

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestPushBack()
{
  std::cout << "TestPushBack..." << std::endl;

  int size = 5;
  CS170::List<Person> list;
  for (int i = 1; i <= size; i++)
    list.push_back(*PersonRecs[i]);

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestPushFrontBack()
{
  std::cout << "TestPushFrontBack..." << std::endl;

  int size = 5;
  CS170::List<Person> list;
  for (int i = 1; i <= size; i++)
  {
    list.push_front(*PersonRecs[i]);
    list.push_back(*PersonRecs[i + 10]);
  }

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestPopFront()
{
  std::cout << "TestPopFront..." << std::endl;

  int size = 5;
  CS170::List<Person> list;
  for (int i = 1; i <= size; i++)
    list.push_front(*PersonRecs[i]);

  std::cout << list;
  while (!list.empty())
  {
    Person item = list.front();
    list.pop_front();
    std::cout << "First item was: " << item << std::endl;
    std::cout << "New list:\n";
    std::cout << list;
    std::cout << "Items in the list: " << list.size() << std::endl;
  }
  std::cout << std::endl;
}

void TestArray1()
{
  std::cout << "TestArray1..." << std::endl;

  Person array[] = {{"101001", "Faith",      "Ian",      80000, 10},
                    {"102001", "Tufnel",     "Nigel",    90000, 12},
                    {"103001", "Savage",     "Viv",      50000,  4},
                    {"104001", "Shrimpton",  "Mick",     50000,  4},
                    {"105001", "Besser",     "Joe",      40000,  1},
                    {"106001", "Smalls",     "Derek",    80000, 10},
                    {"107001", "St.Hubbins", "David",    90000, 12},
                    {"108001", "Fleckman",   "Bobbi",   120000,  8},
                    {"109001", "Eton-Hogg",  "Denis",   250000, 22},
                    {"110001", "Upham",      "Danny",    60000,  5}
                   };

  int size = static_cast<int>(sizeof(array) / sizeof(*array));

    // Construct from array
  CS170::List<Person> list(array, size);

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestArray2()
{
  std::cout << "TestArray2..." << std::endl;

  const
  Person array[] = {{"101001", "Faith",      "Ian",      80000, 10},
                    {"102001", "Tufnel",     "Nigel",    90000, 12},
                    {"103001", "Savage",     "Viv",      50000,  4},
                    {"104001", "Shrimpton",  "Mick",     50000,  4},
                    {"105001", "Besser",     "Joe",      40000,  1},
                    {"106001", "Smalls",     "Derek",    80000, 10},
                    {"107001", "St.Hubbins", "David",    90000, 12},
                    {"108001", "Fleckman",   "Bobbi",   120000,  8},
                    {"109001", "Eton-Hogg",  "Denis",   250000, 22},
                    {"110001", "Upham",      "Danny",    60000,  5}
                   };

  int size = static_cast<int>(sizeof(array) / sizeof(*array));

    // Construct from array
  CS170::List<Person> list(array, size);

  std::cout << list;
  std::cout << "Items in the list: " << list.size() << std::endl;
  std::cout << std::endl;
}

void TestCopyConstructor1()
{
  std::cout << "TestCopyConstructor1..." << std::endl;
  int size = 10;
  CS170::List<Person> list1;
  for (int i = 1; i <= size; i++)
    list1.push_front(*PersonRecs[i]);

  std::cout << "List 1:\n";
  std::cout << list1;

  CS170::List<Person> list2(list1);
  std::cout << "List 2:\n";
  std::cout << list2;

  std::cout << std::endl;
}

void TestCopyConstructor2()
{
  std::cout << "TestCopyConstructor2..." << std::endl;
  int size = 10;
  CS170::List<Person> list1;
  for (int i = 1; i <= size; i++)
    list1.push_front(*PersonRecs[i]);

  std::cout << "List 1:\n";
  std::cout << list1;

  const CS170::List<Person> list2(list1);
  std::cout << "List 2:\n";
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
  CS170::List<Person> list1, list2;
  for (int i = 1; i <= size; i++)
    list1.push_front(*PersonRecs[i]);

  std::cout << "Before assignment:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;

  list2 = list1;
  std::cout << "After assignment:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;

  std::cout << std::endl;
}

void TestAssignment2()
{
  std::cout << "TestAssignment2..." << std::endl;
  int size = 10;
  CS170::List<Person> list1, list2, list3;
  for (int i = 1; i <= size; i++)
    list1.push_front(*PersonRecs[i]);

  std::cout << "Before assignment:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;
  std::cout << "List 3:\n";
  std::cout << list3;

  list3 = list2 = list1;
  std::cout << "After assignment:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;
  std::cout << "List 3:\n";
  std::cout << list3;

  list1 = list1;
  std::cout << "After self assignment:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;

  std::cout << std::endl;
}

void TestAddition1()
{
  std::cout << "TestAddition1..." << std::endl;

  int size = 5;
  CS170::List<Person> list1, list2;
  for (int i = 1; i <= size; i++)
  {
    list1.push_front(*PersonRecs[i]);
    list2.push_front(*PersonRecs[i + 10]);
  }

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;

  CS170::List<Person> list3;
  list3 = list1 + list2;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;
  std::cout << "List 3:\n";
  std::cout << list3;
  std::cout << std::endl;
}

void TestAddition2()
{
  std::cout << "TestAddition2..." << std::endl;

  int size = 5;
  CS170::List<Person> list1, list2;
  for (int i = 1; i <= size; i++)
  {
    list1.push_front(*PersonRecs[i]);
    list2.push_front(*PersonRecs[i + 10]);
  }

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;

  const CS170::List<Person> list3(list1 + list2);
  std::cout << "List 3:\n";
  std::cout << list3;

  CS170::List<Person> list4;
  list4 = list1 + list2 + list3;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 4:\n";
  std::cout << list4;
  std::cout << "Items in the list: " << list4.size() << std::endl;
  std::cout << std::endl;
}

void TestAddAssign1()
{
  std::cout << "TestAddAssign1..." << std::endl;

  int size = 5;
  CS170::List<Person> list1, list2;
  for (int i = 1; i <= size; i++)
  {
    list1.push_front(*PersonRecs[i]);
    list2.push_front(*PersonRecs[i + 5]);
  }

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;

  list1 += list2;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;
  std::cout << "Items in the list: " << list1.size() << std::endl;
  std::cout << std::endl;
}

void TestAddAssign2()
{
  std::cout << "TestAddAssign2..." << std::endl;

  int size = 5;
  CS170::List<Person> list1, list2;
  for (int i = 1; i <= size; i++)
    list1.push_front(*PersonRecs[i]);

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;

  list1 += list2;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;
  std::cout << "Items in the list: " << list1.size() << std::endl;
  std::cout << std::endl;
}

void TestAddAssign3()
{
  std::cout << "TestAddAssign3..." << std::endl;

  int size = 5;
  CS170::List<Person> list1, list2;
  for (int i = 1; i <= size; i++)
    list1.push_front(*PersonRecs[i]);

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;

  list2 += list1;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;
  std::cout << "Items in the list: " << list1.size() << std::endl;
  std::cout << std::endl;
}

void TestAddAssign4()
{
  std::cout << "TestAddAssign4..." << std::endl;

  int size = 5;
  CS170::List<Person> list1, list2, list3;
  for (int i = 1; i <= size; i++)
  {
    list1.push_front(*PersonRecs[i]);
    list2.push_front(*PersonRecs[i + 8]);
    list3.push_front(*PersonRecs[i + 15]);
  }

  std::cout << "Before addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;
  std::cout << "List 3:\n";
  std::cout << list3;

  list1 += list2 += list3;
  std::cout << "After addition:" << std::endl;
  std::cout << "List 1:\n";
  std::cout << list1;
  std::cout << "List 2:\n";
  std::cout << list2;
  std::cout << "List 3:\n";
  std::cout << list3;
  std::cout << "Items in the list: " << list1.size() << std::endl;
  std::cout << std::endl;
}

void TestSubscript1()
{
  std::cout << "TestSubscript1..." << std::endl;

  int size = 10;
  CS170::List<Person> list1;
  for (int i = 1; i <= size; i++)
    list1.push_back(*PersonRecs[i]);

  std::cout << "list[0] = " << list1[0];
  std::cout << "list[5] = " << list1[5];
  std::cout << "list[9] = " << list1[9];
  std::cout << std::endl;
}

void TestSubscript2()
{
  std::cout << "TestSubscript2..." << std::endl;

  int size = 10;
  CS170::List<Person> list1;
  for (int i = 1; i <= size; i++)
    list1.push_back(*PersonRecs[i]);

  std::cout << "Original list:\n";
  std::cout << list1;

  list1[0] = *PersonRecs[12];
  list1[5] = *PersonRecs[15];
  list1[9] = *PersonRecs[19];
  list1[7] = list1[2];

  std::cout << "Modified list:\n";
  std::cout << list1;
}

void InUse()
{
  std::cout << "============================================\n";
  std::cout << "Total number of Nodes in use: ";
  std::cout << CS170::List<Person>::node_count();
  std::cout << std::endl;
  std::cout << "============================================\n";
  std::cout << std::endl;
}

int main()
{
  FillPersonRecs();

  try {
    TestPushFront();
    InUse();
  }
  catch (...) {
    std::cout << "***TestPushFront revealed something bad in the List class" << std::endl;
  }

  try {
    TestPushBack();
    InUse();
  }
  catch (...) {
    std::cout << "***TestPushBack revealed something bad in the List class" << std::endl;
  }

  try {
    TestPushFrontBack();
    InUse();
  }
  catch (...) {
    std::cout << "***TestPushFrontBack revealed something bad in the List class" << std::endl;
  }

  try {
    TestPopFront();
    InUse();
  }
  catch (...) {
    std::cout << "***TestPopFront revealed something bad in the List class" << std::endl;
  }

  try {
    TestArray1();
    InUse();
  }
  catch (...) {
    std::cout << "***TestArray1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestArray2();
    InUse();
  }
  catch (...) {
    std::cout << "***TestArray2 revealed something bad in the List class" << std::endl;
  }

  try {
    TestCopyConstructor1();
    InUse();
  }
  catch (...) {
    std::cout << "***TestCopyConstructor1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestCopyConstructor2();
    InUse();
  }
  catch (...) {
    std::cout << "***TestCopyConstructor2 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAssignment1();
    InUse();
  }
  catch (...) {
    std::cout << "***TestAssignment1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAssignment2();
    InUse();
  }
  catch (...) {
    std::cout << "***TestAssignment2 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddAssign1();
    InUse();
  }
  catch (...) {
    std::cout << "***TestAddAssign1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddAssign2();
    InUse();
  }
  catch (...) {
    std::cout << "***TestAddAssign2 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddAssign3();
    InUse();
  }
  catch (...) {
    std::cout << "***TestAddAssign3 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddAssign4();
    InUse();
  }
  catch (...) {
    std::cout << "***TestAddAssign4 revealed something bad in the List class" << std::endl;
  }

  try {
    TestSubscript1();
    InUse();
  }
  catch (...) {
    std::cout << "***TestSubscript1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestSubscript2();
    InUse();
  }
  catch (...) {
    std::cout << "***TestSubscript2 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddition1();
    InUse();
  }
  catch (...) {
    std::cout << "***TestAddition1 revealed something bad in the List class" << std::endl;
  }

  try {
    TestAddition2();
    InUse();
  }
  catch (...) {
    std::cout << "***TestAddition2 revealed something bad in the List class" << std::endl;
  }

  InUse();

  FreePersonRecs();

  return 0;
}
