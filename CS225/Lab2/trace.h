#ifndef TRACE_H
#define TRACE_H
#include "shapes.h"

//one and only global function (not counting main)
std::pair<bool,float> Intersect( Shape** shapes, int num_shapes, Ray const& ray);

#endif
