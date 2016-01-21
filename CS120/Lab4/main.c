#include <stdio.h> /* printf */

/* Prototypes implemented in primes1.c */
int is_prime(int number);
void conjecture(int low, int high); 

void check_primes(int count)
{
  int primes = 0; /* number of primes found */
  int i;          /* loop counter           */

    /* Check all values from 1 to count */
  for (i = 1; i <= count; i++)
  {
      /* If it's prime, count it and print it */
    if (is_prime(i))
    {
      primes++;
      printf("#%3i: %3i is prime.\n", primes, i);
    }
  }
}

int main(void)
{
  check_primes(100);
  conjecture(2, 200);
  return 0;
}
