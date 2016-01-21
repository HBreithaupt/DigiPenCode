/* sample-driver-stress1.c */

#include <stdio.h>  /* printf, sprintf */
#include <stdlib.h> /* rand, srand     */
#include <string.h> /* memset          */
#include "memmgr.h"

static enum MMPolicy gPolicy = mmpFirstFit;
static int gPrintValues = false;

void mm_dump(block_info *heap, int show_address, int stats_only)
{
  int allocated = 0, alloc_blocks = 0;
  int unallocated = 0, unalloc_blocks = 0;

  if (!heap)
    return;

  printf("=========================================\n");
  while (heap)
  {
    if (!stats_only)
    {
      printf("    label: %s\n", heap->label);
      if (show_address)
        printf("  address: %p\n", heap->address);
      else
        printf("  address: 0x000000\n");
      printf("     size: %lu\n", heap->size);
      printf("allocated: %s\n", heap->allocated ? "true" : "false");
      printf("--\n");
    }

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
  char *block = mm_allocate(heap, size, label);
  if (!block)
  {
    printf("********** Allocation failed. [%s] **********\n", label);
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
  if (mm_deallocate(heap, block) == FAILURE)
    printf("********** Deallocation failed. **********\n");
}

#define VERBOSE
void stress1(void)
{
  block_info *heap;
  block_info **blocks;
  int count = 0;
  int i;
  int base_count = 10000;
  int num_allocs = 800;
  int block_sizes[] = {12, 8, 20, 8};
  
  blocks = calloc(base_count * 2, sizeof(block_info));

  gPrintValues = false;
  heap = mm_create(base_count, gPolicy);

  for (i = 0; i < num_allocs; i++)
  {
    int sz = block_sizes[i % 4];
    char label[LABEL_SIZE];

    sprintf(label, "%6i:%6i", count + 1, sz);
    blocks[count++] = Allocate(heap, sz, label);
  }
  #ifdef VERBOSE
  printf("-------------------- First Allocation --------------------\n");
  mm_dump(heap, 0, 0);
  #endif

  for (i = 0; i < num_allocs * .5; i++)
  {
    int r = i * 2;

    Deallocate(heap, blocks[r]);
    blocks[r] = NULL;
    /*printf("freeing %i\n", r);*/
    /*mm_dump(heap, 0, 1);*/
  }
  #ifdef VERBOSE
  printf("-------------------- First Deallocation --------------------\n");
  mm_dump(heap, 0, 0);
  #endif

  for (i = 0; i < num_allocs * .25; i++)
  {
    int sz = block_sizes[0];
    char label[LABEL_SIZE];

    sprintf(label, "%6i:%6i", count + 1, sz);
    blocks[count++] = Allocate(heap, sz, label);
    /*printf("allocating size %i\n", sz);*/
    /*mm_dump(heap, 0, 1);*/
  }
  for (i = 0; i < num_allocs * .274; i++)
  {
    int sz = block_sizes[2];
    char label[LABEL_SIZE];

    sprintf(label, "%6i:%6i", count + 1, sz);
    blocks[count++] = Allocate(heap, sz, label);
    /*printf("allocating size %i\n", sz);*/
    /*mm_dump(heap, 0, 1);*/
  }
  printf("-------------------- Second Allocation --------------------\n");
  mm_dump(heap, 0, 0);

  free(blocks);
  mm_destroy(heap);
}

int main(int argc, char **argv)
{
  srand(4);

  if (argc > 1)
    if (atoi(argv[1]))
      gPolicy = mmpBestFit;

  stress1();

  return 0;
}
