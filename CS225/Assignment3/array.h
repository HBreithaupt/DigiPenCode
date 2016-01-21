#ifndef ARRAY_H
#define ARRAY_H
#include "abstract-element.h"
#include "element-factory.h"
#include <iostream>

namespace CS225 {

/*
 * Class Array implements a simple array-like data structure.
 * Objects inside the Array have to be derived from AbstractElement.
 */
	class Array {
		public:
			Array(int * array, unsigned int _size, 
					const ElementFactory* _pElementFactory
					);
    
      Array(const Array &rhs);
    
      ~Array();

			int Get(unsigned int pos) const;
			void Set(int id, int pos, int value);

			void Print() const;
    
      Array& operator=(const Array &rhs);
    
       // deep delete when deleting last object 
      // pointing to data
      void DeleteData();
    
        // deep copies the data inside object
      void DeepCopy();
    
		private:
			
        // size of array
      AbstractElement** data; 
    
        // size of array
			unsigned int size;  
    
        // element factoy to make both elements 1 & 2
			const ElementFactory* pElementFactory; 
    
        // reference counter
      int * refcount;
	};
}
#endif
