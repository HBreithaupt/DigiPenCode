/*******************************************************************************
   filename    pi.c
   author      Haven Breithaupt
   DP email    h.breithaupt@digipen.edu
   course      CS120
   assignment  2
   due date    10/7/2104

Brief Description:
  This program calculates pi by two different methods. One by the quarter 
    circle method and the other by the leibniz method.
*******************************************************************************/

/*******************************************************************************
   Function: circle_pi

   Description: Approximates pi by addind area of rectangles within a quarter 
             circle
             
   Inputs: rectangles - number of rectangles inside quarter circle
             
     
   Outputs: Calculation of pi.
*******************************************************************************/
#include <math.h> /* sqrt */
#define RADIUS 2.0 /*radius of the circle */

double circle_pi(int rectangles)
{   
    int i; /* loop counter */
    double pi_circle = 0.0; /* approx of pi from sum of rectangle areas */
    
    
    for (i = 1; i <= rectangles; i++) 
    {
        double width; /* width of rectangle */
        double midpoint; /* midpoint of rectangle */
        double height; /*height of rectangle */
        double area; /* area of rectangle */
        /*double pi_circle = 0.0;  approx of pi from sum of rectangle areas */
        
        width = RADIUS / rectangles; /* width of rectangle */
        midpoint = ((i - 1) * width) + width/2; /* midpoint of rectangle */
        height = sqrt((RADIUS * RADIUS) - (midpoint * midpoint)); /* height of
                                                                   rectangle */
        area = width * height; /* area of rectangle */
        pi_circle += area; /* sum of rectangle area to calculate pi */
                      
    }
    
    return pi_circle; /* appoximation of pi */
}

/*******************************************************************************
   Function: leibniz_pi

Description: 
     Inputs: iterations - how many times to iterate on leibniz method 
     
    Outputs: Numerical value of pi, getting more accurate with more iterations.
*******************************************************************************/
double leibniz_pi(int iterations)
{
    int j = 0; /* iteration counter */
    double pi_leib = 0.0; /* approximation of pi */
    double sign; /* whether iteration is positive or negative */
    double fraction; /* fraction of the iteration */
    
    while(j++ < iterations) 
    {
        
        if(j%2 == 0)
            sign = -1; /* even iterations negative */
        else 
            sign = 1; /* odd iterations positive */
        
        fraction = (1.0/(j + (j - 1.0))); /* value of the iteration */
        pi_leib += sign * fraction; /* adds iteration to approcimation of pi */
        
        if(j == iterations)
            pi_leib = pi_leib * 4; /* multiplies value of pi/4 by 4 to get pi */

    }
    
    return pi_leib; /* returns calculation of pi */
}
