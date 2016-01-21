/*****************************************************************************/
/*!
\file List.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Assignment 5  
\date   3-22-15

\brief
  Templatizes the List class to accomadate any type.
  
  Functions include:
    - defulat constructor
    - non-default constructor
    - copy constructor
    - destructor
    - push_front : pushes a node to the front of the lise
    - push_back : pushes a node to the back of the list
    - pop_front : pops the node at the front of the list
    - front : accesses data of the front node
    - size : counts how many nodes are in the list
    - empty : whether or not the object is empty
    - clear : properly destroys the object
    - new_node : allocates a node for use
    
  Overloaded Operators:
    - =  : assignment overload
    - +  : concats the right hand list to the left hand list
    - += : creates a list and concats the left hand then right hand list
    - [] : overloaded twice for r-values and l-values
    - << : used to print out list to any ostream
    
Hours spent on assignment: 2

Specific portions that gave you the most trouble: 
  Fairly easy assignment, mostly copy paste with a couple of edits.
*/
/*****************************************************************************/

namespace CS170
{
  
  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  // static members
  
    // initializes static variable
  template <typename T>
    int List<T>::Node::nodes_alive = 0;
  
  /***************************************************************************/
  /*!
  
  \brief
    Checks the number of nodes alive.
  
  \return
    The number of nodes alive.
  */
  /***************************************************************************/
  template <typename T>
    int List<T>::node_count(void)
    {
      return Node::nodes_alive;
    }
  
  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  // List::Node methods
  
  /***************************************************************************/
  /*!
  
  \brief
    Templated constructor for the Node struct.
  
  \param value
    The data you want inserted into the node.
  
  */
  /***************************************************************************/
  template <typename T>
    List<T>::Node::Node(T value) : data(value)
    {
      nodes_alive++;
    }
  
  /***************************************************************************/
  /*!
  
  \brief
    Destructor for Nodes.
  
  */
  /***************************************************************************/
  template <typename T>
    List<T>::Node::~Node()
    {
        // decrements node counter
      nodes_alive--;
    }
  
  
  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  // public methods
  
  /***************************************************************************/
  /*!
  
  \brief
    Templated constructor for List class.
  
  */
  /***************************************************************************/
  template <typename T>
    List<T>::List()
    {
        // assign pointers
      head_ = 0;
      tail_ = 0;
      
        // assign size counter
      size_ = 0;
    }
  
  /***************************************************************************/
  /*!
  
  \brief
    Templated copy construcotr for List class.
  
  \param original
    A reference to the object you wish to copy.
  
  */
  /***************************************************************************/
  template<typename T>
    List<T>::List(const List& original)
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
    }
  
  /***************************************************************************/
  /*!
  
  \brief
    Templated non-default constructor for List class.
  
  \param array
    The array to use to assign the data in the object.
  
  */
  /***************************************************************************/
  template <typename T>
    List<T>::List(const T *array, int size)
    {
        // assign pointers
      head_ = 0;
      tail_ = 0;
      
        // assign size counter
      size_ = 0;
        
        // while there are nodes to add push them back in the list
      for(int i = 0; i < size; i++)
        List::push_back(array[i]);
    }
  
  /***************************************************************************/
  /*!
  
  \brief
    Templated destructor for List class.
    
  */
  /***************************************************************************/
  template <typename T>
    List<T>::~List()
    {
        // call clear to destroy object
      clear();
    }
  
  /***************************************************************************/
  /*!
  
  \brief
    Pushes an object to the front of the list.
  
  \param Value
    Reference to the data you want to put in the object.
  
  */
  /***************************************************************************/
  template <typename T>
    void List<T>::push_front(const T& Value)
    {
      
        // if head is null there are no items in the list
        // can also assume tail is null
      if(!head_)
      {
        head_ = new_node(Value);
        tail_ = head_;
        size_++;
        return;
      }
    
        // create node to push
      Node *push = new_node(Value);
    
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
    Pushses an object to the back of the list.
  
  \param Value
    A reference to the data you want to put in the object.
  
  */
  /***************************************************************************/
  template <typename T>
    void List<T>::push_back(const T& Value)
    {
        // if head is null there are no items in list
        // can also assume tail is null
      if(!head_)
      {
        head_ = new_node(Value);
        tail_ = head_;
        size_++;
        return;
      }
    
        // make node to push
      Node *push = new_node(Value);
    
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
    Pops the front piece of data in the list.

  */
  /***************************************************************************/
  template <typename T>
    void List<T>::pop_front()
    {
        // if list is empty do nothing
      if(empty())
          return;
      
        // temp pointer to 2nd node
      Node *temp = head_->next;
      
        // remove head node
      delete head_;
      
        // move head pointer
      head_ = temp;
      
        // decrement size counter
      size_--;
    }
  
  /***************************************************************************/
  /*!
  
  \brief
    Checks the value of the first data in the list.
  
  */
  /***************************************************************************/
  template <typename T>
    T List<T>::front() const
    {
        // return data in the head node
      return head_->data;
    }
  
  /***************************************************************************/
  /*!
  
  \brief
    Checks the size of the object.
  
  \return
    The number of items in the list.
    
  */
  /***************************************************************************/
  template <typename T>
    int List<T>::size() const
    {
        // returns number of nodes in the list
      return size_;
    }
  
  /***************************************************************************/
  /*!
  
  \brief
    Checks if the object is empty.
  
  \return
    A boolean if the object has data in it (1) or if the object is empty (0).
    
  */
  /***************************************************************************/
  template <typename T>
    bool List<T>::empty() const
    {
        // if size is 0 return 1, if not return 0
      return size_ == 0 ? 1 : 0;
    }
    
  /***************************************************************************/
  /*!
  
  \brief
    Overloads operator = for assignment.
  
  \param rhs
    A reference to the object yo use in the assignment.
  
  \return
    A reference to the List thats been modified.
    
  */
  /***************************************************************************/
  template <typename T>
    List<T>& List<T>::operator=(const List& rhs)
    {
     
        // self assignment check
        // if left hand and rhs are at same locations in memory just
        // retur left hand object
      if(this == &rhs)
        return *this;
      
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
    Overloads operator + to make a list and assigns it with the values of the 
    left hand and right hand lists.
  
  \param rhs
    A reference to the list being concatenated.
    
  \return
    The list created with the values.
    
  */
  /***************************************************************************/
  template <typename T>
    List<T> List<T>::operator+(const List& rhs) const
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
    Overloads operator += that concatenates the right hand list to the 
    left hand list.
  
  \param rhs
    A reference to the list being used to add to the created list.
  
  \return
    Reference to the left hand list.
    
  */
  /***************************************************************************/
  template<typename T>
    List<T>& List<T>::operator+=(const List& rhs)
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
    Overloads subscript operator for rvalues.
  
  \param index
    How far into the list to go to access the data.
  
  \return
    The data at the specified index.
    
  */
  /***************************************************************************/
  template<typename T>
    const T& List<T>::operator[](int index) const
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
    Overloads subcript operator for lvalues.
  
  \param index
    How far into the list to go to access the data.
    
  \return
    A reference to the data at the specified index.
    
  */
  /***************************************************************************/
  template<typename T>
    T& List<T>::operator[](int index)
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
    Removes all of the nodes in the list.
    
  */
  /***************************************************************************/
  template <typename T>
    void List<T>::clear()
    {
      while (!empty())
        pop_front();
    }
  
  
  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  // private methods
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Allocate a node, initialoze the data and the next pointer.
  
  \param data
    The data to put in the node.
  
  \return
    A pointer to the node.
  */
  /***************************************************************************/
  template <typename T>
    typename List<T>::Node *List<T>::new_node(const T& data) const
    {
      Node *node = new Node(data); // create the node
      node->next = 0;              // no next pointer yet
      return node;
    }
  
} // namespace CS170


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// non-members

#include <iomanip>

/*****************************************************************************/
/*!

\brief 
  Output the list into an ostream object.
  
\param os 
  ostream object to output to

\param list 
  the List to output
  
\return
  The ostream object that was passed in.
*/
/*****************************************************************************/
template <typename T>
std::ostream &CS170::operator<<(std::ostream & os, const CS170::List<T> &list)
{
    // Start at the top
  typename CS170::List<T>::Node *pnode = list.head_;

    // Print each item
  while (pnode != 0)
  {
    os << std::setw(4) << pnode->data;
    pnode = pnode->next;
  }
  os << std::endl;
  return os;
}

