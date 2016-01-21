/*****************************************************************************/
/*!
\file slist.c
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par Assignment 1
\date 5/15/2015

\brief
  Implementation to perform simple operations on a singly linked list.

  Function list:
    - make_node : makes a node to use in the list
    - sll_add : adds a node to the end of the list
    - sll_remove : remove a node with a certain value
    - sll_insert_before : inserts a node before a node with a certain value
    - sll_insert_after : inserts a node after a node with a certain value
    - sll_destroy : deletes a list, freeing all memory
    - sll_dump : prints out a list
    
Hours spent on assignment: 1 

Specific portions that gave you the most trouble:
  Nothing really, easy assignment (as described).
*/
/*****************************************************************************/

#include <stdio.h>  /* printf             */
#include <stdlib.h> /* malloc, free, exit */
#include <string.h> /* strncpy            */
#include "slist.h"

/*****************************************************************************/
/*!

\brief
  Creates a node to use in the list.

/param value
  The value to put into the created node.
  
\param label
  String to put in the label data of the created node.

\return
  Apointer to the created node.
*/
/*****************************************************************************/
static sll_node *make_node(int value, const char *label)
{
    /* allocates data for a node */
  sll_node *node = (sll_node *)malloc(sizeof(sll_node));
    
    /* check for successful allocation */
  if (!node)
  {
    printf("Can't allocate new node.\n");
    exit(-1);
  }

    /* assign data of the node */
  node->value = value;
  node->next = NULL;

    /* Be sure not to overwrite memory */
  strncpy(node->label, label, LABEL_SIZE - 1);
  node->label[LABEL_SIZE - 1] = 0;
  
    /* return pointer to node created */
  return node;
}

/*****************************************************************************/
/*!

\brief
  Takes a list and prints the contents out to the screen.

\param list
  The list to print out.

*/
/*****************************************************************************/
void sll_dump(const sll_node *list)
{
  printf("==================\n");
  while (list)
  {
    printf("%4i: %s\n", list->value, list->label);
    list = list->next;    
  }
}

/*****************************************************************************/
/*!

\brief
  Adds a node to the end of the list.

\param list 
  The list to add to.
 
\param value
  The value to put into the node being inserted.
  
\param label
  Label to put in the node being added to the list.

\return
  A pointer to the head node.
*/
/*****************************************************************************/
sll_node *sll_add(sll_node *list, int value, const char *label)
{
    /* two node pointers, one to add the the list, the other to wealk it*/
  sll_node *add, *walk;
  
    /* list is empty so assign list with valid data and return it */
  if(!list)
  {
    list = make_node(value, label);
    
    return list;
  }
  
    /* assign add with data to be added at the end of the list */
  add = make_node(value, label);
  
    /* start the walking pointer at the head of the list */
  walk = list;
  
    /* walk the list until the last node before the NULL */
  while(walk->next)
    walk = walk->next;
  
    /* insert node at the end */
  walk->next = add;
  
    /* return head of the list */
  return list;
}

/*****************************************************************************/
/*!

\brief
  Removes a node with a passed value.

\param list
  The list to search for node with passed search value.
  
\param search_value
  The value to search for in the list.

\return
  A pointer to the head node.
*/
/*****************************************************************************/
sll_node *sll_remove(sll_node *list, int search_value)
{
    /* pointers to walk the list */
  sll_node *current, *previous;
  
    /* assign pointers */
  current = list;
  previous = current;
 
  if(!list)
    return list;
  
    /* walk list until we reach the end or find the value */
  while(current && current->value != search_value)
  {
    previous = current;
    current = current->next;
  }
  
    /* case of removing the head node */
  if(current == list)
  {
      /* move list */
    list = list->next;
    
      /* free the previous head of the list */
    free (current);
    
      /* return new head of list */
    return list;
  }
  
  if(current && current->value == search_value)
  {
    current = current->next;
    
    free (previous->next);
    
    previous->next = current;
    
    return list;
  }
  
  return list;
}

/*****************************************************************************/
/*!

\brief
  Inserts a node before a node in the list with a certain value.

\param list
  The list to search through.

\param search_value
  Teh value to search for in the list.
  
\param value
  The value to put into the node being inserted.

\param label
  the label to put into the node being inserted into the list.
  
\return
  A pointer to the head node.
*/
/*****************************************************************************/
sll_node *sll_insert_before(sll_node *list, int search_value, 
                            int value, const char *label)
{
    /* node pointers */
  sll_node *current, *previous, *insert;
  
    /* two pointer to walk the list */
  current = list;
  previous = current;
  
    /* move current until either search value is found or
     * reach end of the list */
  while(current && current->value != search_value)
  {
    previous = current;
    current = current->next;
  }
  
    /* case of inserting before the head of the list */
  if(current == list)
  {
      /* assign insert data */
    insert = make_node(value, label);
    
      /* put insert ahead of head of list */
    insert->next = list;
    
      /* move head of list */
    list = insert;
    
      /* return new head of list */
    return list;
  }
    /* search value is found, if value isnt found return head of list */
  if(current)
  {
      /* assign insert data */
    insert = make_node(value, label);
    
      /* link insert into the list */
    previous->next = insert;
    insert->next = current;
    
    return list;
    
  }
  else 
    return list;
  
}

/*****************************************************************************/
/*!

\brief
  Inserts a node after a node in the list with a certain value.

\param list
  The list to search through
  
\param search_value
  The value to search for.
  
\param value
  The value to put into the node being inserted.
  
\param label
  Label to put in the node being inserted.

*/
/*****************************************************************************/
void sll_insert_after(sll_node *list, int search_value,
                      int value, const char *label)
{
    /* pointer to walk list and one to insert */
  sll_node *current, *aftercurrent, *insert;
  
    /* start at head of list */
  current = list;
  
    /* walk the list until we find our value or reach the end */
  while(current && current->value != search_value)
    current = current->next;
  
    /* current is valid, therefore we found our value */
  if(current)
  {
      /* assign insert data */
    insert = make_node(value, label);
    
      /* get pointer to node after the one with value to link back up*/
    aftercurrent = current->next;
    
      /* put insert in after current */
    current->next = insert;
    
      /* relink insert into the list */
    insert->next = aftercurrent;
  }
}

/*****************************************************************************/
/*!

\brief
  Deletes a list.

\param list
  The list to delete.

*/
/*****************************************************************************/
void sll_destroy(sll_node *list)
{
    /* pointer to walk the list freeing nodes */
  sll_node  *remove = list;
  
   /* make sure list actually exists first */
  if(!list)
    return;
  
  while(list)
  {
      /* move list to next node */
    list = list->next;
    
      /* free previous node */
    free (remove);
  
      /* move remove pointer to list */
    remove = list;
  }
}

