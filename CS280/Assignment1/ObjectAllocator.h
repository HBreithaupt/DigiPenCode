/*****************************************************************************/
/*!
\file ObjectAllocator.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS280
\par Assignment 1
\date 9/8/15

\brief
  Prototypes of ObjectAllocator functionality.

*/
/*****************************************************************************/

//---------------------------------------------------------------------------
#ifndef OBJECTALLOCATORH
#define OBJECTALLOCATORH
//---------------------------------------------------------------------------

#include <string.h>
#include <iostream>

// If the client doesn't specify these:
static const int DEFAULT_OBJECTS_PER_PAGE = 4;  
static const int DEFAULT_MAX_PAGES = 3;


// DO NOT EDIT
/*! Exception class used in Object Allocator */
class OAException
{
  public:
			///< Possible exception codes
    enum OA_EXCEPTION 
		{
			E_NO_MEMORY,      ///< out of physical memory (operator new fails)
			E_NO_PAGES,       ///< out of logical memory (max pages has been reached)
			E_BAD_BOUNDARY,   ///< block address is on a page, but not on any block-boundary
			E_MULTIPLE_FREE,  ///< block has already been freed
			E_CORRUPTED_BLOCK ///< block has been corrupted (pad bytes have been overwritten)
		};

    /*!
      \brief
        Constructor for exception class used in ObjectAllocator
        
      \param ErrCode
        Error code chosen from enum above for type of error that occured
        
      \param Message
        Human readable string to describe the error that occured
    */
    OAException(OA_EXCEPTION ErrCode, const std::string& Message) : error_code_(ErrCode), message_(Message) {};

    virtual ~OAException() {
    }
      /*! 
        \brief
          returns error code of exception thrown 
        
        \return 
          Returns OA_EXCEPTION code for error that occured
      */
    OA_EXCEPTION code(void) const { 
      return error_code_; 
    }

      /*! 
        \brief
          returns string of error that occured
        
        \return 
          Returns human readable string to describe the error that occured
      */
    virtual const char *what(void) const {
      return message_.c_str();
    }
  private:  
    OA_EXCEPTION error_code_; ///< OA_EXCEPTION enum for type of error that occured
    std::string message_;     ///< human readable string to describe error
};

/*! ObjectAllocator configuration parameters */
struct OAConfig
{
	static const size_t BASIC_HEADER_SIZE = sizeof(unsigned) + 1; ///< allocation number + flags
	static const size_t EXTERNAL_HEADER_SIZE = sizeof(void*);     ///< just a pointer

      /*! types of headers to choose from */
	enum HBLOCK_TYPE{hbNone, hbBasic, hbExtended, hbExternal};
  
      /*! header block fonfiguration */
	struct HeaderBlockInfo
	{
		HBLOCK_TYPE type_;  ///< type of header used in object allocator
		size_t size_;       ///< size of header block
		size_t additional_; ///< additional bytes needed for extended block
      
        /*! 
          \brief
            Constructor for HeaderBlockInfo struct
            
          \param type
            Type of header block being used in this memory manager
            
          \param additional
            Additional bytes needed for header. Only used when type of header
            is extended.
        
          
        */
		HeaderBlockInfo(HBLOCK_TYPE type = hbNone, unsigned additional = 0) : type_(type), size_(0), additional_(additional)
		{
			if (type_ == hbBasic)
				size_ = BASIC_HEADER_SIZE;
			else if (type_ == hbExtended) // alloc # + use counter + flag byte + user-defined
				size_ = sizeof(unsigned int) + sizeof(unsigned short) + sizeof(char) + additional_;
			else if (type_ == hbExternal)
				size_ = EXTERNAL_HEADER_SIZE;
		};
	};

    /*!
    
      \brief
        Constructor for config struct for memory manager
        
      \param UseCPPMemManager
        Bool to optionally turn off the memory manager and use new/delete directly
        
      \param ObjectsPerPage
        how many objects desired for each page 
        
      \param MaxPages
        Max pages this allocator should create if needed
        
      \param DebugOn
        Turns on/off debug features
        
      \param PadBytes
        Number of bytes for padding 
        
      \param HBInfo
        Header block information for this manager
        
      \param Alignment
        Address alignment of each block
    */  
	OAConfig(bool UseCPPMemManager = false,
			 unsigned ObjectsPerPage = DEFAULT_OBJECTS_PER_PAGE, 
             unsigned MaxPages = DEFAULT_MAX_PAGES, 
			 bool DebugOn = false, 
			 unsigned PadBytes = 0,
			 const HeaderBlockInfo &HBInfo = HeaderBlockInfo(),
			 unsigned Alignment = 0) : UseCPPMemManager_(UseCPPMemManager),
			 				       ObjectsPerPage_(ObjectsPerPage), 
			 				       MaxPages_(MaxPages),
					                         DebugOn_(DebugOn), 
                                             PadBytes_(PadBytes),
                                             HBlockInfo_(HBInfo),
                                             Alignment_(Alignment)
	{
		HBlockInfo_ = HBInfo;
		LeftAlignSize_ = 0;  
		InterAlignSize_ = 0;
	}

	bool UseCPPMemManager_;      ///< by-pass the functionality of the OA and use new/delete
    unsigned ObjectsPerPage_;    ///< number of objects on each page
    unsigned MaxPages_;          ///< maximum number of pages the OA can allocate (0=unlimited)
	bool DebugOn_;               ///< enable/disable debugging code (signatures, checks, etc.)
	unsigned PadBytes_;          ///< size of the left/right padding for each block
	HeaderBlockInfo HBlockInfo_; ///< size of the header for each block (0=no headers)
	unsigned Alignment_;         ///< address alignment of each block

	unsigned LeftAlignSize_;     ///< number of alignment bytes required to align first block
	unsigned InterAlignSize_;    ///< number of alignment bytes required between remaining blocks
};

/*! ObjectAllocator statistical info */
struct OAStats
{
	OAStats(void) : ObjectSize_(0), PageSize_(0), FreeObjects_(0), ObjectsInUse_(0), PagesInUse_(0),
                  MostObjects_(0), Allocations_(0), Deallocations_(0) {};

	size_t ObjectSize_;      ///< size of each object
	size_t PageSize_;        ///< size of a page including all headers, padding, etc.
	unsigned FreeObjects_;   ///< number of objects on the free list
	unsigned ObjectsInUse_;  ///< number of objects in use by client
	unsigned PagesInUse_;    ///< number of pages allocated
	unsigned MostObjects_;   ///< most objects in use by client at one time
	unsigned Allocations_;   ///< total requests to allocate memory
	unsigned Deallocations_; ///< total requests to free memory
};

/*! This allows us to easily treat raw objects as nodes in a linked list */
struct GenericObject
{
  GenericObject *Next; ///< pointer to next node
};

/*! struct for external headers */
struct MemBlockInfo
{
	bool in_use;        ///< Is the block free or in use?
	char *label;        ///< A dynamically allocated NUL-terminated string
	unsigned alloc_num; ///< The allocation number (count) of this block
};

/*! This memory manager class */
class ObjectAllocator
{
  public:
  	
      // Defined by the client (pointer to a block, size of block)
	typedef void (*DUMPCALLBACK)(const void *, size_t); ///< client defined callback function
	typedef void (*VALIDATECALLBACK)(const void *, size_t); ///< client defined callback function
  
      // Predefined values for memory signatures
    static const unsigned char UNALLOCATED_PATTERN = 0xAA; ///< unallocated nodes
    static const unsigned char ALLOCATED_PATTERN = 0xBB;   ///< allocated node
    static const unsigned char FREED_PATTERN = 0xCC;       ///< freed node
    static const unsigned char PAD_PATTERN = 0xDD;         ///< padding
    static const unsigned char ALIGN_PATTERN = 0xEE;       ///< alignment
    static const unsigned char HEADER_PATTERN = 0xFF;      ///<headers

      // Creates the ObjectManager per the specified values
      // Throws an exception if the construction fails. (Memory allocation problem)
    ObjectAllocator(size_t ObjectSize, const OAConfig& config);

      // Destroys the ObjectManager (never throws)
    ~ObjectAllocator();

      // Take an object from the free list and give it to the client (simulates new)
      // Throws an exception if the object can't be allocated. (Memory allocation problem)
    void *Allocate(const char *label = 0);

      // Returns an object to the free list for the client (simulates delete)
      // Throws an exception if the the object can't be freed. (Invalid object)
    void Free(void *Object);

      // Calls the callback fn for each block still in use
    unsigned DumpMemoryInUse(DUMPCALLBACK fn) const;

      // Calls the callback fn for each block that is potentially corrupted
	  unsigned ValidatePages(VALIDATECALLBACK fn) const;
  
  	   // Frees all empty pages (extra credit)
    unsigned FreeEmptyPages(void);
  
  	   // Returns true if FreeEmptyPages and alignments are implemented
    static bool ImplementedExtraCredit(void);
    
      // Testing/Debugging/Statistic methods
    void SetDebugState(bool State);       ///< true=enable, false=disable
    const void *GetFreeList(void) const;  ///< returns a pointer to the internal free list
    const void *GetPageList(void) const;  ///< returns a pointer to the internal page list
    OAConfig GetConfig(void) const;       ///< returns the configuration parameters
    OAStats GetStats(void) const;         ///< returns the statistics for the allocator
    
    private:
    
      // Some "suggested" members (only a suggestion!)
    GenericObject *PageList_;           // the beginning of the list of pages
    GenericObject *FreeList_;           // the beginning of the list of objects
    void allocate_new_page(void);       // allocates another page of objects
    void put_on_freelist(void *Object); // puts Object onto the free list
    OAStats stats;                      // statistics for this manager
    OAConfig configuration;             // config for this manager
    void write_signatures(char *page);  // write signatures on a page
    void header_assignment (char * object, const char * label); // writes header bytes when client requests a node
    void header_free(char * object);   // clears any data from node when freed
    void * hand_over_node(void);  // hands over a node to the client
    size_t total_header_size;            // total header size for this manager
    void check_bounds(char * Object);   // check for bad boundaries on free
    void check_padding(unsigned char * Object) const;  // check pad bytes for corruption on free
    
    // Make private to prevent copy construction and assignment
    ObjectAllocator(const ObjectAllocator &oa);
    ObjectAllocator& operator=(const ObjectAllocator &oa);
};

#endif
