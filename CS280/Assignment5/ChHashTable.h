/*****************************************************************************/
/*!
\file ChHashTable.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS170
\par Assignment 5
\date   11/13/15

\brief
  Prototypes for hash table class.

*/
/*****************************************************************************/


//---------------------------------------------------------------------------
#ifndef OAHASHTABLEH
#define OAHASHTABLEH
//---------------------------------------------------------------------------

#include <string>
#include <iostream>
#include "ObjectAllocator.h"
#include "support.h"
#include "cmath"

/// client-provided hash function: takes a key and table size,
// returns an index in the table.
typedef unsigned (*HASHFUNC)(const char *, unsigned);

/// Max length of our "string" keys
const unsigned MAX_KEYLEN = 10;

/// exception class
class HashTableException
{
  private:
    int error_code_; ///< type of error code
    std::string message_; ///< human readable string to parse the exception

  public:
      /// constructor
    HashTableException(int ErrCode, const std::string& Message) :
        error_code_(ErrCode), message_(Message) {};

      /// destructor
    virtual ~HashTableException() {
    }

      /// returns type of exception
    virtual int code() const {
      return error_code_;
    }

      /// returns string of the exception
    virtual const char *what() const {
      return message_.c_str();
    }
      /// exception options
    enum HASHTABLE_EXCEPTION {E_ITEM_NOT_FOUND, E_DUPLICATE, E_NO_MEMORY};
};


/// HashTable statistical info
struct HTStats
{
  HTStats() : Count_(0), TableSize_(0), Probes_(0), Expansions_(0),
                    HashFunc_(0) {};
  unsigned Count_;      ///< Number of elements in the table
  unsigned TableSize_;  ///< Size of the table (total slots)
  unsigned Probes_;     ///< Number of probes performed
  unsigned Expansions_; ///< Number of times the table grew
  HASHFUNC HashFunc_;   ///< Pointer to primary hash function
  ObjectAllocator *Allocator_; ///< The allocator in use (may be 0)
};

/// hash table class
template <typename T>
class ChHashTable
{
  public:

      /// function provided by client to free their data
    typedef void (*FREEPROC)(T); // client-provided free proc (we own the data)

      /// configuration struct to use for the hash tab;e
    struct HTConfig
    {
          /// constructor
        HTConfig(unsigned InitialTableSize,
                 HASHFUNC HashFunc,
                 double MaxLoadFactor = 3.0,
                 double GrowthFactor = 2.0,
                 FREEPROC FreeProc = 0) :

        InitialTableSize_(InitialTableSize),
        HashFunc_(HashFunc),
        MaxLoadFactor_(MaxLoadFactor),
        GrowthFactor_(GrowthFactor),
        FreeProc_(FreeProc) {}

        /// starting size of the hash table
      unsigned InitialTableSize_;

        /// hashing function for this table
      HASHFUNC HashFunc_;

        /// max load factor before growing the tab;e
      double MaxLoadFactor_;

        /// how much the table should grow
      double GrowthFactor_;

        /// function provded by client to free their data
      FREEPROC FreeProc_;
    };

      /// Nodes that will hold the key/data pairs
    struct ChHTNode
    {
      char Key[MAX_KEYLEN]; ///< Key is a string
      T Data;               ///< Client data
      ChHTNode *Next;       ///< pointer to next node in list
        /// constructor
      ChHTNode(const T& data) : Data(data) {};
    };

      /// Each list has a special head pointer
    struct ChHTHeadNode
    {
      ChHTNode *Nodes; ///< pointer to head of list of data at this index
      ChHTHeadNode() : Nodes(0), Count(0) {}; ///< constructor
      int Count; ///< For testing
    };

      /// pointer to a ChHTNode
    typedef ChHTNode* DataNode;

      /// pointer to a ChHTHeadNode node
    typedef ChHTHeadNode* HeadNode;

      /// condstructor
    ChHashTable(const HTConfig& Config, ObjectAllocator* allocator = 0);

      /// destructor
    ~ChHashTable();

      /// Insert a key/data pair into table. Throws an exception if the
      /// insertion is unsuccessful.
    void insert(const char *Key, const T& Data);

      /// Delete an item by key. Throws an exception if the key doesn't exist.
    void remove(const char *Key);

      /// Find and return data by key. Throws an exception if the
      /// key doesn't exist.
    const T& find(const char *Key) const;

      /// Removes all items from the table (Doesn't deallocate table)
    void clear();

      /// Allow the client to peer into the data
    HTStats GetStats() const;

      /// allow the client to peer into the hash table
    const ChHTHeadNode *GetTable() const;

  private:

    // Any private members ...


    DataNode make_node(const T& Data);
    void remove_node(DataNode &removal);
    void grow_table();

      /// allocator for object
    ObjectAllocator *allocator;

      /// configuration for this hash table
    HTConfig config;

      /// array of head pointers (the hash table itself)
    HeadNode table;

      /// stats of the object
    mutable HTStats stats;

};

#include "ChHashTable.cpp"

#endif
