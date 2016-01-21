////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // ostream

namespace CS170
{

  class List
  {
    public:
    
      // default constructor
    List();
    
      // copy constructor
    List(const List& original);
    
      // non-default constructor
    List(const int *array, int length);
    
      // destructor
    ~List();
        
        
      //   push_front, adds the item to the front of the list
    void push_front(int value);
      
      //   push_back, adds the item to the end of the list
    void push_back(int value);
      
      //   pop_front, removes the first item in the list
    int pop_front();
      
      //   size, returns the number of items in the list
    int size() const;
      
      //   empty, returns true if empty, else false
    int empty() const;
      
      //   clear, clears the list (removes all of the nodes)
    void clear();
      
      
      //   operator=
    List& operator=(const List& rhs);
    
      //   operator+=
    List& operator+=(const List& rhs);
      
      //   operator+
    List operator+(const List& rhs) const;

      // read only
    int operator[](int index) const;
    
      // write-able
    int& operator[](int index);
    

      // Output operator for printing lists (<<)
    friend std::ostream & operator<<(std::ostream & os, const List &list);

      // Returns the number of Lists that have been created
    static int list_count();

      // Returns the number of Nodes that are still alive
    static int node_count();

    private:

        // used to build a linked list of integers
      struct Node
      {
        Node(int value);              // constructor
        ~Node();                // destructor
        Node *next;             // pointer to the next Node
        int data;               // the actual data in the node
        static int nodes_alive; // count of nodes still allocated
      };

      Node *head_; // pointer to the head of the list
      Node *tail_; // pointer to the last node
      int size_;   // number of items on the list

      static int list_count_;       // number of Lists created
      List::Node* new_node(int data) const; // allocate node, initialize data/next
  };

} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
