#include "perm-lexicographical.h"
#include <algorithm>
#include <iostream>

bool nextPermLexicographical (std::vector<int> & p)
{
  //expand search from the back looking for peak (4 5)

  // now back track to the end replacing each smallest biggest number
  // return true


  // if reach first digit without flagging a peak no more permutations are
  // possible
  // happens when digits are in decreasing order (54321)
}
