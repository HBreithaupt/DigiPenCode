#include <stdio.h>  /* printf */
#include <stdlib.h> /* atoi   */
#include "list.h"

void test_add_front(void)
{
  int i;
  struct Node *list = NULL;

  for (i = 1; i <= 10; i++)
  {
    printf("add %2i to front: ", i);
    add_front(&list, i);
    print_list(list);
  }

  free_list(list);
}

void test_add_back(void)
{
  int i;
  struct Node *list = NULL;

  for (i = 1; i <= 10; i++)
  {
    printf("add %2i to back: ", i);
    add_back(&list, i);
    print_list(list);
  }

  free_list(list);
}

void test_add_front_back(void)
{
  int i;
  struct Node *list = NULL;

  for (i = 1; i <= 5; i++)
  {
    printf("add %2i to front and back: ", i);
    add_front(&list, i);
    add_back(&list, i);
    print_list(list);
  }

  free_list(list);
}

void test_remove(void)
{
  int i;
  struct Node *list = NULL;
  int items[] = {5, 6, 10, 9, 2, 1, 3, 7, 8, 4};

    /* Populate the list */
  for (i = 1; i <= 10; i++)
    add_front(&list, i);

  printf("Start list : ");
  print_list(list);

    /* These values don't exist, but you need to handle that */
  remove_item(&list, 100);
  remove_item(&list, 99);

    /* Remove "random" order */
  for (i = 0; i < 10; i++)
  {
    printf("Removing %2i: ", items[i]);
    remove_item(&list, items[i]);
    print_list(list);
  }

    /* List should empty, but this is legal */
  printf("Removing  0: ");
  remove_item(&list, 1); 
  print_list(list);

#if 1
  free_list(list); /* should be empty at this point           */
  free_list(NULL); /* This is legal and you need to handle it */
#endif
}

void test_size(void)
{
  int i;
  struct Node *list = NULL;

  printf("Size is %2i: ", size_list(list));
  print_list(list);

  for (i = 1; i <= 10; i++)
  {
    add_front(&list, i);
    printf("Size is %2i: ", size_list(list));
    print_list(list);
  }

  free_list(list);
}

void test_sum(void)
{
  int i, sum = 0;
  struct Node *list = NULL;

  for (i = 1; i <= 10; i++)
    add_front(&list, i);

  sum = sum_list(list);
  print_list(list);
  printf("Sum is %i\n", sum);
  free_list(list);
}

int main(int argc, char **argv)
{
  int test = 0;
  if (argc > 1)
    test = atoi(argv[1]);

  switch (test)
  {
    case 1:
      printf("\ntest_add_front ========================================\n");
      test_add_front();
      break;
    case 2:
      printf("\ntest_size ========================================\n");
      test_size();
      break;
    case 3:
      printf("\ntest_sum ========================================\n");
      test_sum();
      break;

    case 4:
      printf("\ntest_add_back ========================================\n");
      test_add_back();
      break;

    case 5:
      printf("\ntest_add_front_back ========================================\n");
      test_add_front_back();
      break;
  
    case 6:
      printf("\ntest_remove ========================================\n");
      test_remove();
      break;

    default:
      printf("\ntest_add_front ========================================\n");
      test_add_front();
      printf("\ntest_size ========================================\n");
      test_size();
      printf("\ntest_sum ========================================\n");
      test_sum();
      printf("\ntest_add_back ========================================\n");
      test_add_back();
      printf("\ntest_add_front_back ========================================\n");
      test_add_front_back();
      printf("\ntest_remove ========================================\n");
      test_remove();
      break;
  }

  return 0;
}
