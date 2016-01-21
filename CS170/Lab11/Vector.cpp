/*****************************************************************************/
/*!
\file Vector.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Lab 11  
\date 3-27-15  

\brief
  Implementation for the Vector class.
  
  Functions include:
    - default contructor
    - copy constructor
    - non-default constructor (params: array, size of array)
    - push back : adds data to the back of the array
    - push_front : adds data to the front of the array
    - pop_back : removes the data at the end of the array
    - pop_front : removes the data at the front of the array
    - remove : removes the first occurence of a specified value
    - clear : deletes the array and resets size counter
    - empty : whether or not the array is empty
    - size : number of items in the array 
    - capacity : the total number items the array can hold
    - allocations : how many times the array has been grown
    
    
  Operators:
    - = : assignment 
    - += : concates a vector to the left hand operand
    - + : concats two vectors 
    - [] : subscript operators (two of them for r and l values)


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
    Non-default constructor that uses an array to contruct a vector.
  
  \param array
    An array of integers
    
  \param size
    how many items are in the array passed
  
  */
  /***************************************************************************/
  Vector::Vector(const int array[], unsigned size)
  {
      // copy size of array
    size_ = size;
    
      // set capcaity to size
    capacity_ = size;
    
      // allocate once to needed size
    array_ = new int[size];
    
      // copy data from passed array
    for(unsigned int i = 0; i < size_; i++)
      array_[i] = array[i];
    
      // set alloc to 1
    allocs_ = 1;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Copy constructor.
  
  \param rhs
    The vector to be copied.
  
  \return
  */
  /***************************************************************************/
  Vector::Vector(const Vector& rhs)
  {
      // copy size of right hand vector
    size_ = rhs.size_;
    
      // copy capacity from right hand vector
    capacity_ = rhs.size_;
    
      // initiliaze new array to the capacity of right hand array
    array_ = new int[rhs.capacity_];
    
      // copy data
    for(unsigned int i = 0; i < rhs.size_; i++)
      array_[i] = rhs.array_[i];
    
      // set allocations to 1
    allocs_ = 1;
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
    Removes the data at the front of the Vector
  
  */
  /***************************************************************************/
  void Vector::pop_front()
  {
      // shift data to the left
    for(unsigned int i = 1; i < size_; i++)
      array_[i - 1] = array_[i];
    
      // decrement size
    size_--;
  }

  /***************************************************************************/
  /*!
  
  \brief
    Inserts a specified value at a specified position in the vector.
  
  \param value
    The value to be inserted.
    
  \param position
    The position in the vector to be inserted.
    
  */
  /***************************************************************************/
  void Vector::insert(int value, unsigned position)
  {
      // bounds check index being inserted
    check_bounds(position);
    
      // pre-grow array if neccessary to avoid losing data
    if(size_ + 1 > capacity_)
      grow();
    
      // case of inserting at the front
    if(position == 0)
    {
        // shift data over
      for(unsigned int i = size_ - 1; i > position; i--)
        array_[i + 1] = array_[i];
      
        // move over the first element
      array_[1] = array_[0];
      
        // insert value
      array_[0] = value;
      
        // increment size
      size_++;
      
        // we're done
      return;
      
    }
    
      // shift data to the right after inserted position
    for(unsigned int i = size_ - 1; i >= position; i--)
      array_[i + 1] = array_[i];
    
      // insert the value
    array_[position] = value;
    
      // increment size
    size_++;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Removes the first occurence of a value.
  
  \param value
    The value to be removed.
  
  */
  /***************************************************************************/
  void Vector::remove(int value)
  {
      // save index number of the value being removed
    unsigned int occurence_index = 0;
    
      // search for the number being removed
    for(unsigned int i = 0; i < size_ - 1; i++)
    {
      if(array_[i] == value)
        occurence_index = i;
    }
    
      // check if we actually found the number, 
      // might have not found it
    if(array_[occurence_index] == value)
    {
        // shift items over starting at the index being removed
      for(unsigned int i = occurence_index; i < size_ - 1; i++)
        array_[i] = array_[i + 1];
      
        // decrement size
      size_--;
      
    }
    
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Removes the data at the back of the array.
  
  */
  /***************************************************************************/
  void Vector::pop_back()
  {
      // do nothing if vector is empty
    if(size_ == 0)
      return;
    
      // delete node at back by decrementing size
    size_--;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Assignment operator overload.
  
  \param rhs
    The Vector to be used in assignment
  
  \return
    A referenced the left hand operand once it has been assigned.
  */
  /***************************************************************************/
  Vector& Vector::operator=(const Vector& rhs)
  {
      // check for self assignment
    if(this == &rhs)
      return *this;
    
      // rhs is smaller than left hand so it will fit inside left hand
    if(rhs.capacity_ <= this->capacity_)
    {
      for(unsigned int i = 0; i < rhs.size_; i++)
        array_[i] = rhs.array_[i];
      
      size_ = rhs.size_;
      
      return *this;
    }
    
    // right hand array is larger than left hand 
    
      // clear left hand array
    clear();
    
      // re-allocate left hand to the size we need
    array_ = new int[rhs.size_];
    
      // set capacity to size of right hand array
    capacity_ = rhs.size_;
    
      // increment allocations
    allocs_++;
        
      // push back data from right hand list
    for(unsigned int i = 0; i < rhs.size_; i++)
      push_back(rhs.array_[i]);
    
      // return left hand list
    return *this;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Concats a vector to the end of the left hand operand.
  
  \param rhs
    The vector to be concatenated.
  
  \return
    A reference to the left hand vector.
  */
  /***************************************************************************/
  Vector& Vector::operator+=(const Vector& rhs)
  {
    unsigned int size = rhs.size_;
    
      // push back each node from the right hand list
    for(unsigned int i = 0; i < size; i++)
    {
      push_back(rhs.array_[i]);
    }
    
    return *this;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Creates a vector and concats two Vector to it.
  
  \param rhs
    A vector to be used in concatenation.
  
  \return
    The vector that now holds both the left-hand and right-hand vectors.
  */
  /***************************************************************************/
  Vector Vector::operator+(const Vector& rhs) const
  {
      // construct a vector to hold answer
    Vector concat(*this);
    
      // push back items from left hand list
    /*for(unsigned int i = 0; i < size_; i++)
      concat.push_back(this->array_[i]);*/
  
      // push back items from right hand list
    for(unsigned int j = 0; j < rhs.size_; j++)
      concat.push_back(rhs.array_[j]);
    
        // return vector with cpmbined arrays
    return concat;
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
