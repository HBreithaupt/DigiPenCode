/*****************************************************************************/
/*!
\file    List.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Assignment #4
\date 3-17-2105

\brief
  Performs operations on a linked list with the the node struct encapsulated
  in the class.


Hours spent on assignment: 4

Specific portions that gave you the most trouble: 
  - Changing the return type of new_node to List::Node* to get it to work
*/
/*****************************************************************************/

#include <iostream> // ostream, endl
#include <iomanip>  // setw
#include "List.h"   // List class


namespace CS170
{
    // init list counter
  int List::list_count_ = 0;
  
    // init node counter
  int List::Node::nodes_alive = 0;
  
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  // Node methods
  // Constructor, destructor
  
  /***************************************************************************/
  /*!
  
  \brief
    Non-default constructor for Node.
  
  \param value
    Integer to assign to the container.
  
  */
  /***************************************************************************/
  List::Node::Node(int value)
  {
    // assign data
    data = value;
    
    // assign next pointer
    next = 0;
    
    // increment node counter
    List::Node::nodes_alive++;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Default destructor for Node.

  */
  /***************************************************************************/
  List::Node::~Node()
  {
    List::Node::nodes_alive--;
  }
  
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  // public methods in this order: 
  // Constructors (default, copy, non-defaults), destructor, operators, others
  
  /***************************************************************************/
  /*!
  
  \brief
    Default constructor for List.
  
  */
  /***************************************************************************/
  List::List()
  {
    // assign pointers
    head_ = 0;
    tail_ = 0;
    
    // assign size counter
    size_ = 0;
    
    // increment ist counter
    list_count_++;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Copy constructor for List.
  
  \param original
    The List to copy over.
  
  */
  /***************************************************************************/
  List::List(const List& original)
  {
      // assign pointers
    head_ = 0;
    tail_ = 0;
    
      // assign size counter
    size_ = 0;
    
      // pointer to walk list to copy
    Node* original_walker = original.head_;
    
      // while there are nodes to copy
    while(original_walker)
    {
        // push a node to the back with the value of list being copied
      push_back(original_walker->data);
      
      original_walker = original_walker->next;
    }
    
      // increment list counter
    list_count_++;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Non-default constructor for List.
  
  \param array
    An array integers you want to make into a List.
  
  */
  /***************************************************************************/
  List::List(const int* array, int length)
  { 
  }
    
  /***************************************************************************/
  /*!
  
  \brief
    Destructor for list class.
  
  */
  /***************************************************************************/
  List::~List()
  {
      // call clear to clear out the list
    List::clear();
  }
    
  /***************************************************************************/
  /*!
  
  \brief
    Overloads = operator to assign the right hand operand to the left.
  
  \param rhs 
    A List reference to assign to the left hand operand.
  
  \return
    A list reference to the left hand list.
  */
  /***************************************************************************/
  List& List::operator=(const List& rhs)
  {
      // pointer to walk rhs list
    Node *walkerrhs = rhs.head_;
    
      // while there are nodes to assign
    while(walkerrhs)
    {
        // call push back with value of rhs node
      List::push_back(walkerrhs->data);
      
        // move walker pointer
      walkerrhs = walkerrhs->next;
    }
    
      // return left hand list
    return *this;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Overloads += to concatenate the right hand list to the left hand list.
  
  \param rhs
    A list reference to concatenate with.
  
  \return
    A reference to the left hand list.
  */
  /***************************************************************************/
  List& List::operator+=(const List& rhs)
  {
      // pointer to walk rhs list
    Node *walkerrhs = rhs.head_;
    
      // while there are nodes to add
    while(walkerrhs)
    {
        // add node to end of lhs
      List::push_back(walkerrhs->data);
      
        // move walker pointer
      walkerrhs = walkerrhs->next; 
    }
      // return left hand list
    return *this;
  }
    
  /***************************************************************************/
  /*!
  
  \brief
    Overloads + operator to create a list and make it a combination of the
    left hand list and right hand list.
  
  \param rhs
    A reference to a List to copy.
  
  \return
    A list that has been copied and concatenated from the left and right hand 
    operands.
  */
  /***************************************************************************/
  List List::operator+(const List& rhs) const
  {
      // pointer to walk each list
    Node *walkerlhs = head_;
    Node *walkerrhs = rhs.head_;
    
      // create list to return
    List sum;
    
      // while there are nodes to add from the left hand list
    while(walkerlhs)
    {
        // push nodes to add to created list w/ value from left hand list
      sum.push_back(walkerlhs->data);
      
        // move the walker
      walkerlhs = walkerlhs->next;
    }
    
      // while there are nodes to add from the right hand list
    while(walkerrhs)
    {
        // push nodes to add to created list w/ values from right hand list
      sum.push_back(walkerrhs->data);
      
        // move walker 
      walkerrhs = walkerrhs->next;
    }
    
      // return the list created
    return sum;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Overloads subscript operator to read a number from the list.
  
  \param index
    How far into the list to go.
  
  \return
    The integer portion of the container at the specified index.
  */
  /***************************************************************************/
  int List::operator[](int index) const
  {
      // create walker pointer
    Node *walker = head_;
    
      // while we need to keep walking the list
    for(int i = 0; i < index; i++)
      walker = walker->next;
    
      // return the number
    return walker->data;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Overloads subscript operator to write over the data portion at a certain 
    index of the list.
  
  \param index
    How far into the list to go.
  
  \return
    A reference to the integer you want to write over.
  */
  /***************************************************************************/
  int& List::operator[](int index)
  {
      // node to walk the list
    Node *walker = head_;
    
      // keep walking until appropriate index
    for(int i = 0; i < index; i++)
      walker = walker->next;
    
      // return number there
    return walker->data;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Push a node to the front of the list.
  
  \param value
    The vale you want to assign the node being pushed.
  
  */
  /***************************************************************************/
  void List::push_front(int value)
  {
      // if head is null there are no items in the list
      // can also assume tail is null
    if(!head_)
    {
      head_ = new_node(value);
      tail_ = head_;
      size_++;
      return;
    }
  
      // create node to push
    Node *push = new_node(value);
  
      // insert before head node
    push->next = head_;
  
      // move head pointer
    head_ = push;
  
      // increment size counter
    size_++;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Pushes a node the back of the list.
  
  \param value
    The value you want to assign the node being pushed.
  
  */
  /***************************************************************************/
  void List::push_back(int value)
  {
    
      // if head is null there are no items in list
      // can also assume tail is null
    if(!head_)
    {
      head_ = new_node(value);
      tail_ = head_;
      size_++;
      return;
    }
  
      // make node to push
    Node *push = new_node(value);
  
      // push at the end
    tail_->next = push;
  
      // move tail pointer
    tail_ = push;
  
      // increment size counter
    size_++;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Pops the first node in the list.
  
  \return
    Return the integer -1 if the list was already empty or the integer from
    the container removed.
  */
  /***************************************************************************/
  int List::pop_front()
  {
      // list is empty, return -1
    if(size_ == 0)
      return -1;
  
      // temp pointer to 2nd node
    Node *temp = head_->next;
    
    int removed = head_->data;
  
      // remove head node
    delete head_;
  
      // move head pointer
    head_ = temp;
  
      // decrement size counter
    size_--;
    
      // return 1 for successful pop
    return removed;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Returns the number of nodes in the list.
  
  \return
    How many nodes are in the list.
  */
  /***************************************************************************/
  int List::size() const
  {
      // return size counter
    return size_;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Checks if the list is empty.
  
  \return
    Returns 1 if the list is empty, or 0 if the list is not empty.
  */
  /***************************************************************************/
  int List::empty() const
  {
      // if size is 0 return true (1) else return false (0)
    if(size_ == 0)
      return 1;
    else 
      return 0;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Removes all nodes from a list.
  
  */
  /***************************************************************************/
  void List::clear()
  {
      // while there are still nodes to be removed keep going
    while(pop_front() != -1)
      continue;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Returns how many lists have been created.
  
  \return
    Number of lists created.
  */
  /***************************************************************************/
  int List::list_count()
  {
    return list_count_;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Returns how many nodes are alive.
  
  \return
    Number of Nodes alive.
  */
  /***************************************************************************/
  int List::node_count()
  {
    return List::Node::nodes_alive;
  }
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  // private methods

  /***************************************************************************/
  /*!
  
  \brief
    Creates a node with dynamic allocation.
  
  \param data
    The value you want to assign to the node.
  
  \return
    A pointer to the node created.
  */
  /***************************************************************************/
  List::Node* List::new_node(int data) const
  {
    return new Node(data);
  }

  /////////////////////////////////////////////////////////////////////////////
  // non-member methods

  /***************************************************************************/
  /*!
  
  \brief
    Overloads << to print out the list.
  
  \param os 
    The stream you want to print to.
    
  \param list
    The list you want to print out.
  
  \return
    A reference to the stream you're using.
  */
  /***************************************************************************/
  std::ostream & operator<<(std::ostream & os, const List &list)
  {
      // Start at the first node
    List::Node *pnode = list.head_;

      // Until we reach the end of the list
    while (pnode != 0)
    {
      os << std::setw(4) << pnode->data; // print the data in this node
      pnode = pnode->next;               // move to the next node
    }
  
    os << std::endl; // extra newline for readability
    return os;
  }

} //namespace CS170
