#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

namespace utils {
/**
 * @brief Advances multiple iterators by a specified number of steps.
 *
 * This function advances each of the provided iterators by N steps.
 * The default value for N is 1.
 *
 * @tparam N The number of steps to advance the iterators. Default is 1.
 * @tparam InputIts Variadic template parameter for the types of the iterators.
 *
 * @param iterators The iterators to be advanced.
 *
 */
template <std::size_t N = 1, typename... InputIts>
void advance(InputIts &...iterators) {
  static_assert(N >= std::size_t{1}, "N must be greater than zero");
  (std::advance(iterators, N), ...);
}

/**
 * @brief Computes the difference in distances between two ranges.
 *
 * This function calculates the absolute difference between the distances
 * of two given ranges. The first range is defined by a pair of iterators
 * of the same type, and the second range is defined by a pair of iterators
 * of possibly different types.
 *
 * @tparam InputIt1 Input iterator type for the first range.
 * @tparam InputIt2 Input iterator type for the second range.
 *
 * @param first1 Iterator to the beginning of the first range.
 * @param last1 Iterator to the end of the first range.
 * @param first2 Iterator to the beginning of the second range.
 * @param last2 Iterator to the end of the second range.
 *
 * @return long long The difference between the modulus of distances of the two
 * ranges.
 */
template <typename InputIt1, typename InputIt2>
long long distanceDifference(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                               InputIt2 last2) {
  return static_cast<long long>(std::abs(std::distance(first1, last1))) -
         static_cast<long long>(std::abs(std::distance(first2, last2)));
}

/**
 * @brief Returns the range with the longer distance between two given ranges.
 *
 * This function compares the distances of two ranges and returns the range
 * with the longer distance. If the distances are equal, it returns the first range.
 *
 * @tparam InputIt1 Input iterator type for the first range.
 * @tparam InputIt2 Input iterator type for the second range.
 *
 * @param first1 Iterator to the beginning of the first range.
 * @param last1 Iterator to the end of the first range.
 * @param first2 Iterator to the beginning of the second range.
 * @param last2 Iterator to the end of the second range.
 *
 * @return A pair of iterators representing the range with the longer distance.
 */
template <typename InputIt1, typename InputIt2>
auto getLongerRange(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                     InputIt2 last2) {
  if (distanceDifference(first1, last1, first2, last2) >= 0) {
    return std::make_pair(first1, last1);
  }
  return std::make_pair(first2, last2);
}

} // namespace utils
#endif // ITERATOR_HPP
