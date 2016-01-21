/***************************************************************************/
/*!
\file vector.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS225
\par Assignment#2
\date 5/6/15

\brief
  Implementation of SparseVector in C++. Implements functions prototyped in 
  vector.h.
  
  Functions Include:
    
    For Class SparseVector:
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
        
      For Class ElementProxy:
        - non-default contructor
        - automatically generated destructor is used
        
        Operators:
          - int : converts ElementProxy -> int
          - = : assignment (accepts either int or another Proxy as rhs operand)
          - += : regular += (works the same as it would on an int variable)
          - -= : regular -= (works the same as it would on an int variable)
*/
/***************************************************************************/

#include "vector.h"

namespace CS225
{   
  /***************************************************************************/
  /*!
  
  \brief
    Helper function to dynamically allocate a node to insert into vector.
  
  \param val
    Data to use in node.
    
  \param pos
    Position to assign in node.
  
  \return
    Pointer to the node created.
  */
  /***************************************************************************/
  static ElementNode* CreateNode(int val, long pos)
  {
      // allocate a node
    ElementNode* create = new ElementNode;
    
      // assign members
    create->pos = pos;
    create->data = val;
    create->next = 0;
    
      // return pointer to node created;
    return create;
  }
   
  /***************************************************************************/
  /*!
  
  \brief
    Global Function to accept syntax of double * SparseVector,
    just calls member operator* with operands reordered to handle operation.
  
  \param scaler
    Left hand operand of *.
  
  \param rhs
    Right hand operand of *.
  
  \return
    The Vector thats was passed, now with all of it's data multiplied
    by the scaler;
  */
  /***************************************************************************/
  SparseVector const operator*(double scaler, const SparseVector &rhs)
  {
      // re-order operands to use member function
    return rhs * scaler;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Default constructor for SparseVector class. Initializes data feilds to 0.
    
  */
  /***************************************************************************/
  SparseVector::SparseVector() : pHead(0), dimension(0)
  {
    
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Destructor for class SparseVector. Deallocates all memory used in the
    vector.
  
  */
  /***************************************************************************/
  SparseVector::~SparseVector()
  {
      // pointer to walk ahead of pHead
    ElementNode *temp;
    
      // iterate entire vector
    while(pHead)
    {
        // move temp to next node
      temp = pHead->next;
      
        // delete current node
      delete pHead;
      
        // move pHead to temp
      pHead = temp;
    }
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Copy constructor for class SparseVector.
  
  */
  /***************************************************************************/
  SparseVector::SparseVector(const SparseVector &rhs) : pHead(0), 
                                                        dimension(rhs.dimension)
  {
      // pointer to traverse vector being copied
    ElementNode *rhs_walker = rhs.pHead;
    
      // iterate entire vector
    while(rhs_walker)
    {
      Insert(rhs_walker->data, rhs_walker->pos);
      rhs_walker = rhs_walker->next;
    }
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Gets data at specified position in Vector. Will return 0 if node doesnt 
    exist.
  
  \param pos
    The position to get data from in the vector.
  
  \return
    The number stored in the node at pos or 0 if pos doesnt exist.
  */
  /***************************************************************************/
  int SparseVector::Get(long pos) const
  {
    // pointer to walk the vector
    ElementNode *pVector = pHead;
    
    // walk the vector
    while(pVector)
    {
      // return data if we found correct position
      if (pVector->pos == pos)
        return pVector->data;
      
      // have gone further than pos requested
      // therefore pos doesnt exist, so return a 0
      if (pVector->pos > pos)
        return 0;
      
        // move to next node
      pVector = pVector->next;
    }
    
    // return 0 as failsafe
    return 0;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Inserts a node into the vector. If requested value is 0 will call delete to 
    remove the node. If position is already occupied, the data will be updated.
  
  \param val
    The val to insert into the vector.
    
  \param pos
    The position in the vector to insert.
  
  */
  /***************************************************************************/
  void SparseVector::Insert(int val, long pos)
  {
    ElementNode dummy;
    dummy.next = pHead;
    dummy.pos = -1;
    
      // pointers to walk the vector
    ElementNode *current = &dummy, *previous = current, *insert;
    
      // if val passed is 0 just call Delete to handle removal
      // of node
    if(val == 0)
    {
      SparseVector::Delete(pos);
      return;
    }
    
      // maintain dimension size
    if(pos >= dimension)
      dimension = pos + 1;
    
      // walk until find point of insertion or reach end of list
    while (current && current->pos < pos)
    {
      previous = current;
      current = current->next;
    }
    
      // is pos requested for insert is already occupied
      // update data of the node
    if(current && current->pos == pos)
    {
      current->data = val;
      return;
    }
    else // else insert a node into the vector
    {
        // create a node to insert
      insert = CreateNode(val, pos);
      
        // link up the node into the vector
      insert->next  = current;
      previous->next = insert;
      
      pHead = dummy.next;
      
      return;
    }
  }
  
  /***************************************************************************/
  /*!
  
  \brief  
    Deletes a node at requested position in the vector.
  
  \param pos
    The position to delete.
  
  */
  /***************************************************************************/
  void SparseVector::Delete(long pos)
  {
      // create dummy head node & assign data
    ElementNode dummy;
    dummy.pos = -1;
    dummy.next = pHead;
  
      // pointers to walk the vector
    ElementNode *current = &dummy, *previous = current;
    
      // iterate until either pos is found
      // or end of vector
    while(current && current->pos < pos)
    {
      previous = current;
      current = current->next;
    }
    
      // if pos was found remove the node
    if(current && current->pos == pos)
    {
        // adjust pointers
      previous->next = current->next;
      
        // delete node
      delete current;
      
        // readjust head pointer
        // incase of deleting real ehad node
      pHead = dummy.next;
      
      return;
    }
    else // if node at pos wasnt found do nothing
      return;
  }
  
  /****************************************************************************/
  /*!
  
  \brief
    Subscript operator overload to use in r-val expressions.
  
  \param pos
    The position to get data from in the vector.
  
  \return
    The number stored at requested position. Will return if position doesn't
    exist.
  */
  /***************************************************************************/
  int SparseVector::operator[](long pos) const
  {
      // pointer to traverse vector
    ElementNode *pVec = pHead;

      // iterate entire vector
    while(pVec)
    {
        // found pos, return data
      if(pVec->pos == pos)
        return pVec->data;
      
        // have gone past pos requested
        // therefore it doesnt exist in vector, return 0
      if(pVec->pos > pos)
        return 0;
      
        // move pointer to next node
      pVec = pVec->next;
    }
    
      // return 0 failsafe
    return 0;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Adds two vectors together.
  
  \param rhs
    The right hand vector to work with.
  
  \return
    A new vector containing the sum of both lists. (returned by value).
  */
  /***************************************************************************/
  SparseVector const SparseVector::operator+(const SparseVector &rhs) const
  {
      // create vector to hold sum
    SparseVector sum;
    
    int sum_nodes;
    
      // pointers to iterate both vectors
    ElementNode *pLHS = pHead, *pRHS = rhs.pHead, *remainder = 0;
    
      // while both pointers are still valid
    while(pLHS && pRHS)
    {
        // if lhs pos is before rhs insert just lhs data and move
        // just lhs pointer
      if(pLHS->pos < pRHS->pos)
      {
        sum.Insert(pLHS->data, pLHS->pos);
        pLHS = pLHS->next;
      }
        // else if rhs is before lhs insert just rhs and move
        // just rhs pointer
      else if(pLHS->pos > pRHS->pos)
      {
        sum.Insert(pRHS->data, pRHS->pos);
        pRHS = pRHS->next;
      }
        // both pointers are at some pos
        // so insert sum of both nodes at same pos
        // move both pointers
      else
      {
        sum_nodes = pLHS->data + pRHS->data;
        
        if(sum_nodes != 0)
          sum.Insert(sum_nodes, pLHS->pos);
        
        pLHS = pLHS->next;
        pRHS = pRHS->next;
      }
    }
    
      // if either list is longer than the other still 
      // need to add it to sum
    if(pLHS)
      remainder = pLHS;
    else if(pRHS)
      remainder = pRHS;
      
      // concat remainder of whatever list was longer
    while(remainder)
    {
      sum.Insert(remainder->data, remainder->pos);
      remainder = remainder->next;
    }
    
      // return list by value;
    return sum;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Assignment operator.
  
  \param rhs
    the right hand vector to use in assignment.
  
  \return
    A reference to the left hand vector, now containging the same data as
    the right hand vector.
  */
  /***************************************************************************/
  SparseVector& SparseVector::operator=(const SparseVector &rhs)
  {
      // self assignment check
    if(this == &rhs)
      return *this;
    
      // pointer to walk right hand vector
    ElementNode *rhs_walker = rhs.pHead;
    
      // iterate entire vector
    while(rhs_walker)
    {
        // insert into left hand vector
      Insert(rhs_walker->data, rhs_walker->pos);
      
        // move pointer
      rhs_walker = rhs_walker->next;
    }
    
      // return left hand vector as reference
    return *this;
  }
    
  /***************************************************************************/
  /*!
  
  \brief
    Multiplies all data in vector by passed scaler.
  
  \param scaler
    The value to multiply data by.
  
  \return
    A new vector that contains original vector's data multiplied
    by the scaler.
  */
  /***************************************************************************/
  SparseVector const SparseVector::operator*(double scaler) const
  {
      // if multipliying by 0 create empty vector and return that
    if(scaler == 0)
    {
        // create empty vector and return that
      SparseVector product;
      return product;
    }
       
      // copy vector to then perform multiplication  
    SparseVector product(*this);
    
      // pointer to iterate new vector
    ElementNode *pProduct = product.pHead;
    
      // iterate entire vector
    while(pProduct)
    {
        // multiply data
      pProduct->data *= scaler;
      
        // move pointer
      pProduct = pProduct->next;
    }
    
      // return new vector by value
    return product;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Multiplies two vectors, resulting in sum of multplication of all data.
  
  \param rhs
    The right hand vector to use in operation.
  
  \return
    An integer that is the sum of all multiplications of the two vectors.
  */
  /***************************************************************************/
  int SparseVector::operator*(const SparseVector &rhs) const
  {
      // product of both vectors
    int product = 0;
    
      // iterate over both lists
    ElementNode *plhs = pHead, *prhs = rhs.pHead;
    
      // while both pointers are valid
    while(plhs && prhs)
    {
        // move lhs pointer if pos is < rhs
      if(plhs->pos < prhs->pos) 
        plhs = plhs->next;
      
        // else move rhs pointer if pos > rhs
      else if(plhs->pos > prhs->pos) 
        prhs = prhs->next;
      
        // if both positions are the sum, multiply data in both nodes
        // add it to the product
        // move both pointers
      else
      {
        product += plhs->data * prhs->data;
        plhs = plhs->next;
        prhs = prhs->next;
      }
    }
    
      // return product of both vectors
    return product;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Overloads output operator to display vector
  
  \param out
    The stream to output to.
    
  \param v
    The vector to display.
  
  \return
    Reference to the stream used.
  */
  /***************************************************************************/
  std::ostream& operator<<(std::ostream &out, const SparseVector &v) 
  {
    int i,last_pos=-1; 
    ElementNode* p_e=v.pHead; 
    
    while (p_e) 
    { 
      for (i=last_pos+1;i<p_e->pos;++i) out << " " << "0"; 
      out << " " << p_e->data; 
      last_pos=p_e->pos; 
      p_e = p_e->next; 
    }
    
    for (i=last_pos+1;i<v.dimension;++i) out << " " << "0"; 
    
    return out; 
  }
    
  // Class ElementProxy implementation
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Non-default constructor.
  
  \param v
    Vector to store, contained as reference.
  
  \param pos
    Position in vector to store.
  
  */
  /***************************************************************************/
  ElementProxy::ElementProxy(SparseVector& v, long pos) : v(v), pos(pos)
  {
    
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Subscript operator that to use in l-value expressions. Takes position 
    from vector and contructs Proxy object to use in write.
    
  \param pos
    Position in vector to store in object.
  
  \return
    Returns a Proxy object by value to be used in writing to vector.
  */  
  /***************************************************************************/
  ElementProxy SparseVector::operator[](long pos)
  { 
    return ElementProxy(*this, pos);
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Conversion operator to convert ElementProxy -> int.
  
  \return
    The integers in the Vector at pos.
  
  */
  /***************************************************************************/
  ElementProxy::operator int() const
  {
    return v.Get(pos);
  }
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Assignment operator, inserts integer into vector at the pos of the 
    ElementProxy object.
  
  \param val
    Value to insert into vector.
  
  \return 
    Reference to object that invocted this method.
    
  */
  /***************************************************************************/
  ElementProxy& ElementProxy::operator=(int val) //const?
  {
      // insert value into vector
    v.Insert(val, pos);
    
      // return object by reference
    return *this;
  }  
  
  
  /***************************************************************************/
  /*!
  
  \brief
    Assignment operator that uses another ElementProxy as right hand operand.
  
  \param rhs
    ElementProxy to get data from.
  
  \return
    Reference to object that invocted this method.
    
  */
  /***************************************************************************/
  ElementProxy& ElementProxy::operator=(const ElementProxy &rhs)
  {
      // gete data from right hand proxy
    int assign = rhs.v.Get(rhs.pos);
    
      // insert into left hand vector
    v.Insert(assign, pos);
    
      // return reference to object that invocted this method
    return *this;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Operator +=, works like it would on an integer.
  
  \param val
    value to use in changing the data stored in Proxy object.
  
  \return
    Reference to object that invocted this method.
    
  */
  /***************************************************************************/
  ElementProxy& ElementProxy::operator+=(int val)
  {
      // get number stored in node already
    int stored_value = v.Get(pos);
    
      // update number with rhs operand
    stored_value += val;
    
      // now update it in vector using Insert
    v.Insert(stored_value, pos);
    
      // return reference to object that invocted the method
    return *this;
  }
  
  /***************************************************************************/
  /*!
  
  \brief
    Operator -=, works like it would on an int. Negates val and uses += to 
    perform the operation.
  
  \param val
    The value to use in operation.
  
  \return
    Reference to object that invocted this method.
  */
  /***************************************************************************/
  ElementProxy& ElementProxy::operator-=(int val)
  {
      // negate operand and use already implemented +=
    return *this += -val;
  }
}

