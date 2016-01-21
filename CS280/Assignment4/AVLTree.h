/*****************************************************************************/
/*!
 \file AVLTree.h
 \author      Haven Breithaupt
 \par DP email: h.breithaupt\@digipen.edu
 \par Course: CS280
 \par Assignment 4
 \date
 
 \brief
  function prototypes for AVLTree
 */
/*****************************************************************************/



//---------------------------------------------------------------------------
#ifndef AVLTREE_H
#define AVLTREE_H
//---------------------------------------------------------------------------
#include <stack> 
#include "BSTree.h"
#include <iostream>

/// avl tree class
template <typename T>
class AVLTree : public BSTree<T>
{
  public:
      /// making typename for compiler to resolve recognizing bintree*
    typedef typename BSTree<T>::BinTreeNode* BinTree;

      /// defining type for transparency (mostly for myself)
    typedef std::stack<BinTree> stack;
  
    AVLTree(ObjectAllocator *OA = 0, bool ShareOA = false);
    virtual ~AVLTree();
    virtual void insert(const T& value);
    virtual void remove(const T& value);
    
  private:
    // private stuff
  
  void InsertItemAVL(BinTree &tree, const T& value, stack &nodes, int depth);
  void Balance(stack &nodes, bool Inserting = true);
  void RotateLeft(BinTree &tree);
  void RotateRight(BinTree &tree);
  void DeleteItemAVL(BinTree &tree, const T& value, std::stack<BinTree> &nodes);
  void AttachRotation(BinTree &parent, BinTree &rotation);
  void LeftHeavyBalance(BinTree &y, std::stack<BinTree> &nodes);
  void RightHeavyBalance(BinTree &y, std::stack<BinTree>& nodes);
  unsigned int count_nodes(BinTree &Root);
  
};

#include "AVLTree.cpp"

#endif
//---------------------------------------------------------------------------
