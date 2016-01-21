#include <stdio.h>  /* printf */
#include <string.h> /* strlen */

/* Prototype for the dumper function */
void format(const char* inbuf, char *outbuf, int count, int start);
void dump(const char *filename);

void test_format(void)
{
  int i;

  char *input = "Violets are blue";
  char buffer[16];
  char output[75];

  format(input, output, strlen(input), 0);
  printf("%s\n", output);
  format(input, output, strlen(input), 16);
  printf("%s\n", output);
  format(input, output, strlen(input), 32);
  printf("%s\n", output);
  printf("\n");

  input = "Roses are red\n";
  format(input, output, strlen(input), 0);
  printf("%s\n", output);
  format(input, output, strlen(input), 16);
  printf("%s\n", output);
  format(input, output, strlen(input), 32);
  printf("%s\n", output);
  printf("\n");

  input = "Green\teggs\n";
  format(input, output, strlen(input), 0);
  printf("%s\n", output);
  format(input, output, strlen(input), 16);
  printf("%s\n", output);
  format(input, output, strlen(input), 32);
  printf("%s\n", output);
  printf("\n");

  input = "and\nham\n";
  format(input, output, strlen(input), 0);
  printf("%s\n", output);
  format(input, output, strlen(input), 16);
  printf("%s\n", output);
  format(input, output, strlen(input), 32);
  printf("%s\n", output);
  printf("\n");

  for (i = 0; i < 16; i++)
    buffer[i] = i;

  for (i = 0; i < 16; i++)
  {
    format(buffer, output, i + 1, 16 << i);
    printf("%s\n", output);
  }
}

void test_dump(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Usage: %s filename\n", argv[0]);
    return;
  }

  dump(argv[1]);
}

int main(int argc, char **argv)
{
  test_format();

  test_dump(argc, argv);

  return 0;
}
