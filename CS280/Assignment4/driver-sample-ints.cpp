#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <sstream>
#include <cstring>

#include "BSTree.h"
#include "AVLTree.h"
#include "PRNG.h"
#include "ObjectAllocator.h"

bool SHOW_COUNTS = true;

using std::cout;
using std::endl;

//*********************************************************************
// Printing/Debugging
//*********************************************************************
static int Position;
void SetTreePositions(const BSTree::BinTreeNode *tree, 
                      int depth, 
                      std::map<const BSTree::BinTreeNode *, 
                      std::pair<int, int> >& NodePositions)
{
  if (!tree)
    return;

  SetTreePositions(tree->left, depth + 1, NodePositions);
  std::pair<int, int>XY(Position++, depth);
  std::pair<const BSTree::BinTreeNode *, std::pair<int, int> > pr(tree, XY);
  NodePositions.insert(pr);
  SetTreePositions(tree->right, depth + 1, NodePositions);
}


//template <typename T>
void SetTreePositions(const BSTree &tree, 
                      std::map<const BSTree::BinTreeNode *, 
                      std::pair<int, int> >& NodePositions)
{
  Position = 0;
  NodePositions.clear();
  SetTreePositions(tree.root(), 0, NodePositions);
}

//template <typename T>
std::vector<std::pair<const BSTree::BinTreeNode *, int> >
GetNodesAtLevel(int level, 
                std::map<const BSTree::BinTreeNode *, 
                std::pair<int, int> >& NodePositions)
{
  std::vector<std::pair<const BSTree::BinTreeNode *, int> >nodes;
  typename std::map<const BSTree::BinTreeNode *, std::pair<int, int> >::iterator it;
  for (it = NodePositions.begin(); it != NodePositions.end(); ++it)
  {
    std::pair<int, int>XY = it->second;
    if (XY.second == level)
    {
      std::pair<const BSTree::BinTreeNode *, int> pr( it->first, XY.first);
      nodes.push_back(pr);
    }
  }
  return nodes;
}  

//template <typename T>
bool SortNodes(const std::pair<const BSTree::BinTreeNode *, int>&a, 
               const std::pair<const BSTree::BinTreeNode *, int>&b)
{
  if (a.second < b.second)
    return true;
  else
    return false;
}

//template <typename T>
class fSortNodes
{
public:
  bool operator()(const std::pair<const BSTree::BinTreeNode *, int>&a, 
                  const std::pair<const BSTree::BinTreeNode *, int>&b)
  {
    if (a.second < b.second)
      return true;
    else
      return false;
  }
};


void Print(int *array, int count)
{
  for(int i = 0; i < count; ++i)
    std::cout << array[i] << ", ";
  
  std::cout << std::endl;
}

//template <typename T>
void PrintBST(const BSTree &tree)
{
  std::map<const BSTree::BinTreeNode *, std::pair<int, int> > NodePositions;

  SetTreePositions(tree, NodePositions);
  int height = tree.height();
  int offset = 0;
  int fudge = 5;
  for (int i = 0; i <= height; i++)
  {
    std::vector<std::pair<const BSTree::BinTreeNode *, int> >nodes = GetNodesAtLevel(i, NodePositions);
    // Borland doesn't like the function, wants a function object
    //std::sort(nodes.begin(), nodes.end(), SortNodes<T>);
    std::sort(nodes.begin(), nodes.end(), fSortNodes());
    typename std::vector<std::pair<const BSTree::BinTreeNode *, int> >::iterator iter;
    char buffer[1024 * 2] = {0};
    std::memset(buffer, ' ', 1024 * 2);

    for (iter = nodes.begin(); iter != nodes.end(); ++iter)
    {
      //char data[60] = {0};
      int value = (*iter).first->data;
      //std::sprintf(data, "%g", value);  // <<**>>

      std::stringstream ss;
      if (SHOW_COUNTS)
        ss << value << "[" << (*iter).first->count << "]";
      else
        ss << value;

      offset = (height / 2) + iter->second * fudge;  // fudge factor (change to 4 for big numbers)
      //strncpy(buffer + offset, data, strlen(data));
      strncpy(buffer + offset, ss.str().c_str(), ss.str().length());
    }
    buffer[offset + fudge * 2] = 0; // should handle 4 digits easily
    std::cout << buffer << std::endl << std::endl;
  }
}

const char *ReadableType(const char *name)
{
  if (std::strstr(name, "AVL"))
    return "AVLTree";
  else
    return "BSTree";
}

template <typename T>
void PrintInfo(const T& tree)
{
  std::cout << "type: " << ReadableType(typeid(T).name()) << ", height: " << tree.height();
  std::cout << ", nodes: " << tree.size() << std::endl;
}

//*********************************************************************
// End Printing/Debugging
//*********************************************************************

int RandomInt(int low, int high)
{
  //return std::rand() % (high - low + 1) + low;
  return Digipen::Utils::Random(low, high);
}

template <typename T>
void SwapInt(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
}

template <typename T> void Shuffle(T *array, int count, int stride = 1)
{
  for (int i = 0; i < count; i += stride)
  {
    int r = RandomInt(0, count - 1);
    SwapInt(array[i], array[r]);
  }
}

void GetValues(int *array, int size)
{
  //std::srand(1);
  Digipen::Utils::srand(1, 2);
  for (int i = 0; i < size; i++)
    array[i] = i;

  Shuffle(array, size);
}

template <typename T>
void Test1(void)
{
  T tree;
  const int size = 10;
  int vals[size];
  GetValues(vals, size);
  const char *test = "Test1 - random insert";

  std::cout << "\n====================== " << test << " ======================\n";
  std::cout << ReadableType(typeid(T).name()) << std::endl;
  try
  {
    for (int i = 0; i < size; i++)
    {
      tree.insert(vals[i]);
      PrintBST(tree);
      std::cout << "\n====================== " << test << " ======================\n";
    }
    
    std::cout << "height: " << tree.height() << std::endl;
    std::cout << " nodes: " << tree.size() << std::endl;
    if (tree.empty())
      std::cout << "tree is empty\n\n";
    else
      std::cout << "tree is NOT empty\n\n";

    PrintBST(tree);
    //int count = 0;
    for (unsigned i = 0; i < tree.size(); i++)
    {
      //if (tree[i])
      {
        //count++;
        //std::cout << "TREE is " << tree[i] << std::endl;
        //std::cout << "data is " << tree[i]->data << std::endl;      
        //std::cout << "Index " << i << ": " << tree[i]->data << std::endl;
      }
    }
    //std::cout << "count is " << count << std::endl;
  }
  catch (const BSTException &e)
  {
    std::cout << "Caught BSTException in " << test;
    int value = e.code();
    if (value == BSTException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...)
  {
    std::cout << "Caught unknown exception in " << test << std::endl;
  }
}


template <typename T>
void Test2(void)
{
  T tree;
  const int size = 10;
  const char *test = "Test2 - sorted insert";

  std::cout << "\n====================== " << test << " ======================\n";
  std::cout << ReadableType(typeid(T).name()) << std::endl;
  try
  {
    for (int i = 0; i < size; i++)
    {
      tree.insert(i);
      PrintBST(tree);
      std::cout << "\n====================== " << test << " ======================\n";
    }
    std::cout << "height: " << tree.height() << std::endl;
    std::cout << " nodes: " << tree.size() << std::endl;
    if (tree.empty())
      std::cout << "tree is empty\n\n";
    else
      std::cout << "tree is NOT empty\n\n";

    PrintBST(tree);
  }
  catch (const BSTException &e)
  {
    std::cout << "Caught BSTException in " << test;
    int value = e.code();
    if (value == BSTException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...)
  {
    std::cout << "Caught unknown exception in " << test << std::endl;
  }
}

template <typename T>
void Test3(void)
{
  T tree;
  const int size = 10;
  int vals[size];
  GetValues(vals, size);
  const char *test = "Test3 - random insert/remove";

  std::cout << "\n====================== " << test << " ======================\n";
  std::cout << ReadableType(typeid(T).name()) << std::endl;
  try
  {
    for (int i = 0; i < size; i++)
    {
      tree.insert(vals[i]);
    
        // comment back three lines
      //std::cout << "====================================\n";
      //std::cout << "Inserting: " << vals[i] << std::endl;
      //PrintBST(tree);
    }
  
    std::cout << "remove 2, 6, 3:\n";
    tree.remove(2);
    tree.remove(6);
    tree.remove(3);

    std::cout << "height: " << tree.height() << std::endl;
    std::cout << " nodes: " << tree.size() << std::endl;
    if (tree.empty())
      std::cout << "tree is empty\n\n";
    else
      std::cout << "tree is NOT empty\n\n";

    PrintBST(tree);
    //int count = 0;
    for (unsigned i = 0; i < tree.size(); i++)
    {
      //if (tree[i])
      {
        //count++;
        //std::cout << "TREE is " << tree[i] << std::endl;
        //std::cout << "data is " << tree[i]->data << std::endl;      
        //std::cout << "Index " << i << ": " << tree[i]->data << std::endl;
      }
    }
    //std::cout << "count is " << count << std::endl;
  }
  catch (const BSTException &e)
  {
    std::cout << "Caught BSTException in " << test;
    int value = e.code();
    if (value == BSTException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...)
  {
    std::cout << "Caught unknown exception in " << test << std::endl;
  }
}

template <typename T>
void Test4(void)
{
  T tree;
  const int size = 10;
  int vals[size];
  GetValues(vals, size);
  const char *test = "Test4 - random insert/remove all";

  std::cout << "\n====================== " << test << " ======================\n";
  std::cout << ReadableType(typeid(T).name()) << std::endl;
  try
  {
    for (int i = 0; i < size; i++)
      tree.insert(vals[i]);
    
      // remove two lines
    PrintBST(tree);
    std::cout << "\n====================== " << test << " ======================\n";
    
    std::cout << "remove all and then some:\n";

    for (int i = 0; i < size + 2; i++)
    {
      tree.remove(i);
      PrintBST(tree);
      std::cout << "\n====================== " << test << " ======================\n";
    }

    std::cout << "height: " << tree.height() << std::endl;
    std::cout << " nodes: " << tree.size() << std::endl;
    if (tree.empty())
      std::cout << "tree is empty\n\n";
    else
      std::cout << "tree is NOT empty\n\n";

    PrintBST(tree);
  }
  catch (const BSTException &e)
  {
    std::cout << "Caught BSTException in " << test;
    int value = e.code();
    if (value == BSTException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...)
  {
    std::cout << "Caught unknown exception in " << test << std::endl;
  }
}

template <typename T>
void Test5(void)
{
  T tree;
  const int size = 10;
  int vals[size];
  GetValues(vals, size);
  const char *test = "Test5 - random insert/clear";

  std::cout << "\n====================== " << test << " ======================\n";
  std::cout << ReadableType(typeid(T).name()) << std::endl;
  try
  {
    for (int i = 0; i < size; i++)
      tree.insert(vals[i]);

    std::cout << "clear:\n";
    tree.clear();

    std::cout << "height: " << tree.height() << std::endl;
    std::cout << " nodes: " << tree.size() << std::endl;
    if (tree.empty())
      std::cout << "tree is empty\n\n";
    else
      std::cout << "tree is NOT empty\n\n";

    PrintBST(tree);
  }
  catch (const BSTException &e)
  {
    std::cout << "Caught BSTException in " << test;
    int value = e.code();
    if (value == BSTException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...)
  {
    std::cout << "Caught unknown exception in " << test << std::endl;
  }
}

template <typename T>
void Test6(void)
{
  T tree;
  const int size = 10;
  int vals[size];
  GetValues(vals, size);
  const char *test = "Test6 - random insert/find";

  std::cout << "\n====================== " << test << " ======================\n";
  std::cout << ReadableType(typeid(T).name()) << std::endl;
  try
  {
    for (int i = 0; i < size; i++)
      tree.insert(vals[i]);

    PrintBST(tree);
    int value;
    unsigned compares;
    bool found;

    value = 1;
    compares = 0;
    found = tree.find(value, compares);
    if (found)
      std::cout << "Value " << value << " found with " << compares << " compares\n";
    else
      std::cout << "Value " << value << " NOT found with " << compares << " compares\n";

    value = 3;
    compares = 0;
    found = tree.find(value, compares);
    if (found)
      std::cout << "Value " << value << " found with " << compares << " compares\n";
    else
      std::cout << "Value " << value << " NOT found with " << compares << " compares\n";

    value = 5;
    compares = 0;
    found = tree.find(value, compares);
    if (found)
      std::cout << "Value " << value << " found with " << compares << " compares\n";
    else
      std::cout << "Value " << value << " NOT found with " << compares << " compares\n";

    value = 50;
    compares = 0;
    found = tree.find(value, compares);
    if (found)
      std::cout << "Value " << value << " found with " << compares << " compares\n";
    else
      std::cout << "Value " << value << " NOT found with " << compares << " compares\n";
  }
  catch (const BSTException &e)
  {
    std::cout << "Caught BSTException in " << test;
    int value = e.code();
    if (value == BSTException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...)
  {
    std::cout << "Caught unknown exception in " << test << std::endl;
  }
}

template <typename T>
void Test7(void)
{
  T tree1, tree2;
  const int size = 10;
  int vals[size];
  GetValues(vals, size);
  const char *test = "Test7 - assignment";

  std::cout << "\n====================== " << test << " ======================\n";
  std::cout << ReadableType(typeid(T).name()) << std::endl;
  try
  {
    for (int i = 0; i < size; i++)
    {
      tree1.insert(vals[i]);
      tree2.insert(vals[i] * 3);
    }
    std::cout << "height: " << tree1.height() << std::endl;
    std::cout << " nodes: " << tree1.size() << std::endl;
    PrintBST(tree1);

    std::cout << "height: " << tree2.height() << std::endl;
    std::cout << " nodes: " << tree2.size() << std::endl;
    PrintBST(tree2);

    tree1 = tree2;

    std::cout << "tree 1 ------------------------------------------\n";
    PrintBST(tree1);
    std::cout << "tree 2------------------------------------------\n";
    PrintBST(tree2);
  }
  catch (const BSTException &e)
  {
    std::cout << "Caught BSTException in " << test;
    int value = e.code();
    if (value == BSTException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...)
  {
    std::cout << "Caught unknown exception in " << test << std::endl;
  }
}

template <typename T>
void Test8(void)
{
  T tree1;
  const int size = 10;
  int vals[size];
  GetValues(vals, size);
  const char *test = "Test8 - copy constructor";

  std::cout << "\n====================== " << test << " ======================\n";
  std::cout << ReadableType(typeid(T).name()) << std::endl;
  try
  {
    for (int i = 0; i < size; i++)
      tree1.insert(vals[i]);

    std::cout << "height: " << tree1.height() << std::endl;
    std::cout << " nodes: " << tree1.size() << std::endl;
    PrintBST(tree1);

    T tree2(tree1);
    std::cout << "height: " << tree2.height() << std::endl;
    std::cout << " nodes: " << tree2.size() << std::endl;

    std::cout << "tree 1------------------------------------------\n";
    PrintBST(tree1);
    std::cout << "tree 2------------------------------------------\n";
    PrintBST(tree2);
  }
  catch (const BSTException &e)
  {
    std::cout << "Caught BSTException in " << test;
    int value = e.code();
    if (value == BSTException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...)
  {
    std::cout << "Caught unknown exception in " << test << std::endl;
  }
}

template <typename T>
void TestIndex(void)
{
  T tree;

  if (!tree.ImplementedIndexing())
    return;

  int vals[] = {8, 6, 7, 5, 3, 0, 9};
  const int size = static_cast<int>(sizeof(vals) / sizeof(*vals));
  const char *test = "TestIndex - random insert/subscript";

  std::cout << "\n====================== " << test << " ======================\n";
  std::cout << ReadableType(typeid(T).name()) << std::endl;
  try
  {
    for (int i = 0; i < size; i++)
    {
      tree.insert(vals[i]);
      //std::cout << "============================\n";
      //PrintBST(tree);     
    }
    std::cout << "height: " << tree.height() << std::endl;
    std::cout << " nodes: " << tree.size() << std::endl;
    if (tree.empty())
      std::cout << "tree is empty\n\n";
    else
      std::cout << "tree is NOT empty\n\n";

    PrintBST(tree);
    for (int i = 0; i < size; i++)
      std::cout << "Index " << i << ": " << tree[static_cast<int>(i)]->data << std::endl;

  }
  catch (const BSTException &e)
  {
    std::cout << "Caught BSTException in " << test;
    int value = e.code();
    if (value == BSTException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...)
  {
    std::cout << "Caught unknown exception in " << test << std::endl;
  }
}


void AVLStress(void)
{
  const char *test = "AVLStress";
  std::cout << "\n====================== " << test << " ======================\n";

  int *ia = 0;
  try
  {
    AVLTree tree;

    int size = 10000;

    ia = new int[size];
    for (int i = 0; i < size; i++)
      ia[i] = i;

    Shuffle(ia, size, 1);
    Print(ia, size);

    for (int i = 0; i < size; i++)
    {
      tree.insert(ia[i]);
      PrintInfo(tree);
      //PrintBST(tree);
    }

      // Stress indexing
    if (tree.ImplementedIndexing())
    {
      int sum = 0;
      for (int j = 0; j < 1000; j++)
        for (int i = size - 1; i > size - 1000; i--)
          sum += tree[i]->data;
      std::cout << "Sum is " << sum << std::endl;
    }

    PrintInfo(tree);
    //PrintBST(tree);

    Shuffle(ia, size, 1);
    for (int i = 0; i < size - 10; i++)
    {
      tree.remove(ia[i]);
      PrintInfo(tree);
    }
    PrintInfo(tree);
    PrintBST(tree);

    if (tree.ImplementedIndexing())
      for (unsigned i = 0; i < tree.size(); i++)
        std::cout << "Index " << i << ": " << tree[static_cast<int>(i)]->data << std::endl;

  }
  catch(const BSTException& e)
  {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cout << "Unknown exception." << std::endl;
  }
  delete [] ia;
}

void AVLStressSmall(void)
{
  const char *test = "AVLStressSmall";
  std::cout << "\n====================== " << test << " ======================\n";

  int *ia = 0;
  try
  {
    AVLTree tree;
    int correct_nums[] = {1, 15, 22, 20, 12, 3, 0, 19, 18, 17, 8, 10, 9, 24, 6, 11, 4, 21, 7, 14, 13, 23, 5, 2, 16};
    int size = 25;
    ia = new int[size];
    for (int i = 0; i < size; i++)
      ia[i] = correct_nums[i];

    //Shuffle(ia, size, 1);
    Print(ia, size);

    for (int i = 0; i < size; i++)
    {
      tree.insert(ia[i]);
      //PrintInfo(tree);
      std::cout << "Insert item #" << i << ":" << ia[i] << " =========================================\n";
      PrintBST(tree);
    }

    PrintInfo(tree);
    //PrintBST(tree);

    Shuffle(ia, size, 1);
    for (int i = 0; i < size - 10; i++)
    {
      tree.remove(ia[i]);
      std::cout << "Remove item #" << i << ":" << ia[i] << " =========================================\n";
      PrintBST(tree);
    }
    PrintInfo(tree);
    PrintBST(tree);

    if (tree.ImplementedIndexing())
      for (unsigned i = 0; i < tree.size(); i++)
        std::cout << "Index " << i << ": " << tree[static_cast<int>(i)]->data << std::endl;

  }
  catch(const BSTException& e)
  {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cout << "Unknown exception." << std::endl;
  }
  delete [] ia;
}

//***********************************************************************
//***********************************************************************
//***********************************************************************

typedef void (*TestFn)(void);

#define WATCHDOGx
#if defined(_MSC_VER) && defined(WATCHDOG)

#ifdef _MSC_VER
#include <process.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#endif

static bool Completed = false;

unsigned __stdcall ThreadTest(void *fn)
{
  Completed = false;

  clock_t start, end;
  try
  {
    TestFn testFn = reinterpret_cast<TestFn>(fn);
    start = clock();
    testFn();
    end = clock();
    Completed = true;
  }
  catch(...)
  {
    printf("Unexpected exception thrown in ThreadTest.\n");
  }

  return 0;
}

void ExecuteTest(TestFn fn, int maxwait = 1000, int safewait = 1000)
{
  HANDLE thread;
  unsigned threadID;

  thread = (HANDLE) _beginthreadex(NULL, 0, &ThreadTest, fn, 0, &threadID);

  clock_t start = clock();
  WaitForSingleObject(thread, maxwait);
  clock_t end = clock();
  CloseHandle(thread);

  if (!Completed)
    printf("\n********** Test test took too long to complete (over %i ms). **********\n", maxwait);
  else if (end - start > safewait)
    printf("\n********** Test took %i ms. (Inefficient) **********\n", end - start);
  else 
  {
    //printf("\nTest completed within efficient time limit. (%i ms)\n", safewait);
    //printf("Actual time: %i ms\n", end - start);
  }

  //printf("\n");
}
//***********************************************************************
//***********************************************************************
//***********************************************************************

#else // WATCHDOG

void ExecuteTest(TestFn fn, int maxwait = 1000, int safewait = 1000)
{
  if (maxwait + safewait > 0)
    fn();
}

#endif


int main(int argc, char **argv)
{

  size_t test_num = 0;
  if (argc > 1)
    test_num = static_cast<size_t>(std::atoi(argv[1]));

  struct TimedTest
  {
    void (*test)(void);
    int maxwait;
    int safewait;
  };
  TimedTest Tests[] = {{Test1<BSTree>,       1000,  500}, //  1 random insert
                       {Test2<BSTree>,       1000,  500}, //  2 sorted insert
                       {Test3<BSTree>,       1000,  500}, //  3 random insert/remove some
                       {Test4<BSTree>,       1000,  500}, //  4 random insert/remove all
                       {Test5<BSTree>,       1000,  500}, //  5 random insert/clear
                       {Test6<BSTree>,       1000,  500}, //  6 random insert/find

                       {Test1<AVLTree>,      1000,  500}, //  7 random insert
                       {Test2<AVLTree>,      1000,  500}, //  8 sorted insert
                       {Test3<AVLTree>,      1000,  500}, //  9 random insert/remove some
                       {Test4<AVLTree>,      1000,  500}, // 10 random insert/remove all
                       {Test5<AVLTree>,      1000,  500}, // 11 random insert/clear
                       {Test6<AVLTree>,      1000,  500}, // 12 random insert/find

                       {Test7<BSTree>,       1000,  500}, // 13 assignment
                       {Test8<BSTree>,       1000,  500}, // 14 copy constructor

                       {Test7<AVLTree>,      1000,  500}, // 15 assignment
                       {Test8<AVLTree>,      1000,  500}, // 16 copy constructor

                       {TestIndex<BSTree>,   1000,  500}, // 17 random insert/select
                       {TestIndex<AVLTree>,  1000,  500}, // 18 random insert/select
                       {AVLStress,          10000, 3000}, // 19 stress avl only
                       {AVLStressSmall,     10000, 3000}, // 20 stress avl only
                      };

    SHOW_COUNTS = BSTree::ImplementedIndexing();
  
  size_t num = sizeof(Tests) / sizeof(*Tests);
  if (test_num == 0)
  {
    for (size_t i = 0; i < num; i++)
      ExecuteTest(Tests[i].test, Tests[i].maxwait, Tests[i].safewait);
  }
  else if (test_num > 0 && test_num <= num)
  {
    ExecuteTest(Tests[test_num - 1].test, Tests[test_num - 1].maxwait, Tests[test_num - 1].safewait);
  }

  return 0;
}
