///////////////////////////////////////////////////////////////////////////////
#ifndef POINT_H
#define POINT_H
///////////////////////////////////////////////////////////////////////////////

/*****************************************************************************/
/*!
\file Point.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Assignment 3  
\date 2-17-2015

\brief
  Contains function prototypes for Point.cpp.
*/
/*****************************************************************************/

#include <iostream> // istream, ostream

namespace CS170
{
  class Point
  {
    public:
        // Constructors (2)
    
      //default constructor, sets to 0,0
    Point();
    
      //constructor that initliazes to paramters
    Point(double x, double y);

        // Overloaded operators (14 member functions)
    
      // rotate a point by an angle
    Point operator%(double angle) const;
    
      // distance between two points
    double operator-(const Point& p2) const;
    
      // midpoint of two points
    Point operator^(const Point& rhs) const;
    
      //adds two points together
    Point& operator+=(const Point& rhs);
    
      //adds double to a point
    Point& operator+=(double rhs);
    
      //subtracts a double from a point
    Point operator-(double rhs) const;
    
      // pre increment
    Point& operator++();
    
      //post increment
    const Point operator++(int);
    
      // pre decrement
    Point& operator--();
    
      //post decrement
    const Point operator--(int);
    
      // unary negation
    Point operator-() const;
    
      //translates a point by a point
    Point operator+(const Point& rhs) const;
    
      //translates a point by a double
    Point operator+(double translate) const;
    
      // scales a point
    Point operator*(double scaler) const;
        
        // Overloaded operators (2 friend functions)
    
      // output the point
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
        
      // input into a point
    friend std::istream& operator>>(std::istream& is, Point& point);
      
    private:
      double x_; // The x-coordinate of a Point
      double y_; // The y-coordinate of a Point

        // Helper functions
      double DegreesToRadians(double degrees) const;
      double RadiansToDegrees(double radians) const;
  };
  
    // Overloaded operators (2 non-member, non-friend functions)
    
    //translates a point by a double  
  Point operator+(double lhs, const Point& rhs);
    
    //scales a point by a double
  Point operator*(double lhs, const Point& rhs);
  
  
} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
