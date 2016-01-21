/*****************************************************************************/
/*!
\file             ObjectAllocator.cpp
\author           Haven Breithaupt
\par DP email:    h.breithaupt\@digipen.edu
\par Course:      CS280
\par              Assignment 1
\date             9/8/15

\brief
  Implementation of custom memory manager.
  
  Functions Include:
    Constructor/Destructor
    GetConfig - returns configuration of this instantiation
    GetStats - Get statistics from this instantiation
    GetPageList - returns pointer to internal page list
    write_signatures - writes signatures to an entire page
    ImplementedExtraCredit
    allocate_new_page - allocates new page of memory for use (if permitted)
    Allocate - gives free node to client
    header_free - does housekeeping on header when a node is given back to the manager
    header_assignment - writes header data to node being given to client
    DumpMemoryInUse - dumps memory being used by the client, calls a callback function
                      defined by the client
    FreeEmptyPages - removes pages where all nodes aree free (not implemented)
    Free - returns node back to manager
    ValidatePages - checks fro corruption over the entire memory being used by the manageer
    hand_over_node - does some house-keeping when giving a node to the client
    check_bounds - checks the bounds of a pointer for verification that it is
                   an object
    check_padding - checks padding for corruption on a given object


Hours spent on assignment: 20

Specific portions that gave you the most trouble: 
  Nothing in particular was incredibly taxing, but getting all the pieces to fit 
  together and synch up was chalenging.
*/
/*****************************************************************************/

#include "ObjectAllocator.h"

/*****************************************************************************/
/*!

\brief 
  Constructor for the class.

\param ObjectSize
  Size of the objects used in this manager.

\param config
  A configuration struct for this manager

*/
/*****************************************************************************/
ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig& config) : stats(), configuration(config)
{
  try
  {

      // if this flag is set DO NOT USE object allocate
    if(config.UseCPPMemManager_)
    {
        // set PageList_ to destructor to recognize
      PageList_ = 0;
      
        // do nothing
      return;
    }

      // record Object Size in stat struct for this manager
    stats.ObjectSize_ = ObjectSize;

      // start calculating bytes needed for every page
      // start with page list pointer at front of page
    stats.PageSize_ += sizeof(void*);

      // calculate bytes for objects on the page
    stats.PageSize_ += ObjectSize * config.ObjectsPerPage_;
      
      //add padding bytes if needed
    if(config.PadBytes_ != 0)
      stats.PageSize_ += 2 * config.PadBytes_ * config.ObjectsPerPage_;

    total_header_size = config.HBlockInfo_.size_;

      // add header bytes if needed
    stats.PageSize_ += total_header_size * config.ObjectsPerPage_;

      // allocate array
    char * new_manager = new char[stats.PageSize_];

      // increment page counter after successful new
    stats.PagesInUse_++;

      // set free objects to how many objects fit on a page
      // because theres only one page constructed
    stats.FreeObjects_ = config.ObjectsPerPage_;

      // if debug mode is on, wrtie signatures to the page
    if(config.DebugOn_)
      write_signatures(new_manager);

      // point page list at beginning of page
    PageList_ = reinterpret_cast<GenericObject*>(new_manager);

      // set next to null
    PageList_->Next = 0;

      // hold front bytes off page as variable for reuse
    char * front_bytes = new_manager + sizeof(void*) + config.PadBytes_ +
                         total_header_size;

      // get initial pointer to first free node
    FreeList_ = reinterpret_cast<GenericObject *>(front_bytes);
    FreeList_->Next = 0;

    size_t object_length = stats.ObjectSize_ + 2 * configuration.PadBytes_ + configuration.HBlockInfo_.size_;
      // assign free list
      // since first pointer is manually claculated
      // do ObjectsPerPage - 1 iterations
    for(unsigned int i = 1; i < config.ObjectsPerPage_; i++)
    {
        // find next object by adding next_object to front_bytes 
      GenericObject * temp = reinterpret_cast<GenericObject *>
                             (front_bytes + i * object_length);

        // link pointers
      temp->Next = FreeList_;
      
        // move FreeList to next node
      FreeList_ = temp;
    }
  }
    // catch exception from operator new
  catch(std::bad_alloc &)
  {
      // throw own exception
    throw OAException(OAException::E_NO_MEMORY, "No memory available");
  }
}

/*****************************************************************************/
/*!

\brief
  Destructor for the class.

*/
/*****************************************************************************/
ObjectAllocator::~ObjectAllocator()
{
    // while there are pages to delete
  while(PageList_)
  {
      // if there are external headers need to do some more work 
      // to destroy those
    if(configuration.HBlockInfo_.type_ == OAConfig::hbExternal)
    {
        // calculate the offset for the first object
      char * object = reinterpret_cast<char *>(PageList_) + configuration.PadBytes_ + 2 * sizeof(void*);
      
        // iterate every object on the page
      for(unsigned int i = 0; i < configuration.ObjectsPerPage_; i++)
      {
          // find where the header would be
        char * header = object - configuration.PadBytes_ - sizeof(void*);

          // check just the first byte, if there is anything there
          // that means an external header is there
        if(*header)
          header_free(object);

          // move to the next onject
        object += stats.ObjectSize_ + 2 * configuration.PadBytes_ + sizeof(void*);
      }
    }
      // cast pagelist ptr to char pointer
    char * page = reinterpret_cast<char *>(PageList_);
    
      // move pagelist ptr to next page
    PageList_ = PageList_->Next;

      // delete the entire page
    delete [] page;
  }
}

/*****************************************************************************/
/*!

\brief
  Gets the configuration information for this manager.

\return
  Returns the configuration struct for this manager.

*/
/*****************************************************************************/
OAConfig ObjectAllocator::GetConfig(void) const
{
    // return config for this manager
  return configuration;
}

/*****************************************************************************/
/*!

\brief
  Gets statistics for this manager ( how many allocations, how many frees, etc).

\return
  Returns the statistics struct for this manager.
*/
/*****************************************************************************/
OAStats ObjectAllocator::GetStats(void) const
{
    // return statistics for this manager
  return stats;
}

/*****************************************************************************/
/*!

\brief
  Returns the PageList pointer for all the pages used by this manager.

\return
  Pointer to the internal page list.
*/
/*****************************************************************************/
const void *ObjectAllocator::GetPageList(void) const 
{
    // return pointer to page list
  return PageList_;
}

/*****************************************************************************/
/*!

\brief
  Writes signatures on all memory used by this manager.
  Used for debugging purposes only.

\param page
  A pointer to the page that needs to be written to.

*/
/*****************************************************************************/
void ObjectAllocator::write_signatures(char *page)
{
    // write first bytes to unallocted
  memset(page, UNALLOCATED_PATTERN, sizeof(void*));

    // move pointer past where PageList pointer will be
  page += sizeof(void*);

  for(unsigned i = 0; i < configuration.ObjectsPerPage_; i++)
  {
      // if headers were requested
    if(configuration.HBlockInfo_.type_ != OAConfig::hbNone)
    {
        // set header bytes to 0
      memset(page, 0, total_header_size);

        // skip over header written
      page += total_header_size;
    }

      // if pad bytes were requested
    if(configuration.PadBytes_)
    {
        // wrtie left pad bytes
      memset(page, PAD_PATTERN, configuration.PadBytes_);

        // move pad bytes written
      page += configuration.PadBytes_;

        // write unallocated bytes over object
      memset(page, UNALLOCATED_PATTERN, stats.ObjectSize_);

        // move over object written
      page += stats.ObjectSize_;

        // write right side pad bytes
      memset(page, PAD_PATTERN, configuration.PadBytes_);

        // move over bytes written
      page += configuration.PadBytes_;
    }
    else
    {
      memset(page, UNALLOCATED_PATTERN, stats.ObjectSize_);
      page += stats.ObjectSize_;
    }
  }
}

/*****************************************************************************/
/*!

\brief
  Returns whether or not the extra credit portions are implemented.

\return
  A bool if the extra credit is implemented or not.
*/
/*****************************************************************************/
bool ObjectAllocator::ImplementedExtraCredit(void)
{
    // exrta credit IS NOT implemented
  return false;
}

  // make another page of nodes
  // if this is called assume FreeList_ is null
/*****************************************************************************/
/*!

\brief
  Makes a new page of memory (if allowed,available) for the manager.

*/
/*****************************************************************************/
void ObjectAllocator::allocate_new_page(void)
{
  try
  {
      // allocated new page
      // pagesize already calculated in constructor
    char * page = new char[stats.PageSize_];

      // increment number of free objects available
    stats.FreeObjects_ += configuration.ObjectsPerPage_;

      // increment page counter
    stats.PagesInUse_++;

      // if debug mode is on write signatures to the page
    if(configuration.DebugOn_)
      write_signatures(page);

      // create pointer to page allocated
    GenericObject * next_page = reinterpret_cast<GenericObject *>(page);

      // link to rest of pages
    next_page->Next = PageList_;

      // move PageList_ ptr
    PageList_ = next_page;

      // calculate fist bytes offset for ruse
    char * front_bytes = page + sizeof(void*) + total_header_size + configuration.PadBytes_;

      // point free list at first object
    FreeList_ = reinterpret_cast<GenericObject *>(front_bytes);
    
      // set next to null
    FreeList_->Next = 0;

      // link rest of objects into free list
    for(unsigned int i = 1; i < configuration.ObjectsPerPage_; i++)
    {

        // find next object
      GenericObject *next_object = reinterpret_cast<GenericObject*>(front_bytes + i * 
                                (stats.ObjectSize_ + 2 * configuration.PadBytes_ + total_header_size));


        // link to free list
      next_object->Next = FreeList_;

        // move free list pointer
      FreeList_ = next_object;
    }
  }
  catch(std::bad_alloc &)
  {
      // throw allocation exception to client
    throw OAException(OAException::E_NO_MEMORY, "No memory available");
  }
}


//////////////////////////////////////////////////
// DO NOT FORGET TO COME BACK AND IMPLEMENT HEADER FEATURES
//////////////////////////////////////////////////
/*****************************************************************************/
/*!

\brief
  Hands a free node to the client from the manager.

\param label
  A label for the node they want to use. Label is ONLY used when
  external headers are used.

\return
*/
/*****************************************************************************/
void *ObjectAllocator::Allocate(const char *label)
{
      // if this flag is set, bypass
      // using ObjectAllocator and use new directly
  if(configuration.UseCPPMemManager_)
  {
    try
    { 
        // increment allocation counter
      stats.Allocations_++;

        // update most objects if needed
      if(stats.Allocations_ > stats.MostObjects_)
        stats.MostObjects_ = stats.Allocations_;

        // allocate simple pointer
      int * temp = new int;

        // give it to client
      return temp;

    }
    catch(std::bad_alloc &)
    {
        // catch exception from new, still throw ObjectAllocator related exception
      throw OAException(OAException::E_NO_MEMORY, "No memory available");
    }
  }

      // if FreeList is valid it's pointing at free node
    if(FreeList_)
    {
        // assign header to to node that will be given to client
      header_assignment(reinterpret_cast<char*>(FreeList_), label);
    
        // hand over to the node to the client
      return hand_over_node();
    }
      // if freelist is null attempt making another page
    else
    {
        // if max pages is 0 (unlimited) just make another page
      if(configuration.MaxPages_ == 0)
      {
          // make another page
        allocate_new_page();

          // assign headers
        header_assignment(reinterpret_cast<char*>(FreeList_), label);

        char * object = reinterpret_cast<char*>(FreeList_) + sizeof(void*);

        memset(object, ALLOCATED_PATTERN, stats.ObjectSize_ - sizeof(void*));

          // ahnd the node to the client
        return hand_over_node();

      }
        // if pages in use < max pages make another pages
      else if((stats.FreeObjects_ == 0) && stats.PagesInUse_ < configuration.MaxPages_)
      {
          // make another page
        allocate_new_page();

          // assign header to node going to be given 
          // to client
        header_assignment(reinterpret_cast<char*>(FreeList_), label);

        char * object = reinterpret_cast<char*>(FreeList_) + sizeof(void*);

        memset(object, ALLOCATED_PATTERN, stats.ObjectSize_ - sizeof(void*));

          // hand over the node to the client
        return hand_over_node();
      }
      else // pages have reached the limit, throw exception
      {
        throw OAException(OAException::E_NO_PAGES, "No more pages can be allocated");
      }
    }
  }

/*****************************************************************************/
/*!

\brief
  Deletes relevant header information when a node is released from the client.

\param object
  Pointer to the object that was released.

*/
/*****************************************************************************/
void ObjectAllocator::header_free(char *object)
{
  if(configuration.HBlockInfo_.type_ == OAConfig::hbBasic)
  {
      // move backwards to start of header
    object -= 5 + configuration.PadBytes_;

      // zero out header block
    memset(object, 0, 5);

  }
  else if(configuration.HBlockInfo_.type_ == OAConfig::hbExtended)
  {
      // back pedal to start of header
    object -= 5 + configuration.PadBytes_;

      // zero out header block
    memset(object, 0, 5);

      // leave user defined bytes alone ?

  }
  else if(configuration.HBlockInfo_.type_ == OAConfig::hbExternal)
  {
      // create a double pointer to save location of node on the page
    MemBlockInfo **header = reinterpret_cast<MemBlockInfo **>(
                            object - configuration.PadBytes_ - sizeof(void*));

      // delete the label
    delete [] (*header)->label;

      // delete the node
    delete *header;

      // zero out the bytes occupied by the pointer
    char * node = reinterpret_cast<char *>(header);
    memset(node, 0, sizeof(void*));

  }
}

  // set header bytes when client requests node
  // parameter is pointer to an onject so header is BEFORE pointer sent
/*****************************************************************************/
/*!

\brief
  Fills in header information when a node is given to the client.

\param object
  Pointer to the object given to the client.

\param label
  Label for the header. Used ONLY when external headers are used.

*/
/*****************************************************************************/
void ObjectAllocator::header_assignment (char * object, const char * label)
{
  if(configuration.HBlockInfo_.type_ == OAConfig::hbBasic)
  {

      // back pedal over pad bytes and an additional byte to 
      // get to the flag byte
    object -= configuration.PadBytes_ + 1;

      // set flag byte
    *object = 0x01;

      // grab the first 4 bytes of header as an int ptr
    unsigned int * alloc_num = reinterpret_cast<unsigned int *>(object - sizeof(int));

      // set allocation number of this block
    *alloc_num = ++stats.Allocations_;
  }
  else if(configuration.HBlockInfo_.type_ == OAConfig::hbExternal)
  {
      // back pedal to start of header pointer
    object -= configuration.PadBytes_ + sizeof(void*);

    try
    {
        // allocate external header
      MemBlockInfo * ext_header = new MemBlockInfo;

        // set fields in header
      ext_header->in_use = true;
      ext_header->alloc_num = ++stats.Allocations_;
      
        // check if label was provided
      if(label)
      {
          // allocate space for label
        ext_header->label = new char[strlen(label) + 1];
        
          // copy label into header
        strcpy(ext_header->label, label);
      }
      else
      {
          // if no label was provided insert NUL into label
        ext_header->label = new char[1];
        ext_header->label[0] = 0;
      }

        // save address of allocated header in the page
      MemBlockInfo ** header_node = reinterpret_cast<MemBlockInfo **>(object);
      *header_node = ext_header;
      
    }
    catch(std::bad_alloc &)
    {
      throw OAException(OAException::E_NO_MEMORY, "No memory available");
    }
  }
  else if(configuration.HBlockInfo_.type_ == OAConfig::hbExtended)
  {
      // back pedal to flag byte of header
    object -= configuration.PadBytes_ + 1;

      // set flag btye
    *object = 0x01;

      // grab 4 byte counter
    unsigned int * alloc_num = reinterpret_cast<unsigned int*>(object - sizeof(int));

      // increment allocation counter
    *alloc_num = ++stats.Allocations_;

      // get a short * for the use counter
    short * use_counter = reinterpret_cast<short*>(reinterpret_cast<char*>(alloc_num) - 2);

        // increment use counter for this block
    (*use_counter)++;
  }
}

/*****************************************************************************/
/*!

\brief
  Dumps the memory that is currently in use by the client.

\param fn
  A callback function defined by the client.

\return
  How many nodes were dumped.
*/
/*****************************************************************************/
unsigned ObjectAllocator::DumpMemoryInUse(DUMPCALLBACK fn) const
{
    // create pointer to walk pages
  GenericObject *temp = PageList_;

    // 
  unsigned count = 0;
    
    // calculate offset from the front of the page
  size_t offset = sizeof(void*) + configuration.PadBytes_ + total_header_size;
  
    // calculate total length of a block
  size_t object_length = stats.ObjectSize_ + 2 * configuration.PadBytes_ + total_header_size;

    // walk every page
  while(temp)
  {
      // get pointer to first object on page
    unsigned char * object = reinterpret_cast<unsigned char *>(temp) + offset;

      // iterate every object on this page
    for(unsigned int i = 0; i < configuration.ObjectsPerPage_; i++)
    {
        // if this block is allocated, call the callback function
        // and increment InUse counter
      if(*object == ALLOCATED_PATTERN)
      {
        fn(reinterpret_cast<char*>(object), stats.ObjectSize_);
        count++;
      }

        // move to next object
      object += object_length;
    }

      // move to next page
    temp = temp->Next;
  }

    // return number of blocks in use
  return count;
}

/*****************************************************************************/
/*!

\brief
  Frees empty pages, part of extra credit.

\return
  How many pages were freed.
*/
/*****************************************************************************/
unsigned ObjectAllocator::FreeEmptyPages(void)
{
  return 0;
}

/*****************************************************************************/
/*!

\brief
  Client uses this to return a node to the manager.

\param Object
  Object being released by the client.

*/
/*****************************************************************************/
void ObjectAllocator::Free(void *Object)
{
    // if this is flag is set, bypass ObjectAllocater functionality
    // use delete explicitly
  if(configuration.UseCPPMemManager_)
  {
      // cast object to int * to be useful
    int * freed = reinterpret_cast<int *>(Object);

      // delete the object passed in
    delete freed;

      // increment deallocation counter
    stats.Deallocations_++;

      // return from function
    return;
  }

    // if debug mode is enable, do some checks
  if(configuration.DebugOn_)
  {
      // try checking the bounds and padding for corruption
    try
    {
      check_bounds(reinterpret_cast<char*>(Object)); 
      
      if(configuration.PadBytes_)
        check_padding(reinterpret_cast<unsigned char*>(Object));
    }
      // catch any exception the error checking functions throw
      // and throw them back again to client
    catch(OAException &exception) 
    {
      throw exception;
    }
  }

    // if free list is valid add this node to the front
  if(FreeList_)
  {
      // reinterpret to generic object
    GenericObject * real_object = reinterpret_cast<GenericObject *>(Object);

      // add to front of free list
    real_object->Next = FreeList_;

    stats.FreeObjects_++;
    stats.ObjectsInUse_--;
    stats.Deallocations_++;

      // move FreeList
    FreeList_ = real_object;
    
  }
  else // restart free list
  {
      // reinterpret to generic object
    GenericObject * real_object = reinterpret_cast<GenericObject *>(Object);

      // set next to null since its only node on free list
    real_object->Next = 0;

    stats.FreeObjects_++;
    stats.ObjectsInUse_--;
    stats.Deallocations_++;
      // move FreeList_
    FreeList_ = real_object;
  }

    // remove any relevant data from the header of freed object
  header_free(reinterpret_cast<char*>(Object));
}

/*****************************************************************************/
/*!

\brief
  Checks for corruption over the entire manager. Checks ONLY pad bytes
  for corruption.

\param fn
  A callback function defined by the client to be used when a corrupted
  object is found.

\return
  How many corrupted objects were found.
*/
/*****************************************************************************/
unsigned ObjectAllocator::ValidatePages(VALIDATECALLBACK fn) const
{
    // copy page_list
  GenericObject * temp = PageList_;

  // calculate offsets
  size_t offset = sizeof(void*) + total_header_size + configuration.PadBytes_;
  size_t object_length = stats.ObjectSize_ + 2 * configuration.PadBytes_ + total_header_size;

  unsigned corrupted = 0;
    // iterate pages
  while(temp)
  {
      // get object pointer
    unsigned char * object = reinterpret_cast<unsigned char *>(temp);
    
      // point to first object
    object += offset;

      // iterate every object
    for(unsigned i = 0; i < configuration.ObjectsPerPage_; i++)
    {
      try
      {
          // check the padding for corruption on this node
        check_padding(object);

          // move to next object 
          // IF OBJECT EXAMINED IS UNCORRUPTED
        object += object_length;
      }
        // if a block is corrupted call the call back function
      catch(OAException &)
      {
          // increment corrupted counter
        corrupted++;

          // move to next object for next iteration
        object += object_length;

          // call call back function for this block
        fn(object, stats.ObjectSize_);
      }
    }
      // move to next page
    temp = temp->Next;
  }
  return corrupted;
}

/*****************************************************************************/
/*!

\brief
  Gives a node to the client while doing some housekeeping before
  it's released.

\return
  Pointer to the node being given to the client.
*/
/*****************************************************************************/
void * ObjectAllocator::hand_over_node(void)
{
      // capture current freelist position
    GenericObject *object = FreeList_;
    
    char *prev_free = reinterpret_cast<char *>(FreeList_);

      // move free list to the next node
    FreeList_ = FreeList_->Next;

    if(configuration.DebugOn_)
      memset(prev_free, ALLOCATED_PATTERN, sizeof(void*));

      // increment object counter
    stats.ObjectsInUse_++;

    if(stats.ObjectsInUse_ > stats.MostObjects_)
      stats.MostObjects_ = stats.ObjectsInUse_;

    stats.FreeObjects_--;

      // increment allocation counter if there are no headers
      // if there are headers allocation will be monitored
      // in header_assignment
    if(configuration.HBlockInfo_.type_ == OAConfig::hbNone)
      ++stats.Allocations_;

      // return first free object on list
    return object;
}

/*****************************************************************************/
/*!

\brief
  Checks the bounds of a potential object. Verifies that pointer given
  was valid.

\param Object
  Pointer trying to verify.

*/
/*****************************************************************************/
void ObjectAllocator::check_bounds(char *Object)
{
    // create temp pointer to walk pages
  GenericObject * temp_page = PageList_;

    // find page object is on
  while(temp_page)
  {
      // calculate difference of object 
      // requested to be free and the beginning of current page
    size_t page_difference = static_cast<size_t>(Object - reinterpret_cast<char*>(temp_page));

      // if distance between object and beginning of page is < page size
      // we found correct page
    if(page_difference < stats.PageSize_)
      break;

      // move to next page
    temp_page = temp_page->Next;
  }

    // if we reached end of page list
    // object couldnt be found so client gave bad address
  if(!temp_page)
    throw OAException(OAException::E_BAD_BOUNDARY, "Bad boundary received");

    // find first object on this page for comparison
  char * first_object = reinterpret_cast<char*>(temp_page) +
                        configuration.PadBytes_ + total_header_size + sizeof(void*);

    // find difference from freed object and first object on page
  size_t difference_Object_first = static_cast<size_t>(Object - first_object);

    // calculate length of node
  size_t object_length = stats.ObjectSize_ + 
                         2 * configuration.PadBytes_ + 
                         total_header_size;

  /*cout << "left hand " << difference_freed_first << endl;
  cout << "right hand " << difference_first_page << endl;*/
    // check if parameter given is actually an object
  if(difference_Object_first % object_length != 0)
    throw OAException(OAException::E_BAD_BOUNDARY, "Bad boundary received");

  // at this point we have real object pointer, check for double free

    // skip to object bytes for verification
  unsigned char *verify = reinterpret_cast<unsigned char*>(Object) + sizeof(void*);

  for(unsigned int i = 0; i < stats.ObjectSize_ - sizeof(void*);i++, verify++)
  {
    if(*verify == FREED_PATTERN)
      throw OAException(OAException::E_MULTIPLE_FREE, "Double Free");

  } 
    // write freed pattern to successfully freed node
  memset(Object, FREED_PATTERN, stats.ObjectSize_);
}

/*****************************************************************************/
/*!

\brief
  Checks the padging of an object looking for corrupted bytes.

\param Object
  The Object to check corruption for.

*/
/*****************************************************************************/
void ObjectAllocator::check_padding(unsigned char *Object) const
{
    // get pointers to left and right padding
  unsigned char * left_padding = Object - configuration.PadBytes_;
  unsigned char * right_padding = Object + stats.ObjectSize_;

    // iterate over the padding
  for(unsigned int i = 0; i < configuration.PadBytes_; i++)
  {
      // if data doesnt match pre defined pattern, throw exception
    if(*left_padding != PAD_PATTERN || *right_padding != PAD_PATTERN)
    {
      /*printf("Left Padding is : %02X\n", *left_padding);
      printf("Right Padding is : %02X\n", *right_padding);
      cout << endl;*/
      throw OAException(OAException::E_CORRUPTED_BLOCK, "This block has been corrupted");
    }

    left_padding++;
    right_padding++;
  }
}

