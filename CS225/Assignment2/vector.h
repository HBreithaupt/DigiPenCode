/*****************************************************************************/
/*!
\file vector.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS225
\par Assignment#2
\date 5/6/15

\brief
  Interface file for classes Sparsevector and ElementProxy.


Hours spent on assignment:

Specific portions that gave you the most trouble: 
*/
/*****************************************************************************/

#include <iostream>

namespace CS225
{
  
    // struct used as node in our 'vector' (linked list)
  typedef struct ElementNode 
  {
    int data;
    int pos;
    struct ElementNode *next;
  } ElementNode;
  
    //forward declaration
  class ElementProxy;
  
  /***************************************************************************/
  /*!
  
  \class SparseVector
  
  \brief
    SparseVector is a linked list disguised as vector. Does not store any
    occurences of 0 in the list.
    
    Methods include:
    
      - default constructor
      - copy constructor
      - destructor
      - Get : gets data from requested position
      - Insert : Inserts data at requested position
      - Delete : deletes node from requested position
      - PrintRaw (defined in header) : prints out the vector
      
      Operators:
        - subscript : 2 overloads, 1 returning an integer for r-val,
                      second overload returns a proxy class to use for l-values
        - + : adds two vectors together, returns new vector
        - = : regular assignment
        - * : multiplies data in vector by a scaler
    
  */
  /***************************************************************************/
  class SparseVector 
  {
    public:
    
    
    SparseVector();
    
    ~SparseVector();
    
    SparseVector(const SparseVector &rhs);
    
    int Get(long pos) const;
    
    void Insert(int val, long pos);
    
    void Delete(long pos);
    
    int operator[](long pos) const;
    
    ElementProxy operator[](long pos);
    
    SparseVector const operator+(const SparseVector &rhs) const;
    
    SparseVector& operator=(const SparseVector &rhs);
    
    int operator*(const SparseVector &rhs) const;
    
    SparseVector const operator*(double scaler) const;
    
    void PrintRaw () const 
    { //used for grading 
      
      ElementNode* curr=pHead;
      std::cout << "Raw vector: ";
      
      while (curr) 
      {
        std::cout << "(" << curr->data << ", " << curr->pos << ")";
        curr=curr->next;
      }
      
      std::cout << std::endl;
    }
    
    friend std::ostream& operator<<(std::ostream &out, const SparseVector &v);
    
    private:
    ElementNode* pHead;
    long dimension;
  };
  
    // global function to support multplication syntax (double * SparseVector)
  SparseVector const operator*(double scaler, const SparseVector &rhs);
  
  /**************************************************************************/
  /*!
  
  \class ElementProxy
  \brief
    This is used as a Proxy to a SparseVector position. Use of this class
    if for l-value expression to a vector.
    
    Methods Include:
    
        - non-default contructor
        - automatically generated destructor is used
        
        Operators:
          - int : converts ElementProxy -> int
          - = : assignment (accepts either int or another Proxy as rhs operand)
          - += : regular += (works the same as it would on an int variable)
          - -= : regular -= (works the same as it would on an int variable)
  
  */
  /**************************************************************************/  
  class ElementProxy 
  {
    public:
    ElementProxy(SparseVector& v, long pos);
    operator int() const;
    
    // ElementProxy& operator=(const ElementProxy &rhs);
    ElementProxy& operator=(int val); //const?
    ElementProxy& operator=(const ElementProxy &rhs);
    
      // fix this, test 13, haveing problem w/ chaining
    ElementProxy& operator+=(int val);
    
    ElementProxy& operator-=(int val);
    
     private:
    SparseVector &v;
    long pos;
  }; 
}

