#include <limits> // std::numeric_limits<T>::max(), std::numeric_limits<T>::min()
#include <cmath>  //std::sqrt
#include <iostream>
#include "shapes.h"

////////////////////////////////////////////////////////////////////////////////
//Ray class implementation
////////////////////////////////////////////////////////////////////////////////

Ray::Ray( float o_x, float o_y, float d_x, float d_y ) : origin_x(o_x), origin_y(o_y), dir_x(d_x), dir_y(d_y) {}

std::ostream& operator<<( std::ostream& os, Ray const& ray ) {
    os << " origin(" << ray.origin_x << "," << ray.origin_y << "), direction ( " << ray.dir_x << "," << ray.dir_y << ")";
    return os;
}

std::pair<bool,float>  Ray::IntersectSegment( float p1x, float p1y, float p2x, float p2y ) const {
    float ox = origin_x;
    float oy = origin_y;
    float dx = dir_x;
    float dy = dir_y;
    
    //std::cout << "Segment " << p1x << "," << p1y << " - " << p2x << "," << p2y << " with ray " << ray << std::endl;

    //ray parametric:      XR = ox + dx*t, YR = oy + dy*t
    //segment parametric:  XI = p1x + (p2x-p1x)*s, YI = p1y + (p2y-p1y)*s
    //solve for t, make sure 0<s<1 (strict inequality means corner point 
    //does not reflect the ray)

    //solve system:
    //ox + dx*t = p1x + (p2x-p1x)*s
    //oy + dy*t = p1y + (p2y-p1y)*s
    //-----------------------------
    //dx*t = p1x + (p2x-p1x)*s - ox
    //dy*t = p1y + (p2y-p1y)*s - oy
    //-----------------------------
    //dy*dx*t = dy*( p1x + (p2x-p1x)*s - ox )
    //dx*dy*t = dx*( p1y + (p2y-p1y)*s - oy )
    //-----------------------------
    //dy*( p1x + (p2x-p1x)*s - ox ) = dx*( p1y + (p2y-p1y)*s - oy )
    //-----------------------------
    //dy*p1x + dy*(p2x-p1x)*s - dy*ox = dx*p1y + dx*(p2y-p1y)*s - dx*oy
    //-----------------------------
    //dy*(p2x-p1x)*s - dx*(p2y-p1y)*s = dx*p1y - dx*oy + dy*ox - dy*p1x
    //-----------------------------
    //[ dy*(p2x-p1x) - dx*(p2y-p1y) ]*s = dx*p1y - dx*oy + dy*ox - dy*p1x

    if ( dy*(p2x-p1x) - dx*(p2y-p1y) == 0 ) { // parallel lines
        //std::cout << "parallel\n";
        return std::make_pair( false, -1 );
    }

    float s = ( dx*p1y - dx*oy + dy*ox - dy*p1x ) / ( dy*(p2x-p1x) - dx*(p2y-p1y) );
    if ( s <= 0 || s>= 1 ) { 
        //std::cout << "c<=0 or c>=1\n";
        return std::make_pair( false, -1 ); 
    }

    //to find t use any of the previous equations, for example 
    //ox + dx*t = p1x + (p2x-p1x)*s
    //t = [ p1x - ox + ( (p2x-p1x)*s ) ] / dx
    float t;
    if ( dx == 0 ) { //vertical segment
        //use 
        //oy + dy*t = p1y + (p2y-p1y)*s 
        //t = [ p1y - oy  + (p2y-p1y)*s ] / dy
        //dx and dy cannot be both 0
        t = ( p1y - oy  + (p2y-p1y)*s ) / dy;
    } else {
        t = ( p1x - ox + ( (p2x-p1x)*s ) ) / dx;
    }

    //only if t is positive
    //std::cout << "t = " << t << "\n";
    return t>=0 ? std::make_pair( true, t ) : std::make_pair( false, -1.0f );
}


////////////////////////////////////////////////////////////////////////////////
//BoundingCircle class implementation
////////////////////////////////////////////////////////////////////////////////

BoundingCircle::BoundingCircle( float c_x, float c_y, float r ) : center_x(c_x), center_y(c_y), radius(r) {}

bool BoundingCircle::IntersectTest( Ray const& ray ) const {
    float ox = ray.Origin_x();
    float oy = ray.Origin_y();
    float dx = ray.Direction_x();
    float dy = ray.Direction_y();
    //to test - find distance from circle center to  the ray, 
    //if >=r - no intersection
    //use ray equation (X-ox)*dy - (Y-oy)*dx = 0
    //then distance is      [ (cx-ox)*dy - (cy-oy)*dx ] / sqrt( dx^2+dy^2 ) 
    //to eliminate sqrt:    [ (cx-ox)*dy - (cy-oy)*dx ]^2 / ( dx^2+dy^2 ) < r^2
    float temp = ( (center_x-ox)*dy - (center_y-oy)*dx );
    return ( ( temp*temp ) / ( dx*dx+dy*dy ) < radius*radius );
}

std::ostream & operator<< ( std::ostream & os, BoundingCircle const& bs) {
    os << "center (" << bs.center_x << "," << bs.center_y << "), radius " << bs.radius;
    return os;
}

////////////////////////////////////////////////////////////////////////////////
//Box class implementation
////////////////////////////////////////////////////////////////////////////////

Box::Box( float c_x, float c_y, float s_x, float s_y ) : Shape(), center_x(c_x), center_y(c_y), side_x(s_x), side_y(s_y)
{
  
}

BoundingCircle Box::GetBoundingCircle() const
{
  float left_x, top_y, right_x, bottom_y, box_diagonal,
        x_distance, y_distance;
  
    // coordinate of top left corner of box
  left_x = center_x - side_x / 2;
  top_y = center_y + side_y / 2;
  
    // coordinate of bottom right corner of box
  right_x = center_x + side_x / 2;
  bottom_y = center_y - side_y / 2;
  
    // find distance between x and y coordinate of the corners
  x_distance = left_x - right_x;
  y_distance = top_y - bottom_y;
  
    // use distance formule to find length of diagonal of box
  box_diagonal = std::sqrt(x_distance * x_distance + y_distance * y_distance);
  
    // create bounding circle with radius of half the diagonal of the box
  return BoundingCircle(center_x, center_y, box_diagonal / 2);
}



std::pair<bool,float> Box::Intersect( Ray const& ray ) const {
    //for each side (segment) solve segment-ray intersection and find minimum
    bool intersect = false;
    float t = std::numeric_limits<float>::max();
    std::pair<bool,float> t1 = ray.IntersectSegment( 
                center_x-side_x/2, center_y-side_y/2, 
                center_x+side_x/2, center_y-side_y/2 );
    if ( t1.first ) { t = ( (t1.second<t) ? t1.second : t ); intersect = true; }
    std::pair<bool,float>  t2 = ray.IntersectSegment( 
            center_x-side_x/2, center_y-side_y/2, 
            center_x-side_x/2, center_y+side_y/2 );
    if ( t2.first ) { t = ( (t2.second<t) ? t2.second : t ); intersect = true; }
    std::pair<bool,float>  t3 = ray.IntersectSegment( 
            center_x+side_x/2, center_y+side_y/2, 
            center_x-side_x/2, center_y+side_y/2 );
    if ( t3.first ) { t = ( (t3.second<t) ? t3.second : t ); intersect = true; }
    std::pair<bool,float>  t4 = ray.IntersectSegment( 
            center_x+side_x/2, center_y+side_y/2, 
            center_x+side_x/2, center_y-side_y/2 );
    if ( t4.first ) { t = ( (t4.second<t) ? t4.second : t ); intersect = true; }

    return std::make_pair( intersect, t );

}

std::ostream & operator<< ( std::ostream & os, Box const& box) {
    os << "Box( center (" << box.center_x << "," << box.center_y << "), sides ("
        << box.side_x << "," << box.side_y << ") )";
    return os;
}

void Box::Print() const {
    std::cout << *this;
}

////////////////////////////////////////////////////////////////////////////////
//Rhombus class implementation
////////////////////////////////////////////////////////////////////////////////

Rhombus::Rhombus( float c_x, float c_y, float dia_x, float dia_y ) : Shape(), center_x(c_x), center_y(c_y), diag_x(dia_x), diag_y(dia_y)
{
  
}

BoundingCircle Rhombus::GetBoundingCircle() const {
    return BoundingCircle( center_x,center_y, std::max( diag_x, diag_y ) /2 );
}

std::pair<bool,float> Rhombus::Intersect( Ray const& ray ) const
{
  bool intersect = false;
  float t = std::numeric_limits<float>::max();
  
  // solve segment-ray intersection for each side
  std::pair<bool, float> t1 = ray.IntersectSegment ( 
            center_x - diag_x / 2, center_y, 
            center_x, center_y + diag_y / 2);
  if( t1.first ) { t = t1.second < t ? t1.second : t; intersect = true; }
  
  std::pair<bool, float> t2 = ray.IntersectSegment(
            center_x, center_y + diag_y / 2, 
            center_x + diag_x / 2, center_y);
  if( t2.first ) { t = t2.second < t ? t2.second : t; intersect = true; }
  
  std::pair<bool, float> t3 = ray.IntersectSegment(
            center_x + diag_x / 2, center_y ,
            center_x, center_y - diag_y / 2);
  if( t2.first ) { t = t3.second < t ? t3.second : t; intersect = true; }
  
  std::pair<bool, float> t4 = ray.IntersectSegment(
            center_x, center_y - diag_y / 2,
            center_x - diag_x / 2, center_y);
  if( t4.first ) { t = t4.second < t ? t4.second : t; intersect = true; }
  
  return std::make_pair<bool, float>(intersect, t);
}

std::ostream & operator<< ( std::ostream & os, Rhombus const& rhombus) {
    os << "Rhombus( center (" << rhombus.center_x << "," << rhombus.center_y << "), diagonals ("
        << rhombus.diag_x << "," << rhombus.diag_y << ") )";
    return os;
}

void Rhombus::Print() const {
    std::cout << *this;
}
