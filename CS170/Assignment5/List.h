/*****************************************************************************/
/*!
\file List.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Assignment 5
\date   3-22-15

\brief
  Prototypes for List.cpp.

*/
/*****************************************************************************/

///////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
///////////////////////////////////////////////////////////////////////////////

#include <iostream> /* ostream, endl */

namespace CS170
{
  template <typename T> class List;

  template <typename T>
  std::ostream & operator<<(std::ostream & os, const List<T> &list);

  template <typename T>
  class List
  {
    public:
        // Default constructor
      List();

        // Copy contructor for constructing a list from an existing list
      List(const List &list);

        // Contruct a list from a T array
      List(const T *array, int size);

        // Destructor
      ~List();

      void push_front(const T& Value); // adds the item to the front of the list
      void push_back(const T& Value);  // adds the item to the end of the list
      void pop_front();                // removes the first item in the list
      T front() const;                 // retrieves the first item in the list
      int size() const;                // returns the number of items in the list
      bool empty() const;              // true if empty, else false
      void clear();                    // clears the list

        // Overloaded assignment operator (=) for assigning one list to another
      List& operator=(const List &list);

        // Overloaded addition operator (+) for adding two lists
      List operator+(const List &list) const;

        // Overloaded addition/assignment (+=) for adding to a list "in place"
      List& operator+=(const List &list);

        // Overloaded subscript operators
      const T& operator[](int index) const;
      T& operator[](int index);

        // Output operator for printing lists (<<)
      friend std::ostream & operator<< <T> (std::ostream & os, const List &list);

        // Returns the number of Nodes that have been created
     static int node_count();

    private:
        // Used to build the linked list
      struct Node
      {
        Node(T value);          // constructor
        ~Node();            // destructor
        Node *next;             // pointer to the next Node
        T data;                 // the actual data in the node
        static int nodes_alive; // number of Nodes created
      };

      Node *head_; // pointer to the head of the list
      Node *tail_; // pointer to the last node
      int size_;   // number of items on the list

        // All nodes are created in this method
      Node *new_node(const T& data) const;
  };

} // namespace CS170

#include "List.cpp"

#endif
////////////////////////////////////////////////////////////////////////////////

