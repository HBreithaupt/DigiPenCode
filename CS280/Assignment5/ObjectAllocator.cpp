#include "ObjectAllocator.h"

ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig& config) : Config_(config)
{
  ObjectSize_ = ObjectSize;
  ObjectsAllocated_ = 0;
}

  void * ObjectAllocator::Allocate(const char *)
{
  ObjectsAllocated_++;
  return new char[ObjectSize_];
}

  void ObjectAllocator::Free(void *Object) 
{
  // Defer to C++ heap manager
  delete [] reinterpret_cast<char *>(Object);
}

OAStats ObjectAllocator::GetStats(void) const
{
  OAStats stats;
  stats.Allocations_ = ObjectsAllocated_;
  return stats;
}
