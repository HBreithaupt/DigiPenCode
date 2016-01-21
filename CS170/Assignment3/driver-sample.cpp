#include <iostream> // cin, cout, endl
#include "Point.h"  // Point class

using CS170::Point;
using std::cout;
using std::endl;
using std::cin;

void ConstructorTest(void)
{
  cout << "\n********** Constructor test ********** " << endl;

  Point pt1(3, 4);
  Point pt2;
  Point pt3(pt1);
  Point pt4 = pt1;
  Point pt5;
 
  pt5 = pt4;

  // DO NOT ALLOW THIS SYNTAX:
  //Point p6 = 4; // this should not compile
  //Point p7(4);  // this should not compile

  cout << "Point pt1(3, 4): " << pt1 << endl;
  cout << "Point pt2: " << pt2 << endl;
  cout << "Point pt3(pt1): " << pt3 << endl;
  cout << "Point pt4 = pt1: " << pt3 << endl;
  cout << "pt5 = pt4: " << pt5 << endl;

  cout << endl;
}

void TranslateTest(void)
{
  cout << "\n********** Translate test ********** " << endl;

  Point pt1(3, 4);
  Point pt2(7, 12);
  Point pt3;

  pt3 = pt1 + pt2;
  cout << pt1 << " + " << pt2 << " = " << pt3 << endl;

  pt3 = pt1 + 5;
  cout << pt1 << " + 5 = " << pt3 << endl;

  pt3 = 7 + pt1;
  cout << "7 + " << pt1 << " = " << pt3 << endl;

  pt3 = pt1 - 2;
  cout << pt1 << " - 2 = " << pt3 << endl;

  pt3 = pt1 + -2;
  cout << pt1 << " + -2 = " << pt3 << endl;

  // THIS SHOULD NOT COMPILE
  //pt3 = 2 - pt1;

  cout << endl;
}

void ScaleTest(void)
{
  cout << "\n********** Scale test ********** " << endl;

  Point pt1(3, 4);
  Point pt2 = pt1 * 3;
  cout << pt1 << " * 3 = " << pt2 << endl;

  Point pt3(5, 8);
  Point pt4 = 5 * pt3;
  cout << "5 * " << pt3 << " = " << pt4 << endl;

  cout << endl;
}

void RotateTest(void)
{
  cout << "\n********** Rotate test ********** " << endl;

  Point pt1(-50, -50);
  double angle = 45;

  Point pt2 = pt1 % angle;

  cout.setf(std::ios_base::fixed, std::ios::floatfield);
  std::cout.precision(3);
  cout << "Point " << pt1 << " rotated " << angle << " degrees is " << pt2 << endl;

  pt1 = Point(-6, -6);
  angle = 45;

  pt2 = pt1 % angle;
  cout << "Point " << pt1 << " rotated " << angle << " degrees is " << pt2 << endl;

  cout << endl;
  cout.unsetf(std::ios_base::fixed);
  std::cout.precision(6);
}

void DistanceTest(void)
{
  cout << "\n********** Distance test ********** " << endl;

  Point pt1(3, 4);
  Point pt2(7, 12);
  double distance;
 
  distance = pt2 - pt1;
  cout.setf(std::ios_base::fixed, std::ios::floatfield);
  std::cout.precision(3);
  cout << "Distance between " << pt2 << " and " << pt1 << " is " << distance << endl;
 
  distance = pt1 - pt2;
  cout << "Distance between " << pt1 << " and " << pt2 << " is " << distance << endl;

  pt1 = Point(-5, 3);
  pt2 = Point(-1, -7);

  distance = pt2 - pt1;
  cout << "Distance between " << pt2 << " and " << pt1 << " is " << distance << endl;

  cout << endl;
  cout.unsetf(std::ios_base::fixed);
  std::cout.precision(6);
}

void MidpointTest(void)
{
  cout << "\n********** Midpoint test ********** " << endl;

  Point pt1(3, 4);
  Point pt2(7, 12);

  Point pt3 = pt1 ^ pt2;
  cout.setf(std::ios_base::fixed, std::ios::floatfield);
  std::cout.precision(3);
  cout << "Midpoint of " << pt1 << " and " << pt2 << " is " << pt3 << endl;

  pt1 = Point(-5, 3);
  pt2 = Point(-1, -7);
  pt3 = pt1 ^ pt2;
  cout << "Midpoint of " << pt1 << " and " << pt2 << " is " << pt3 << endl;

  cout << endl;
  cout.unsetf(std::ios_base::fixed);
  std::cout.precision(6);
}

void InputTest(void)
{
  cout << "Input test ********** " << endl;

  Point pt1, pt2;

  cout << "Enter an X Y pair (e.g. 3 7): ";
  cin >> pt1;

  cout << "Enter an X Y pair (e.g. 3 7): ";
  cin >> pt2;

  cout << "Midpoint of " << pt1 << " and " << pt2 << " is " << (pt1 ^ pt2) << endl;
  cout << "Distance between " << pt1 << " and " << pt2 << " is " << (pt1 - pt2) << endl;

  cout << endl;
}

void AssignmentTest(void)
{
  cout << "\n********** Assignment test ********** " << endl;

  Point pt1(3, 4);
  Point pt2(-5, 1);

  cout << "pt1 = " << pt1 << endl;
  cout << "pt2 = " << pt2 << endl;
  pt1 += pt2;
  cout << "pt1 += pt2" << endl;
  cout << "pt1 = " << pt1 << endl;
  cout << "pt2 = " << pt2 << endl;

  cout << endl;

  Point pt3(3, 4);
  cout << "pt3 = " << pt3 << endl;
  cout << "pt3 += 5" << endl;
  pt3 += 5;
  cout << "pt3 = " << pt3 << endl;

  cout << endl;

  pt1 += pt2 += pt3;
  cout << "pt1 += pt2 += pt3" << endl;
  cout << "pt1 = " << pt1 << endl;
  cout << "pt2 = " << pt2 << endl;
  cout << "pt3 = " << pt3 << endl;

}

void IncDecTest(void)
{
  cout << "\n********** Inc/Dec test ********** " << endl;

  Point pt1(3, 4);
  cout << "pt1 = " << pt1 << endl;

  Point pt2 = pt1++;
  cout << "pt2 = pt1++" << endl;
  cout << "pt1 = " << pt1 << endl;
  cout << "pt2 = " << pt2 << endl;


  Point pt3(6, 8);
  cout << "pt3 = " << pt3 << endl;

  Point pt4 = ++pt3;
  cout << "pt4 = ++pt3" << endl;
  cout << "pt3 = " << pt3 << endl;
  cout << "pt4 = " << pt4 << endl;

  cout << endl;

  Point pt5(3, 4);
  cout << "pt5 = " << pt5 << endl;

  Point pt6 = pt5--;
  cout << "pt6 = pt5--" << endl;
  cout << "pt5 = " << pt5 << endl;
  cout << "pt6 = " << pt6 << endl;

  Point pt7(6, 8);
  cout << "pt7 = " << pt7 << endl;

  Point pt8 = --pt7;
  cout << "pt8 = --pt7" << endl;
  cout << "pt7 = " << pt7 << endl;
  cout << "pt8 = " << pt8 << endl;

  cout << endl;

  Point pt9 = (--pt7)++; 
  cout << "pt9 = (--pt7)++" << endl;
  cout << "pt7 = " << pt7 << endl;
  cout << "pt9 = " << pt9 << endl;

  Point pt10 = (++pt7)--; 
  cout << "pt10 = (++pt7)--" << endl;
  cout << "pt7 = " << pt7 << endl;
  cout << "pt9 = " << pt9 << endl;
  cout << "pt10 = " << pt10 << endl;

    // These should fail to compile.
    // If it compiles, your code is wrong.
  //Point pt11 = ++(pt7--); 
  //Point pt12 = --(pt7++); 

}

void UnaryTest(void)
{
  cout << "\n********** Unary test ********** " << endl;

  Point pt1(3, 4);
  cout << "pt1 = " << pt1 << endl;
  Point pt2 = -pt1;
  cout << "pt2 = -pt1" << endl;

  cout << "pt1 = " << pt1 << endl;
  cout << "pt2 = " << pt2 << endl;

  cout << endl;

  Point pt3(-3, 4);
  cout << "pt3 = " << pt3 << endl;
  Point pt4 = - - -pt3;
  cout << "pt4 = - - -pt3" << endl;

  cout << "pt3 = " << pt3 << endl;
  cout << "pt4 = " << pt4 << endl;
}

int main(void)
{
  ConstructorTest();
  TranslateTest();
  ScaleTest();
  RotateTest();
  DistanceTest();
  MidpointTest();
  InputTest();
  AssignmentTest();
  IncDecTest();
  UnaryTest();

  return 0;
}

