/*****************************************************************************/
/*!
 \file AVLTree.cpp
 \author      Haven Breithaupt
 \par DP email: h.breithaupt\@digipen.edu
 \par Course: CS280
 \par Assignment 4
 \date 10/31/15
 
 \brief
  Implmentation of AVL tree funciontality.
 
 
 Hours spent on assignment: 10
 
 Specific portions that gave you the most trouble:
 - using templates here gave me a lot of trouble, not sure why. I had
   some trouble getting to use functions and data inherited from BSTree.
 
 - deleting nodes was troublesome took me awhile to get all cases correct, even
   with pseudocode posted on the site.
 
 - stree test will fail. At some point along the way pointers were being dropped.
   StressSmall works correctly and I implemented example from website to make 
   sure I was handling multiple rotations in one deletion and it was correct. 
   I just couldnt figure out where things went wrong.
 
 */
/*****************************************************************************/


/*****************************************************************************/
/*!
 
 \brief
  Constructor for AVLTree
 
 \param OA
  Object Allocator to be used with the tree. (either provided or object makes 
  its own).
 
 \param ShareOA
  Flag to indicate sharing of an allocator between copies of objects
 
 */
/*****************************************************************************/
template <typename T>
AVLTree<T>::AVLTree(ObjectAllocator *OA, bool ShareOA) : BSTree<T>(OA, ShareOA)
{

}

/*****************************************************************************/
/*!
 
 \brief
  Destructor, will call base class destructor and that will be sufficient
 
 */
/*****************************************************************************/
template <typename T>
AVLTree<T>::~AVLTree()
{

}

/*****************************************************************************/
/*!
 
 \brief
  Public insert function. Redirects to private recursive function to handle
  insertion.
 
 \param value
  Whate is being inserted into the tree

 
 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::insert(const T& value)
{
  try
  {
    // stack to keep track how we got to insertion place
    std::stack<BinTree> nodes;
    InsertItemAVL(this->Root, value, nodes, 0);
    
    this->Height = this->tree_height(this->Root);
  }
  catch (const BSTException &e)
  {
    throw e;
  }
}

/*****************************************************************************/
/*!
 
 \brief
  Public remove function. Redirects to private recursive function.
 
 \param value
  What's being removed from the tree.
 
 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::remove(const T& value)
{
    // use private function to recursively delete and balance the tree
  std::stack<BinTree> nodes;
  DeleteItemAVL(this->Root, value, nodes);
  
    // re calculate height after removal
  this->Height = this->tree_height(this->Root);
  
  //unsigned int count = count_nodes(this->Root);
  //std::cout << "real count is : " << count << std::endl;
}

/*****************************************************************************/
/*!
 
 \brief
  Private recursive insert function to properly insert an item
 
 \param tree
  Reference to a pointer of the root of the tree
 
 \param value
  What's being added to the tree
 
 \param nodes
  Reference to a stack to keep track of where we went to balance the tree
  after inserting.
 
 \param depth
  How deep down the tree we went. Used to update height

 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::InsertItemAVL(BinTree &tree, const T& value, stack &nodes, int depth)
{
  try
  {
    // found our spot to be
    if(!tree)
    {
      // insert
      tree = this->make_node(value);
      
      //balance
      Balance(nodes);
      
      // increment node counter
      ++(this->NumNodes);
      
      //if(depth > this->Height)
        //++(this->Height);
    }
    else if(value < tree->data)
    {
      // push address of visited node onto the stack
      // move on to left subtree
      nodes.push(tree);
      InsertItemAVL(tree->left, value, nodes, ++depth);
    }
    else // value > tree->data
    {
      // push address of visited node onto the stack
      // move on to right subtree
      nodes.push(tree);
      InsertItemAVL(tree->right, value, nodes, ++depth);
    }
  }
  catch (const BSTException &e)
  {
    throw e;
  }
}

/*****************************************************************************/
/*!
 
 \brief
  Balances an AVL Tree.
 
 \param nodes
  stack of where we went for insertion/deletion
 
 \param Inserting
  Bool to indicate whether we are balancing because of an insertion or deletion.
  If inserting we only need one rotation to fix the balance, if deleting
  we have to back track all the way up the tree.
 
 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::Balance(stack &nodes, bool Inserting)
{
  while(!nodes.empty())
  {
    BinTree y = nodes.top();
    nodes.pop();
    
      // find the node that is now out of balance
    int LeftHeight = this->tree_height(y->left);
    int RightHeight = this->tree_height(y->right);
    
    //compare heights
    // v and w are always the left and right children of u, respectively
    
      // left heavy
    if(LeftHeight > RightHeight + 1)
    {
        // call left havy balance function
      LeftHeavyBalance(y, nodes);
      
        // if inserting only do one rotation
        // else this was called from deleting
        // so we must continue until the stack is empty
      if(Inserting)
        return;
    }
      // right heavy
    else if(RightHeight > LeftHeight + 1)
    {
      RightHeavyBalance(y, nodes);
        // if this was called from insert
        // we are done, if called from delete
        // must keep going until stack is empty
      if(Inserting)
        return;
    }
  }
}

/*****************************************************************************/
/*!
 
 \brief
  Balance if we are right heavy.
 
 \param y
  The node that is out of balance.
 
 \param nodes
  Stack of nodes we traveled. Need to get the parent of y to properly
  rotate.
 
 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::RightHeavyBalance(BinTree &y, stack &nodes)
{
  BinTree u, v, w, NulParent = 0;
  
  u = y->right;
  v = u->left;
  w = u->right;
  
    // height of subtrees at v & w
  int VHeight = this->tree_height(v);
  int WHeight = this->tree_height(w);
  
  /*  y
       \
        u
       /
      v */
  // zig-zag
  if(VHeight > WHeight)
  {
      // promote v twice
    RotateRight(y->right);
    RotateLeft(y);
    
    /*      v
          /   \
         y     u  */
    
    // attach rotation back to the tree
    if(nodes.empty())
      AttachRotation(NulParent, v);
    else
      AttachRotation(nodes.top(), v);
  }
  
  /*    y
         \
          u
           \
            w  */
  
  // zig-zig
  else if(WHeight > VHeight || VHeight == WHeight)
  {
    //  rotate left about y
    
    /*      u
          /   \
         y     w  */
    RotateLeft(y);
    
    // attach rotation back to the tree
    if(nodes.empty())
      AttachRotation(NulParent, u);
    else
      AttachRotation(nodes.top(), u);
  }
}

/*****************************************************************************/
/*!
 
 \brief
  Balance if offending node is left heavy.
 
 \param y
  Offending node
 
 \param nodes
  stack of nodes traveled. needed to get parent of y to rotate
 
 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::LeftHeavyBalance(BinTree &y, std::stack<BinTree>& nodes)
{
  BinTree u, v, w, NulParent = 0;
  
  u = y->left;
  v = u->left;
  w = u->right;
  
  // height of subtrees at v & w
  int VHeight = this->tree_height(v);
  int WHeight = this->tree_height(w);
  
  
  /*      y
         /
        u
       /
      v     */
  // zig-zig
  if(VHeight > WHeight || WHeight == VHeight)
  {
    // rotate right about u

    /*      u
          /   \
         v     y */
    RotateRight(y);
    
    // attach rotation done back to tree
    if(nodes.empty())
      AttachRotation(NulParent, u);
    else
      AttachRotation(nodes.top(), u);
  }
  
  /*       y
          /
         u
          \
           w     */
  
  // zig zag
  else if (WHeight > VHeight)
  {
    // rotate about u, promote w
    
    /*      y
           /
          w
         /
        u        */
    RotateLeft(y->left);
    
    /* rotate about y, promote w again
            w
          /   \
         u     y  */
    RotateRight(y);
    
    // reattach rotations
    if(nodes.empty())
      AttachRotation(NulParent, w);
    else
      AttachRotation(nodes.top(), w);
  }
}

/*****************************************************************************/
/*!
 
 \brief
  Reataches a rotation since we dont inheritanly have a parent pointer.
 
 \param parent
  Parent of the offending node that was rotated.
 
 \param rotation
  The 'top' node (see diagram a few lines above, w is the 'top')
  of a rotation to hook back up.
 
 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::AttachRotation(BinTree &parent, BinTree &rotation)
{
    // if parent is null then we rotated around the root
    // else attach accordginly
  if(!parent)
    this->Root = rotation;
  else
  {
    if(rotation->data < parent->data)
      parent->left = rotation;
    else
      parent->right = rotation;
  }
}

template <typename T>
unsigned int AVLTree<T>::count_nodes(BinTree &Root)
{
  unsigned int count = 0;
  if (Root != NULL)
  {
    count = 1 + count_nodes(Root->left) + count_nodes(Root->right);
  }
  
  return count;
}

/*****************************************************************************/
/*!
 
 \brief
  Rotate a node left
 
 \param tree
  Offending node
 
 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::RotateLeft(BinTree &tree)
{
  BinTree temp = tree;
  tree = tree->right;
  temp->right = tree->left;
  tree->left = temp;
}

/*****************************************************************************/
/*!
 
 \brief
  Rotate a node right
 
 \param tree
  the offending node
 
 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::RotateRight(BinTree &tree)
{
  BinTree temp = tree;
  tree = tree->left;
  temp->left = tree->right;
  tree->right = temp;
}

/*****************************************************************************/
/*!
 
 \brief
  Deleting an item in avl tree.
 
 \param tree
  node to start at (in first call it is the root).
 
 \param value
  Value being removed from the tree
 
 \param nodes
  Stack of nodes we traversed to balance the tree after deletion
 
 */
/*****************************************************************************/
template <typename T>
void AVLTree<T>::DeleteItemAVL(BinTree &tree, const T& value, stack &nodes)
{
    // didnt find item where it should be
    // does not exist in the tree
  if(tree == 0)
    return;
  
  else if(value < tree->data)
  {
      // push visited node onto the stack
      // and move on to left subtree
    nodes.push(tree);
    DeleteItemAVL(tree->left, value, nodes);
  }
  else if(value > tree->data)
  {
      // push visited node onto the stack
      // move on to right subtree
    nodes.push(tree);
    DeleteItemAVL(tree->right, value, nodes);
  }
  else //value == tree->data
  {
      // leaf node deletion, base case
    if(tree->left == 0)
    {
      BinTree temp = tree;
      tree = tree->right;
      this->FreeNode(temp);
      --(this->NumNodes);
      
        // call balance with flag to indicate
        // a deletion happened
        // so must exhaust stack looking for iffending nodes
      Balance(nodes, false);
    }
      // leaf node deletion, base case
    else if (tree->right == 0)
    {
      BinTree temp = tree;
      tree = tree->left;
      this->FreeNode(temp);
      --(this->NumNodes);
      
        // call balance with flag to indicate
        // a deletion happened
        // so must exhaust stack looking for iffending nodes
      Balance(nodes, false);
    }
    else // node has two children
    {
        // find predecessor
        // and then delete source of predecessor
      BinTree pred = 0;
      this->FindPredecessor(tree, pred);
      tree->data = pred->data;
      nodes.push(tree);
      DeleteItemAVL(tree->left, tree->data, nodes);
    }
  }
}

