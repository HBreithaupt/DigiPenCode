
#include <stdio.h>  /* printf, putchar                  */
#include "jumble.h" /* mystrlen, jumble, ENCODE, DECODE */

void test_stress(int passes)
{
  unsigned char phrase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  unsigned char *password = (unsigned char*) "rumpelstiltskin";
  size_t length = sizeof(phrase);
  size_t i;

  printf("\nStress ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, passes);

  printf("\nEncoded phrase:\n");
  for (i = 0; i < length; i++)
    putchar(phrase[i]);

  jumble(phrase, password, DECODE, passes);
  printf("\nDecoded back:\n");
  printf("%s\n", phrase);
}

int main(void)
{
  test_stress(100);
  test_stress(1000);
  test_stress(10000);
  test_stress(100000);
  test_stress(1000000);
  test_stress(10000000);
  return 0;
}
