#include "array.h"

CS225::Array::Array(int * array, 
		unsigned int _size, 
		const ElementFactory* _pElementFactory
		) 
	: data(new AbstractElement*[_size]),size(_size),
		pElementFactory(_pElementFactory), refcount(new int(1))
{
	for (unsigned int i=0;i<size;++i) {
		//create Element with id = 1 (that is Element1 )
		data[i] = pElementFactory->MakeElement( 1, array[i] );
	}
}

  // copy ctor
  // initialize all members as shallow copies of original object
CS225::Array::Array(const Array &rhs) 
  : data(rhs.data), size(rhs.size), pElementFactory(rhs.pElementFactory),
    refcount(rhs.refcount)
{
  
    // increment reference counter
  ++(*refcount);
}
  

  // dtor
CS225::Array::~Array()
{
    // decrement reference counter
  --(*refcount);
  
    // if deleteing last object
    // call delete data for deep delete
  if(*refcount == 0)
    DeleteData();
  
  
}
  
int CS225::Array::Get(unsigned int pos) const 
{ 
  return data[pos]->Get(); 
}

void CS225::Array::Set(int id, int pos, int value) 
{
  if(*refcount > 1)
    DeepCopy();
  
	//setter will delete the old and create new 
	//slightly inefficient if new and old have the same type
	delete data[pos];
	data[pos] = pElementFactory->MakeElement(id,value); 
}

void CS225::Array::Print() const {
	for (unsigned int i=0;i<size;++i) data[i]->Print(); 
	std::cout << std::endl;
}

CS225::Array& CS225::Array::operator=(const Array &rhs)
{
    // self assign check
  if(this == &rhs)
    return *this;
  
    // if left hand object is only object pointing to it's data
    // delete it
  if(*refcount == 1)
    DeleteData();
  else
    --(*refcount);
  
    // shallow copy 
  data = rhs.data;
  
    // shallow copy 
  size = rhs.size;
  
    // decrement reference counter for data previously pointed at
  
    // shallow copy right hand reference counter
  refcount = rhs.refcount;
  
    // increment reference counter
  ++(*refcount);
  
  pElementFactory = rhs.pElementFactory;
  
  return *this;
}

void CS225::Array::DeleteData()
{
  
  for(unsigned int i = 0; i < size; i++)
    delete data[i];
  
  delete [] data;
  
    // delete pointer
  delete refcount;
}

void CS225::Array::DeepCopy()
{ 
    // temp pointer to point at array to copy
  AbstractElement** original_data = data;
  
    // allocate new array 
  data = new AbstractElement*[size];

    // deep copy data 
  for(unsigned int i = 0; i < size; i++)
    data[i] = original_data[i]->clone();
  
    // decrement refcounter of original
  --(*refcount);
  
    // make new refcounter for this data
  refcount = new int(1);
}

















  
