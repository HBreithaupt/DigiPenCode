/*****************************************************************************/
/*!
\file slist.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par Assignment 1
\date 5/15/15

\brief
  Function prototypes for slist.c.

*/
/*****************************************************************************/

  /* hard code label size for the nodes */
#define LABEL_SIZE 16

  /* defintion of node struct being used */
typedef struct sll_node
{
  char label[LABEL_SIZE];
  int value;
  struct sll_node* next;
}sll_node;

  /* adds a node to the end of the list */
sll_node *sll_add(sll_node *list, int value, const char *label);

  /* removes first occurence of a node with passed value */
sll_node *sll_remove(sll_node *list, int search_value);

  /* inserts a node before a node in the list with a certain value */
sll_node *sll_insert_before(sll_node *list, int search_value, 
                            int value, const char *label);

  /* inserts a node after a node in the list with a certain value*/
void sll_insert_after(sll_node *list, int search_value, 
                      int value, const char *label);

  /* destroys a list */
void sll_destroy(sll_node *list);

  /* prints out a list */
void sll_dump(const sll_node *list);
