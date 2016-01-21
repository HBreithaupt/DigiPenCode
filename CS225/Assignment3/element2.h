#ifndef ELEMENT2_H
#define ELEMENT2_H
#include <iostream>
#include "abstract-element.h"

/*
 * A concrete class implementing AbstractElement interface
 * Uses dynamically allocated data.
 */
namespace CS225 {

  class Element2 : public AbstractElement {
    public:
      Element2(int _val);
      Element2(const Element2& rhs);
      Element2& operator=(const Element2& rhs);
      virtual int Get() const;
      virtual void Set(int new_val);
      virtual void Print() const;
      virtual AbstractElement* clone() const;
      virtual ~Element2();
    private:
      int * p_val;
  };

}
#endif
