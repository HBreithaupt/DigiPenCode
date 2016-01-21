/*****************************************************************************/
/*!
\file List.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Lab #4  
\date 1-30-2015

\brief
*/
/*****************************************************************************/

#include <iostream> // cout, endl
#include "List.h"

namespace CS170
{
  namespace ListLab
  {
    namespace 
    {
      struct Node* MakeNode(int value)
      {
        struct Node *pNode = new Node; // Allocate memory
        pNode->number = value;         // Set number
        pNode->next = 0;               // Set next (no next yet)

        return pNode;
      }
    }

    /*************************************************************************/

    /*!
    \fn void CS170::ListLab::PrintList(struct Node *list)

    \brief
      Takes a linked list and prints out the data of the list.

    \param list
      A pointer to a Node struct in a linked list.
      
    \return 
      N/A
    */
    /*************************************************************************/
    void PrintList(struct Node *list)
    {
      while (list)
      {
        std::cout << list->number << "   ";
        list = list->next;
      }
      std::cout << std::endl;
    }

    /*************************************************************************/
    /*!
    \fn int Count(struct Node *list)

    \brief 
      Counts the number of nodes in a linked list.

    \param list
      A pointer to the first node in the list.

    \return 
      Number of nodes in the list.
    */
    /*************************************************************************/
    int Count(struct Node *list)
    {
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
    \fn  void AddToEnd(Node **pList, int value)

    \brief
      Inserts a node to the end of a linked list

    \param pList
      Pointer to a pointer to the first Node in a linked list.
      
    \param value
      The value to place in new node. 

    \return 
      N/A
    */
    /*************************************************************************/
    void AddToEnd(Node **pList, int value)
    {
        /* list is valid and already exists */
      if(*pList)
      {
        
          /* pointer to walk the list */
        struct Node *current = *pList; 
        
          /* walk until the end of the list */
        while(current->next)
          current = current->next;
        
          /* now that we are at the end make a new node */
        current->next = MakeNode(value);
      }
      else /* list doesn't exist so start it */
      {
        AddToFront(pList, value);
      }
    }
    
    /*************************************************************************/
    /*!
    \fn void AddToFront(Node **pList, int value)

    \brief 
      Adds a node to the front of a linked list.

    \param pList
      A pointer to a pointer to the first node in a linked list.
      
    \param value
      The value to place in the new node.

    \return
      N/A
    */
    /*************************************************************************/
    void AddToFront(Node **pList, int value)
    {
        /* list is already created */
      if(*pList)
      {
          /* create new Node to add to the front */
        Node *NewFirst = MakeNode(value);
        
          /* change next member of new node to previous first node */
        NewFirst->next = *pList;
        
          /* move pList to point at new fron node */
        *pList = NewFirst;
      }
      else  /* if list doesnt exists create it */
      {
          /* create a new node and have pList point to it */
        *pList = MakeNode(value);
      }
    }
    
    /*************************************************************************/
    /*!
    \fn Node *FindItem(Node *list, int value)

    \brief
      Finds a node that contains a certain value in a linked list.

    \param list
      A pointer to the first nide in a linked list.
      
    \param value
      The value to look for while lookin through the list.

    \return 
      A pointer to the node containing value.
    */
    /*************************************************************************/
    Node *FindItem(Node *list, int value)
    {
        /* list exists */
      if(list)
      {
          /* while next isnt null */
        while(list->next)
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
    \fn void FreeList(Node *pList)

    \brief 
      Frees all nodes of a linked list.

    \param pList
      A pointer to the first node in the list.

    \return 
      N/A
    */
    /*************************************************************************/
    void FreeList(Node *pList)
    {
        /* list pointer is valid */
      if(pList)
      {
          /* while list is not null */
        while(pList)
        {
            /* pointer to next node in the list  */
          struct Node *temp = pList->next;

            /* delete node we're looking at */   
          delete pList;
          
          pList = temp;
        }
      }
    }
    
    /*************************************************************************/
    /*!
    \fn void Insert(Node **pList, int value, int position)

    \brief 
      Insert a node to a certain position in the list.

    \param pList
      A pointer to a pointer to the first node in the list.
      
    \param value
      The value to place in allocated node.
      
    \param position
      The position in the list in which to place the new node.

    \return 
      N/A
    */
    /*************************************************************************/
    void Insert(Node **pList, int value, int position)
    {
        /* list already exists */
      if (*pList)
      {
       
          /* do nothing is position is higher than count */
        if (position > Count(*pList))
          return;
        
          /* pointer to walk and count the list */
        struct Node *current = *pList;
        struct Node *previous = *pList;
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
          AddToFront(pList, value);
        }
          /* anywhere in list that isnt front or back */
        else if(current && i == position)
        {
            /* create new node */
          Node *Insert = MakeNode(value);
          
            /* previous node points to new node */
          previous->next = Insert;
          
            /* new node points to current */
          Insert->next = current;
          
          // Insert is now inbetween previous and current
        }
          /* if previous is valid and current is null add to end */
        else if (previous && !current)
        {
          AddToEnd(pList, value);
        }
      }
    }
  
  } // namespace ListLab
} // namespace CS170
