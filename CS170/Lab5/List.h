////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*!
\file List.h
\author      Haven Breithaupt
\par DP email: h.breithaupt@digipen.edu
\par Course: CS170
\par Lab #5  
\date 2-6-2015

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
        
          // Other public methods...
        int Count();
        void AddToFront(int value);
        void AddToEnd(int value);
        Node *FindItem(int value);
        void Insert(int value, int position);
        void PrintList() const;
      
      private:
        Node *head_;
        Node* MakeNode(int value) const;
        
        
          // Any private helper methods you need...
    };
  } // namespace ListLab
} // namespace CS170

#endif // LIST_H

