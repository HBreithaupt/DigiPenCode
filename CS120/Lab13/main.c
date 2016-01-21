#include <stdlib.h>    /* atoi           */
#include <stdio.h>     /* printf         */
#include "fractions.h" /* FRACTION stuff */

enum FRACTION_OPERATION {foAdd, foSubtract, foMultiply};

struct FRACTION make_fraction(int numerator, int denominator)
{
  struct FRACTION f;

  f.numerator = numerator;
  f.denominator = denominator;

  return f;
}

void test_fraction(int numerator1, int denominator1, 
                   int numerator2, int denominator2,
                   enum FRACTION_OPERATION operation, 
                   int mixed)
{
  struct FRACTION a = make_fraction(numerator1, denominator1);
  struct FRACTION b = make_fraction(numerator2, denominator2);
  struct FRACTION c;
  char op;

  if (operation == foAdd)
  {
    c = add_fractions(&a, &b);
    op = '+';
  }
  else if (operation == foSubtract)
  {
    c = subtract_fractions(&a, &b);
    op = '-';
  }
  else
  {
    c = multiply_fractions(&a, &b);
    op = '*';
  }

  printf("%i/%i %c %i/%i = %i/%i", a.numerator, a.denominator,
                                   op,
                                   b.numerator, b.denominator,
                                   c.numerator, c.denominator);
  if (mixed)
  {
    struct MIXED_FRACTION mixed = reduced_to_mixed(&c);

    printf(" ==> ");
      /* There's a whole number portion */
    if (mixed.whole_number)
      printf("%i ", mixed.whole_number);

      /* There's a proper fraction portion */
    if (mixed.proper_fraction.numerator)
      printf("%i/%i", mixed.proper_fraction.numerator, 
                      mixed.proper_fraction.denominator);

    if (!mixed.whole_number && !mixed.proper_fraction.numerator)
      printf("0");
  }
  printf("\n");
}

void testGCD(void)
{
  int m, n;

  m = 15; n = 18; /* GCD is 3 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));

  m = 80; n = 20; /* GCD is 20 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));

  m = 21; n = 47; /* GCD is 1 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));

  m = 68; n = 153; /* GCD is 17 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));

  m = 0; n = 18; /* GCD is 18 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));

  m = 0; n = 0; /* GCD is 0 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));
}

int main(int argc, char **argv)
{
  int test = 0;
  if (argc > 1)
    test = atoi(argv[1]);

  switch (test)
  {
    case 1:
      printf("===== Testing GCD =====\n");
      testGCD();
      printf("\n");
      break;

    case 2:
      printf("===== Testing add =====\n");
      test_fraction(2, 3, 1, 6, foAdd, 0);
      test_fraction(1, 5, 4, 9, foAdd, 0);
      test_fraction(3, 7, 12, 21, foAdd, 0);
      test_fraction(5, 8, 3, 16, foAdd, 0);
      test_fraction(7, 8, 3, 12, foAdd, 0);
      test_fraction(0, 8, 3, 16, foAdd, 0);
      test_fraction(1, 1, 3, 16, foAdd, 0);
      test_fraction(5, 8, -3, 16, foAdd, 0);
      test_fraction(1, 5, -4, 9, foAdd, 0);
      test_fraction(-1, 5, -4, 9, foAdd, 0);
      test_fraction(1, 2, 1, 2, foAdd, 0);
      test_fraction(5, 5, -5, 5, foAdd, 0);
      break;

    case 3:
      printf("===== Testing subtract =====\n");
      test_fraction(2, 3, 1, 6, foSubtract, 0);
      test_fraction(1, 5, 4, 9, foSubtract, 0);
      test_fraction(3, 7, 12, 21, foSubtract, 0);
      test_fraction(5, 8, 3, 16, foSubtract, 0);
      test_fraction(7, 8, 3, 12, foSubtract, 0);
      test_fraction(0, 8, 3, 16, foSubtract, 0);
      test_fraction(1, 1, 3, 16, foSubtract, 0);
      test_fraction(5, 8, -3, 16, foSubtract, 0);
      test_fraction(1, 5, -4, 9, foSubtract, 0);
      test_fraction(-1, 5, -4, 9, foSubtract, 0);
      test_fraction(5, 5, 5, 5, foSubtract, 0);
      break;

    case 4:
      printf("===== Testing multiply =====\n");
      test_fraction(2, 3, 1, 6, foMultiply, 0);
      test_fraction(1, 5, 4, 9, foMultiply, 0);
      test_fraction(3, 7, 12, 21, foMultiply, 0);
      test_fraction(5, 8, 3, 16, foMultiply, 0);
      test_fraction(7, 8, 3, 12, foMultiply, 0);
      test_fraction(0, 8, 3, 16, foMultiply, 0);
      test_fraction(1, 1, 3, 16, foMultiply, 0);
      test_fraction(5, 8, -3, 16, foMultiply, 0);
      test_fraction(1, 5, -4, 9, foMultiply, 0);
      test_fraction(-1, 5, -4, 9, foMultiply, 0);
      test_fraction(5, 5, 5, 5, foMultiply, 0);
      test_fraction(0, 4, 5, 7, foMultiply, 0);
      test_fraction(0, 0, 0, 0, foMultiply, 0);
      break;

    case 5:
      printf("===== Testing add and mixed =====\n");
      test_fraction(2, 3, 1, 6, foAdd, 1);
      test_fraction(1, 5, 4, 9, foAdd, 1);
      test_fraction(3, 7, 12, 21, foAdd, 1);
      test_fraction(5, 8, 3, 16, foAdd, 1);
      test_fraction(7, 8, 3, 12, foAdd, 1);
      test_fraction(0, 8, 3, 16, foAdd, 1);
      test_fraction(1, 1, 3, 16, foAdd, 1);
      test_fraction(5, 8, -3, 16, foAdd, 1);
      test_fraction(1, 5, -4, 9, foAdd, 1);
      test_fraction(-1, 5, -4, 9, foAdd, 1);
      test_fraction(1, 2, 1, 2, foAdd, 1);
      test_fraction(5, 5, -5, 5, foAdd, 1);
      break;

    case 6:
      printf("===== Testing subtract and mixed =====\n");
      test_fraction(2, 3, 1, 6, foSubtract, 1);
      test_fraction(1, 5, 4, 9, foSubtract, 1);
      test_fraction(3, 7, 12, 21, foSubtract, 1);
      test_fraction(5, 8, 3, 16, foSubtract, 1);
      test_fraction(7, 8, 3, 12, foSubtract, 1);
      test_fraction(0, 8, 3, 16, foSubtract, 1);
      test_fraction(1, 1, 3, 16, foSubtract, 1);
      test_fraction(5, 8, -3, 16, foSubtract, 1);
      test_fraction(1, 5, -4, 9, foSubtract, 1);
      test_fraction(-1, 5, -4, 9, foSubtract, 1);
      test_fraction(5, 5, 5, 5, foSubtract, 1);
      break;

    case 7:
      printf("===== Testing multiply and mixed =====\n");
      test_fraction(2, 3, 1, 6, foMultiply, 1);
      test_fraction(1, 5, 4, 9, foMultiply, 1);
      test_fraction(3, 7, 12, 21, foMultiply, 1);
      test_fraction(5, 8, 3, 16, foMultiply, 1);
      test_fraction(7, 8, 3, 12, foMultiply, 1);
      test_fraction(0, 8, 3, 16, foMultiply, 1);
      test_fraction(1, 1, 3, 16, foMultiply, 1);
      test_fraction(5, 8, -3, 16, foMultiply, 1);
      test_fraction(1, 5, -4, 9, foMultiply, 1);
      test_fraction(-1, 5, -4, 9, foMultiply, 1);
      test_fraction(5, 5, 5, 5, foMultiply, 1);
      test_fraction(0, 4, 5, 7, foMultiply, 1);
      test_fraction(0, 0, 0, 0, foMultiply, 1);
      break;

    default:
      printf("===== Testing GCD =====\n");
      testGCD();
      printf("\n");

      printf("===== Testing add =====\n");
      test_fraction(2, 3, 1, 6, foAdd, 0);
      test_fraction(1, 5, 4, 9, foAdd, 0);
      test_fraction(3, 7, 12, 21, foAdd, 0);
      test_fraction(5, 8, 3, 16, foAdd, 0);
      test_fraction(7, 8, 3, 12, foAdd, 0);
      test_fraction(0, 8, 3, 16, foAdd, 0);
      test_fraction(1, 1, 3, 16, foAdd, 0);
      test_fraction(5, 8, -3, 16, foAdd, 0);
      test_fraction(1, 5, -4, 9, foAdd, 0);
      test_fraction(-1, 5, -4, 9, foAdd, 0);
      test_fraction(1, 2, 1, 2, foAdd, 0);
      test_fraction(5, 5, -5, 5, foAdd, 0);
      printf("\n");

      printf("===== Testing subtract =====\n");
      test_fraction(2, 3, 1, 6, foSubtract, 0);
      test_fraction(1, 5, 4, 9, foSubtract, 0);
      test_fraction(3, 7, 12, 21, foSubtract, 0);
      test_fraction(5, 8, 3, 16, foSubtract, 0);
      test_fraction(7, 8, 3, 12, foSubtract, 0);
      test_fraction(0, 8, 3, 16, foSubtract, 0);
      test_fraction(1, 1, 3, 16, foSubtract, 0);
      test_fraction(5, 8, -3, 16, foSubtract, 0);
      test_fraction(1, 5, -4, 9, foSubtract, 0);
      test_fraction(-1, 5, -4, 9, foSubtract, 0);
      test_fraction(5, 5, 5, 5, foSubtract, 0);
      printf("\n");

      printf("===== Testing multiply =====\n");
      test_fraction(2, 3, 1, 6, foMultiply, 0);
      test_fraction(1, 5, 4, 9, foMultiply, 0);
      test_fraction(3, 7, 12, 21, foMultiply, 0);
      test_fraction(5, 8, 3, 16, foMultiply, 0);
      test_fraction(7, 8, 3, 12, foMultiply, 0);
      test_fraction(0, 8, 3, 16, foMultiply, 0);
      test_fraction(1, 1, 3, 16, foMultiply, 0);
      test_fraction(5, 8, -3, 16, foMultiply, 0);
      test_fraction(1, 5, -4, 9, foMultiply, 0);
      test_fraction(-1, 5, -4, 9, foMultiply, 0);
      test_fraction(5, 5, 5, 5, foMultiply, 0);
      test_fraction(0, 4, 5, 7, foMultiply, 0);
      test_fraction(0, 0, 0, 0, foMultiply, 0);
      printf("\n");

      printf("===== Testing add and mixed =====\n");
      test_fraction(2, 3, 1, 6, foAdd, 1);
      test_fraction(1, 5, 4, 9, foAdd, 1);
      test_fraction(3, 7, 12, 21, foAdd, 1);
      test_fraction(5, 8, 3, 16, foAdd, 1);
      test_fraction(7, 8, 3, 12, foAdd, 1);
      test_fraction(0, 8, 3, 16, foAdd, 1);
      test_fraction(1, 1, 3, 16, foAdd, 1);
      test_fraction(5, 8, -3, 16, foAdd, 1);
      test_fraction(1, 5, -4, 9, foAdd, 1);
      test_fraction(-1, 5, -4, 9, foAdd, 1);
      test_fraction(1, 2, 1, 2, foAdd, 1);
      test_fraction(5, 5, -5, 5, foAdd, 1);
      printf("\n");

      printf("===== Testing subtract and mixed =====\n");
      test_fraction(2, 3, 1, 6, foSubtract, 1);
      test_fraction(1, 5, 4, 9, foSubtract, 1);
      test_fraction(3, 7, 12, 21, foSubtract, 1);
      test_fraction(5, 8, 3, 16, foSubtract, 1);
      test_fraction(7, 8, 3, 12, foSubtract, 1);
      test_fraction(0, 8, 3, 16, foSubtract, 1);
      test_fraction(1, 1, 3, 16, foSubtract, 1);
      test_fraction(5, 8, -3, 16, foSubtract, 1);
      test_fraction(1, 5, -4, 9, foSubtract, 1);
      test_fraction(-1, 5, -4, 9, foSubtract, 1);
      test_fraction(5, 5, 5, 5, foSubtract, 1);
      printf("\n");

      printf("===== Testing multiply and mixed =====\n");
      test_fraction(2, 3, 1, 6, foMultiply, 1);
      test_fraction(1, 5, 4, 9, foMultiply, 1);
      test_fraction(3, 7, 12, 21, foMultiply, 1);
      test_fraction(5, 8, 3, 16, foMultiply, 1);
      test_fraction(7, 8, 3, 12, foMultiply, 1);
      test_fraction(0, 8, 3, 16, foMultiply, 1);
      test_fraction(1, 1, 3, 16, foMultiply, 1);
      test_fraction(5, 8, -3, 16, foMultiply, 1);
      test_fraction(1, 5, -4, 9, foMultiply, 1);
      test_fraction(-1, 5, -4, 9, foMultiply, 1);
      test_fraction(5, 5, 5, 5, foMultiply, 1);
      test_fraction(0, 4, 5, 7, foMultiply, 1);
      test_fraction(0, 0, 0, 0, foMultiply, 1);
      break;
  }
  return 0;
}
