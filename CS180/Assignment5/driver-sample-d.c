#include <stdio.h>  /* printf, sprintf, fopen, fclose, FILE */
#include <stdlib.h> /* malloc, free, rand, srand, atoi      */
#include <string.h> /* strcpy, strcat, memset               */
#include <dlfcn.h>  /* dl stuff                             */

#include "memmgr.h"
#include "shared.h"

#define DUMP(x) mm_dump(x, 0)
#define GRAPHVIZx

static MMPolicy gPolicy = mmpFirstFit;
static int gPrintValues = false;

static void *gLib;

static MM_CREATE mmlib_create;
static MM_ALLOCATE mmlib_allocate;
static MM_DEALLOCATE mmlib_deallocate;
static MM_DESTROY mmlib_destroy;

void mm_dump(block_info *heap, int show_address)
{
  int allocated = 0, alloc_blocks = 0;
  int unallocated = 0, unalloc_blocks = 0;

  if (!heap)
    return;

  printf("=========================================\n");
  while (heap)
  {
    printf("    label: %s\n", heap->label);
    if (show_address)
      printf("  address: %p\n", heap->address);
    else
      printf("  address: 0x000000\n");
    printf("     size: %lu\n", (long unsigned)heap->size);
    printf("allocated: %s\n", heap->allocated ? "true" : "false");
    printf("--\n");
    if (heap->allocated)
    {
      allocated += heap->size;
      alloc_blocks++;
    }
    else
    {
      unallocated += heap->size;
      unalloc_blocks++;
    }

    heap = heap->next;
  }
  printf("Allocated bytes: %8i [blocks: %5i]\n", allocated, alloc_blocks);
  printf("     Free bytes: %8i [blocks: %5i]\n", unallocated, unalloc_blocks);
}


void mm_dump_gv(block_info *heap, const char *filename)
{
  FILE *fp;
  int count = 0;
  char *buffer;
  char id[32];
  block_info *save = heap;

  if (!heap)
    return;

  if ((fp = fopen(filename, "wt")) == NULL)
    return;

    /* Preamble */
  fprintf(fp, "digraph g {\n");
  fprintf(fp, "graph [rankdir = \"LR\"];\n");
  fprintf(fp, "node [fontsize = \"12\" shape = \"record\"];\n");
  fprintf(fp, "edge [arrowhead = \"normal\"];\n");
  fprintf(fp, "\n");

    /* How many nodes do we have? */
  while (heap)
  {
    count++;
    heap = heap->next;
  }

    /* Allocate  20 bytes per node, for the id/label */
  if ((buffer = malloc(20 * count + 200)) == NULL)
  {
    fclose(fp);
    return;
  }

  heap = save;
  count = 0;
  while (heap)
  {
    char next[32], node[32], nnode[32];
    count++;
    if (heap->next)
      sprintf(next, "%p", (void *)heap->next);
    else
      strcpy(next, "NULL");

    sprintf(node, "node%i", count);
    sprintf(nnode, "node%i", count + 1);

      /* Create the node */
    sprintf(buffer, "%s [label = \"<f1> %i | <f2> %p | <f3> %lu | <f4> %s | <f5> %s\" shape=record];\n", 
            node,
            heap->allocated ? 1 : 0,
            heap->address,
            (long unsigned)heap->size,
            heap->label,
            next);
    fprintf(fp, "%s", buffer);

      /* If there is a next node, create an edge to it */
    if (heap->next)
    {
      sprintf(buffer, "%s:f5->%s:f1;\n", node, nnode);
      fprintf(fp, "%s", buffer);
    }

    heap = heap->next;
  }

    /* Create the real "heap" node */
  strcpy(buffer, "memory [label = \"");
  heap = save;
  count = 0;
  while (heap)
  {
    count++;
    if (heap->allocated)
      sprintf(id, "<f%i> allocated", count);
    else
      sprintf(id, "<f%i> free", count);

    strcat(buffer, id);
    if (heap->next)
      strcat(buffer, "|");
    heap = heap->next;
  }
  strcat(buffer, "}\"];");
  fprintf(fp, "%s\n", buffer);

    /* Create all of the edges from the heap blocks to the memory */
  heap = save;
  count = 0;
  while (heap)
  {
    count++;
    sprintf(buffer, "node%i:f2->memory:f%i;\n", count, count);
    fprintf(fp, "%s", buffer);
    heap = heap->next;
  }
  fprintf(fp, "}\n");

  fclose(fp);
  free(buffer);
}


void DUMP_GV(block_info *heap, const char *filename)
{
  #ifdef GRAPHVIZ
  mm_dump_gv(heap, filename);
  #endif
  if (heap && filename)
    return;
}

int RandomInt(int low, int high)
{
  int number;
  number = rand() % (high - low + 1) + low;
  return number;
}

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

static void *Allocate(block_info *heap, int size, char *label)
{
  char *block = mmlib_allocate(heap, size, label);
  if (!block)
  {
    printf("********** Allocation failed. **********\n");
    return NULL;
  }

  memset(block, 'A', size - 1);
  block[size - 1] = '\0';
  if (gPrintValues)
    printf("%s\n", block);

  return block;
}

void Deallocate(block_info *heap, void *block)
{
  if (mmlib_deallocate(heap, block) == FAILURE)
    printf("********** Deallocation failed. **********\n");
}

void test_alloc1(void)
{
  block_info *heap;
  gPrintValues = true;
  printf("\n<<<<<<<< test_alloc1 >>>>>>>>\n");

  heap = mmlib_create(300, gPolicy);
    DUMP(heap);
  DUMP_GV(heap, "gv_alloc1.txt");
  mmlib_destroy(heap);
}

void test_alloc2(void)
{
  block_info *heap;
  gPrintValues = true;
  printf("\n<<<<<<<< test_alloc2 >>>>>>>>\n");

  heap = mmlib_create(300, gPolicy);
    DUMP(heap);
    Allocate(heap, 30, "one");
    DUMP(heap);
  DUMP_GV(heap, "gv_alloc2.txt");
  mmlib_destroy(heap);
}

void test_alloc3(void)
{
  block_info *heap;
  gPrintValues = true;
  printf("\n<<<<<<<< test_alloc3 >>>>>>>>\n");

  heap = mmlib_create(300, gPolicy);

    DUMP(heap);

    Allocate(heap, 10, "one");
    DUMP(heap);

    Allocate(heap, 20, "two");
    DUMP(heap);

    Allocate(heap, 25, "three");
    DUMP(heap);

    Allocate(heap, 30, "four");
    DUMP(heap);

    Allocate(heap, 35, "five");
    DUMP(heap);

    Allocate(heap, 30, "six");
    DUMP(heap);

    Allocate(heap, 20, "seven");
    DUMP(heap);

  DUMP_GV(heap, "gv_alloc3.txt");
  mmlib_destroy(heap);
}

void test_alloc4(void)
{
  block_info *heap;
  gPrintValues = true;
  printf("\n<<<<<<<< test_alloc4 >>>>>>>>\n");

  heap = mmlib_create(30, gPolicy);

    DUMP(heap);
    Allocate(heap, 30, "one");
    DUMP(heap);

  DUMP_GV(heap, "gv_alloc4.txt");
  mmlib_destroy(heap);
}

void test_alloc5(void)
{
  block_info *heap;
  gPrintValues = true;
  printf("\n<<<<<<<< test_alloc5 >>>>>>>>\n");

  heap = mmlib_create(50, gPolicy);

    DUMP(heap);
    Allocate(heap, 60, "one");
    DUMP(heap);

  DUMP_GV(heap, "gv_alloc5.txt");
  mmlib_destroy(heap);
}


void test_alloc6(void)
{
  block_info *heap;
  gPrintValues = true;
  printf("\n<<<<<<<< test_alloc6 >>>>>>>>\n");

  heap = mmlib_create(150, gPolicy);

    DUMP(heap);

    Allocate(heap, 20, "one");
    DUMP(heap);

    Allocate(heap, 30, "two");
    DUMP(heap);

    Allocate(heap, 40, "three");
    DUMP(heap);

    Allocate(heap, 30, "four");
    DUMP(heap);

    Allocate(heap, 20, "five");
    DUMP(heap);

    Allocate(heap, 30, "six");
    DUMP(heap);

    Allocate(heap, 20, "seven");
    DUMP(heap);

  DUMP_GV(heap, "gv_alloc6.txt");
  mmlib_destroy(heap);
}

void test_dealloc1(void)
{
  block_info *heap;
  void *block;
  gPrintValues = false;
  printf("\n<<<<<<<< test_dealloc1 >>>>>>>>\n");

  heap = mmlib_create(100, gPolicy);

    DUMP(heap);
    block = Allocate(heap, 10, "one");
    DUMP(heap);
    Deallocate(heap, (char *)block);
    DUMP(heap);

  DUMP_GV(heap, "gv_dealloc1.txt");
  mmlib_destroy(heap);
}

void test_dealloc2(void)
{
  block_info *b[10];
  block_info *heap;
  gPrintValues = false;
  printf("\n<<<<<<<< test_dealloc2 >>>>>>>>\n");

  heap = mmlib_create(100, gPolicy);

    b[1] = Allocate(heap, 10, "one");
           Allocate(heap, 20, "two");
    b[3] = Allocate(heap, 30, "three");
           Allocate(heap, 15, "four");
    b[5] = Allocate(heap, 10, "five");
    DUMP(heap);

    Deallocate(heap, b[1]);
    DUMP(heap);

    Deallocate(heap, b[3]);
    DUMP(heap);

    Deallocate(heap, b[5]);
    DUMP(heap);

  DUMP_GV(heap, "gv_dealloc2.txt");
  mmlib_destroy(heap);
}

void test_dealloc3(void)
{
  block_info *b[10];
  block_info *heap;
  gPrintValues = false;
  printf("\n<<<<<<<< test_dealloc3 >>>>>>>>\n");

  heap = mmlib_create(100, gPolicy);

           Allocate(heap, 10, "one");
    b[2] = Allocate(heap, 20, "two");
    b[3] = Allocate(heap, 30, "three");
           Allocate(heap, 15, "four");
           Allocate(heap, 10, "five");
    DUMP(heap);

    Deallocate(heap, b[2]);
    DUMP(heap);

    Deallocate(heap, b[3]);
    DUMP(heap);

  DUMP_GV(heap, "gv_dealloc3.txt");
  mmlib_destroy(heap);
}

void test_dealloc4(void)
{
  block_info *b[10];
  block_info *heap;
  gPrintValues = false;
  printf("\n<<<<<<<< test_dealloc4 >>>>>>>>\n");

  heap = mmlib_create(100, gPolicy);

           Allocate(heap, 10, "one");
    b[2] = Allocate(heap, 20, "two");
    b[3] = Allocate(heap, 30, "three");
           Allocate(heap, 15, "four");
           Allocate(heap, 10, "five");
    DUMP(heap);

    Deallocate(heap, b[3]);
    DUMP(heap);

    Deallocate(heap, b[2]);
    DUMP(heap);

  DUMP_GV(heap, "gv_dealloc4.txt");
  mmlib_destroy(heap);
}

void test_dealloc5(void)
{
  block_info *b[10];
  block_info *heap;
  gPrintValues = false;
  printf("\n<<<<<<<< test_dealloc5 >>>>>>>>\n");

  heap = mmlib_create(100, gPolicy);

    b[1] = Allocate(heap, 10, "one");
    b[2] = Allocate(heap, 20, "two");
    b[3] = Allocate(heap, 30, "three");
    b[4] = Allocate(heap, 15, "four");
    b[5] = Allocate(heap, 10, "five");
    DUMP(heap);

    Deallocate(heap, b[1]);
    DUMP(heap);

    Deallocate(heap, b[3]);
    DUMP(heap);

    Deallocate(heap, b[5]);
    DUMP(heap);

    Deallocate(heap, b[4]);
    DUMP(heap);

    Deallocate(heap, b[2]);
    DUMP(heap);

  DUMP_GV(heap, "gv_dealloc5.txt");
  mmlib_destroy(heap);
}

void test_ada1(void)
{
  block_info *b[10];
  block_info *heap;
  gPrintValues = false;
  printf("\n<<<<<<<< test_ada1 >>>>>>>>\n");

  heap = mmlib_create(1000, gPolicy);

    b[1] = Allocate(heap, 100, "one");
    b[2] = Allocate(heap, 200, "two");
    b[3] = Allocate(heap, 50, "three");
    b[4] = Allocate(heap, 50, "four");
    b[5] = Allocate(heap, 100, "five");
    b[6] = Allocate(heap, 500, "six");

    Deallocate(heap, b[2]);
    Deallocate(heap, b[4]);
    DUMP(heap);

    Allocate(heap, 50, "seven");
    DUMP(heap);
    Allocate(heap, 200, "eight");
    DUMP(heap);

  DUMP_GV(heap, "gv_ada1.txt");
  mmlib_destroy(heap);
}

void test_ada2(void)
{
  block_info *b[20];
  block_info *heap;
  gPrintValues = false;
  printf("\n<<<<<<<< test_ada2 >>>>>>>>\n");

  heap = mmlib_create(1200, gPolicy);

    b[1] = Allocate(heap, 100, "one");
    b[2] = Allocate(heap, 200, "two");
    b[3] = Allocate(heap, 300, "three");
    b[4] = Allocate(heap, 100, "four");
    b[5] = Allocate(heap, 100, "five");
    b[6] = Allocate(heap, 50, "six");
    b[7] = Allocate(heap, 50, "seven");
    b[8] = Allocate(heap, 200, "eight");
    DUMP(heap);

    Deallocate(heap, b[1]);
    Deallocate(heap, b[3]);
    Deallocate(heap, b[5]);
    Deallocate(heap, b[7]);
    DUMP(heap);

    b[9] = Allocate(heap, 100, "nine");
    DUMP(heap);
    b[10] = Allocate(heap, 10, "ten");
    DUMP(heap);
    b[11] = Allocate(heap, 100, "eleven");
    DUMP(heap);
    b[12] = Allocate(heap, 40, "twelve");
    DUMP(heap);
    b[13] = Allocate(heap, 50, "thirteen");
    DUMP(heap);
    b[14] = Allocate(heap, 150, "fourteen");
    DUMP(heap);
    b[15] = Allocate(heap, 150, "fifteen");
    DUMP(heap);

  DUMP_GV(heap, "gv_ada2.txt");
  mmlib_destroy(heap);
}

void setup(void)
{
  const char *fn_names[] = {"mm_create", "mm_destroy", "mm_allocate", "mm_deallocate"};
  LibraryFunctions funs;
  int error;

  error = load_library("./libmemmgr.so", &gLib);
  if (error == FAILURE)
  {
    printf("load_library failed! %s\n", dlerror());
    exit(-1);
  }

  error = get_functions(gLib, &funs, fn_names);
  if (error == FAILURE)
  {
    printf("get_functions failed! %s\n", dlerror());
    exit(-1);
  }

  mmlib_create = funs.create;
  mmlib_destroy = funs.destroy;
  mmlib_allocate = funs.allocate;
  mmlib_deallocate = funs.deallocate;
}

void teardown(void)
{
  dlclose(gLib);
}

int main(int argc, char **argv)
{
  unsigned test = 0;
  unsigned policy = 0;
  unsigned count;
  void (*fp[])(void) = {
                        test_alloc1,   /*  1 */
                        test_alloc2,   /*  2 */
                        test_alloc3,   /*  3 */
                        test_alloc4,   /*  4 */
                        test_alloc5,   /*  5 */
                        test_alloc6,   /*  6 */
                        test_dealloc1, /*  7 */
                        test_dealloc2, /*  8 */
                        test_dealloc3, /*  9 */
                        test_dealloc4, /* 10 */
                        test_dealloc5, /* 11 */
                        test_ada1,     /* 12 */
                        test_ada2      /* 13 */
                       };

  count = sizeof(fp) / sizeof(*fp);

  srand(4);

  if (argc > 1)
    test = atoi(argv[1]);
  if (argc > 2)
    policy = atoi(argv[2]);

  if (test > count)
    test = 0;

  if (policy)
    gPolicy = mmpBestFit;
  else
    gPolicy = mmpFirstFit;

  setup();
  
  if (test)
    fp[test - 1]();
  else
  {
    unsigned i;
    for (i = 0; i < count; i++)
      fp[i]();
  }

  /*
  test_alloc1();
  test_alloc2();
  test_alloc3();
  test_alloc4();
  test_alloc5();
  test_alloc6();
  test_dealloc1();
  test_dealloc2();
  test_dealloc3();
  test_dealloc4();
  test_dealloc5();
  test_ada1();
  */
 
  /*printf("policy is %s fit\n", policy ? "best" : "first");*/

  teardown();
  return 0;
}

