
/*****************************************************************************/
 /*!
 \file fibonacci.cpp
 \author Haven Breithaupt
 \par DP email: h.breithaupt\@digipen.edu
 \par Course: CS170
 \par Lab #3
 \date 1-23-2015
 
 \brief 
    This program prints the fibonacci number sequence.
 
 - fibonacci
    calculates the fibonacci number in an incrementing sequence
  */

/****************************************************************************/

#include <iostream> // cout
#include <iomanip>  // 


/****************************************************************************/

 /*!
 \fn void fibonacci(int max)

 \brief 
    Takes an input to genereate the fibonacci number sequence up until the 
    input number.
    
 \param max
    How many iterations the sequence generator should produce.
 */
/****************************************************************************/
void fibonacci(int max)
{
  std::cout << "           Fibonacci        Fibonacci" << std::endl;
  std::cout << " N           number          quotient" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << " 0             0                  N/A" << std::endl;
  std::cout << " 1             1                  N/A" << std::endl;

  int count = max;
  int fib1 = 0, fib2 = 1;
  for (int i = 2; i <= count; i++)
  {
    int next = fib1 + fib2;
    
    std::cout << std::right
              << std::setw(2)
              << i
              << std::right
              << std::setw(14)
              << next
              << std::fixed
              << std::setprecision(17)
              << std::right
              << std:: setw(21)
              << double(next)/fib2
              << std::endl;
    
    fib1 = fib2;
    fib2 = next;
  }
}
