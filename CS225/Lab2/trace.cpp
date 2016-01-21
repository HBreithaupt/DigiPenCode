#include <limits> // std::numeric_limits<T>::max()
#include "trace.h"

std::pair<bool,float> Intersect( Shape** shapes, int num_shapes, Ray const& ray)
{
  std::pair<bool, float> compare;
  
  
  bool intersect = false;
  float t = std::numeric_limits<float>::max();
  
    // check all shapes
  for(int i = 0; i < num_shapes; i++)
  {    
      // get gounding circle for shape
    BoundingCircle Bound = shapes[i]->GetBoundingCircle();
    
      // if ray hits bounding circle, move to check the actual shape
    if(  Bound.IntersectTest(ray))
    { 
      compare = shapes[i]->Intersect(ray);
      
      if(compare.first)
      {
        intersect = true;
        
        t = compare.second < t ? compare.second : t;
      }
    }
  }
  
  return std::make_pair<bool, float>(intersect, t);
}