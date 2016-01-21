#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "ALGraph.h"
#include "PRNG.h"

bool RunDijkstra = true;
bool DumpDijkstra = true;
bool DumpList = true;
bool MakeGVizFile = false;

enum GType { gtUndirected, gtDirected };
void MakeGraphvizFile(const char *filename, GType type, const ALIST& alist)
{
  if (!MakeGVizFile)
    return;

  std::ofstream viz(filename);
  if (!viz.is_open())
  {
    std::cout << "Couldn't open " << filename << std::endl;
    return;
  }

  const char *edge;
  const char *gtype;
  if (type == gtUndirected)
  {
    edge = "--";
    gtype = "strict graph";
  }
  else
  {
    edge = "->";
    gtype = "digraph";
  }

  viz << gtype << " {\n";
    ALIST::const_iterator it = alist.begin();
    int count = 1;
    while (it != alist.end())
    {
      const std::vector<AdjacencyInfo> list = *it;
      for (std::vector<AdjacencyInfo>::const_iterator it2 = list.begin(); it2 != list.end(); ++it2)
      {
        AdjacencyInfo info = *it2;
        viz << std::setw(6) << count << " " << edge << " " << std::setw(3) << info.id;
        viz << " [ label = \"" << info.weight << "\"];\n";
      }
      ++it;
      count++;
    }
  viz << "}\n";
}

int RandomInt(int low, int high)
{
  return Digipen::Utils::Random(low, high);
}

template <typename T>
void SwapInt(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
}

template <typename T>
void Shuffle(T *array, unsigned count)
{
  for (unsigned i = 0; i < count; i++)
  {
    int r = RandomInt(0, static_cast<int>(count) - 1);
    SwapInt(array[i], array[r]);
  }
}

template <typename T>
void PrintArray(T *array, int count)
{
  for (int i = 0; i < count; i++)
    std::cout << array[i] << "  ";
  std::cout << std::endl;
}

void DumpDijkstraInfo(const std::vector<DijkstraInfo>& pi, unsigned start)
{
  //unsigned total = 0;
  //unsigned hops = 0;
  std::vector<DijkstraInfo>::const_iterator it = pi.begin();
  int count = 1;
  std::cout << "Cost to reach all nodes from node " << start << ":\n";
  std::cout << "------------------------------------\n";
  while (it != pi.end())
  {
    std::cout << "Node: " << std::setw(2) << count++ << ": ";
    DijkstraInfo pi = *it;
    std::cout << " Cost: " << std::setw(3) << static_cast<int>(pi.cost); // account for -1
    std::cout << "  Path: ";
    for (int unsigned i = 0; i < pi.path.size(); i++)
      std::cout << std::setw(2) << pi.path[i] << " ";
    std::cout << std::endl;
    //total += pi.cost;
    //hops += static_cast<unsigned>(pi.path.size() - 1);
    ++it;
  }
  //std::cout << "Total cost: " << total << ", total hops: " << hops << std::endl;
}

void DumpAList(const ALIST& alist)
{
  std::cout << "Adjacency list:\n-------------------------------\n";
  ALIST::const_iterator it = alist.begin();
  int count = 1;
  while (it != alist.end())
  {
    std::cout << "ID: [" << std::setw(2) << count++ << "]";
    const std::vector<AdjacencyInfo> list = *it;
    for (std::vector<AdjacencyInfo>::const_iterator it2 = list.begin(); it2 != list.end(); ++it2)
    {
      AdjacencyInfo info = *it2;
      std::cout << " -- ";
      std::cout << std::setw(3) << info.weight << " --> ";
      std::cout << "[" << std::setw(2) <<info.id << "]";
    }
    ++it;
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void DumpSearch(const std::vector<unsigned>& list, unsigned start, ALGraph::TRAVERSAL_METHOD method, bool as_char = true)
{
  std::vector<unsigned>::const_iterator it = list.begin();
  if (method == ALGraph::BREADTH_FIRST)
    std::cout << "Breadth first, greatest first, from node " << start << ":\n";
  else
    std::cout << "Depth first, greatest first, from node " << start << ":\n";

  while (it != list.end())
  {
    if (as_char)
      std::cout << char(*it + 64) << "  ";
    else
      std::cout << *it << "  ";

    ++it;
  }
  std::cout << std::endl;
}

void TestDijkstra0(unsigned start, bool dump_alist = true, bool dump_paths = true)
{
  const char *fn = "TestDijkstra0";
  std::cout << "\n****************************** " << fn << " ******************************\n";
  try
  {
    ALGraph g(6);

    g.AddUEdge(1, 2, 13);
    g.AddUEdge(1, 4, 29);
    g.AddUEdge(1, 6, 11);
    g.AddUEdge(2, 3, 20);
    g.AddUEdge(2, 4, 12);
    g.AddUEdge(3, 4, 5);
    g.AddUEdge(3, 5, 4);
    g.AddUEdge(4, 5, 28);
    g.AddUEdge(4, 6, 15);
    g.AddUEdge(5, 6, 24);

    if (dump_alist)
    {
      ALIST alist = g.GetAList();
      DumpAList(alist);
      MakeGraphvizFile("Dijkstra0-gviz.txt", gtUndirected, alist);
    }

    if (RunDijkstra)
    {
      std::vector<DijkstraInfo> pi = g.Dijkstra(start);
      if (dump_paths)
        DumpDijkstraInfo(pi, start);
    }
  }
  catch (...)
  {
    std::cout << "***** Unknown exception caught in " << fn << " *****\n";
  }

}

void TestDijkstra1(unsigned start, bool dump_alist = true, bool dump_paths = true)
{
  const char *fn = "TestDijkstra1";
  std::cout << "\n****************************** " << fn << " ******************************\n";
  try
  {
    ALGraph g(6);

    g.AddUEdge(1, 2, 8);
    g.AddUEdge(1, 3, 16);
    g.AddUEdge(1, 5, 13);
    g.AddUEdge(2, 3, 7);
    g.AddUEdge(2, 4, 17);
    g.AddUEdge(2, 5, 11);
    g.AddUEdge(2, 6, 10);
    g.AddUEdge(3, 4, 5);
    g.AddUEdge(4, 5, 14);
    g.AddUEdge(4, 6, 6);

    if (dump_alist)
    {
      ALIST alist = g.GetAList();
      DumpAList(alist);
      MakeGraphvizFile("Dijkstra1-gviz.txt", gtUndirected, alist);
    }

    if (RunDijkstra)
    {
      std::vector<DijkstraInfo> pi = g.Dijkstra(start);
      if (dump_paths)
        DumpDijkstraInfo(pi, start);
    }
  }
  catch (...)
  {
    std::cout << "***** Unknown exception caught in " << fn << " *****\n";
  }
}

void TestDijkstra4(unsigned start, bool dump_alist = true, bool dump_paths = true)
{
  const char *fn = "TestDijkstra4";
  std::cout << "\n****************************** " << fn << " ******************************\n";
  try
  {
    ALGraph g(16);

    g.AddDEdge(1, 2, 1);
    g.AddDEdge(1, 5, 3);
    g.AddDEdge(2, 3, 2);
    g.AddDEdge(2, 5, 1);
    g.AddDEdge(3, 4, 3);

    g.AddDEdge(3, 7, 5);
    g.AddDEdge(4, 8, 2);
    g.AddDEdge(5, 6, 3);
    g.AddDEdge(5, 9, 2);
    g.AddDEdge(5, 10, 1);

    g.AddDEdge(6, 2, 6);
    g.AddDEdge(6, 10, 1);
    g.AddDEdge(7, 2, 2);
    g.AddDEdge(7, 8, 1);
    g.AddDEdge(7, 6, 1);

    g.AddDEdge(7, 10, 1);
    g.AddDEdge(8, 3, 1);
    g.AddDEdge(9, 13, 4);
    g.AddDEdge(9, 14, 5);
    g.AddDEdge(10, 9, 2);

    g.AddDEdge(10, 14, 1);
    g.AddDEdge(11, 7, 3);
    g.AddDEdge(11, 10, 2);
    g.AddDEdge(11, 12, 2);
    g.AddDEdge(12, 7, 2);

    g.AddDEdge(12, 8, 3);
    g.AddDEdge(12, 16, 1);
    g.AddDEdge(14, 13, 2);
    g.AddDEdge(14, 15, 1);
    g.AddDEdge(15, 10, 5);

    g.AddDEdge(15, 11, 2);
    g.AddDEdge(16, 11, 3);
    g.AddDEdge(16, 15, 2);

    if (dump_alist)
    {
      ALIST alist = g.GetAList();
      DumpAList(alist);
      MakeGraphvizFile("Dijkstra4-gviz.txt", gtDirected, alist);
    }

    if (RunDijkstra)
    {
      std::vector<DijkstraInfo> pi = g.Dijkstra(start);
      if (dump_paths)
        DumpDijkstraInfo(pi, start);
    }
  }
  catch (...)
  {
    std::cout << "***** Unknown exception caught in " << fn << " *****\n";
  }
}

void TestDijkstra4a(unsigned start, bool dump_alist = true, bool dump_paths = true)
{
  const char *fn = "TestDijkstra4a";
  std::cout << "\n****************************** " << fn << " ******************************\n";
  try
  {
    ALGraph g(16);

    g.AddDEdge(1, 2, 11);
    g.AddDEdge(1, 5, 13);
    g.AddDEdge(2, 3, 21);
    g.AddDEdge(2, 5, 31);
    g.AddDEdge(3, 4, 29);

    g.AddDEdge(3, 7, 15);
    g.AddDEdge(4, 8, 12);
    g.AddDEdge(5, 6, 13);
    g.AddDEdge(5, 9, 23);
    g.AddDEdge(5, 10, 29);

    g.AddDEdge(6, 2, 16);
    g.AddDEdge(6, 10, 31);
    g.AddDEdge(7, 2, 26);
    g.AddDEdge(7, 8, 10);
    g.AddDEdge(7, 6, 12);

    g.AddDEdge(7, 10, 14);
    g.AddDEdge(8, 3, 31);
    g.AddDEdge(9, 13, 45);
    g.AddDEdge(9, 14, 15);
    g.AddDEdge(10, 9, 2);

    g.AddDEdge(10, 14, 51);
    g.AddDEdge(11, 7, 33);
    g.AddDEdge(11, 10, 22);
    g.AddDEdge(11, 12, 12);
    g.AddDEdge(12, 7, 27);

    g.AddDEdge(12, 8, 13);
    g.AddDEdge(12, 16, 41);
    g.AddDEdge(14, 13, 28);
    g.AddDEdge(14, 15, 19);
    g.AddDEdge(15, 10, 35);

    g.AddDEdge(15, 11, 23);
    g.AddDEdge(16, 11, 33);
    g.AddDEdge(16, 15, 22);

    if (dump_alist)
    {
      ALIST alist = g.GetAList();
      DumpAList(alist);
      MakeGraphvizFile("Dijkstra4a-gviz.txt", gtDirected, alist);
    }

    if (RunDijkstra)
    {
      std::vector<DijkstraInfo> pi = g.Dijkstra(start);
      if (dump_paths)
        DumpDijkstraInfo(pi, start);
    }
  }
  catch (...)
  {
    std::cout << "***** Unknown exception caught in " << fn << " *****\n";
  }
}

void TestDijkstra5(unsigned start, bool dump_alist = true, bool dump_paths = true)
{
  const char *fn = "TestDijkstra5";
  std::cout << "\n****************************** " << fn << " ******************************\n";
  try
  {
    ALGraph g(9);

    g.AddUEdge(1, 2, 73);
    g.AddUEdge(1, 5, 76);
    g.AddUEdge(1, 4, 57);
    g.AddUEdge(2, 3, 95);
    g.AddUEdge(2, 7, 87);
    g.AddUEdge(2, 4, 26);
    g.AddUEdge(3, 6, 92);
    g.AddUEdge(3, 7, 127);
    g.AddUEdge(4, 7, 82);
    g.AddUEdge(4, 5, 74);
    g.AddUEdge(5, 9, 128);
    g.AddUEdge(6, 7, 148);
    g.AddUEdge(7, 8, 128);
    g.AddUEdge(7, 9, 83);
    g.AddUEdge(6, 8, 87);

    if (dump_alist)
    {
      ALIST alist = g.GetAList();
      DumpAList(alist);
      MakeGraphvizFile("Dijkstra5-gviz.txt", gtUndirected, alist);
    }

    if (RunDijkstra)
    {
      std::vector<DijkstraInfo> pi = g.Dijkstra(start);
      if (dump_paths)
        DumpDijkstraInfo(pi, start);
    }
  }
  catch (...)
  {
    std::cout << "***** Unknown exception caught in " << fn << " *****\n";
  }
}

void TestDijkstra9(unsigned start, bool dump_alist = true, bool dump_paths = true)
{
  const char *fn = "TestDijkstra9";
  std::cout << "\n****************************** " << fn << " ******************************\n";
  try
  {
    ALGraph g(10);

    g.AddUEdge(1, 2, 33);
    g.AddUEdge(1, 3, 10);
    g.AddUEdge(1, 4, 56);
    g.AddUEdge(2, 4, 13);
    g.AddUEdge(2, 5, 21);
    g.AddUEdge(3, 4, 23);
    g.AddUEdge(3, 6, 24);
    g.AddUEdge(3, 7, 65);
    g.AddUEdge(4, 5, 51);
    g.AddUEdge(4, 7, 20);
    g.AddUEdge(5, 7, 17);
    g.AddUEdge(5, 8, 35);
    g.AddUEdge(6, 7, 40);
    g.AddUEdge(6, 9, 72);
    g.AddUEdge(7, 8, 99);
    g.AddUEdge(7, 9, 45);
    g.AddUEdge(7, 10, 42);
    g.AddUEdge(8, 10, 38);
    g.AddUEdge(9, 10, 83);

    if (dump_alist)
    {
      ALIST alist = g.GetAList();
      DumpAList(alist);
      MakeGraphvizFile("Dijkstra9-gviz.txt", gtUndirected, alist);
    }

    if (RunDijkstra)
    {
      std::vector<DijkstraInfo> pi = g.Dijkstra(start);
      if (dump_paths)
        DumpDijkstraInfo(pi, start);
    }
  }
  catch (...)
  {
    std::cout << "***** Unknown exception caught in " << fn << " *****\n";
  }
}

void TestDijkstra10(unsigned start, bool dump_alist = true, bool dump_paths = true)
{
  const char *fn = "TestDijkstra10";
  std::cout << "\n****************************** " << fn << " ******************************\n";
  try
  {
    ALGraph g(14);

    g.AddUEdge(1, 2, 70);
    g.AddUEdge(1, 5, 61);
    g.AddUEdge(2, 3, 31);
    g.AddUEdge(2, 4, 110);
    g.AddUEdge(3, 6, 70);
    g.AddUEdge(3, 8, 65);
    g.AddUEdge(4, 7, 30);
    g.AddUEdge(4, 8, 67);
    g.AddUEdge(5, 6, 88);
    g.AddUEdge(5, 10, 59);
    g.AddUEdge(6, 8, 100);
    g.AddUEdge(6, 10, 65);
    g.AddUEdge(7, 9, 74);
    g.AddUEdge(7, 11, 126);
    g.AddUEdge(7, 13, 105);
    g.AddUEdge(8, 10, 26);
    g.AddUEdge(8, 11, 12);
    g.AddUEdge(9, 13, 30);
    g.AddUEdge(10, 14, 140);
    g.AddUEdge(11, 12, 19);
    g.AddUEdge(12, 13, 39);
    g.AddUEdge(12, 14, 85);

    if (dump_alist)
    {
      ALIST alist = g.GetAList();
      DumpAList(alist);
      MakeGraphvizFile("Dijkstra10-gviz.txt", gtUndirected, alist);
    }

    if (RunDijkstra)
    {
      std::vector<DijkstraInfo> pi = g.Dijkstra(start);
      if (dump_paths)
        DumpDijkstraInfo(pi, start);
    }
  }
  catch (...)
  {
    std::cout << "***** Unknown exception caught in " << fn << " *****\n";
  }
}

void TestSearch1(unsigned start, bool dump_alist = true)
{
  const char *fn = "TestSearch1";
  std::cout << "\n****************************** " << fn << " ******************************\n";

  if (!ALGraph::ImplementedSearches())
    return;

  try
  {
    ALGraph g(8);

    g.AddDEdge(1, 2, 3);
    g.AddDEdge(1, 3, 9);
    g.AddDEdge(1, 4, 7);
    g.AddDEdge(2, 5, 6);
    g.AddDEdge(2, 6, 5);
    g.AddDEdge(4, 7, 4);
    g.AddDEdge(4, 8, 2);
    g.AddDEdge(6, 5, 8);
    g.AddDEdge(7, 1, 5);
    g.AddDEdge(7, 3, 1);
    g.AddDEdge(7, 6, 4);
    g.AddDEdge(8, 6, 8);

    if (dump_alist)
    {
      ALIST alist = g.GetAList();
      DumpAList(alist);
      MakeGraphvizFile("Search1-gviz.txt", gtDirected, alist);
    }

    std::vector<unsigned> list = g.SearchFrom(start, ALGraph::DEPTH_FIRST);
    DumpSearch(list, start, ALGraph::DEPTH_FIRST);

    std::vector<unsigned> list2 = g.SearchFrom(start, ALGraph::BREADTH_FIRST);
    DumpSearch(list2, start, ALGraph::BREADTH_FIRST);
  }
  catch (...)
  {
    std::cout << "***** Unknown exception caught in " << fn << " *****\n";
  }
}

void TestSearch2(unsigned start, bool dump_alist = true)
{
  const char *fn = "TestSearch2";
  std::cout << "\n****************************** " << fn << " ******************************\n";

  if (!ALGraph::ImplementedSearches())
    return;

  try
  {
    ALGraph g(16); // same as Dijkstra4

    g.AddDEdge(1, 2, 1);
    g.AddDEdge(1, 5, 3);
    g.AddDEdge(2, 3, 2);
    g.AddDEdge(2, 5, 1);
    g.AddDEdge(3, 4, 3);

    g.AddDEdge(3, 7, 5);
    g.AddDEdge(4, 8, 2);
    g.AddDEdge(5, 6, 3);
    g.AddDEdge(5, 9, 2);
    g.AddDEdge(5, 10, 1);

    g.AddDEdge(6, 2, 6);
    g.AddDEdge(6, 10, 1);
    g.AddDEdge(7, 2, 2);
    g.AddDEdge(7, 8, 1);
    g.AddDEdge(7, 6, 1);

    g.AddDEdge(7, 10, 1);
    g.AddDEdge(8, 3, 1);
    g.AddDEdge(9, 13, 4);
    g.AddDEdge(9, 14, 5);
    g.AddDEdge(10, 9, 2);

    g.AddDEdge(10, 14, 1);
    g.AddDEdge(11, 7, 3);
    g.AddDEdge(11, 10, 2);
    g.AddDEdge(11, 12, 2);
    g.AddDEdge(12, 7, 2);

    g.AddDEdge(12, 8, 3);
    g.AddDEdge(12, 16, 1);
    g.AddDEdge(14, 13, 2);
    g.AddDEdge(14, 15, 1);
    g.AddDEdge(15, 10, 5);

    g.AddDEdge(15, 11, 2);
    g.AddDEdge(16, 11, 3);
    g.AddDEdge(16, 15, 2);

    if (dump_alist)
    {
      ALIST alist = g.GetAList();
      DumpAList(alist);
      MakeGraphvizFile("Search2-gviz.txt", gtDirected, alist);
    }

    std::vector<unsigned> list = g.SearchFrom(start, ALGraph::DEPTH_FIRST);
    DumpSearch(list, start, ALGraph::DEPTH_FIRST, false);

    std::vector<unsigned> list2 = g.SearchFrom(start, ALGraph::BREADTH_FIRST);
    DumpSearch(list2, start, ALGraph::BREADTH_FIRST, false);
  }
  catch (...)
  {
    std::cout << "***** Unknown exception caught in " << fn << " *****\n";
  }
}

void TestAllDijkstra()
{
  for (unsigned i = 1; i <= 14; i++)
    TestDijkstra10(i, false, true);
}

void TestAllLists()
{
  TestDijkstra0(1, true, false);
  TestDijkstra1(1, true, false);
  TestDijkstra4(1, true, false);
  TestDijkstra4a(1, true, false);
  TestDijkstra5(1, true, false);
  TestDijkstra9(1, true, false);
  TestDijkstra10(1, true, false);
}

void TestAllSearch1()
{
  if (!ALGraph::ImplementedSearches())
    return;

  for (unsigned i = 1; i <= 8; i++)
    TestSearch1(i, false);
}

void TestAllSearch2()
{
  if (!ALGraph::ImplementedSearches())
    return;

  for (unsigned i = 1; i <= 16; i++)
    TestSearch2(i, false);
}

#include <time.h>
void TestBig(unsigned nodes, unsigned percentage)
{
  std::cout << "\n******************** Test Big ********************\n";
  Digipen::Utils::srand(1, 2);

  unsigned num_nodes = nodes, edges = 0;

  const int size = 99;
  unsigned *array = new unsigned[size];
  for (int i = 0; i < size; i++)
    array[i] = static_cast<unsigned>(i + 1);

  unsigned density = 100 / percentage;

#define DUMP_MAPx

  //std::cout << "Creating graph ...\n";
  //time_t start_create = clock();
  ALGraph g(num_nodes);
  for (unsigned i = 1; i <= num_nodes; i++)
  {
    Shuffle(array, size);
    for (unsigned j = 1; j <= num_nodes; j++)
    {
      unsigned random = static_cast<unsigned>(RandomInt(1, static_cast<int>(density)));
      if ( (random < 2) && (i != j) )
      {
        int index = RandomInt(0, size - 1);
				unsigned weight = array[index];
#ifdef DUMP_MAP
        std::cout << std::setw(2) << weight << " ";
#endif
        g.AddDEdge(i, j, weight);
        edges++;
      }
#ifdef DUMP_MAP
      else
        std::cout << std::setw(2) << -1 << " ";
#endif
    }
#ifdef DUMP_MAP
    std::cout << std::endl;
#endif
  }
  //time_t end_create = clock();

  std::cout << "Nodes: " << num_nodes << ", Edges: " << edges << ", Density: " << percentage << "%" << std::endl;
  ALIST alist = g.GetAList();

  if (DumpList)
    DumpAList(alist);

  std::stringstream ss;
  ss << "TestBig-" << nodes << "-" << percentage << "-gviz.txt";
  MakeGraphvizFile(ss.str().c_str(), gtDirected, alist);

  unsigned start_node = 1;
  //std::cout << "Searching graph ...\n";
  //time_t start_search = clock();
  if (RunDijkstra)
  {
    std::vector<DijkstraInfo> pi = g.Dijkstra(start_node);
    if(DumpDijkstra)
      DumpDijkstraInfo(pi, start_node);
  }
  //long create = (long)(end_create - start_create);
  //long search = (long)(end_search - start_search);
  //long total = create + search;
  //std::cout << "Create = " << create << " ms, ";
  //std::cout << "Search = " << search << " ms, ";
  //std::cout << "Total = " << total << " ms\n";
  delete [] array;
}

int main(int argc, char **argv)
{
  size_t test_num = 0, rund = 0;
  if (argc > 1)
    test_num = static_cast<size_t>(std::atoi(argv[1]));
  if (argc > 2)
    rund = static_cast<size_t>(std::atoi(argv[2]));

  //RunDijkstra = rund ? true : false;
  switch(test_num)
  {
    // ********** Adjaceny list tests **********
    case 1:
      TestAllLists();
      break;

    // ********** Dijkstra tests **********
    case 2:
      TestDijkstra0(1);
      break;
    case 3:
      TestDijkstra1(1);
      break;
    case 4:
      TestDijkstra4(1);
      break;
    case 5:
      TestDijkstra4a(1);
      break;
    case 6:
      TestDijkstra5(1);
      break;
    case 7:
      TestDijkstra9(1);
      break;
    case 8:
      TestDijkstra10(14);
      break;
    case 9:
      TestDijkstra10(1);
      break;
    case 10:
      TestAllDijkstra();
      break;

    // ********** Search tests **********
    case 11:
      TestSearch1(1);
      break;
    case 12:
      TestAllSearch1();
      break;
    case 13:
      TestSearch2(1);
      break;
    case 14:
      TestAllSearch2();
      break;

    // ********** Stress tests **********
    case 15:
      DumpDijkstra = true;
      DumpList = true;
      RunDijkstra = true;
      TestBig(10, 100);
      break;
    case 16:
      DumpDijkstra = true;
      DumpList = true;
      RunDijkstra = true;
      TestBig(30, 10);
      break;
    case 17:
      DumpDijkstra = true;
      DumpList = true;
      RunDijkstra = true;
      TestBig(99, 2);
      break;
    case 18:
      DumpDijkstra = false;
      DumpList = false;
      RunDijkstra = true;
      MakeGVizFile = false;
      TestBig(2000, 50);
      break;
  }

  return 0;
}
