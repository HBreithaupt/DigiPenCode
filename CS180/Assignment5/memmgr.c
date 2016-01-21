/*****************************************************************************/
/*!
\file    memmgr.c
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par Assignment 5
\date  7/8/15

\brief
  Implementation of a memory manager using a linked list;
  
  Functions Include:
    - mm_create : creates block of memory to manage
    - allocate_firstfit : divides up memory using first fit algorithm
    - allocate_bestfit : divides up memory using best fit algorithm
    - mm_allocate : divides up memory 
                    (just calls correspnding management alogorithm)
    - mm_deallocate : removes a node from the list
    - mm_destroy : desroys entire memory being used, nodes included

Hours spent on assignment: 5

Specific portions that gave you the most trouble: 
  - Fairly easy assignment, most dificult thing was trying to assign members
    of the struct properly but beyond that just a linked list.

*/
/*****************************************************************************/


#include "memmgr.h" /* struct info */
#include <stdlib.h> /* malloc  */
#include <string.h> /* strncpy */


  /* global variable to store memory management policy */
static MMPolicy mem_policy;

/*****************************************************************************/
/*!

\brief
  Allocates block of memory to use in the manager.

\param bytes
  Size of block to allocate.
  
\param policy
  Type of algorithm to use for allocations.

\return
  Pointer to head node containing all the memory to manage.
*/
/*****************************************************************************/
block_info *mm_create(size_t bytes, enum MMPolicy policy)
{
    /* allocate first node */
  block_info *heap = malloc(sizeof(block_info));
  
  heap->allocated = 0;            /* not alloacted */
  heap->size = bytes;             /* set size to total number of bytes */
  heap->address = malloc(bytes);  /* allocate the bytes requested */
  strncpy(heap->label, "START", LABEL_SIZE);        /* set label to start */
  mem_policy = policy;            /* save management policy in global */
  heap->next = 0;                 /* next is null */
  
    /* malloc check */
  if(heap->address == NULL)
    return NULL;
  
    /* return pointer to head node */
  return heap;
}

/*****************************************************************************/
/*!

\brief
  Allocates nodes using first fit algorithm.

\param heap
  List to allocate in.
  
\param bytes
  Size of memory requested form the block.
  
\param label
  Label to put in the node allocated.

\return
  Address of the node allocated into the list.
  
*/
/*****************************************************************************/
void *allocate_firstfit(block_info *heap, size_t bytes, char *label)
{
    /* pointer to node if needed */
  block_info *carve;
  
    /* iterate list */
  while(heap)
  {
      /* perfect match */
    if(heap->size == bytes && !heap->allocated)
    {
        /* set allocation flag to 1*/
      heap->allocated = 1;
      
        /* copy label desired */
      strncpy(heap->label, label, LABEL_SIZE);
      
      
      /* since this node was already allocated just no longer used,
       * the other fields will already have correct data */
      
        /* return address of this block */
      return heap->address;
    }
    
      /* found a chunk that will fit, but will have to carve in two */
    if(heap->size > bytes && !heap->allocated)
    {
        /* create a node to carve out the empty space */
      carve = malloc(sizeof(block_info));
      
        /* allocation flag set to 0 */
      carve->allocated = 0;
      
        /* calculate remaining size */
      carve->size = heap->size - bytes;
      
        /* calculate address */
      carve->address = heap->address + bytes;
        
        /* copy label free into empty block */
      strncpy(carve->label, "FREE", LABEL_SIZE);
      
        /* link up to list */
      carve->next = heap->next;
      
      /* now adjust heap node for allocation */
      
      
        /* allocation flag set to 1 */
      heap->allocated = 1;
      
        /* set number of bytes for this block */
      heap->size = bytes;
      
        /* copy label into the node */
      strncpy(heap->label, label, LABEL_SIZE);
      
        /* link up to list */
      heap->next = carve;
      
        /* return address of allocated node */
      return heap->address;
    }
    
      /* move pointer */
    heap = heap->next;
  }
  
    /* reached of of list with no suitable allocations
     * return null */
  return NULL;
}

/*****************************************************************************/
/*!

\brief
  Allocates nodes usign best fit algorithm.

\param heap
  List to allocate in.
  
\param bytes
  Size of memory requested form the block.
  
\param label
  Label to put in the node allocated.

\return
  Address of the node allocated into the list.
*/
/*****************************************************************************/
void *allocate_bestfit(block_info *heap, size_t bytes, char *label)
{
  size_t difference = -1;
  block_info *best_fit = 0, *carve;
  
  while(heap)
  {
      /* found perfect match, plug in right here */
    if(heap->allocated == 0 && heap->size == bytes)
    {
        /* set allocation flag */
      heap->allocated = 1;
      
        /* copy label */
      strncpy(heap->label, label, LABEL_SIZE);
      
        /* return address of allocated node */
      return heap->address;
    }
    
    if(heap->allocated == 0 && 
       heap->size > bytes &&
       heap->size - bytes < difference)
    {
      difference = heap->size - bytes;
      best_fit = heap;
    }
    
    heap = heap->next;
  }
  
  if(!best_fit)
    return NULL;
  
  carve = malloc(sizeof(block_info));
  
  carve->allocated = 0;
  
  carve->size = best_fit->size - bytes;
  
  carve->address = best_fit->address + bytes;
  
  strncpy(carve->label, "FREE", LABEL_SIZE);
  
  carve->next = best_fit->next;
  
  best_fit->allocated = 1;
  
  best_fit->size = bytes;
  
  strncpy(best_fit->label, label, LABEL_SIZE);
  
  best_fit->next = carve;
  
  return best_fit->address;
  
}

/*****************************************************************************/
/*!

\brief
  Allocates node in the list. Just passes off to coreespoinding policy function
  to do the work.

\param heap
  List to allocate in.
  
\param bytes
  Size of memory requested form the block.
  
\param label
  Label to put in the node allocated.

\return
  Address of node allocated into the list.
*/
/*****************************************************************************/
void *mm_allocate(block_info *heap, size_t bytes, char *label)
{
    /* if first fit call allocate function for first fit */
  if(mem_policy == mmpFirstFit)
    return allocate_firstfit(heap, bytes, label);
  
    /* if best fit call allocate function for best fit */
  else if (mem_policy == mmpBestFit)
    return allocate_bestfit(heap, bytes, label);
  
    
    /* requested unknown memory allocation policy
     * return null */
  return NULL;
}

/*****************************************************************************/
/*!

\brief
  Deallocates a node from the manager.

\param heap
  List to deallocate from.
  
\param address
  Address of the node to remove
  
\return
  Returns SUCCESS for successful deletion and FAILURE for unsuccessful removal.
*/
/*****************************************************************************/
int mm_deallocate(block_info *heap, void *address)
{
    /* pointer to trail heap for possible merge */
  block_info *previous = heap;
  
    /* temp pointer for use in merging in front */
  block_info *temp;
  
    /* copy address requested into char ptr for comparison */
  char* address_del = (char*) address;
  
    /* iterate over list */
  while(heap)
  {
      /* record current address */
    char *address_check = heap->address;
    
      /* if we found block requested*/
    if(address_check == address_del)
    {
        /* bloack has already been deallocated,
         * return failure for second attempt */
      if(heap->allocated == 0)
        return FAILURE;
        
        /* set allocation flag to 0 */
      heap->allocated = 0;
      
        /* check node in front of current for merging */
      if(heap->next && heap->next->allocated == 0)
      {
          /* add size to current node */
        heap->size += heap->next->size;
        
          /* grab pointer to node being merged */
        temp = heap->next;
        
          /* skip over node being merged */
        heap->next = heap->next->next;
        
          /* free merged node */
        free(temp);
      }
        /* check node behind for merging */
      if(previous != heap && previous->allocated == 0)
      {
          /* merge sizes */
        previous->size += heap->size;
        
          /* link list */
        previous->next = heap->next;
        
          /* free node being merged */
        free(heap);
      }
        /* return successful deallocation */
      return SUCCESS;
    }
    
      /* move to next node */
    previous = heap;
    heap = heap->next;
  }
  
    /* reached end of list */
  return FAILURE;
}

/*****************************************************************************/
/*!

\brief
  Destroys manager and all memory being used.

\param heap
  The manager to destroy.

*/
/*****************************************************************************/
void mm_destroy(block_info *heap)
{
    /* temp pointer to traverse list */
  block_info *temp;
  
    /* free chunk of memory alloc'ed in create */
  free(heap->address);
    
  while(heap)
  {
      /* set temp to next node */
    temp = heap->next;
    
      /* free current node */
    free (heap);
    
      /* move to next node */
    heap = temp;
  }
}