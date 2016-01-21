/*****************************************************************************/
/*!
\file ChHashTable.cpp
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Assignment 5
\date   11/13/15

\brief
  Implementation of hash table class.

  Functions include:




Hours spent on assignment: 4

Specific portions that gave you the most trouble:
- not much trouble, just using arrays and linked lists which is pretty
  trivial by now.
*/
/*****************************************************************************/


/*****************************************************************************/
/*!

\brief
  constructor

\param Config
  Congifuration struct for thhis object

\param allocator
  Object allocator to manage memory for us, if provided.

*/
/*****************************************************************************/
template <typename T>
ChHashTable<T>::ChHashTable(const HTConfig& Config, ObjectAllocator* allocator) : allocator(allocator), config(Config), stats()
{
    // make the inital table
  table = new ChHTHeadNode[config.InitialTableSize_];

    // record some inital statistics
  stats.TableSize_ = config.InitialTableSize_;
  stats.HashFunc_ = config.HashFunc_;
  stats.Allocator_ = allocator;
}

/*****************************************************************************/
/*!

\brief
  Destructor

*/
/*****************************************************************************/
template <typename T>
ChHashTable<T>::~ChHashTable()
{
    // delete all the nodes
  clear();

    // delete array
  delete [] table;
}

/*****************************************************************************/
/*!

\brief
  Grows the hash table when load factor reaches the maximum allowed.

*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::grow_table()
{
  try
  {
      // record old table size to move nodes to new one
    unsigned old_table_size = stats.TableSize_;

      // calculate new table size
    double factor = std::ceil(stats.TableSize_ * config.GrowthFactor_);
    unsigned new_table_size = GetClosestPrime(static_cast<unsigned>(factor));
    stats.TableSize_ = new_table_size;

      // make the new table
    HeadNode new_table = new ChHTHeadNode[stats.TableSize_];

      //start moving nodes
    for(unsigned i = 0; i < old_table_size; ++i)
    {
      DataNode list = table[i].Nodes;

        // move keys from this list to new table
      while(list)
      {
        DataNode temp = list->Next;

          // get updated index from new table size
        unsigned index = stats.HashFunc_(list->Key, stats.TableSize_);

          // hook up this node to the new table
        list->Next = new_table[index].Nodes;
        new_table[index].Nodes = list;

          // move to the next node
        list = temp;
      }

      // go to next list of keys
    }

      // delete the old table and connect the new one
    delete [] table;
    table = new_table;
    ++stats.Expansions_;
  }
  catch (std::bad_alloc &ba)
  {
    throw(HashTableException(HashTableException::E_NO_MEMORY,
          "No memory is available"));

  }
}

/*****************************************************************************/
/*!

\brief
  Inserts s key/data pair into the hash table

\param Key
  Key to use in hashing function to determine place in the hash table

\param Data
  Information being stored in the hash table

\return
*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::insert(const char *Key, const T& Data)
{
  try
  {
    if( ((stats.Count_ + 1) / static_cast<double>(stats.TableSize_)) > config.MaxLoadFactor_)
      grow_table();
      // place in hash table where this will be inserted
    unsigned index = config.HashFunc_(Key, stats.TableSize_);
    HeadNode head = &table[index];

        // get head of the list of keys
    DataNode list = head->Nodes;

      // increment probe counter for initally finding place
      // in hash table
    ++stats.Probes_;

      // check list for duplicate
    while(list)
    {
        // increment probe counter
      ++stats.Probes_;

        // found a duplicate, throw exception
      if(strncmp(Key, list->Key, MAX_KEYLEN) == 0)
        throw (HashTableException(HashTableException::E_DUPLICATE,
          "Item being inserted is a duplicate"));

          // move to next node
      list = list->Next;
    }

    // duplicate was not found, start inserting


      // make the node
    DataNode insert_node = make_node(Data);
    strncpy(insert_node->Key, Key, MAX_KEYLEN);

      // insert at the front of the list at the correct index
    insert_node->Next = head->Nodes;
    head->Nodes = insert_node;

      // increment item counter
    ++stats.Count_;

      // increment counter for list at table[index]
    ++head->Count;
  }
    // catch ecept from make_node call
  catch (HashTableException &exception)
  {
      // throw it back to client
    throw exception;
  }
}

/*****************************************************************************/
/*!

\brief
  Given a node, removes it from the hash table and deallocates memory.

\param removal
  The node being removed

*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::remove_node(DataNode &removal)
{
    // if client owns the data, give it to them to
    // properly destroy it
  if(config.FreeProc_)
    config.FreeProc_(removal->Data);

  // now delete the node itself

    // if using an allocator give it the allocator
  if(allocator)
    allocator->Free(removal);
  else // else do it ourself
    delete removal;

}

/*****************************************************************************/
/*!

\brief
  Removes a node form the hash table

\param Key
  ID of the data requested to be removed

*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::remove(const char *Key)
{
    // find where key should be and record head of the list
    // incase of removing the first key
  unsigned index = stats.HashFunc_(Key, stats.TableSize_);
  HeadNode head = &table[index];
  DataNode current = head->Nodes, previous = 0;

    // walk list of keys
  while(current)
  {
      // increment probe counter
    ++stats.Probes_;

      // found our key
    if(strncmp(Key, current->Key, MAX_KEYLEN) == 0)
    {
        // fix pointers
      if(previous)
        previous->Next = current->Next;
      else
        head->Nodes = current->Next;

        // decrement counter for this list of keys
        // & overall count
      --head->Count;
      --stats.Count_;
        // hand off node to removal helper function and return
      remove_node(current);
      return;
    }

      // move pointers
    previous = current;
    current = current->Next;
  }
}

/*****************************************************************************/
/*!

\brief
  Finds a node in the hash table

\param Key
  ID of the node requested.

\returns
  Reference to the node requested
*/
/*****************************************************************************/
template <typename T>
const T& ChHashTable<T>::find(const char *Key) const
{
    // find where requested key would be
  unsigned index = stats.HashFunc_(Key, stats.TableSize_);
  DataNode list = table[index].Nodes;

    // walk list of keys looking for requested key
  while(list)
  {
      // increment probe counter
    ++stats.Probes_;

      // found our key, return the Data
    if(strncmp(Key, list->Key, MAX_KEYLEN) == 0)
      return list->Data;

        // move to next key
    list = list->Next;
  }

    // didnt find key requested, throw exception
  throw(HashTableException(HashTableException::E_ITEM_NOT_FOUND,
        "Item requested to be found does not exist"));
}

/*****************************************************************************/
/*!

\brief
  Deletes all nodes from the hash table, DOES NOT delete hash table itself.

*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::clear()
{
    // walk over entire hash table
  for(unsigned i = 0; i < stats.TableSize_; ++i)
  {
      // stat deleting keys
    DataNode list = table[i].Nodes;

      // delete all key/data in this list
    while(list)
    {
      DataNode temp = list->Next;
      remove_node(list);
      list = temp;
    }

      // set head to null
    table[i].Nodes = 0;
  }

    // reset node counter
  stats.Count_ = 0;
}

/*****************************************************************************/
/*!

\brief
  Get statistics about this hash table.

\return
  Statistics of this hash table
*/
/*****************************************************************************/
template <typename T>
HTStats ChHashTable<T>::GetStats() const
{
    // return stats of this object
  return stats;
}

/*****************************************************************************/
/*!

\brief
  Returns reference to the hash table.

\return
  Reference to the hash table.
*/
/*****************************************************************************/
template <typename T>
const typename ChHashTable<T>::ChHTHeadNode* ChHashTable<T>::GetTable() const
{
  return table;
}

/*****************************************************************************/
/*!

\brief
  Makes a node to be inserted into the hash table.

\param Data
  Data to be stored in the node

\return
  Pointer to the node created
*/
/*****************************************************************************/
template <typename T>
typename ChHashTable<T>::DataNode ChHashTable<T>::make_node(const T& Data)
{
  try
  {
      // if we have an allocator, use it
    if(allocator)
    {
      DataNode mem = reinterpret_cast<ChHTNode*>(allocator->Allocate());

      DataNode node = new (mem) ChHTNode(Data);

      return node;
    }

      // no allocator, just use new
    DataNode node = new ChHTNode(Data);

    return node;
  }
    // catach exception from new, throw our own
  catch (std::bad_alloc &ba)
  {
    throw(HashTableException(HashTableException::E_NO_MEMORY,
          "No memory is available"));
  }
}
