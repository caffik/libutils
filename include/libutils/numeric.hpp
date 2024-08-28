#ifndef NUMERICS_HPP
#define NUMERICS_HPP

#include <numeric>
#include "type_traits.hpp"

namespace utils {
/**
 * @brief Computes the product of a range of elements.
 *
 * This function calculates the product of the elements in the range [first,
 * last) starting with the initial value init.
 *
 * @tparam InputIt Input iterator type for the range.
 * @tparam T The type of the initial value and the result.
 *
 * @param first The beginning of the range.
 * @param last The end of the range.
 * @param init The initial value to start the product.
 *
 * @return T The product of the elements in the range.
 */
template <typename InputIt, typename T>
T product(InputIt first, const InputIt last, T init) {
  return std::accumulate(first, last, init, std::multiplies());
}

/**
 * @brief Computes the mean of a range of elements.
 *
 * This function calculates the mean (average) of the elements in the range
 * [first, last).
 *
 * @tparam InputIt Input iterator type for the range.
 *
 * @param first The beginning of the range.
 * @param last The end of the range.
 *
 * @return decltype(*first) The mean of the elements in the range.
 *
 * @note The return type is the same as the type of the elements in the range.
 * Overflow may occur.
 */

template <typename InputIt>
auto mean(InputIt first, const InputIt last) -> remove_cvref_t<decltype(*first)> {
  using return_type = remove_cvref_t<decltype(*first)>;
  if (auto distance{std::distance(first, last)}; distance) {
    return std::accumulate(first, last, return_type(0)) / distance;
  }
  return return_type(0);
}

/**
* @brief Computes the mean of a range of elements.
*
* This function calculates the mean (average) of the elements in the range [first, last).
*
* @tparam T The type of the result.
* @tparam InputIt Input iterator type for the range.
*
* @param first The beginning of the range.
* @param last The end of the range.
*
* @return T The mean of the elements in the range.
*
* @note If type T is incorrectly specified, overflow may occur.
*/
template <typename T, typename InputIt>
T mean(InputIt first, const InputIt last) {
  if (auto distance{std::distance(first, last)}; distance) {
    return std::accumulate(first, last, T(0)) / distance;
  }
  return T(0);
}

} // namespace utils

#endif // NUMERICS_HPP
