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
\par Lab #5  
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
    
*/
/*****************************************************************************/

namespace CS170
{
  namespace ListLab
  {
    List::List()
    {
      head_ = 0;
    }
    
    /*****************************************************************************/
    /*!

    \brief 
      Constructor for the class List 
      
      
    */
    /*****************************************************************************/
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

    
    /*****************************************************************************/
    /*!

    \brief
      Makes a new node to add to the list.

    \param value
      The number to assign to the node.

    \return
      A node pointer to the node created.
    */
    /*****************************************************************************/
    Node* List::MakeNode(int value) const
    {
        // The Node constructor sets the value, and sets next to 0.
      return new Node(value);
    }

    /*****************************************************************************/
    /*!
    
    \brief
      Prints the linked list values out.
      
    */
    /*****************************************************************************/
    void List::PrintList() const
    {
      Node *list = head_;
      while (list)
      {
        std::cout << list->number << "   ";
        list = list->next;
      }
      std::cout << std::endl;
    }
    
    /*****************************************************************************/
    /*!

    \brief
      Counts the number of nodes in the list.

    \return
      The number of nodes in the list.
    */
    /*****************************************************************************/
    int List::Count()
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
    
    /*****************************************************************************/
    /*!

    \brief
      Adds a node to the front of the list.

    \param value
      Value to assign the node tht is created in the function.

    */
    /*****************************************************************************/
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
    
    /*****************************************************************************/
    /*!

    \brief
      Adds a node to the end of the list.

    \param value
      Number to assign to the node created in the function.

    */
    /*****************************************************************************/
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
    
    /*****************************************************************************/
    /*!

    \brief
      Attempts to find a node that contains a certain value in the list.

    \param value
      The value to search for in the nodes.

    \return
      Apointer to the node that contains 'value'.
    */
    /*****************************************************************************/
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
    
    
    /*****************************************************************************/
    /*!

    \brief
      Inserts a node into the list at a certain point in the list.

    \param value
      Value to assign to the node created.
      
    \param position
      Position in the list in which to insert the new node.
      
    */
    /*****************************************************************************/
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
    
  }
}
