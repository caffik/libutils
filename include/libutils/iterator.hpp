#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "tuple.hpp"
#include <iterator>
#include <tuple>

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
 * of the same types, and the second range is defined by a pair of iterators
 * of possibly different types.
 *
 * @tparam InputIt1 Input iterator type for the first range.
 * @tparam InputIt2 Input an iterator type for the second range.
 *
 * @param first1 Iterator to the beginning of the first range.
 * @param last1 Iterator to the end of the first range.
 * @param first2 Iterator to the beginning of the second range.
 * @param last2 Iterator to the end of the second range.
 *
 * @return The difference between the modulus of distances of the two
 * ranges.
 */
template <typename InputIt1, typename InputIt2>
long long distance_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                              InputIt2 last2) {
  return static_cast<long long>(std::abs(std::distance(first1, last1))) -
         static_cast<long long>(std::abs(std::distance(first2, last2)));
}

/**
 * @brief Returns the range with the longer distance between two given ranges.
 *
 * This function compares the distances of two ranges and returns the range
 * with the longer distance.
 * If the distances are equal, it returns the first range.
 *
 * @tparam InputIt1 Input iterator type for the first range.
 * @tparam InputIt2 Input an iterator type for the second range.
 *
 * @param first1 Iterator to the beginning of the first range.
 * @param last1 Iterator to the end of the first range.
 * @param first2 Iterator to the beginning of the second range.
 * @param last2 Iterator to the end of the second range.
 *
 * @return A pair of iterators representing the range with the longer distance.
 */
template <typename InputIt1, typename InputIt2>
auto get_longer_range(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                      InputIt2 last2) {
  if (distance_difference(first1, last1, first2, last2) >= 0) {
    return std::make_pair(first1, last1);
  }
  return std::make_pair(first2, last2);
}

/////////////////////////// MultiIterator /////////////////////////////////

/**
 * @brief A class template for iterating over multiple iterators simultaneously.
 *
 * This class template allows for the simultaneous iteration over multiple
 * iterators of potentially different types.
 * It provides various operators to advance, compare, and access the elements
 * pointed to by the iterators.
 *
 * @tparam InputIts Variadic template parameter for the types of the iterators.
 */
template <typename... InputIts> class MultiIterator {
public:
  /**
   * @brief The iterator category type.
   */
  using iterator_category = std::common_type_t<
      typename std::iterator_traits<InputIts>::iterator_category...>;

  /**
   * @brief The value type of the elements pointed to by the iterators.
   */
  using value_type =
      std::tuple<typename std::iterator_traits<InputIts>::value_type...>;

  /**
   * @brief The difference type for the iterators.
   */
  using difference_type = std::common_type_t<
      typename std::iterator_traits<InputIts>::difference_type...>;

  /**
   * @brief The pointer type to the elements pointed to by the iterators.
   */
  using pointer =
      std::tuple<typename std::iterator_traits<InputIts>::pointer...>;

  /**
   * @brief The reference type to the elements pointed to by the iterators.
   */
  using reference = pointer_tuple<
      std::remove_reference_t<decltype(*std::declval<InputIts>())>...>;

  MultiIterator() = default;
  MultiIterator(const MultiIterator &multi_iterator) = default;
  MultiIterator(MultiIterator &&multi_iterator) = default;

  /**
   * @brief Constructs a MultiIterator from multiple iterators.
   *
   * @param iterators The iterators to be used for the MultiIterator.
   */
  explicit MultiIterator(InputIts &&...iterators) : iterators_(iterators...) {}

  MultiIterator &operator=(const MultiIterator &multi_iterator) = default;
  MultiIterator &operator=(MultiIterator &&multi_iterator) = default;
  ~MultiIterator() = default;

  /**
   * @brief Creates a MultiIterator from multiple iterators.
   *
   * @tparam InputIters Variadic template parameter for the types of the
   * iterators.
   * @param iterators The iterators to be used for the MultiIterator.
   * @return A MultiIterator object.
   */
  template <typename... InputIters>
  MultiIterator<InputIters...> make_multi_iterator(InputIters &&...iterators) {
    return MultiIterator(std::forward<InputIters>(iterators)...);
  }

  /**
   * @brief Dereferences the MultiIterator to access the elements.
   *
   * @return A reference to the elements pointed to by the iterators.
   */
  reference operator*() const {
    return std::apply([](auto &&...args) { return reference(&(*args)...); },
                      iterators_);
  }

  /**
   * @brief Accesses the elements pointed to by the iterators.
   *
   * @return A pointer to the elements pointed to by the iterators.
   */
  pointer operator->() const {
    return std::apply(
        [](auto &&...args) { return std::make_tuple(&(*args)...); },
        iterators_);
  }

  /**
   * @brief Pre-increment operator to advance the iterators.
   *
   * @return A reference to the advanced MultiIterator.
   */
  MultiIterator &operator++() {
    std::apply([](auto &&...args) { ((++args), ...); }, iterators_);
    return *this;
  }

  /**
   * @brief Post-increment operator to advance the iterators.
   *
   * @return A copy of the MultiIterator before advancing.
   */
  MultiIterator operator++(int) {
    MultiIterator tmp(*this);
    operator++();
    return tmp;
  }

  /**
   * @brief Pre-decrement operator to move the iterators backward.
   *
   * @return A reference to the MultiIterator after moving backward.
   */
  MultiIterator &operator--() {
    static_assert(
        !std::is_base_of_v<iterator_category, std::forward_iterator_tag>,
        "The iterator category must be at least bidirectional iterator.");
    std::apply([](auto &&...args) { ((--args), ...); }, iterators_);
    return *this;
  }

  /**
   * @brief Post-decrement operator to move the iterators backward.
   *
   * @return A copy of the MultiIterator before moving backward.
   */
  MultiIterator operator--(int) {
    static_assert(
        !std::is_base_of_v<iterator_category, std::forward_iterator_tag>,
        "The iterator category must be at least bidirectional iterator.");
    MultiIterator tmp(*this);
    operator--();
    return tmp;
  }

  /**
   * @brief Advances the iterators by a specified distance.
   *
   * @param d The distance to advance the iterators.
   * @return A reference to the advanced MultiIterator.
   */
  MultiIterator &operator+=(difference_type d) {
    std::apply([d](auto &&...args) { ((std::advance(args, d)), ...); },
               iterators_);
    return *this;
  }

  /**
   * @brief Returns a new MultiIterator advanced by a specified distance.
   *
   * @param d The distance to advance the iterators.
   * @return A new MultiIterator advanced by the specified distance.
   */
  MultiIterator operator+(difference_type d) const {
    MultiIterator tmp(*this);
    tmp += d;
    return tmp;
  }

  /**
   * @brief Moves the iterators backward by a specified distance.
   *
   * @param d The distance to move the iterators backward.
   * @return A reference to the MultiIterator after moving backward.
   */
  MultiIterator &operator-=(difference_type d) {
    static_assert(
        !std::is_base_of_v<iterator_category, std::forward_iterator_tag>,
        "The iterator category must be at least bidirectional iterator.");
    std::apply([d](auto &&...args) { ((std::advance(args, -d)), ...); },
               iterators_);
    return *this;
  }

  /**
   * @brief Returns a new MultiIterator moved backward by a specified distance.
   *
   * @param d The distance to move the iterators backward.
   * @return A new MultiIterator moved backward by the specified distance.
   */
  MultiIterator operator-(difference_type d) const {
    static_assert(
        !std::is_base_of_v<iterator_category, std::forward_iterator_tag>,
        "The iterator category must be at least bidirectional iterator.");
    MultiIterator tmp(*this);
    tmp -= d;
    return tmp;
  }

  /**
   * @brief Computes the difference between two MultiIterators.
   *
   * @param rhs The right-hand side MultiIterator.
   * @return The difference between the two MultiIterators.
   */
  auto operator-(const MultiIterator &rhs) const {
    return std::get<0>(iterators_) - std::get<0>(rhs.iterators_);
  }

  /**
   * @brief Equality comparison operator.
   *
   * @param rhs The right-hand side MultiIterator.
   * @return True if the iterators are equal, false otherwise.
   */
  bool operator==(const MultiIterator &rhs) const {
    return (iterators_ == rhs.iterators_);
  }

  /**
   * @brief Inequality comparison operator.
   *
   * @param rhs The right-hand side MultiIterator.
   * @return True if all the iterators are different, false otherwise.
   */
  bool operator!=(const MultiIterator &rhs) const {
    bool result{true};
    utils::constexpr_for_tuples(
        [&result](auto &a, auto &b) {
          if (result) {
            result = !(a == b);
          }
        },
        iterators_, rhs.iterators_);
    return result;
  }

  /**
   * @brief Less-than comparison operator.
   *
   * @param rhs The right-hand side MultiIterator.
   * @return True if this MultiIterator is less than the right-hand side, false
   * otherwise.
   */
  bool operator<(const MultiIterator &rhs) const {
    static_assert(
        !std::is_base_of_v<iterator_category, std::bidirectional_iterator_tag>,
        "The iterator category must be at least random access iterator.");
    return iterators_ < rhs.iterators_;
  }

  /**
   * @brief Greater-than comparison operator.
   *
   * @param rhs The right-hand side MultiIterator.
   * @return True if this MultiIterator is greater than the right-hand side,
   * false otherwise.
   */
  bool operator>(const MultiIterator &rhs) const {
    static_assert(
        !std::is_base_of_v<iterator_category, std::bidirectional_iterator_tag>,
        "The iterator category must be at least random access iterator.");
    return iterators_ > rhs.iterators_;
  }

  /**
   * @brief Less-than-or-equal-to comparison operator.
   *
   * @param rhs The right-hand side MultiIterator.
   * @return True if this MultiIterator is less than or equal to the right-hand
   * side, false otherwise.
   */
  bool operator<=(const MultiIterator &rhs) const {
    static_assert(
        !std::is_base_of_v<iterator_category, std::bidirectional_iterator_tag>,
        "The iterator category must be at least random access iterator.");
    return iterators_ <= rhs.iterators_;
  }

  /**
   * @brief Greater-than-or-equal-to comparison operator.
   *
   * @param rhs The right-hand side MultiIterator.
   * @return True if this MultiIterator is greater than or equal to the
   * right-hand side, false otherwise.
   */
  bool operator>=(const MultiIterator &rhs) const {
    static_assert(
        !std::is_base_of_v<iterator_category, std::bidirectional_iterator_tag>,
        "The iterator category must be at least random access iterator.");
    return iterators_ >= rhs.iterators_;
  }

private:
  /**
   * @brief The tuple of iterators.
   */
  std::tuple<InputIts...> iterators_;
};

} // namespace utils

#endif // ITERATOR_HPP
