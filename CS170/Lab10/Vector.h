/*****************************************************************************/
/*!
\file Vector.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Lab 10
\date 3-22-15

\brief
  Prototypes for the Vector class.

*/
/*****************************************************************************/

///////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_H
#define VECTOR_H
///////////////////////////////////////////////////////////////////////////////

namespace CS170
{

class Vector
{
  public:

      // Default constructor
    Vector();

      // Destructor
    ~Vector();

      // Adds an element to the back of the array. If there is
      // not enough room in the array, it will be grown to
      // handle more items.
    void push_back(int value);

      // Adds an element to the front of the array. If there is
      // not enough room in the array, it will be grown to
      // handle more items. All items to the right must be
      // shifted over one slot to the right.
    void push_front(int value);

      // Subscript operators for const and non-const
    int operator[](unsigned index) const;
    int& operator[](unsigned index);

      // Deletes the underlying array and sets size_ to 0
    void clear();

      // Return true if the vector is empty, otherwise, false
    bool empty() const;

      // Returns the number of elements in the vector
    unsigned size() const;

      // Returns the size of the underlying array
    unsigned capacity() const;

      // The number of memory allocations that have occurred
    unsigned allocations() const;

  private:
    int *array_;        // The dynamically allocated array
    unsigned size_;     // The number of elements in the array
    unsigned capacity_; // The allocated size of the array
    unsigned allocs_;   // Number of allocations (resizes)

      // Makes sure the subscript or position is valid.
      // Aborts the program if it's invalid.
    void check_bounds(unsigned index) const;

      // Grows the array when necessary. (Twice as large as before.)
      // Copies the existing values into the new array. 
      // Deletes the old array.
    void grow();

    // Other private methods...
};

} // namespace CS170

#endif // VECTOR_H
