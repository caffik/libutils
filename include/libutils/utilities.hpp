#ifndef UTILS
#define UTILS

#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>

namespace utils
{
  /** @defgroup ext_numeric Extended numeric
   * @{
   */ 

  /**
   * @brief Computes the product of the given value `init` and the elements in the range `[first, last).`
   *
   * Initialize the product `prod` (of type `T`) with the inital value `init` and then
   * modify it with `prod *= *i` for every iterator `i` in the range `[first, last).`
   * 
   * @note
   * **If any of the following conditions is satisfied, the behaviour is undefined:**
   * - `T` is not CopyConstructible.
   * - `T` is not CopyAssignable  
   * 
   * @param first, last the range of elements
   * @param init initial value 
   * 
   * @par Type requirements:  
   * - InputIt must meet the requirements of LegacyInputIterator.
   *  
   * @return 
   * `prod` after all modifications.
  */
  template <typename InputIt, typename T>
  T product(InputIt first, const InputIt last, T init)
  {
    return std::accumulate(first, last, init, std::multiplies());
  }
  /** @} */ // end group ext_algorithm

}

#endif