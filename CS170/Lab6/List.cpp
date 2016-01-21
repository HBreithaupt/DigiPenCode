#include <iostream> // cout
#include "List.h"

/*******************************************************************/
/*******************************************************************/

/*****************************************************************************/
/*!
\file List.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt@digipen.edu
\par Course: CS170
\par Lab #6  
\date 2-6-2015

\brief
  Contains function definitions of funcitons from class List:
    - contructor & destructor
    - Count - Counts nodes in a list
    - AddToFront - adds node to front of list
    - AddToEnd - adds node to end of list
    - PrintList - prints out the list
    - MakeNode - makes a new node 
    - FindItem - finds a node containing a passed value
    - InsertNode - Inserts a node into a list
    - Delete - deletes one occurence of a value
    - Delete(overloaded) - deletes multiple values from a list
    - Insert(overloaded) - Inserts into a list based on numverical value
    - Concat - Concats a list to another list
    - operator << overloaded to print out list
*/
/*****************************************************************************/

namespace CS170
{
  namespace ListLab
  {
    /*************************************************************************/
    /*!

    \brief 
      constructor for the class List.

    */
    /*************************************************************************/
    List::List()
    {
      head_ = 0;
    }
    
    /*************************************************************************/
    /*!

    \brief 
      Destructor for the class List 
      
    */
    /*************************************************************************/
    List::~List()
    {
      /* list pointer is valid */
      if(head_)
      {
          /* while list is not null */
        while(head_)
        {
            /* pointer to next node in the list  */
          struct Node *temp = head_->next;

            /* delete node we're looking at */   
          delete head_;
          
          head_ = temp;
        }
      }
    }

    
    /*************************************************************************/
    /*!

    \brief
      Makes a new node to add to the list.

    \param value
      The number to assign to the node.

    \return
      A node pointer to the node created.
    */
    /*************************************************************************/
    Node* List::MakeNode(int value) const
    {
        // The Node constructor sets the value, and sets next to 0.
      return new Node(value);
    }

    /*************************************************************************/
    /*!

    \brief
      Overloads << operator to display the list.

    \param os
      A reference to the stream we want to output in.
      
    \param list
      A constant reference to the List we want to print.

    \return
      A reference to the stream being used.
    */
    /*************************************************************************/
    std::ostream& operator<<(std::ostream& os, const List& list)
    {
      Node *walker = list.head_;
      
      while(walker)
      {
        os << walker->number << "  ";
        
        walker = walker->next;
      }
      
      return os;
    }
    
    
    /*************************************************************************/
    /*!

    \brief
      Counts the number of nodes in the list.

    \return
      The number of nodes in the list.
    */
    /*************************************************************************/
    int List::Count() const
    {
      Node *list = head_;
      int count = 0;
      while (list)
      {
        count++;
        list = list->next;
      }
      return count;
    }
    
    /*************************************************************************/
    /*!

    \brief
      Adds a node to the front of the list.

    \param value
      Value to assign the node tht is created in the function.

    */
    /*************************************************************************/
    void List::AddToFront(int value)
    {
      
      Node *pList = head_;
        /* list is already created */
      if(pList)
      {
          /* create new Node to add to the front */
        Node *NewFirst = List::MakeNode(value);
        
          /* change next member of new node to previous first node */
        NewFirst->next = pList;
        
          /* move pList to point at new fron node */
        head_ = NewFirst;
      }
      else  /* if list doesnt exists create it */
      {
          /* create a new node and have pList point to it */
        head_ = List::MakeNode(value);
      }
    }
    
    /*************************************************************************/
    /*!

    \brief
      Adds a node to the end of the list.

    \param value
      Number to assign to the node created in the function.

    */
    /*************************************************************************/
    void List::AddToEnd(int value)
    {
      
      Node *pList = head_;
      
        /* list is valid and already exists */
      if(pList)
      {
        
          /* pointer to walk the list */
        struct Node *current = pList; 
        
          /* walk until the end of the list */
        while(current->next)
          current = current->next;
        
          /* now that we are at the end make a new node */
        current->next = MakeNode(value);
      }
      else /* list doesn't exist so start it */
      {
        head_ = List::MakeNode(value);
      }
    }
    
    /*************************************************************************/
    /*!

    \brief
      Attempts to find a node that contains a certain value in the list.

    \param value
      The value to search for in the nodes.

    \return
      Apointer to the node that contains 'value'.
    */
    /*************************************************************************/
    Node* List::FindItem(int value)
    {
      
      Node *list = head_;
      
        /* list exists */
      if(list)
      {
          /* while next isnt null */
        while(list)
        {
            /* we foud the value we wanted */
          if (list->number == value)
          {
              /* return pointer to the node with value we want */
            return list;
          }
          
          list = list->next;
        } 
      } 
        /* we didnt find the value we wanted so return NULL */
      return NULL;
    }
    
    
    /*************************************************************************/
    /*!

    \brief
      Inserts a node into the list at a certain point in the list.

    \param value
      Value to assign to the node created.
      
    \param position
      Position in the list in which to insert the new node.
      
    */
    /*************************************************************************/
    void List::Insert(int value, int position)
    {
      Node *pList = head_;
      
        /* list already exists */
      if (pList)
      {
          // copes head so head isnt changed
       
          /* do nothing is position is higher than count */
        if (position > List::Count())
          return;
        
          /* pointer to walk and count the list */
        struct Node *current = pList;
        struct Node *previous = pList;
        int i;
        
          /* count up to position we want */
        for(i = 0; i < position; i++)
        {
          previous = current;
          current = current->next;
        }
        
          /* if position is zero addtofront */
        if(position == 0)
        {
          List::AddToFront(value);
        }
          /* anywhere in list that isnt front or back */
        else if(current && i == position)
        {
            /* create new node */
          Node *Insert = List::MakeNode(value);
          
            /* previous node points to new node */
          previous->next = Insert;
          
            /* new node points to current */
          Insert->next = current;
          
          // Insert is now inbetween previous and current
        }
          /* if previous is valid and current is null add to end */
        else if (previous && !current)
        {
          List::AddToEnd(value);
        }
      }
    }
    
    /*************************************************************************/
    /*!

    \brief
      Inserts a node based on numerical value into a list.

    \param value
      Value to insert into the list.

    */
    /*************************************************************************/
    void List::Insert(int value)
    {
        //if list doesnt exist or you need to insert at the front of the list
      if(head_ == NULL || head_->number > value)
      {
        List::AddToFront(value);
        return;
      }
      
        //two pointer to walk the list
      Node *current = head_->next;
      Node *previous = head_;
      
        //while there are nodes
      while(current)
      {
            //if current's number is > value, insert before current
          if(current->number > value)
          {
              //new node
            Node *Insert = List::MakeNode(value);
            
              //attach Insert->next to current
            Insert->next = current;
            
              //attach previous->next to the new node
            previous->next = Insert;
            
              //return since we're done
            return;
          }
          else
          {
              //move pointers
            previous = current;
            current = current->next;
          }
        }
      
        // we made it to the end of the list without inserting, 
        // therefore add to the end of the list
      List::AddToEnd(value);    
    }
     
    
    /*************************************************************************/
    /*!

    \brief 
      A helper function to return the pointer to the node before the node that
      needs to be deleted.

    \param value
      The value to search for

    \return
      A pointer to the node before the actual node that needs to be deleted.
    */
    /*************************************************************************/
    Node* List::DeleteHelper(int value)
    {
        //nodes to walk the list
      Node *current = head_;
      Node *previous = head_;
      
      while(current)
      {
          //we found the node with value, but return node before it
        if(current->number == value)
          return previous;
        
          //move previous pointer
        previous = current;
        
          //move current pointer
        current = current->next;
      }
      
        //no node with value was found
      return NULL;
    }
    
    
    /*************************************************************************/
    /*!

    \brief
      Deletes the first occurence of a value in a List class.

    \param value
      Value to delete from the list.

    */
    /*************************************************************************/
    void List::Delete(int value)
    {
        //value previous is a pointer to a node before the node with value
      Node *value_previous = DeleteHelper(value);
      
        //list doesnt exist so just return
      if(!value_previous)
        return;
      
        //case of first node needing to be deleted
      if(value_previous == head_ && value_previous->number == value)
      {
        head_ = value_previous->next;
        
        delete value_previous;
        
        return;
      }
      
        //if value _previous is not NULL
      if(value_previous)
      {
          //connector is two nodes ahead of value_previous
        Node *connector = (value_previous->next)->next;
        
          //delete node that has value
        delete value_previous->next;
        
          //reconnect the list
        value_previous->next = connector;
        
      }
    }
    
    /*************************************************************************/
    /*!

    \brief
      Deletes all values gather from Items in another List class.

    \param Items
      A constant reference to a List class to gather input from to be used 
      in deleting values from another List.

    */
    /*************************************************************************/
    void List::Delete(const List& Items)
    {
        // pointer to walk Items
      Node *ItemsWalker = Items.head_;
      
        //while we still have things to delete
      while(ItemsWalker)
      {
          // grab value to delete from List
        int DelValue = ItemsWalker->number;
        
          //call delete (this will be repeated if necessary)
        List::Delete(DelValue);
        
          // if there are no more nodes in List with value from 
          // Items move to the next node in Items
        if(!List::DeleteHelper(DelValue))
          ItemsWalker = ItemsWalker->next;
      }
    }
    
    /*************************************************************************/
    /*!

    \brief 
      Concats a list to another list.

    \param Source
      A constant reference to a List class to copy.
      
    */
    /*************************************************************************/
    void List::Concat(const List& Source)
    {
        // pointer to walk Source
      Node *source_walker = Source.head_;
      
        //while there are nodes
      while(source_walker)
      {
          //call add to add with value from Source
        List::AddToEnd(source_walker->number);
          
          // move pointer to next node
        source_walker = source_walker->next;
      }
    }
  }
}
