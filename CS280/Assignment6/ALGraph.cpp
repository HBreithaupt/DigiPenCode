/*****************************************************************************/
/*!
\file ALGraph.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS280
\par Assignment 6
\date 11/24/15

\brief
  Implementation of using Dijkstra's algorithm on a graph.

  Functions Include:
    - Constructor
    - Destructor (compiler generated one is used)
    - operator </> comparison for sorting
    - AddDEdge add directed edge between two nodes
    - AddUEdge add undirected edge between two nodes
    - SearchFrom searching the graph (not implemented)
    - Dijkstra dijkstra algorithm
    - GetAList get adjacency matrix of the graph for the driver
    - ImplmenetedSearches not implemented

Hours spent on assignment: 4

Specific portions that gave you the most trouble:
- being able to use the STL made this really easy
- hardest thing was implementatin the algorithm but with the pseudo code
  and pictures provided made it easier to translate to code
*/
/*****************************************************************************/


#include "ALGraph.h"

/*****************************************************************************/
/*!

\brief
  Compares to AdjacencyInfo node for sorting

\param lhs
  left hand Node

\param rhs
  right hand ndoe

\return
  True/False
*/
/*****************************************************************************/
bool operator<(const AdjacencyInfo &lhs, const AdjacencyInfo& rhs)
{
    // return true if left hand weight < right hand weight
  if(lhs.weight < rhs.weight)
    return true;

    // if weights are the same go by value of the id
  if(lhs.weight == rhs.weight)
  {
    if(lhs.id < rhs.id)
    return true;
  }

    // return false other wise
    // lhs > rhs
  return false;
}

/*****************************************************************************/
/*!

\brief
  compare AdjacencyInfo nodes for sorting (calls operator<)

\param lhs
  left hand node

\param rhs
  right hand node

\return
  True/False
*/
/*****************************************************************************/
bool operator>(const AdjacencyInfo &lhs, const AdjacencyInfo &rhs)
{

  return !(lhs < rhs);
}

/*****************************************************************************/
/*!

\brief
  Constructor for an AdjacencyInfo node

\param id
  Id of the node being constructed

\param weight
  weight to get to this node from another node.

*/
/*****************************************************************************/
AdjacencyInfo::AdjacencyInfo(unsigned id, unsigned weight) : id(id), weight(weight)
{

}

/*****************************************************************************/
/*!

\brief
  Constructor for ALGraph

\param size
  How many nodes will be in the graph

*/
/*****************************************************************************/
ALGraph::ALGraph(unsigned size)
{
    // expand rows to number of nodes in the graph
    // ids equal row + 1 and weights dont matter here
  graph.resize(size);
}

/*****************************************************************************/
/*!

\brief
  Addsa directed edge between two nodes.

\param source
  Starting node

\param destination
  destination node

\param weight
  Cost to get from source -> destination

*/
/*****************************************************************************/
void ALGraph::AddDEdge(unsigned source, unsigned destination, unsigned weight)
{
    // add neighbor information into the Adjancency list
    // not keeping it sorted here
  graph[source - 1].push_back(AdjacencyInfo(destination, weight));
}

/*****************************************************************************/
/*!

\brief
  Adds undirected node between two nodes

\param node1
  first node

\param node2
  second node

\param weight
  cost to get from node1 -> node 2 & node2 -> node 1

*/
/*****************************************************************************/
void ALGraph::AddUEdge(unsigned node1, unsigned node2, unsigned weight)
{
    // just call add directed edge twice to add both edges
  AddDEdge(node1, node2, weight);
  AddDEdge(node2, node1, weight);
}

/*****************************************************************************/
/*!

\brief
  Searches the graph from a certain node.

\param start_node
  Starting node of the search

\param method
  method of searching

\return
  Vector information from searching
*/
/*****************************************************************************/
std::vector<unsigned> ALGraph::SearchFrom(unsigned, TRAVERSAL_METHOD) const
{
  return std::vector<unsigned>();
}

/*****************************************************************************/
/*!

\brief
  Performs Dijkstra's algorithm on the graph to find shortest path from
  a starting node to every other possible node.

\param start_node
  What node we are starting at.

\return
  Results of Dijkstra algorithm.
*/
/*****************************************************************************/
std::vector<DijkstraInfo> ALGraph::Dijkstra(unsigned start_node) const
{

    // make priority queue to store edges from smallest to largest
  std::greater<AdjacencyInfo> cmp;
  std::priority_queue< AdjacencyInfo,
                       std::vector<AdjacencyInfo>,
                       std::greater<AdjacencyInfo> > edges (cmp);

    // set up vector to store results
  std::vector<DijkstraInfo> dijkstra (graph.size());

    // vector to store when a node has been evaluated
    // (pulled out of the priority queue)
  std::vector<bool> evaluated (graph.size(), false);

    // initialize values to infinity for the path cost
    // to get to every other node
  for(unsigned i = 0; i < dijkstra.size(); ++i)
    dijkstra[i].cost = INFINITY_;

    // set initial value for the starting node
    // and flag as evaluated
  dijkstra[start_node - 1].path.push_back(start_node);
  dijkstra[start_node - 1].cost = 0;
  evaluated[start_node - 1] = true;

    // calculate initial conditions of the neighbors of start_node
  for(auto j : graph[start_node - 1])
  {
      //set cost of neighbors of start_node
      // and path to get to them
    unsigned neighbor = j.id;
    dijkstra[neighbor - 1].cost = j.weight;
    dijkstra[neighbor - 1].path.push_back(start_node);
    dijkstra[neighbor - 1].path.push_back(neighbor);

      // now push neighbors into prority queue
    edges.push(j);
  }

  while(!edges.empty())
  {
      // get top node from the PQ and remove it
    AdjacencyInfo top = edges.top();
    edges.pop();

      // if its already bene evaluated skip it and move to the next one
      // else mark it as evaluated
    if(evaluated[top.id - 1])
      continue;
    else
      evaluated[top.id - 1] = true;

      // check every neighbor of the node popped form the priority queue
    for(auto j : graph[top.id - 1])
    {
      unsigned neighbor = j.id;
      unsigned new_cost = dijkstra[top.id - 1].cost + j.weight;


      if(new_cost < dijkstra[neighbor - 1].cost)
      {
        dijkstra[neighbor -1].cost = new_cost;
        dijkstra[neighbor - 1].path = dijkstra[top.id - 1].path;
        dijkstra[neighbor - 1].path.push_back(neighbor);
      }

      edges.push(AdjacencyInfo(neighbor, new_cost));
    }
  }

  return dijkstra;
}

/*****************************************************************************/
/*!

\brief
  Gets adjacency matrix for the graph.

\return
  Adjacency matrix of the graph.
*/
/*****************************************************************************/
ALIST ALGraph::GetAList() const
{

      // copy adjancecncy list to adjacency matrix
    ALIST GraphMatrix;
    GraphMatrix.resize(graph.size());
    for(unsigned i = 0; i < graph.size(); i++)
    {
      for(auto j : graph[i])
      {
        GraphMatrix[i].push_back(j);
      }
    }

      // sort data
    for(unsigned i = 0; i < GraphMatrix.size(); ++i)
    {
      std::sort(GraphMatrix[i].begin(), GraphMatrix[i].end());
    }


    return GraphMatrix;
  //return graph;
}

/*****************************************************************************/
/*!

\brief
  Whether extra credit is implemented

\return
  True/False
*/
/*****************************************************************************/
bool ALGraph::ImplementedSearches()
{
  return false;
}
