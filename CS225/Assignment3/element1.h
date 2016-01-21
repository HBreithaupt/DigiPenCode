#ifndef ELEMENT1_H
#define ELEMENT1_H
#include <iostream>
#include "abstract-element.h"
/*
 * A concrete class implementing AbstractElement interface
 * Trivial.
 */
namespace CS225 {

  class Element1 : public AbstractElement {
    public:
        // non-default ctor
      Element1(int _val);
    
        // copy stor
      Element1(const Element1 &rhs);
      
        // gets data in object
      virtual int Get() const;
      
        // changes data in object
      virtual void Set(int new_val);
      
        // displays data in object
      virtual void Print() const;
    
        // virtual ctor
      Element1* clone() const;
    
    private:
      int val;
  };
}
#endif
