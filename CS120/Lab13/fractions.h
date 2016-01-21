struct FRACTION
{
  int numerator;
  int denominator;
};

struct MIXED_FRACTION
{
  int whole_number;
  struct FRACTION proper_fraction;
};

struct FRACTION add_fractions(const struct FRACTION *a, const struct FRACTION *b);
struct FRACTION subtract_fractions(const struct FRACTION *a, const struct FRACTION *b);
struct FRACTION multiply_fractions(const struct FRACTION *a, const struct FRACTION *b);
struct MIXED_FRACTION reduced_to_mixed(const struct FRACTION *fraction);
int GCD(int a, int b);