#include <stdio.h>

void print_calendar(int month, int year);
int is_leapyear(int year);
int day_of_the_week(int day, int month, int year);

static char *day_name[] = {"Sunday", "Monday", "Tuesday", "Wednesday", 
                         "Thursday", "Friday", "Saturday"};

void test_leapyear(void)
{
  int year;
  int i;

  year = 1700;
  printf("%4i %s a leap year\n", year, is_leapyear(year) ? "is" : "is not");
  year = 1900;
  printf("%4i %s a leap year\n", year, is_leapyear(year) ? "is" : "is not");
  year = 1901;
  printf("%4i %s a leap year\n", year, is_leapyear(year) ? "is" : "is not");
  year = 1904;
  printf("%4i %s a leap year\n", year, is_leapyear(year) ? "is" : "is not");
  year = 1999;
  printf("%4i %s a leap year\n", year, is_leapyear(year) ? "is" : "is not");
  year = 2000;
  printf("%4i %s a leap year\n", year, is_leapyear(year) ? "is" : "is not");
  year = 2300;
  printf("%4i %s a leap year\n", year, is_leapyear(year) ? "is" : "is not");
  year = 2400;
  printf("%4i %s a leap year\n", year, is_leapyear(year) ? "is" : "is not");

  for (i = 2001; i < 2020; i++)
    printf("%4i %s a leap year\n", i, is_leapyear(i) ? "is" : "is not");
}

void test_day(void)
{
  int day, month, year;
  int day_of_week;
  int i;

  day = 1;
  month = 1;
  year = 2014;
  day_of_week = day_of_the_week(day, month, year);
  printf("day: %i, month: %i, year: %i is on day %i\n", 
          day, month, year, day_of_week);

  day = 1;
  month = 2;
  year = 2014;
  day_of_week = day_of_the_week(day, month, year);
  printf("day: %i, month: %i, year: %i is on day %i\n", 
          day, month, year, day_of_week);

  day = 1;
  month = 3;
  year = 2014;
  day_of_week = day_of_the_week(day, month, year);
  printf("day: %i, month: %i, year: %i is on day %i\n", 
          day, month, year, day_of_week);

  day = 1;
  month = 4;
  year = 2014;
  day_of_week = day_of_the_week(day, month, year);
  printf("day: %i, month: %i, year: %i is on day %i\n", 
          day, month, year, day_of_week);

  day = 1;
  month = 5;
  year = 2014;
  day_of_week = day_of_the_week(day, month, year);
  printf("day: %i, month: %i, year: %i is on day %i\n", 
          day, month, year, day_of_week);

  for (i = 1; i <= 31; i++)
  {
    day_of_week = day_of_the_week(i, 10, 2014);
    printf("day: %i, month: %i, year: %i is on day %i (%s)\n", 
            i, 10, 2014, day_of_week, day_name[day_of_week - 1]);
  }
}

void test_calendar(void)
{
  int i;

  print_calendar(10, 2014);
  printf("\n");
  print_calendar(7, 1776);
  printf("\n");
  print_calendar(7, 2776);
  printf("\n");

  for (i = 1; i <= 12; i++)
  {
    print_calendar(i, 2014);
    printf("\n");
  }
}

int main(void)
{
  test_leapyear();
  test_day();
  test_calendar();
  return 0;
}
