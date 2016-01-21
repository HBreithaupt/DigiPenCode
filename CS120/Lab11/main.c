#include <stdio.h> /* printf */

/* Prototype from tablen.c */
void tablen(const char *filename);

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Usage: tablen filename\n");
    printf("where: filename - file to process.\n");
    return -1;
  }

  tablen(argv[1]);

  return 0;
}