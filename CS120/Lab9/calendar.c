/******************************************************************************
filename    calendar.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  Lab 9
due date    10/29/2014

Brief Description:
  Prints out a monthly calendar when given a day in time.
******************************************************************************/

#include <stdio.h> /* printf */

#define TRUE  1    /* year is leap year */
#define FALSE 0    /* year is not leap year */

/******************************************************************************
   Function: is_leapyear

Description: determines if a year is a leap year

     Inputs: year - a year to check if it's a leap year
     
    Outputs: TRUE - is leap year
             FALSE - is not leap year
******************************************************************************/
int is_leapyear(int year)
{
    /* year is a divisible by 4 and NOT divisible by 100 */
  if(year % 4 == 0 && year % 100 != 0)
    return TRUE;
  
    /* special case: year is divisble by 100 and 400 so it is a leap year */
  if(year % 100 == 0 && year % 400 == 0)
    return TRUE;
  
  return FALSE;
}

/******************************************************************************
   Function: day_of_week

Description: finds day of the week given a date in time

     Inputs: day - day of the month
             month - month of the year
             year - year given
     
    Outputs: number between 1 and 7 to denote day of week. 1 = Sunday, 
             2 = Monday, 3 = Tuesday, 4 = Wednesday, 5 = Thursday, 
             6 = Friday, 7 = Saturday.
******************************************************************************/
int day_of_the_week(int day, int month, int year)
{
    /* values for months */
  int month_keys[] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
    
    /* century code values */
  int year_keys[] = {4, 2, 0, 6};
  
    
  int day_of_week;    /* day of the week */
  int century_code;   /* holds index number to use in years_keys array */
  
  day_of_week = year % 100; /* extracts last two digits of year */
  
  day_of_week /= 4;   /* divides by 4 */
  
  day_of_week += day; /* adds day of the month */
  
  day_of_week += month_keys[month - 1]; /* adds month key value */
  
    /* if month is January or February and year is leap year */
  if((month - 1 == 0 || month - 1 == 1) && is_leapyear(year))
    day_of_week -= 1;
  
    /* takes years greater than 2099 to calculate index number for year_keys */
  if(year > 2099)
    century_code = (year / 100 - 17) % 4;
  else if(year <= 2099)
    century_code = year / 100 - 17;
    
    /* adds the value of year_keys */
  day_of_week += year_keys[century_code];
  
    /* adds last two digits of year given */
  day_of_week += year % 100;
  
    /* divides by 7 to find day of the week */
  day_of_week = day_of_week % 7;
  
    /* special case of Saturday being 0 but we want 7 */
  if(day_of_week == 0)
    return 7;
  else
    return day_of_week;

}

/******************************************************************************
   Function: print_calendar

Description: prints out a calendar for a given month and year in time

     Inputs: month - month of the year
             year - year given from main.c
     
    Outputs: n/a
******************************************************************************/
void print_calendar(int month, int year)
{
  
  int i; /* loop counter */
  int first_day; /* holds first day of the week of the date given */
  int num_days; /* number of days in month from array */
    /* how many days are in each month */
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  
  
    /* name of the months, only used from main.c */
  char *months[] = {"January",   "February", "March",    "April", 
                    "May",       "June",     "July",     "August",
                    "September", "October",  "November", "December"};

    /* Print calendar header */
  printf("%s, %i\n", months[month - 1], year);
  printf("Su Mo Tu We Th Fr Sa\n");
  printf("---------------------\n");
  
    /* calculates day of the week for first day of date given */  
  first_day = day_of_the_week(1, month, year);
  
    /* number of days in month given */
  num_days = days_in_month[month - 1];
  
    /* prints first week of calendar */
  switch (first_day)
  {
    case 1:
      printf("%2d%3d%3d%3d%3d%3d%3d \n", 1, 2, 3, 4, 5, 6, 7); 
      break;
    case 2:
      printf("%5d%3d%3d%3d%3d%3d \n", 1, 2, 3, 4, 5, 6);
      break;
    case 3:
      printf("%8d%3d%3d%3d%3d \n", 1, 2, 3, 4, 5);
      break;
    case 4:
      printf("%11d%3d%3d%3d \n", 1, 2, 3, 4);
      break;
    case 5:
      printf("%14d%3d%3d \n", 1, 2, 3);
      break;
    case 6:
      printf("%17d%3d \n", 1, 2);
      break;
    case 7:
      printf("%20d \n",  1);
      break;
  }
  
    /* initialize i for for loop */
  i = 9 - first_day;
  
  /* prints each day after first week with 
     * conditionals for Sunday and Saturday */
  for(; i <= num_days; i++)
  {
    if(day_of_the_week(i, month, year) == 1)
      printf("%2d", i);
    else if(day_of_the_week(i, month, year) == 7 && i != num_days)
      printf("%3d \n", i);
    else
      printf("%3d", i);
    
    if(i == num_days)
      printf(" \n");
  }
}
