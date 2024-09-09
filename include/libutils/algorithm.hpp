#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <algorithm>

namespace utils {
  /**
   * Finds the index of the maximum element in a range.
   *
   * @tparam Iterator Type of the input iterator.
   * @param first Iterator to the beginning of the range.
   * @param last Iterator to the end of the range.
   * @return The index of the maximum element in the range.
   */
  template<typename Iterator>
  std::size_t argmax(Iterator first, Iterator last) {
    return std::distance(first, std::max_element(first, last));
  }

  template<typename InputIt1, typename InputIt2, typename UnaryPred>
  InputIt1 max_element_conditional(InputIt1, InputIt1, InputIt2, UnaryPred p);

  /**
   * Finds the index of the maximum element in a range that satisfies a given
   * predicate.
   *
   * @tparam InputIt1 Type of the first input iterator.
   * @tparam InputIt2 Type of the second input iterator.
   * @tparam UnaryPred Type of the unary predicate.
   * @param first1 Iterator to the beginning of the first range.
   * @param last1 Iterator to the end of the first range.
   * @param first2 Iterator to the beginning of the second range.
   * @param p Unary predicate that returns true for the elements to be considered.
   * @return A pair where the first element is a boolean indicating if a valid
   * maximum element was found, and the second element is the index of the maximum
   * element in the first range that satisfies the predicate.
   */
  template<typename InputIt1, typename InputIt2, typename UnaryPred>
  std::pair<bool, std::size_t> argmax_conditional(InputIt1 first1, InputIt1 last1,
                                                  InputIt2 first2, UnaryPred p) {
    const auto max_cond{max_element_conditional(first1, last1, first2, p)};
    const auto arg_max_cond{std::distance(first1, max_cond)};
    return std::make_pair(max_cond != last1, arg_max_cond);
  }

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
  template<typename InputIt, typename OutputIt>
  OutputIt copy_range_n_times(InputIt first, InputIt last, OutputIt d_first,
                              std::size_t n) {
    if (!n) { return d_first; }
    auto size{std::distance(first, last)};
    for (auto i{0}; i < n - 1; ++i) {
      std::copy(first, last, std::next(d_first, i * size));
    }
    return std::copy(first, last, std::next(d_first, (n - 1) * size));
  }

  /**
   * Finds the maximum element in a range that satisfies a given predicate.
   *
   * @tparam InputIt1 Type of the first input iterator.
   * @tparam InputIt2 Type of the second input iterator.
   * @tparam UnaryPred Type of the unary predicate.
   * @param first1 Iterator to the beginning of the first range.
   * @param last1 Iterator to the end of the first range.
   * @param first2 Iterator to the beginning of the second range.
   * @param p Unary predicate that returns true for the elements to be considered.
   * @return Iterator to the maximum element in the first range that satisfies the
   * predicate.
   */
  template<typename InputIt1, typename InputIt2, typename UnaryPred>
  InputIt1 max_element_conditional(InputIt1 first1, InputIt1 last1,
                                   InputIt2 first2, UnaryPred p) {
    first2 = std::find_if(first2, std::next(first2, std::distance(first1, last1)),
                          [&first1, &p](const auto &e) {
                            if (p(e))
                              return true;
                            ++first1;
                            return false;
                          });
    auto max_element{first1};
    for (; first1 != last1; ++first1, ++first2) {
      if (*first1 > *max_element && p(*first2)) {
        max_element = first1;
      }
    }
    return max_element;
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
  template<typename BidirIt1, typename BidirIt2>
  std::pair<BidirIt1, BidirIt2>
  mismatch_from_end(BidirIt1 first1, BidirIt1 last1,
                    BidirIt2 last2) {
    auto pair{
      std::mismatch(
        std::reverse_iterator(last1), std::reverse_iterator(first1),
        std::reverse_iterator(last2))
    };
    return std::pair(pair.first.base(), pair.second.base());
  }

  /**
   * @brief Reorders elements in a range based on given indices.
   *
   * This function reorders the elements in the range [first1, last1) according to the
   * indices provided in the range starting at indices_first2. The indices specify the
   * new positions of the elements.
   *
   * @note It is assumed that the indices are valid and within the range [0, std::distance(first1, last1)).
   * @remark Range [indices_first2, std::next(indices_first2, std::distance(first1, last1))) is modified.
   *
   * @tparam RandomIt1 Type of the random access iterator for the elements.
   * @tparam RandomIt2 Type of the random access iterator for the indices.
   * @param first1 Iterator to the beginning of the elements range.
   * @param last1 Iterator to the end of the elements range.
   * @param indices_first Iterator to the beginning of the indices range.
   */
  template<typename RandomIt1, typename RandomIt2>
  void reorder_elements_by_indices(RandomIt1 first1, RandomIt1 last1, RandomIt2 indices_first) {
    using integer_type = typename std::iterator_traits<RandomIt2>::value_type;
    auto distance{std::distance(first1, last1)};

    for (integer_type i{0}; i < distance; ++i) {
      integer_type current{i};
      auto current_it{std::next(indices_first, current)};

      while (i != *current_it) {
        auto next{*current_it};
        std::swap(*std::next(first1, current), *std::next(first1, next));
        *current_it = current;
        current = next;
        current_it = std::next(indices_first, current);
      }
      *current_it = current;
    }
  }
} // namespace utils
#endif // ALGORITHM_HPP
