/******************************************************************************
filename    list.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  14
due date    12/3/2014

Brief Description:
  
******************************************************************************/

#include "list.h"    /* struct and function prototypes */
#include <stdlib.h>  /* malloc, free */
#include <stdio.h>   /* printf */

/******************************************************************************
   Function: add_front

Description: adds a node to the front of the linked list

     Inputs: list - a pointer to a pointer a struct
             value - a number to put in new node
     
    Outputs: n/a
******************************************************************************/
void add_front(struct Node **list, int value)
{
    /* if pointer isn't null */
  if(*list)
  {
      /* new node pointer */
    struct Node *front;
    
      /* allocate memory for new struct */
    front = malloc(sizeof(struct Node));
    
    front->number = value; /* assign number of new struct*/
    front->next = *list;   /* put new node in front of list pointer  */
    *list = front;         /* moves list pointer to new front of list */
  }
  else                     /* list doesn't exist so make it */
  {
      /* allocate new node */
    *list = malloc(sizeof(struct Node)); 
    
      /* assign next to null since there's one item */
    (*list)->next = NULL;           
    
      /* assign number of node */
    (*list)->number = value; 
  }
 
}

/******************************************************************************
   Function: add_back

Description: adds a node to the back of a linked list

     Inputs: list - a pointer to a pointer to a struct
             value - number to put it new node
     
    Outputs: n/a
******************************************************************************/
void add_back(struct Node **list, int value)
{
    /* list pointer isn't null */
  if(*list)
  {
    struct Node *back;                   /* a node to insert at end */
    struct Node *current;                /* pointer to walk the list */
    
      /* allocate memory for new node */
    back = malloc(sizeof(struct Node)); 
    
      /* assign next to null since it will be new end */
    back->next = NULL; 
    
      /* assign number of new node */
    back->number = value; 
    
      /* assign current to beginning of list */
    current = *list;              
    
      /* walk the list until we find the end */
    while(current->next)
      current = current->next;
    
      /* insert new end node into the list */
    current->next = back;
  }
  else                    /* list doesn't exist so create it */
  {
    *list = malloc(sizeof(struct Node)); /* allocate memory for new node */
    (*list)->next = NULL;                /* assign next to null */
    (*list)->number = value;             /* assign number of node */
  }
}

/******************************************************************************
   Function: free_list

Description: frees the memory of all nodes in a linked list

     Inputs: list - a pointer to a struct
     
    Outputs: n/a
******************************************************************************/
void free_list(struct Node *list)
{
    /* if list pointer isnt null */
  if(list)
  {
      /* while list isn't null */
    while(list)
    {
        /* node pointer to next node in list */
      struct Node *temp = list->next;
      
        /* frees node we're looking at */
      free(list);
      
        /* move temp to list so now we're looking at it */
      list = temp;
    }
  }
}
  
/******************************************************************************
   Function: printf_list

Description: prints the numbers in a linked list

     Inputs: list - a pointer a struct
     
    Outputs: n/a
******************************************************************************/ 
void print_list(const struct Node *list)
{
    /* while list isnt null */
  while (list)
  {
      /* print number in node */
    printf("%3i", list->number);
      
      /* move pointer to next node */
    list = list->next;
  } 
  
    /* print new line at end of list */
  printf("\n"); 
}

/******************************************************************************
   Function: remove_item

Description: remove a node from a linked list if the number matches a number
             passed

     Inputs: list - a pointer to a pointer to a struct
             value - a number to compare to the nodes
     
    Outputs: n/a
******************************************************************************/
void remove_item(struct Node **list, int value)
{
    /* if list pointer isnt null */
  if(*list)
  {
    struct Node *current;      /* node pointer */
    struct Node *previous;     /* node pointer */
    
    current = *list;           /* assign current to beginning of list */
    previous = current;        /* assign previous to beginning of list */
    
    
      /* while the current isnt null */
    while(current)
    {
        /* if the number we want is in current */
      if(current->number == value)
      {
          /* previous next is now current next */
        previous->next = current->next;
        
          /* free current */
        free(current);
        
          /* if we remove the first node in list move list pointer to new
           * start of the list */
        if(previous == *list && current == *list)
          *list = previous->next;
        
          /* only looking to remove number so stop when we do */
        break; 
      }
      
      previous = current;      /* move up previous pointer */
      current = current->next; /* move current pointer froward */
      
    }
  }
}
 
/******************************************************************************
   Function: size_list

Description: counts the numbers of items a linked list

     Inputs: list - a pointer to a struct
     
    Outputs: number of items in the list
******************************************************************************/
int size_list(const struct Node *list)
{
  int count = 0;  /* counter, initialized to 0 */
  
    /* if list isn't null */
  if(list)
  {
      /* while the list isnt null */
    while(list)
    {
        /* move list pointer to next node */
      list = list->next;
      
        /* increment count */
      count++;
    }
  }
  
    /* return count at the end */
  return count;
}

/******************************************************************************
   Function: sum_list

Description: sums the numbers in the linked list

     Inputs: list - a pointer to a struct
     
    Outputs: the sum of the list
******************************************************************************/
int sum_list(const struct Node *list)
{
  int sum = 0;              /* sum of the list */
  
    /* if list isnt null */
  if(list)
  {
      /* while list isnt null */
    while(list)
    {
      sum += list->number;  /* add value of node to sum */
      list = list->next;    /* move list pointer to next node */
    } 
  }
  
  return sum;               /* return sum of the list */
}
  