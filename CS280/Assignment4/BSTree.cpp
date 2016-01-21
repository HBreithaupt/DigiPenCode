/*****************************************************************************/
/*!
 \file BSTree.cpp
 \author      Haven Breithaupt
 \par DP email: h.breithaupt\@digipen.edu
 \par Course: CS280
 \par Assignment 4
 \date 10/31/15
 
 \brief
  Implementation of binary search tree.
 
 
 Hours spent on assignment: 2 (on this file)
 
 Specific portions that gave you the most trouble:
- Not much here, mostly copy paste from the web site. Assignment and copy
  probably the most difficult.
 */
/*****************************************************************************/


/*****************************************************************************/
/*!
 
 \brief
  Constructor for BST
 
 \param OA
  ObjectAllocator to use with the tree (either provided or created).
 
 \param ShareOA
  Flag to indicate sharing of the object allocator with copies
  of the object.
 
 */
/*****************************************************************************/
template <typename T>
BSTree<T>::BSTree(ObjectAllocator *OA, bool ShareOA) : Root(0), Height(-1), NumNodes(0)
{
    // if allocator provided use it
    // else make our own
  if(OA)
  {
      // flag that we do NOT own the allocator
      // and will not delete it (client will handle that)
    OwnOA = false;
    allocator = OA;
  }
  else
  {
      // make our own allocator
    OAConfig config(true);
    allocator = new ObjectAllocator(sizeof(BinTreeNode), config);
    OwnOA = true;
  }

    // flag whether or not to share this allocator with copies of this object
  if(ShareOA)
    ShareAlloc = true;
  else 
    ShareAlloc = false;
}

/*****************************************************************************/
/*!
 
 \brief
  Copy constructor
 
 \param rhs
  Object being copied
 
 */
/*****************************************************************************/
template <typename T>
BSTree<T>::BSTree(const BSTree& rhs)
{
    // if rhs is sharing their allocator, use it
  if(rhs.ShareAlloc)
  {
    allocator = rhs.allocator;
    
      // we dont own the allocator
    OwnOA = false;
    
      // continue sharing the allocator if more copies requested
    ShareAlloc = true;
  }
  else // make our own allocaotr
  {
    OAConfig config(true);
    allocator = new ObjectAllocator(sizeof(BinTreeNode), config);
    
      // we own this, are responsible for deleting it
    OwnOA = true;
    
      // do not share this allocator
    ShareAlloc = false;
  }
  
    // call helper function to copy rhs tree
  CopyHelper(Root, rhs.Root);
  
    // copy stats
  NumNodes = rhs.NumNodes;
  Height = rhs.Height;
}

/*****************************************************************************/
/*!
 
 \brief
  Destructor
 
 */
/*****************************************************************************/
template <typename T>
BSTree<T>::~BSTree()
{
    // call clear to destroy the tree
  clear();
  
  
    // if we own the allocator, delete it
  if(OwnOA)
    delete allocator;
  
}

/*****************************************************************************/
/*!
 
 \brief
  Assignment operator.
 
 \param rhs
  Object being assigned from.
 
 \return
  Reference to lhs object.
 */
/*****************************************************************************/
template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& rhs)
{
    // self assignment check
  if(this == &rhs)
    return *this;

    // use rhs allocator if needed
  if(rhs.ShareAlloc)
  {
      // however if we own our own allocate
      // delete it first
    if(OwnOA)
    {
        // delete underlying nodes first
      clear();
      
        // delete the allocator
      delete allocator;
    }
    
      // use rhs allocator and set flags
    allocator = rhs.allocator;
    OwnOA = false;
    ShareAlloc = true;
    
  }
    // clear out the left list
  clear();
  
    // copy the right hand list
  CopyHelper(Root, rhs.Root);
  
    // copy stats
  NumNodes = rhs.NumNodes;
  Height = rhs.Height;
  
  return *this;
}

/*****************************************************************************/
/*!
 
 \brief
  Indexing operator (not implemented).
 
 \param index
  Node requested from the tree
 
 \return
  Pointer to node requested
 */
/*****************************************************************************/
template <typename T>
const typename BSTree<T>::BinTreeNode* BSTree<T>::operator[](int index) const
{
  // not implemented, DO NOT USE
  
    // 'use' index
  if(index)
    return 0;
  else
    return 0;
}

/*****************************************************************************/
/*!
 
 \brief
  Public insert function. Redirects to private recursive function
  to handle insertion.
 
 \param value
  Balue being inserted.
 
 */
/*****************************************************************************/
template <typename T>
void BSTree<T>::insert(const T& value)
{
  try
  { 
      // call recursive function to insert
      // catch exception from InsertItem and throw back to client
    InsertItem(Root, value, 0);
  }
  catch(const BSTException &e)
  {
    throw ;
  }
}

/*****************************************************************************/
/*!
 
 \brief
  Public removal function. Redirects to private recursive function.
 
 \param value
  Value being removed from the tree.
 
 */
/*****************************************************************************/
template <typename T>
void BSTree<T>::remove(const T& value)
{
    // call private delete to recurisvely delete this value
    // not entirely sure how value lost it's constness
    // tried calling it by value of the paramter given
    // and ocmpiler complained about lost qualifiars
  DeleteItem(Root, const_cast<T&>(value));
  
    // recalculate the height of the tree
  Height = tree_height(Root);
}

/*****************************************************************************/
/*!
 
 \brief
  Removes all nodes from the tree. Calls recursive function
 
 */
/*****************************************************************************/
template <typename T>
void BSTree<T>::clear(void)
{
    // if there are nodes in the tree
    // call ClearRec to delete them
  if(Root)
  {
      // delete all the nodes in th tree
    ClearRec(Root);
    
      // reset counters and pointer
    Root = 0;
    Height = -1;
    NumNodes = 0;
  }
}

/*****************************************************************************/
/*!
 
 \brief
  Recursive functio to delete all nodes in the tree.
 
 \param tree
  node being removed
 
 */
/*****************************************************************************/
template <typename T>
void BSTree<T>::ClearRec(BinTree tree)
{
  // delete all nodes in the tree using post order traversal
  if(!tree)
      return;

  ClearRec(tree->left);
  ClearRec(tree->right);

  FreeNode(tree);
}

/*****************************************************************************/
/*!
 
 \brief
  Finds an item in the tree. Calls recursive function to do the work.
 
 \param value
  Value looking for.
 
 \param compares
  How many comparisons it took to find (or not) the item.
 
 \return
  True if the item was found. False if it was node
 */
/*****************************************************************************/
template <typename T>
bool BSTree<T>::find(const T& value, unsigned &compares) const
{ 
    // call recursive function to find our value
  return FindItem(Root, value, compares);
}

/*****************************************************************************/
/*!
 
 \brief
  Checks if the tree is empty.
 
 \return
  True if it's empty, false if there are nodes in it.
 */
/*****************************************************************************/
template <typename T>
bool BSTree<T>::empty(void) const
{
    // if height is -1 there are no nodes in the tree, 
    // therefore empty
  if(Height == -1)
    return true;
  else
    return false;
}

/*****************************************************************************/
/*!
 
 \brief
  Returns number of nodes in the tree.
 
 
 \return
  Number of ndoes in the tree.
 */
/*****************************************************************************/
template <typename T>
unsigned int BSTree<T>::size(void) const
{ 
    // return count member of the head (total nodes in tree)
    // else if root is null, return 0
  return NumNodes;
}

/*****************************************************************************/
/*!
 
 \brief
  Checks height of the tree.
 
 \return
  Height of the tree.
 */
/*****************************************************************************/
template <typename T>
int BSTree<T>::height(void) const
{ 
    // call tree_height with root of the tree
    // to find total height
  return Height;
}

/*****************************************************************************/
/*!
 
 \brief
  Returns root of the tree.
 
 \return
  Root of the tree.
 */
/*****************************************************************************/
template <typename T>
typename BSTree<T>::BinTree BSTree<T>::root(void) const
{
  return Root;
}

/*****************************************************************************/
/*!
 
 \brief
  Checks for extra credit implementation.
 
 \return
  True if extra credit was implementated. False if not.
 */
/*****************************************************************************/
template <typename T>
bool BSTree<T>::ImplementedIndexing(void)
{ 
    // index not implemented
  return false;
}

/*****************************************************************************/
/*!
 
 \brief
  Makes a node to put in the tree.
 
 \param value
  Value to store increated node
 
 \return
  Pointer to node created.
 */
/*****************************************************************************/
template <typename T>
typename BSTree<T>::BinTree BSTree<T>::make_node(const T& value)
{
  try
  {
      // use objectalloctor to make memory for node
    BinTree mem = reinterpret_cast<BinTree>(allocator->Allocate()); // Allocate memory for the object.
    
      // put node in memoery allocated above
    BinTree node = new (mem) BinTreeNode(value);

      // return node created
    return node;

  }
    // catch any exception from objectallocator and throw our own exception
  catch (const OAException &e)
  {
    throw(BSTException(BSTException::E_NO_MEMORY, e.what()));
  }
}

/*****************************************************************************/
/*!
 
 \brief
  First deleted underlying node in the allocator and then
  gives back thta memory to the allocator.
 
 \param node
  node being freed.
 
 */
/*****************************************************************************/
template <typename T>
void BSTree<T>::FreeNode(BinTree node)
{
    // manually call destructor on the node inside the OA
  node->~BinTreeNode();
  
    // give back the memory used to the OA
  allocator->Free(node);
}

/*****************************************************************************/
/*!
 
 \brief
  Calculate height of the tree.
 
 \param tree  
  Root of the tree
 
 \return
  Height of the tree.
 */
/*****************************************************************************/
template <typename T>
int BSTree<T>::tree_height(BinTree tree) const
{
  if (tree == 0)
    return -1;
  else
    return (1 + std::max(tree_height(tree->left), tree_height(tree->right)));
}

/*****************************************************************************/
/*!
 
 \brief
  Finds predecessor of a node.
 
 \param tree
  Starting node (left of the node being removed).
 
 \param predecessor
  Reference to a pointer that will be used in deleting after
  predecessor is found.

 */
/*****************************************************************************/
template <typename T>
void BSTree<T>::FindPredecessor(BinTree tree, BinTree &predecessor) const
{
    // start looking for the RIGHTMOST node in the LEFT sub-tree
  predecessor = tree->left;

  while (predecessor->right != 0)
    predecessor = predecessor->right;
}

/*****************************************************************************/
/*!
 
 \brief
  Recursive copy function used in copy construcotr and assignment
 
 \param destination
  lhs object
 
 \param source
  rhs object
 
 */
/*****************************************************************************/
template <typename T>
void BSTree<T>::CopyHelper(BinTree &destination, const BinTree &source)
{
    // base case
  if(!source)
    destination  = 0;
  // copy the source
  else
  {
      // copy the node
    destination = make_node(source->data);
    
      // copy the left
    CopyHelper(destination->left, source->left);
      //copy the right
    CopyHelper(destination->right, source->right);
    
  }
}

/*****************************************************************************/
/*!
 
 \brief
  Recursive function to remove an item from the tree
 
 \param tree
  Starts at the root of the tree
 
 \param Data
  Data being removed from the tree.
 
 */
/*****************************************************************************/
template <typename T>
void BSTree<T>::DeleteItem(BinTree& tree, const T& Data)
{
    // didnt find value where it should be
    // does not eist in this tree
  if (tree == 0)
    return;

  else if (Data < tree->data)
    DeleteItem(tree->left, Data);
  else if (Data > tree->data)
    DeleteItem(tree->right, Data);
  else // (Data == tree->data)
  {
      // leaf node deletion
      // base case
    if (tree->left == 0)
    {
      BinTree temp = tree;
      tree = tree->right;
      FreeNode(temp);
      --NumNodes;
    }
      // leaf node deletion
      // base case
    else if (tree->right == 0)
    {
      BinTree temp = tree;
      tree = tree->left;
      FreeNode(temp);
      --NumNodes;
    }
    else
    {
        // find predecessor
        // and call again to get to base casee
      BinTree pred = 0;
      FindPredecessor(tree, pred);
      tree->data = pred->data;
      DeleteItem(tree->left, tree->data);
    }
  }
}

/*****************************************************************************/
/*!
 
 \brief
  Recursively inserts an item into the tree.
 
 \param tree
  Starts at the root of the tree
 
 \param value
  value being inserted into the tree

 \param depth
  how deep down the tree we went. Used to update height
 
 */
/*****************************************************************************/
template <typename T>
void BSTree<T>::InsertItem(BinTree &tree, const T& value, int depth)
{
  try
  {
      // found out spot to be, insert
    if (tree == 0)
    {
        // if we gone further down than height
        // increment height
      if(depth > Height)
        ++Height;

      tree = make_node(value);
      
        // incremener node counter
      ++NumNodes;

      return;
    }

    if (value < tree->data)
      InsertItem(tree->left, value, depth + 1);
    else
      InsertItem(tree->right, value, depth + 1);
  }
  catch (const BSTException &e)
  {
    throw e;
  }
}


/*****************************************************************************/
/*!
 
 \brief
  Finds an item in the tree.
 
 \param tree
  Starts at root of the tree
 
 \param Data
  Data looking for
 
 \param compares
  Number of comparisons it took to find (or not find) the item.

 \return
  True if item was found, False if it wasnt;
 */
/*****************************************************************************/
template <typename T>
bool BSTree<T>::FindItem(BinTree tree, const T& Data, unsigned &compares) const
{
    // increment comparison counter
  ++compares;

    // found where value would have been but its empty
    // value is not in the tree
  if(tree == 0)
    return false;
  else if(Data == tree->data)
    return true;
  else if(Data < tree->data)
    return FindItem(tree->left, Data, compares);
  else
    return FindItem(tree->right, Data, compares);
}








