using namespace std;

template <typename T, int Size>
size_t BList<T, Size>::nodesize(void)
{
  return sizeof(BNode);
}

template <typename T, int Size>
const typename BList<T, Size>::BNode* BList<T, Size>::GetHead() const
{
  return head_;	
}

template <typename T, int Size>
  BListStats BList<T, Size>::GetStats() const
  {
    return stats;
  }

template <typename T, int Size>
  BList<T, Size>::BList() : head_(0), tail_(0), stats()
  {
      // set Array Size of each node in the stats struct
    stats.ArraySize = Size;
    stats.NodeSize = nodesize();
  }

template <typename T, int Size>
  void BList<T, Size>::copy_node(BNode *copy)
  {
    try
    {
        // add to end of list if
        // list already exists
      if(tail_)
      { 
          // adjust pointers
        tail_->next = make_node();
        tail_->next->prev = tail_;
       
          // move tail pointer
        tail_ = tail_->next;
        tail_->next = 0;
      }
      else // start the list
        tail_ = make_node();
      
      
        // copy data
      for(int i = 0; i < copy->count; ++i)
        tail_->values[i] = copy->values[i];
      
        // copy information
      tail_->count = copy->count;
      
        // if head is null this is the first node
      if(!head_)
      {
          // set up head pointer
        head_ = tail_;
        head_->prev = 0;
      }
    }
      // catch exception from make_node
      // and throw it back
    catch (BListException &excep)
    {
      throw excep;
    }
  }

template <typename T, int Size>
  BList<T, Size>::BList(const BList &rhs)
  {
      // copy stats
    stats.ArraySize = rhs.stats.ArraySize;
    stats.NodeCount = rhs.stats.NodeCount;
    stats.ItemCount = rhs.stats.ItemCount;
    stats.NodeSize = rhs.stats.NodeSize;
    
      // pointer to traverse rhs list
    BNode *rhs_walk = rhs.head_;
    
      // assign head and tail pointers to null
    head_ = 0;
    tail_ = 0;
    
      // travel over rhs list
    while(rhs_walk)
    {
      try
      {
          // copy the node
        copy_node(rhs_walk);
        
          // move to the next node
        rhs_walk = rhs_walk->next;
      }
        // catch exception from make_node and throw it 
        // back to the client
      catch(BListException &excep)
      {
        throw excep;
      }
    }
  }
  
  
template <typename T, int Size>
  BList<T, Size>::~BList()
  { 
      // call clear to delete all nodes
    clear();
  }


template <typename T, int Size>
  BList<T, Size>& BList<T, Size>::operator=(const BList &rhs)
  {
      // self assignment check
    if(this == &rhs)
      return *this;
    
      // copy stats
    stats.ArraySize = rhs.stats.ArraySize;
    stats.NodeCount = rhs.stats.NodeCount;
    stats.ItemCount = rhs.stats.ItemCount;
    stats.NodeSize = rhs.stats.NodeSize;
    
      // pointers to traverse both lists
    BNode *right = rhs.head_;
    
      // call clear on lhs list
      // not particulary efficient if the lhs list
      // is long enough for the copy already
    clear();
    
      // traverse rhs list
    while(right)
    {
        // copy the node form the rhs
      copy_node(right);
      
        // move to the next node
      right = right->next;
    }
    
    return *this;
  }
  
  
  
template <typename T, int Size>
  typename BList<T, Size>::BNode* BList<T, Size>::make_node()
  {
    try
    {
        // create a node
      BNode *create = new BNode;
      
        // return the node
      return create;
    }
      // catch bad alloc from new
    catch(std::bad_alloc &)
    {
        // throw our own exception
      throw BListException(BListException::BLIST_EXCEPTION::E_NO_MEMORY, "No memory is available");
    }
    
  }

  // puch back into a node
template <typename T, int Size>
  void BList<T, Size>::insert_back(BNode *node, const T& value)
  {
      // insert value at the back of this node
    node->values[node->count] = value;
    
      // increment counter of this node
    ++node->count;
    
      // increment item counter
    stats.ItemCount++;
  }
  
template <typename T, int Size>
  void BList<T, Size>::push_back(const T& value)
  {
      // set sorted flag to false
    sorted = false;
    
      // if head is null list is empty
      // start the list
    if(!head_)
    {
        // try making a node
      try
      {
          // make a node
        BNode *create = make_node();
        
          // increment node counter
        stats.NodeCount++;
        
            // attach head to node
        head_ = create;
        
          // attach tail to node
        tail_ = create;
        
          // insert value into node
        insert_back(create, value);
        
          // return 
        return;
      }
        // catch exception from make_node
      catch(BListException &excep)
      {
          // throw it back to client
        throw excep;
      }
    }
    
      // make pointer to walk the list
    BNode *walk = head_;
    
      // walk the list to see if there is a node with space in it
    while(walk)
    {
        // check for space in this node
      if(walk->count < stats.ArraySize)
      {
          // insert value
        insert_back(walk, value);
        
          // job complete, return
        return;
      }
      
        // go to next node
      walk = walk->next;
    }
    
    // we've reached to end of the list without an open spot
    // add a node to the end of the list
    
      // try making a new node
    try
    {
        // make the node
      BNode *create = make_node();
      
        // increment node counter
      stats.NodeCount++;
      
        //attach to end of list
      tail_->next = create;
      
        // hook back to the tail
      create->prev = tail_;
      
        // move tail to the new end of list
      tail_ = tail_->next;
      
        // insert value into the new node at the back
      insert_back(create, value);
      
      return;
    }
      // catch exception from make_node
      // and throw back to client
    catch(BListException &excep)
    {
      throw excep;
    }
  }


template <typename T, int Size>
  void BList<T, Size>::insert_front(BNode *node, const T& value)
  {
      // move data if node is not empty
    if(node->count != 0)
      shift_right(node->values, node->count - 1, 0);
    
    
      // put data at front of array
    node->values[0] = value;
    
      // increment total item counter
    stats.ItemCount++;
    
      // increment item count for this node
    node->count++;
  }

template <typename T, int Size>
  void BList<T, Size>::push_front(const T& value)
  {
      // set sorted flag to false
    sorted = false;
    
     // if head is null list is empty
      // start the list
    if(!head_)
    {
        // try making a node
      try
      {
          // make a node
        BNode *create = make_node();
        
            // attach head to node
        head_ = create;
        
          // attach tail to node
        tail_ = create;
        
          // insert value into node
        create->values[0] = value;
        
        create->count++;
        
        stats.ItemCount++;
        stats.NodeCount++;
        
          // return 
        return;
      }
        // catch exception from make_node
      catch(BListException &excep)
      {
          // throw it back to client
        throw excep;
      }
    }
      
      // pointer to walk the list
    BNode *walk = head_;
    
      // walk the list trying to find a node with empty spaces
    while(walk)
    {
        // if this node had an empty space
        // insert into this node
      if(walk->count < stats.ArraySize)
      {  
        insert_front(walk, value);
          
          // job complete, return
        return;
      }
      
        // go to next node
      walk = walk->next;
    }
    
    // reached end of list without a free space, 
    // insert node at front of list
    
    try
    {
        // try to make node
      BNode *create = make_node();
      
        //increment node counter
      stats.NodeCount++;
      
        // link to front of list
      create->next = head_;
      head_->prev = create;
      
        // move head pointer
      head_ = create;
        
        // put data in node
      create->values[0] = value;
      
        // increment count for this node
      create->count++;
      
        // increment item counter
      stats.ItemCount++;
      
        // job complete, return
      return;
    }
      // catach exception form make_node
      // throw back to client
    catch(BListException &excep)
    {
      throw excep;
    }
    
  }

template <typename T, int Size>
  void BList<T, Size>::split(BNode *left, BNode *right, const T& value, bool current)
  {
    using namespace std;
    //cout << left << endl;
    //cout << right << endl;
      // left is valid (not the head)
      // split it up
    if(left)
    {
      try
      {
        
        if(stats.ArraySize > 1)
        {
          BNode *create = make_node();
          
          int half = stats.ArraySize / 2;
          
            // if left was the current we need to drop
            // data in the fron of the new node
              // copy latter half of data from left node
          for(int i = half; i < stats.ArraySize; ++i)
            create->values[i - half] = left->values[i];
          
          
            // hook up pointers
          create->prev = left;
          create->next = right;
          
          
          left->next = create;
          
          if(left == tail_)
            tail_ = create;
          
          if(right)
            right->prev = create;
          
            // adjust count of broken up node
          left->count /= 2;
          create->count = half;
          
          bool dropped = false;
          
          for(int i = 0; i < left->count; ++i)
          {
            if(value < left->values[i])
            {
              shift_right(left->values, i, left->count);
            
              left->values[i] = value;
              ++left->count;
              dropped = true;
              break;
            }
          }
          
          if(!dropped)
          {
            left->values[left->count] = value;
            ++left->count;
          }
            
          
            // increment counters
          ++stats.NodeCount;
          ++stats.ItemCount;
          
        }
        else
        {
            // make a node
          BNode *create = make_node();
          
          // hook up pointers
          create->prev = left;
          create->next = right;
          right->prev = create;
          
          head_ = create;
          
            // drop data into this node since theres only ino
            // piece per node
          create->values[0] = value;
          ++create->count;
          
            // increment counters
          ++stats.NodeCount;
          ++stats.ItemCount;
        }
      }
      catch(BListException &excep)
      {
        throw excep;
      }
    }
    else
    {
      try
      {
          // make a node
        BNode *create = make_node();
        
          // attach it to the head (right)
        create->next = right;
        right->prev = create;
        
          // drop data in the node
        create->values[0] = value;
        ++create->count;
        
        head_ = create;
        
        ++stats.NodeCount;
        ++stats.ItemCount;
      }
      catch(BListException &excep)
      {
        throw excep;
      }
    }
  }
    
template <typename T, int Size>
  void BList<T, Size>::split_tail(const T& value)
  {
    try
    {
      BNode *create = make_node();
      
      int half = stats.ArraySize / 2;
      
      for(int i = half; i < stats.ArraySize; ++i)
        create->values[i - half] = tail_->values[i];
      
      tail_->next = create;
      
      tail_->count /= 2;
      create->count = half;
      
      create->values[create->count] = value;
      
      ++create->count;
      
      tail_ = tail_->next;
      
      ++stats.NodeCount;
      ++stats.ItemCount;
    }
    catch(BListException &excep)
    {
      throw excep;
    }
  }
    
template <typename T, int Size>
  void BList<T, Size>::insert(const T& value)
  {
      // set sorted flag to true
    sorted = true;
    
      // if list doesnt exist, start it
    if(!head_)
    {
      try
      {
          // make a node
        head_ = make_node();
        
          // put the value right in
        head_->values[0] = value;
        
          // increment node count
        ++head_->count;
          
          // set up pointera
        head_->prev = 0;
        tail_ = head_;
        
          // increment counters
        ++stats.NodeCount;
        ++stats.ItemCount;
        
          // done
        return;
      }
        // catch exception from make_node and throw back to the client
      catch (BListException &excep)
      {
        throw excep;
      }        
    }
    
      // pointer to traverse list
    BNode *walk = head_;
    
      // iterate over list
    while(walk)
    {
        // check data in this node
      for(int i = 0; i < walk->count; ++i)
      {
          // found a potential spot to be
        if(value < walk->values[i])
        {
            // check for space in previous node
            // [10, blank] -> [20, blank], insert 15, [10, 15] -> [20, blank]
            // i is pointing at 20 in the second node
          if(walk->prev && (i == 0) && (walk->prev->count < stats.ArraySize))
          {
            printf("dropping left\n");
              // drop data at the back of the previous node
            walk->prev->values[walk->prev->count] = value;
            
              // increment count of previous node
            ++walk->prev->count;
            
              // increment item counter
            ++stats.ItemCount;
  
              // done
            return;
          }
            // check if this node has room
            // [10,12] -> [20, blank], insert 15, [10,12] -> [15,20]
            // i is pointing at 20 in the second node
          else if(walk->count < stats.ArraySize)
          {
            printf("shifting right\n");
              // shift elements of the next node to the right
            shift_right(walk->values,  walk->count, i);
            
              // drop data in to the right node
            walk->values[0] = value;
            
              // increment count
            ++walk->count;
            
              // increment item counter
            ++stats.ItemCount;
            
              // done
            return;
          }
            // time to split nodes since both are full
          else
          {
            printf("splitting\n");
              // split node to the left
            if(i == 0)
            {
              split(walk->prev, walk, value, false);
            }
            else
            {
              split(walk, walk->next, value, true);
            }
            
              // done
            return;
          }
            
        }
      }
      
        // go to next node
      walk = walk->next;
    }
    
    if(tail_->count < stats.ArraySize)
    {
      printf("tail\n");
      tail_->values[tail_->count] = value;
      ++tail_->count;
      
      ++stats.ItemCount;
    }
    else
    {
      split_tail(value);
      
    }
  }

template <typename T, int Size>
  void BList<T, Size>::shift_left(T* data, int from, int to)
  {
    for(;from < to; ++from)
      data[from] = data[from + 1];
  }
        
template <typename T, int Size>
  void BList<T, Size>::shift_right(T* data, int from, int to)
  { 
      // shift data to the right in an array 
      // of T items
    for(; from >= to; --from)
        data[from + 1] = data[from];
  }
      

template <typename T, int Size>
  void BList<T, Size>::remove_node(BNode* node)
  {
      // move haed if needed
    if(node == head_)
      head_ = head_->next;
    
      // move tail if needed
    if(node == tail_)
      tail_ = tail_->prev;
    
      // if node is NOT the head
      // link prev pointer
    if(node->prev)
      node->prev->next = node->next;
    
      // if node is NOT the tail
      // link prev pointer
    if(node->next)
      node->next->prev = node->prev;
    
      // decrement counters
    --stats.ItemCount;
    --stats.NodeCount;
    
      // delete node
    delete node;
  }
  
template <typename T, int Size>
  void BList<T, Size>::remove(int index)
  {
      // bad index
    if(index < 0)
       throw BListException(BListException::BLIST_EXCEPTION::E_BAD_INDEX, 
                            "Invalid Index Requested");
      // pointer to travese list
    BNode *walk = head_;
    
    int node_count = 0;
    for(; node_count < index / stats.ArraySize; ++node_count)
    {
        // index requested was invalid, throw exception
      if(!walk)
        throw BListException(BListException::BLIST_EXCEPTION::E_BAD_INDEX, 
                             "Invalid Index Requested");
      
        // move to next node
      walk = walk->next;
    }
       
    // if exception was not thrown, we have arraived at correct node
      
      // if this is the only piece of data in the node
      // just remove the node entirely
    if(walk->count == 1)
    {
        // call remove_node
        // to remove this node from the list
      remove_node(walk);
    }
    else
    {
        // shift data to the left
      for(int i = index % stats.ArraySize; i < walk->count; ++i)
        walk->values[i] = walk->values[i + 1];
         
        // decrement node count
        // and overall item count
      --walk->count;
      --stats.ItemCount;
    }
  }


template <typename T, int Size>
  void BList<T,Size>::remove_by_value(const T& value)
  {
      // pointer to traverse list
    BNode *walk = head_;
    
      // traverse nodes
    while(walk)
    {
        // check data in this node
      for(int i = 0; i < walk->count; ++i)
      {
          // we found data requested
        if(walk->values[i] == value)
        {
            // if this node has only one piece of data in it
            // (the one being removed) just remove the node entirely
          if(walk->count == 1)
          {
              // remove the node
            remove_node(walk);
            
              // stop working, return
            return;
          }
            // shift data to the left to remove data
          shift_left(walk->values, i, walk->count);
          
            // decrement node count and overall item counter
          --walk->count;
          --stats.ItemCount;
        }
      }
      
        // go to next node
      walk = walk->next;
    }
  }

/*template <typename T, int Size>
  int BList<T, Size>::BinarySearch(int *array, int size, int value)
  {
     if (size <= 1)
      return 1;

    int count = 0;
    int left = 0, right = size - 1;
    while (right >= left)
    {
      count++;
      int middle = (left + right) / 2;
      if (value == array[middle])
        return count;
  
      if (value < array[middle])
        right = middle - 1;
      else
        left = middle + 1;
    }
    return count;
  }*/

template <typename T, int Size>
  int BList<T, Size>::BinarySearchIndex(T *array, int first, int last, int value)
  {
    
      // index of value
    int index;
    
      // base case to escape recursion
    if(first == last && array[first] != value)
       return -1;
    
      // middle of array
    int middle = ( first + last ) / 2;
    
      // if we found our value
      // index = middle
    if(array[middle] == value)
      index = middle;
    
      // else if its to the left
      // make recursive call to preserve index value
    else if (value < array[middle])
      index = BinarySearch(array, first, middle - 1, value);
    
      // else if the value is to the right
      // make recursive call to preserve index value
    else
      index = BinarySearch(array, middle + 1, last, value);
        
        
    return index;
  }

template <typename T, int Size>
  int BList<T, Size>::find(const T& value) const
  {
      // pointer to traverse list
    BNode *walk = head_;
    
      // counter to keep track of how many nodes we have traversed
      // for conversion ito proper index return value
    int node_count = 0;
    
    while(walk)
    {
        // if insert was used
        // use binary search to find index
      if(sorted)
      {
      }
        // else push front/back was used
        // so we must use linear search
      else
      {
          // check data in this node
        for(int i = 0; i < walk->count; ++i)
        {
            // found data looking for
            // return proper index;
          if(walk->values[i] == value)
            return node_count * stats.ArraySize + i;
        }
      }
        // move to next node
      walk = walk->next;
      
        // increment node counter
      ++node_count;
    }
    
      // didnt find what was requested, return -1
    return -1;
  }


template <typename T, int Size>
  T& BList<T, Size>::operator[](int index)
  { 
      // calculate how many nodes deep need to walk to get
      // to requested index
    int node_deep = index / stats.ArraySize;
    
    BNode *walk = head_;
    
    for(int i = 0; i < node_deep; i++)
      walk = walk->next;
    
      // return index data
    return walk->values[(index % stats.ArraySize)  - 1];
      
  }


template <typename T, int Size>
  const T& BList<T, Size>::operator[](int index) const
  {
    
      // calculate how many nodes deep need to walk to get
      // to requested index
    int node_deep = index / stats.ArraySize;
    
    BNode *walk = head_;
    
    for(int i = 0; i < node_deep; i++)
      walk = walk->next;
    
      // return index data
    return walk->values[(index % stats.ArraySize)  - 1];
      
  }

template <typename T, int Size>
  size_t BList<T, Size>::size(void) const
  {
      // return total item counter
    return stats.ItemCount;
  }

template <typename T, int Size>
  void BList<T, Size>::clear(void)
  {
    
      // temp pointer to walk ahead of head
    BNode *temp = head_;
    
      // while there are nodes to delete
    while(head_)
    {
        // move to next node
      temp = head_->next;
      
        // delete current node
      delete head_;
      
        // move up to temp
      head_ = temp;
    } 
    
      // set pointers and stats to nul
      // this is mostly for case when called
      // by operator=
    head_ = 0;
    tail_ = 0;
  }




