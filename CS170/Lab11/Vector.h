/*****************************************************************************/
/*!
\file Vector.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Lab 11
\date  3-27-15
\brief
  Prototypes for Vector.cpp.


Hours spent on assignment: 2

Specific portions that gave you the most trouble: 
 - The assignment overload was tricky to get the correct number of allocations
   and the other paramters.
*/
/*****************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_H
#define VECTOR_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{

class Vector
{
  public:

      // Default constructor
    Vector();

      // Destructor
    ~Vector();

      // Copy constructor
    Vector(const Vector& rhs);

      // Constructor to create a Vector from an array
    Vector(const int array[], unsigned size);

      // Adds a node to the front of the list
    void push_back(int value);

      // Adds a node to the end of the list
    void push_front(int value);

      // Removes the last element. Does nothing if empty.
    void pop_back();

      // Removes the first element. Does nothing if empty.
    void pop_front();

      // Inserts a new node at the specified position. Causes an
      // abort() if the position is invalid. (Calls check_bounds)
    void insert(int value, unsigned position);

      // Removes an element with the specified value (first occurrence)
    void remove(int value);

      // Deletes the underlying array and sets size_ to 0
    void clear();

      // Return true if the vector is empty, otherwise, false
    bool empty() const;

      // Assignment operator
    Vector& operator=(const Vector& rhs);

      // Concatenates a vector onto the end of this vector.
    Vector& operator+=(const Vector& rhs);

      // Concatenates two Vectors.
    Vector operator+(const Vector& rhs) const;

      // Subscript operators.
    int operator[](unsigned index) const;
    int& operator[](unsigned index);

      // Returns the number of elements in the vector.
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

    // Private methods...
    void check_bounds(unsigned index) const;
    void grow();
    
    // Other private methods...
};

} // namespace CS170

#endif // VECTOR_H
