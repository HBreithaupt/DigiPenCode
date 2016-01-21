///////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*!
\file List.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Lab #8  
\date 2-27-2015

\brief
  Contains class of List with member functions to perform various operations
  on linked lists.
*/
/*****************************************************************************/

namespace CS170
{
  namespace ListLab
  {
    struct Node
    {
      int number; // data portion
      Node *next; // pointer portion

        // Conversion constructor
      Node(int value)
      {
        number = value;
        next = 0;
      }
    };

    class List
    {
      public:
          // Default constructor
        List();

          // Destructor
        ~List();
        
          //counts nodes in the list
        int Count() const;
      
          //adds to the front of the list
        void AddToFront(int value);
      
          //adds to the end of the list
        void AddToEnd(int value);
      
          //finds a node with a certain number
        Node *FindItem(int value);
      
          //inserts a node into the list at a given position
        void Insert(int value, int position);
      
          //inserts based on numerical value
        void Insert(int value);
      
          //deletes node with 'value' (first occurence only)
        void Delete(int value);
      
          // deletes all values in the List that are in Items
        void Delete(const List& Items);
      
          // prints out the list to specified stream
        friend std::ostream& operator<<(std::ostream&, const List& list);
      
          // concats Source to List
        void Concat(const List& Source);

          // Merge two lists together  
        void Merge(List& rhs);
      
      private:
          //pointer to head node
        Node *head_;
      
          //makes a new node and assigns it a value
        Node* MakeNode(int value) const;
        
          // finds a node of value and returns pointer to previous node
          // (helper function)
        Node *DeleteHelper(int value);
        
          // Any private helper methods you need...
    };
  } // namespace ListLab
} // namespace CS170

#endif // LIST_H

