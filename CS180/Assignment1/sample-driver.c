#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include "PRNG.h"
#include "slist.h"

void SwapInt(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void Shuffle(int *array, int count)
{
  int i;
  for (i = 0; i < count; i++)
  {
    int r = RandomInt(0, count - 1);
    SwapInt(&array[i], &array[r]);
  }
}

void PrintArray(int *array, int count)
{
  int i;
  for (i = 0; i < count; i++)
    printf("%i  ", array[i]);
  printf("\n");
}

void test_add1(void)
{
  sll_node *list = NULL;

  list = sll_add(list, 1, "one");
  list = sll_add(list, 2, "two");
  list = sll_add(list, 3, "three");
  list = sll_add(list, 4, "four");
  list = sll_add(list, 5, "five");
  list = sll_add(list, 6, "six");
  list = sll_add(list, 7, "seven");

  sll_dump(list);
  sll_destroy(list);
}

void test_remove1(void)
{
  sll_node *list = NULL;

  list = sll_add(list, 1, "one");
  list = sll_add(list, 2, "two");
  list = sll_add(list, 3, "three");
  list = sll_add(list, 4, "four");
  list = sll_add(list, 5, "five");
  list = sll_add(list, 6, "six");
  list = sll_add(list, 7, "seven");
  sll_dump(list);

  list = sll_remove(list, 4);
  sll_dump(list);

  list = sll_remove(list, 5);
  sll_dump(list);

  list = sll_remove(list, 1);
  sll_dump(list);

  list = sll_remove(list, 7);
  sll_dump(list);

  sll_destroy(list);
}


void test_remove2(void)
{
  sll_node *list = NULL;

  list = sll_add(list, 1, "one");
  list = sll_add(list, 2, "two");
  list = sll_add(list, 3, "three");
  list = sll_add(list, 4, "four");
  list = sll_add(list, 5, "five");
  list = sll_add(list, 6, "six");
  list = sll_add(list, 7, "seven");
  sll_dump(list);

  list = sll_remove(list, 99);
  sll_dump(list);

  list = sll_remove(list, 4);
  sll_dump(list);

  list = sll_remove(list, 5);
  sll_dump(list);

  list = sll_remove(list, 1);
  sll_dump(list);

  list = sll_remove(list, 7);
  sll_dump(list);

  list = sll_remove(list, 3);
  sll_dump(list);

  list = sll_remove(list, 6);
  sll_dump(list);

  list = sll_remove(list, 2);
  sll_dump(list);

  list = sll_remove(list, 1);
  sll_dump(list);

  sll_destroy(list);
}

void test_insert_before1(void)
{
  sll_node *list = NULL;

  list = sll_add(list, 1, "one");
  list = sll_add(list, 2, "two");
  list = sll_add(list, 3, "three");
  list = sll_add(list, 4, "four");
  sll_dump(list);

  list = sll_insert_before(list, 3, 101, "fred");
  sll_dump(list);

  list = sll_insert_before(list, 1, 102, "barney");
  sll_dump(list);

  list = sll_insert_before(list, 4, 103, "wilma");
  sll_dump(list);

  list = sll_insert_before(list, 102, 104, "betty");
  sll_dump(list);

  list = sll_insert_before(list, 1000, 105, "dino");
  sll_dump(list);

  sll_destroy(list);
}

void test_insert_after1(void)
{
  sll_node *list = NULL;

  list = sll_add(list, 1, "one");
  list = sll_add(list, 2, "two");
  list = sll_add(list, 3, "three");
  list = sll_add(list, 4, "four");
  sll_dump(list);

  sll_insert_after(list, 2, 101, "fred");
  sll_dump(list);

  sll_insert_after(list, 4, 102, "barney");
  sll_dump(list);

  sll_insert_after(list, 1, 103, "wilma");
  sll_dump(list);

  sll_insert_after(list, 102, 104, "betty");
  sll_dump(list);

  sll_insert_after(list, 1000, 105, "dino");
  sll_dump(list);

  sll_destroy(list);
}

#define VERBOSEx
void test_stress1(void)
{
  #define SIZE 4500
  sll_node *list = NULL;
  int i, count = 0;
  int *a = malloc(2 * SIZE * sizeof(int));
  char buf[LABEL_SIZE];

  for (i = 0; i < SIZE; i++)
  {
    a[count++] = i + 1;
    sprintf(buf, "%08i", a[i]);
    list = sll_add(list, a[i], buf);  
  }
  #ifdef VERBOSE
  sll_dump(list);
  #endif

  for (i = 0; i < SIZE; i++)
  {
    int r1 = RandomInt(0, 1);
    int r2 = RandomInt(1, count);
    a[count] = count + 1;
    count++;
    sprintf(buf, "%08i", count);

    if (r1)
      list = sll_insert_before(list, r2, count, buf);
    else
      sll_insert_after(list, r2, count, buf);

    #ifdef VERBOSE
    sll_dump(list);
    printf("%s %i", r1 ? "before" : "after", r2);
    #endif
  }
  #ifdef VERBOSE
  sll_dump(list);
  #endif

  /*PrintArray(a, count);*/
  Shuffle(a, count);
  /*PrintArray(a, count);*/

  for (i = 0; i < 2 * SIZE - 20; i++)
  {
    list = sll_remove(list, a[i]);
    #ifdef VERBOSE
    sll_dump(list);
    #endif
  }

  sll_dump(list);
  sll_destroy(list);

  free(a);
}

int main(int argc, char **argv)
{
  unsigned test = 0;
  unsigned count;
  void (*fp[])(void) = {
                        test_add1,           /*  1 */
                        test_remove1,        /*  2 */
                        test_remove2,        /*  3 */
                        test_insert_before1, /*  4 */
                        test_insert_after1,  /*  5 */
                        test_stress1         /*  6 */
                       };

  count = sizeof(fp) / sizeof(*fp);

  ut_srand(1, 0);

  if (argc > 1)
    test = atoi(argv[1]);

  if (test > count)
    test = 0;

  if (test)
    fp[test - 1]();
  else
  {
    unsigned i;
    for (i = 0; i < count; i++)
      fp[i]();
  }

  /*  
  test_add1();
  test_remove1();
  test_remove2();
  test_insert_before1();
  test_insert_after1();
  test_stress1();
  */

  return 0;
}
