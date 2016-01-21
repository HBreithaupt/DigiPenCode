/*****************************************************************************/
/*!
\file ALGraph.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS280
\par Assignment  6
\date  11/24/15

\brief
  Prototypes of Graph implementation.

*/
/*****************************************************************************/



//---------------------------------------------------------------------------
#ifndef ALGRAPH_H
#define ALGRAPH_H
//---------------------------------------------------------------------------
#include <vector>         // vector
#include <list>           // list
#include <algorithm>      // sort4
#include <queue>          // std::priority_queue

/// dijkstra results
struct DijkstraInfo
{
  unsigned cost; ///< cost to get to this node from starting node
  std::vector<unsigned> path; ///< path to get here
};


/// node information used in adjacency list
struct AdjacencyInfo
{
  unsigned id; ///< id of this node
  unsigned weight; ///< weight of the path
  AdjacencyInfo(unsigned id, unsigned weight); ///< constructor
};

  /// used to compare adjacency info structs for sorting
bool operator<(const AdjacencyInfo &lhs, const AdjacencyInfo& rhs);

  /// used to compare adjacency info structs for sorting
bool operator>(const AdjacencyInfo &lhs, const AdjacencyInfo &rhs);

  /// communicat with driver
typedef std::vector<std::vector<AdjacencyInfo> > ALIST;

  /// grapgh object
class ALGraph
{
  public:
      /// definition of inifinty fo robject
    const unsigned INFINITY_ = static_cast<unsigned>(-1);

      /// traversal method for extra credit
    enum TRAVERSAL_METHOD {DEPTH_FIRST, BREADTH_FIRST};

      /// constructor
    ALGraph(unsigned size);

      /// add a directed edge between two nodes
    void AddDEdge(unsigned source, unsigned destination, unsigned weight);

      /// add undirected edge between nodes
    void AddUEdge(unsigned node1, unsigned node2, unsigned weight);

      /// search method (extra credit)
    std::vector<unsigned> SearchFrom(unsigned start_node, TRAVERSAL_METHOD method) const;

      /// dijkstra method from specific starting node
    std::vector<DijkstraInfo> Dijkstra(unsigned start_node) const;

      /// get adjacency list for the graph
    ALIST GetAList() const;

      /// implmeneted extra credti
    static bool ImplementedSearches();

  private:

      /// adjacency list of the graph
    std::vector< std::list<AdjacencyInfo> > graph;
};

#endif
