#include "headers.hpp"

#ifndef UTILS
#define UTILS

namespace utils
{
  /** @defgroup details Details
   * @{
   * 
   */ 
  namespace details {
    template <typename Container, typename InputIt>
    void distanceBetweenHelper(Container &container, InputIt first, InputIt second)
    {
      container.push_back(std::distance(first, second));
    }

    template <typename Container, typename InputIt, typename... InputIts>
    void distanceBetweenHelper(Container &container, InputIt first, InputIt second,
                              InputIts... iterators)
    {
      container.push_back(std::distance(first, second));
      distanceBetweenHelper(container, second, iterators...);
    }
  }
  /** @} */ // end details group 
  
  /** @defgroup ext_algorithm Extended algorithms
   * @{
   */ 

  /**
   * @brief Copies `n` times the elements in the range `[first, last)`, to another range beginning at `d_first.`
   * 
   * @note
   * **If any of the following conditions is satisfied, the behaviour is undefined:**
   * - `T` is not CopyConstructible.
   * - `T` is not CopyAssignable  
   * 
   * @param first, last the range of elements
   * @param d_first the beginning of the destination range
   * @param n number of copies to be made   
   * 
   * @par Type requirements:  
   * - InputIt must meet the requirements of LegacyInputIterator.
   * - OutputIt must meet the requirements of LegacyOutputIterator. 
   *  
   * @exception
   * std::invalid_argument if `n` is smaller than one.  
   
   * @return 
   * Output interator to the element in the destination range, one past the last element copied.
   * 
  */
  template <typename InputIt, typename OutputIt>
  OutputIt copy(InputIt first, InputIt last, OutputIt d_first, std::size_t n)
  {
    if (n <= 0) {
      throw std::invalid_argument("Argument n must be greater than zero");
    }
    auto size{std::distance(first, last)};
    for (auto i{0}; i < n - 1; ++i)
    {
      std::copy(first, last, std::next(d_first, i*size));
    }
    return std::copy(first, last, std::next(d_first, (n - 1)*size));
  }

  /**
   * @brief Returns a pair of iterators to the last matching of elements from `(last1, first1]` 
   * and a range starting from `last2` in reverse direction.
   *
   * Second range has `std::distance(first1, last1)` elements.
   *  
   * @param first1, last1 the first range of the elements
   * @param last2 last element of second range
   * 
   * @par Type requirements:
   * Bidir1 must meet the requirements of LegacyBidirectionalIterator
   * Bidir2 must meet the requirements of LegacyBidirectionalIterator 
   *
   * @return 
   * `std::pair` with iterators to the last equal elements. 
  */
  template <typename BidirIt1, typename BidirIt2>
  std::pair<BidirIt1, BidirIt2> 
      mismatch_from_end(BidirIt1 first1, BidirIt1 last1,
                        BidirIt2 last2)
  {
    auto pair{std::mismatch(
        std::reverse_iterator(last1), std::reverse_iterator(first1),
        std::reverse_iterator(last2))};
    return std::pair(pair.first.base(), pair.second.base());
  }

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

  /** @defgroup ext_iterator Extended iterators
   * @{
   * 
   */

  /**
   * @brief Increments given sequence of iterators `iterators` by one.
   * 
   * @param iterators iterators to be advanced
   * 
   * @par Type requirements:  
   * - InputIts must meet the requirements of LegacyInputIterator.
   * 
   * @return
   * (none)
   * 
   * @remark
   * Function is based on `std::advance`. For more information please read  
   * [documentation](https://en.cppreference.com/w/cpp/iterator/advance).
   *  
  */
  template <typename... InputIts>
  void advance(InputIts&...iterators)
  {
    std::size_t n{1};
    (std::advance(iterators, n), ...);
  }

  /** @} */ // end group ext_iterator

  /** @defgroup other_algorithms Other algorithms
   * @{
   * 
   */

  /**
   * @brief Returns the number of hops between iterators.  
   * 
   * @param iterators iterators from the same range of elements  
   * 
   * @par Type requirements:  
   * Iterators must come from the same container.
   *
   * @return 
   * `std::vector` with type `difference_type` of InputIts containing distances between iterators in sequence.
   *
   * @remark
   * Function is based on `std::distance` therefore InputIts must meet all requirements mentioned in 
   * [documentation](https://en.cppreference.com/w/cpp/iterator/distance).
   *  
  */
  template <typename... InputIts>
  auto distanceBetween(InputIts... iterators)
  {
    using difference_type = 
        typename std::iterator_traits<std::common_type_t<InputIts...>>::difference_type;
    std::vector<difference_type> vec;
    details::distanceBetweenHelper(vec, iterators...);
    return vec;
  }

  /**
   * @brief Returns difference between distance of pairs of iterators i.e. `std::abs(std::distance(first1, last1)) - std::abs(std::distance(first2, last2)).`  
   * 
   * @param first1, last1 the first range of the elements
   * @param first2, last2 the second range of the elements
   *
   * @return 
   * (numeric type)
   *
   * @remark
   * Function is based on `std::distance` therefore parameters and InputIts must meet all requirements mentioned in 
   * [documentation](https://en.cppreference.com/w/cpp/iterator/distance).
   *  
  */
  template <typename InputIt1, typename InputIt2>
  auto distanceDifference(InputIt1 first1, InputIt1 last1,
                          InputIt2 first2, InputIt2 last2)
  {
    return std::abs(std::distance(first1, last1)) 
           - std::abs(std::distance(first2, last2));
  }
  
  /**
   * @brief Returns pair of iterators with longer range of elements.  
   * 
   * @param first1, last1 the first range of the elements
   * @param first2, last2 the second range of the elements
   * 
   * @return 
   * `std::pair` of iterators. If length of first range of the elements is not smaller 
   * than length of second range of elements iterators to first range are returned 
   * else iterators to  second range are returned.
   *
   * @remark
   * Function is based on `std::distance` therefore parameters and InputIts must meet all requirements mentioned in 
   * [documentation](https://en.cppreference.com/w/cpp/iterator/distance).
   *  
  */
  template <typename InputIt1, typename InputIt2>
  auto getLongerRange(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
  {
    if (distanceDifference(first1, last1, first2, last2) >= 0)
    {
      return std::pair(first1, last1);
    }
    return std::pair(first2, last2);
  }
  /** @} */ // end group other_algorithms

}

#endif