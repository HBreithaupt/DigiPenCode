#include "Vector.h"
#include <iostream> // cout, endl
#include <cstdlib>  // atoi

void Print(const CS170::Vector& array, bool newline = true)
{
  for (unsigned i = 0; i < array.size(); i++)
  {
    std::cout << array[i] << "  ";
  }

  std::cout << "(size=" << array.size() << ", capacity=" << 
                           array.capacity() << ", allocs=" << 
                           array.allocations() << ")";
  if (newline)
    std::cout << std::endl;
}


void TestPush()
{
  std::cout << "\n********** TestPush **********\n";
  CS170::Vector a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "push_front 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_front(i);
    Print(a);
  }
}

void TestSubscripts()
{
  std::cout << "\n********** TestSubscripts **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);

  Print(a);

  std::cout << "multiple each value by 3:\n";
  for (unsigned i = 0; i < 10; i++)
    a[i] = a[i] * 3;
  Print(a);
}

void TestSubscript1()
{
  std::cout << "\n********** TestSubscript1 **********\n";
  CS170::Vector a;

  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  size_t size = sizeof(ia)/sizeof(*ia);
  std::cout << "push_back 10 even integers:\n";
  for (size_t i = 0; i < size; i++)
    a.push_back(ia[i]);
  Print(a);

  unsigned index = a.size() / 2;
  std::cout << "using subscript: a[" << index << "]" << std::endl;
  std::cout << "a[" << index << "] = " << a[index] << std::endl;
}

void TestSubscript2()
{
  std::cout << "\n********** TestSubscript2 **********\n";
  CS170::Vector a;

  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  size_t size = sizeof(ia)/sizeof(*ia);
  std::cout << "push_back 10 even integers:\n";
  for (size_t i = 0; i < size; i++)
    a.push_back(ia[i]);
  Print(a);

#if 0
  int index = a.size() * 2;
  std::cout << "using subscript: a[" << index << "]" << std::endl;
  std::cout << "a[" << index << "] = " << a[index] << std::endl;
#endif
}

void TestALot1()
{
  std::cout << "\n********** TestALot1 **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);

  std::cout << "push_back 10 odd integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i + 1);
  Print(a);

  std::cout << "push_back 10 more integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(i);
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);
}

int main(int argc, char **argv)
{
  size_t test_num = 0;
  if (argc > 1)
    test_num = static_cast<size_t>(std::atoi(argv[1]));

  typedef void (*Test)();
  Test Tests[] = {
                    TestPush,        //  1 
                    TestSubscripts,  //  2
                    TestSubscript1,  //  3
                    TestSubscript2,  //  4
                    TestALot1,       //  5
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
