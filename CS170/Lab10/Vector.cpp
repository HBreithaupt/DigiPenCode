/*****************************************************************************/
/*!
\file Vector.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Lab 10  
\date 3-22-15  

\brief
  Implementation for the Vector class that is an array with the ability to 
  grow, and be able insert at the front and back.


Hours spent on assignment: 2

Specific portions that gave you the most trouble: 
  - Fixing clear to account for multiple calls
*/
/*****************************************************************************/

#include "Vector.h"
#include <iostream>  // cout
#include <cstdlib>   // abort

namespace CS170
{
  
  /***************************************************************************/
  /*!
  
  \brief
    default contructor that uses initialization list for private data.
  
  */
  /***************************************************************************/
  Vector::Vector() : array_(0), size_(0), capacity_(0), allocs_(0)
  {
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Default destructor that clear when an object is being destroyed.
  
  */
  /***************************************************************************/
  Vector::~Vector()
  {
      // call clear to propery destroy object
    Vector::clear();
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Inserts a piece of data at the back of the array
  
  \param value
    The value of the integer being inserted.
  
  */
  /***************************************************************************/
  void Vector::push_back(int value)
  {
      // array is full so grow it
    if(size_ == capacity_)
      Vector::grow();
    
      // array is empty so insert at index 0
    if(Vector::empty())
    {
        // insert at front since array is empty
      array_[0] = value;
      
        // incrment size counter
      size_++;
      
        // end work
      return;
    }
    
      // array is not empty so insert at the back
    array_[size_] = value;
    
      // increment size counter
    size_++;
    
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Inserts data at the front of the array.
  
  \param value
    The value of the integer being inserted at the front of the array.
  
  */
  /***************************************************************************/
  void Vector::push_front(int value)
  {
      // array is full so grow it
    if(size_ == capacity_)
      Vector::grow();
    
      // move existing items over
   for(int i = (int)size_ - 1; i >= 0; i--)
     array_[i + 1] = array_[i];
    
      // insert value at the front of the array
    array_[0] = value;
    
      // increment size counter
    size_++;
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Subscript overload for rvalues.
  
  \param index
    The index that you want the data from.
    
  \return
    The integer contained at passed index.
  */
  /***************************************************************************/
  int Vector::operator[](unsigned index) const
  {
      // check bounds of requested index
    Vector::check_bounds(index);
    
      // return data at specified index
    return array_[index];
  }
    
  
  /***************************************************************************/
  /*!
  
  \brief
    Subscript overload to lvalues.
  
  \param index
    The index that you want the data from.
  
  \return
    The integer conatined at passed index as a reference so it can be written
    to.
  */
  /***************************************************************************/
  int& Vector::operator[](unsigned index)
  {
      // check bounds of requested index
    Vector::check_bounds(index);
    
      // return data at specified index
    return array_[index];
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Clears out the object, deleting all data inside.
    
  */
  /***************************************************************************/
  void Vector::clear()
  {
      // deletes array
    delete [] array_;
    
      // reassigns array_ to null 
    array_ = 0;
    
      // sets size to 0
    size_ = 0;
    
      // resets capacity
    capacity_ = 0;
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Checks if the object is empty.
  
  \return
    A boolean value depending if the object has no data in it.
  */
  /***************************************************************************/
  bool Vector::empty() const
  {
      // return true/false if size is 0
    return size_ == 0;
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Returns the number of values stored in the array.
  
  \return
    How many integers are in the array.
  */
  /***************************************************************************/
  unsigned Vector::size() const
  {
      // return size counter
    return size_;
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Returns how many integers can fit inside the array.
  
  \return
    How many integers can fir inside the array.
  */
  /***************************************************************************/
  unsigned Vector::capacity() const
  {
      // return capacity of the array
    return capacity_;
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    How many allocations have been made. (growths)
  
  \return
    The number of times the array has been grown
  */
  /***************************************************************************/
  unsigned Vector::allocations() const
  {
      // how many allocations were made
    return allocs_;
  }
  
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  // private 
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Checks the bounds of the requested index.
  
  \param index
    The index you wish to access.
    
  */
  /***************************************************************************/
  void Vector::check_bounds(unsigned index) const
  {
      // Don't have to check for < 0 because index is unsigned
    if (index >= size_)
    {
      std::cout << "Attempting to access index " << index << ".";
      std::cout << " The size of the array is " << size_ << ". Aborting...\n";
      std::abort();
    }
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Grows the array to hold more data.
  
  */
  /***************************************************************************/
  void Vector::grow()
  {
      // Double the capacity
    capacity_ = (capacity_) ? capacity_ * 2 : 1;
    
      // allocate new array
    int* growth = new int[capacity_];
    
      // if original array is NOT empty copy the data
   
        // copy data
    for(unsigned int i = 0; i < size_; i++)
      growth[i] = array_[i];
      
    delete [] array_;
      
      // move pointer to new array
    array_ = growth;
      
      // increment allocation counter
    allocs_++;
      
  }

} // namespace CS170
