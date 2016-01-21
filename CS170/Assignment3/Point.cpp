/*****************************************************************************/
/*!
\file Point.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Assignment 3  
\date 2-17-2015

\brief
  Overloads operators to perform mathematical operations on Point class.


Hours spent on assignment: 3

Specific portions that gave you the most trouble: 
  -Implenting the non-member non-friend functions gave me some trouble when
   trying to figure out the syntax
  -Fixing the pre and post decrement/increments to not allow ++p1++, still
   not sure 100% why the fix works the way it does
*/
/*****************************************************************************/


#include "Point.h"  // Point members
#include <cmath>    // sqrt, atan, sin, cos

namespace CS170
{

const double PI = 3.1415926535897;
const double EPSILON = 0.00001;

///////////////////////////////////////////////////////////////////////////////
// private member functions 
  
/*****************************************************************************/
/*!

\brief
  Converts an angle in degrees to radians.

\param degrees
  degrees to convert

\return
  The angle in radians
*/
/*****************************************************************************/
double Point::DegreesToRadians(double degrees) const
{
  return (degrees * PI / 180.0);
}

  
/*****************************************************************************/
/*!

\brief
  Converts an angle in radians to degrees.

\param radians
  Input to convert to degrees.

\return
  The angle in degrees.
*/
/*****************************************************************************/
double Point::RadiansToDegrees(double radians) const
{
  return (radians * 180.0 / PI);
}


///////////////////////////////////////////////////////////////////////////////
// 16 public member functions (2 constructors, 14 operators) 

/*****************************************************************************/
/*!

\brief
  Default constructor that assigns memebers to 0.

*/
/*****************************************************************************/
Point::Point()
{
  x_ = 0;
  y_ = 0;
}
 
/*****************************************************************************/
/*!

\brief
  Constructor that initializes members to passed values.

*/
/*****************************************************************************/
Point::Point(double x, double y) : x_(x), y_(y)
{
  
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator % to rotate a point by an angle, in degrees, about the 
  origin.

\param degrees
  The degrees to rotate the point

\return
  A Point class with new values.
*/
/*****************************************************************************/
Point Point::operator%(double degrees) const
{
    //new class to hold answer
  Point answer;
  
    //calculates sin and cos of angle 
  double cos_angle = cos(Point::DegreesToRadians(degrees));
  double sin_angle = sin(Point::DegreesToRadians(degrees));
  
    //calculates new x and y values
  answer.x_ = cos_angle * x_ - sin_angle * y_;
  answer.y_ = sin_angle * x_ + cos_angle * y_;
  
    //fixes rounding error from -0 to 0
  if(answer.x_ > -EPSILON && answer.x_ < EPSILON)
    answer.x_ = 0.0;
  
    //fixes rounding error from -0 to 0
  if(answer.y_ > -EPSILON && answer.y_ < EPSILON)
    answer.y_ = 0.0;
  
    //return the answer
  return answer;
}
 
  
/*****************************************************************************/
/*!

\brief
  Overloads operator - to calculate the distance between two points.

\param p2
  A constant reference to a Point class to use as the second point.

\return
  The distance between the points (as a double).
*/
/*****************************************************************************/
double Point::operator-(const Point& p2) const
{
  
  
    //calc value of x and y inside sqrt
  double x = (p2.x_ - x_) * (p2.x_ - x_);
  double y = (p2.y_ - y_) * (p2.y_ - y_);
  
    //do the square root
  double answer = sqrt(x + y);
  
    //return distance
  return answer;
    
}

/*****************************************************************************/
/*!

\brief 
  Overloads operator ^ to calculate the midpoint of two points.

\param rhs
  A constant reference to a point class to use as the second point

\return
  A point class with the midpoint of the two points originally used.
*/
/*****************************************************************************/
Point Point::operator^(const Point& rhs) const
{
    //new class to hold answer
  Point answer;
  
    //calc new x and y
  answer.x_ = (x_ + rhs.x_) / 2;
  answer.y_ = (y_ + rhs.y_) / 2;
  
    //return class with new values
  return answer;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator += to add two points together.

\param rhs
  A constant reference to a Point class to use as the second point.

\return
  A reference to a point class with the two points summed.
*/
/*****************************************************************************/
Point& Point::operator+=(const Point& rhs)
{
    //adds the second point the the first
  x_ += rhs.x_;
  y_ += rhs.y_;
  
    //return this
  return *this;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator += to add a double to a point.

\param rhs
  A double to add the point.

\return
  A reference to a point class with the the new point.
*/
/*****************************************************************************/  
Point& Point::operator+=(double rhs)
{
    //add double to left hand class
  x_ += rhs;
  y_ += rhs;
  
    //return this 
  return *this;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator - subtract a double from a point.

\param rhs
  A double to subrtact from the point.

\return
  A Point class with the translated point.
*/
/*****************************************************************************/
Point Point::operator-(double rhs) const
{
    //new class to hold answer
  Point answer;
  
    //calc value for the answer
  answer.x_ = x_ - rhs;
  answer.y_ = y_ - rhs;
  
    //return the answer
  return answer;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator ++ (pre increment) to increment the members of the Point
  class.

\return
  A reference to a point class containing the incremented point.
*/
/*****************************************************************************/  
Point& Point::operator++()
{
    //increment values
  x_++;
  y_++;
  
  Point &refer = *this;
  
    //return this 
  return refer;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator ++ (post-increment) to increment members of the Point 
  class.

\param int
  A dummy parameter to distinguish between pre and post increment overloads.

\return
  A constant Point class with value originally passed in.
*/
/*****************************************************************************/
const Point Point::operator++(int)
{
    //copies the original point to hold value
  const Point holder = *this;
  
    //increments x and y 
  ++x_;
  ++y_;
    
    //return value of original point
  return holder;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator -- (pre-decrement) to decrement members of the Point
  class.

\return
  A reference to a point class containing the decremented members.
*/
/*****************************************************************************/
Point& Point::operator--()
{
    //increment values
  x_--;
  y_--;
  
  Point &refer = *this;
  
    //return this 
  return refer;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator -- (post-decrement) to decrement members of the Point
  class.

\param int
  A dummy parameter to distinguish between pre and post decrement overloads.

\return
  A constant Point class with the original value passed.
*/
/*****************************************************************************/  
const Point Point::operator--(int)
{
    // new class to hold answer
  const Point holder = *this;
  
    //decrement x and y
  --x_;
  --y_;
  
    //return the new class
  return holder;
}

/*****************************************************************************/
/*!

\brief
  Overloads operator - (unary negate) to negate memebers of the class.

\return
  A Point class with the negates values passed.
*/
/*****************************************************************************/
Point Point::operator-() const
{
    //new class to hold answer
  Point answer;
  
    // negates values of x and y
  answer.x_ = -x_;
  answer.y_ = -y_;
  
    //returns new class with negative values
  return answer;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads oeprator + to add a Point and a Point.

\param rhs
  A constant reference to a Point class to use the right hand operand.

\return
  A point class with the two points summed.
*/
/*****************************************************************************/
Point Point::operator+(const Point& rhs) const
{
    //new class to hold answer
  Point answer;
  
    // new values of x
  answer.x_ = x_ + rhs.x_;
  answer.y_ = y_ + rhs.y_;
  
    //return the answer
  return answer;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator + to add a Point and a double.

\param translate
  A double to add (translate) the point.

\return
  A Point class with the translated point.
*/
/*****************************************************************************/
Point Point::operator+(double translate) const
{
  Point answer;
  
  answer.x_ = x_ + translate;
  answer.y_ = y_ + translate;
  
  return answer;
}
  
/*****************************************************************************/
/*!

\brief
  Overloads operator * to scale a Point by a double.

\param scaler
  A double to scale the Point by.

\return
  A Point class that has the scaled members.
*/
/*****************************************************************************/  
Point Point::operator*(double scaler) const
{
    //new class to hold answer
  Point answer;
  
    //calc new values
  answer.x_ = scaler * x_;
  answer.y_ = scaler * y_;
  
    //return the new values
  return answer;
}
///////////////////////////////////////////////////////////////////////////////
// 2 friend functions (operators)

/*****************************************************************************/
/*!

\brief
  Overloads operator << to print out the Point members.

\param os 
  A reference 

\return
*/
/*****************************************************************************/
std::ostream& operator<<(std::ostream& os, const Point& point)
{
  os << "(" << point.x_ << ", " << point.y_ << ")";
  
  return os;
}

  
std::istream& operator>>(std::istream& is, Point& point)
{
  is >> point.x_ >> point.y_;
  return is;
}


///////////////////////////////////////////////////////////////////////////////
// 2 non-members, non-friends (operators)

Point operator+(double lhs, const Point& rhs)
{
  return rhs + lhs;
}
  
Point operator*(double lhs, const Point& rhs)
{
  return rhs * lhs;
}
  
} // namespace CS170



