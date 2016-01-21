#ifndef ABSTRACT_H
#define ABSTRACT_H
#include <stdlib.h> // size_t
#include "CRTP.h"

namespace CS225
{
  class AbstractElement : public ObjectCounter<AbstractElement>
  {
    public:
    
        // pure virtual functions, used in both elements 1 & 2
      virtual int Get() const = 0;
      virtual void Print() const = 0;
    
        // virtual ctors for both elements 1 & 2
      virtual AbstractElement* clone() const = 0;
  };
  
}


#endif
