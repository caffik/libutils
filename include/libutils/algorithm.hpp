#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <algorithm>

namespace utils {

/**
 * @brief Copies a range of elements multiple times to a destination.
 *
 * This function copies the elements in the range [first, last) to the destination
 * range starting at d_first, n times. The destination range must be large enough
 * to hold n copies of the input range.
 *
 * @tparam InputIt Input iterator type for the source range.
 * @tparam OutputIt Output iterator type for the destination range.
 *
 * @param first The beginning of the source range.
 * @param last The end of the source range.
 * @param d_first The beginning of the destination range.
 * @param n The number of times to copy the source range.
 *
 * @return OutputIt Iterator to the end of the last copied range.
 *
 * @note If n is less than 0, the behavior is undefined.
 */
  template <typename InputIt, typename OutputIt>
  OutputIt copy_range_n_times(InputIt first, InputIt last, OutputIt d_first,
                              std::size_t n) {
    if (!n) { return d_first; }
    auto size{std::distance(first, last)};
    for (auto i{0}; i < n - 1; ++i) {
      std::copy(first, last, std::next(d_first, i*size));
    }
    return std::copy(first, last, std::next(d_first, (n - 1)*size));
  }

/**
* @brief Finds the first position where two ranges differ, starting from the end.
*
* @tparam BidirIt1 Bidirectional iterator type for the first range.
* @tparam BidirIt2 Bidirectional iterator type for the second range.
*
* @param first1, last1 The range of the first sequence.
* @param last2 The end of the second sequence.
*
* @return A pair of iterators to the first mismatching elements from the end.
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
} // namespace utils
#endif // ALGORITHM_HPP