/*****************************************************************************/
/*!
\file memmgr.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par Assignment 5
\date 7/8/15

\brief
  Header file for memory manager. Contains struct definition for linked list
  and function prototypes.

*/
/*****************************************************************************/


#ifndef MEMMGR_H
#define MEMMGR_H

#include <stddef.h> /* size_t  */

  /*! max size of label */
#define LABEL_SIZE 16

  /*! struct that contains node information for manager */
typedef struct block_info
{
  int allocated;            /*!< flag if this node is allocated    */
  size_t size;              /*!< size of memory this node is using */
  char *address;            /*!< address of the node in the list   */
  char label[LABEL_SIZE];   /*!< label of the node                 */
  struct block_info *next;  /*!< pointer to the next node          */
}block_info;

  /*!psuedo booleans (not used?) */
#define false 0

  /*!psuedo booleans (not used?) */
#define true 1

  /*! Definition used in deallocte function return value */
#define SUCCESS 0

  /*! Definition used in deallocte function return value */
#define FAILURE -1

  /* policies for allocates */
typedef enum MMPolicy {mmpFirstFit, mmpBestFit} MMPolicy;


  /* creates block of memory to manage */
block_info *mm_create(size_t bytes, enum MMPolicy policy);

  /* allocates nodes into the list */
void *mm_allocate(block_info *heap, size_t bytes, char *label);

  /* allocates node using first fit algorithm */
void *allocate_firstfit(block_info *heap, size_t bytes, char *label);

  /* allocates node using best fit algorithm */
void *allocate_bestfit(block_info *heap, size_t bytes, char *label);

  /* removes node from manager */
int mm_deallocate(block_info *heap, void *address);

  /* deallocates all memory from the manager */
void mm_destroy(block_info *heap);

#endif
