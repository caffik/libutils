#include <algorithm>
#include <gtest/gtest.h>
#include <libutils/iterator.hpp>
#include <libutils/tuple.hpp>
#include <list>
#include <vector>

/**
 * Advance tests.
 */

TEST(Advance, AdvancesSingleIteratorByDefaultSteps) {
  const std::vector vec{1, 2, 3, 4, 5};
  auto it{vec.begin()};
  utils::advance(it);
  EXPECT_EQ(*it, 2);
}

TEST(Advance, AdvancesSingleIteratorBySpecifiedSteps) {
  const std::vector vec{1, 2, 3, 4, 5};
  auto it{vec.begin()};
  utils::advance<3>(it);
  EXPECT_EQ(*it, 4);
}

TEST(Advance, AdvancesMultipleIteratorsByDefaultSteps) {
  //! [advance_start]
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::list list1{1, 2, 3, 4, 5};
  auto it1{vec1.begin()};
  auto it2{list1.begin()};
  utils::advance(it1, it2);
  //! [advance_end]
  EXPECT_EQ(*it1, 2);
  EXPECT_EQ(*it2, 2);
}

TEST(Advance, AdvancesMultipleIteratorsBySpecifiedSteps) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::list list1{1, 2, 3, 4, 5};
  auto it1{vec1.begin()};
  auto it2{list1.begin()};
  utils::advance<3>(it1, it2);
  EXPECT_EQ(*it1, 4);
  EXPECT_EQ(*it2, 4);
}

/**
 * DistanceDifference tests.
 */

TEST(DistanceDifference, IdenticalRanges) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto result{utils::distance_difference(vec1.begin(), vec1.end(),
                                               vec2.begin(), vec2.end())};
  EXPECT_EQ(result, 0);
}

TEST(DistanceDifference, FirstRangeLonger) {
  const std::vector vec1{1, 2, 3, 4, 5, 6};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto result{utils::distance_difference(vec1.begin(), vec1.end(),
                                               vec2.begin(), vec2.end())};
  EXPECT_EQ(result, 1);
}

TEST(DistanceDifference, SecondRangeLonger) {
  //! [distance_difference_start]
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector vec2{1, 2, 3, 4, 5, 6};
  const auto result{utils::distance_difference(vec1.begin(), vec1.end(),
                                               vec2.begin(), vec2.end())};
  //! [distance_difference_end]
  EXPECT_EQ(result, -1);
}

TEST(DistanceDifference, EmptyFirstRange) {
  const std::vector<int> vec1{};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto result{utils::distance_difference(vec1.begin(), vec1.end(),
                                               vec2.begin(), vec2.end())};
  EXPECT_EQ(result, -5);
}

TEST(DistanceDifference, EmptySecondRange) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector<int> vec2{};
  const auto result{utils::distance_difference(vec1.begin(), vec1.end(),
                                               vec2.begin(), vec2.end())};
  EXPECT_EQ(result, 5);
}

TEST(DistanceDifference, BothRangesEmpty) {
  const std::vector<int> vec1{};
  const std::vector<int> vec2{};
  const auto result{utils::distance_difference(vec1.begin(), vec1.end(),
                                               vec2.begin(), vec2.end())};
  EXPECT_EQ(result, 0);
}

/**
 * GetLongerRange tests.
 */

TEST(GetLongerRange, IdenticalRanges) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto &[first, last] = utils::get_longer_range(vec1.begin(), vec1.end(),
                                                      vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec1.begin());
  EXPECT_EQ(last, vec1.end());
}

TEST(GetLongerRange, FirstRangeLonger) {
  //! [get_longer_range_start]
  const std::vector vec1{1, 2, 3, 4, 5, 6};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto &[first, last] = utils::get_longer_range(vec1.begin(), vec1.end(),
                                                      vec2.begin(), vec2.end());
  //! [get_longer_range_end]
  EXPECT_EQ(first, vec1.begin());
  EXPECT_EQ(last, vec1.end());
}

TEST(GetLongerRange, SecondRangeLonger) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector vec2{1, 2, 3, 4, 5, 6};
  const auto &[first, last] = utils::get_longer_range(vec1.begin(), vec1.end(),
                                                      vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec2.begin());
  EXPECT_EQ(last, vec2.end());
}

TEST(GetLongerRange, EmptyFirstRange) {
  const std::vector<int> vec1{};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto &[first, last] = utils::get_longer_range(vec1.begin(), vec1.end(),
                                                      vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec2.begin());
  EXPECT_EQ(last, vec2.end());
}

TEST(GetLongerRange, EmptySecondRange) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector<int> vec2{};
  const auto &[first, last] = utils::get_longer_range(vec1.begin(), vec1.end(),
                                                      vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec1.begin());
  EXPECT_EQ(last, vec1.end());
}

TEST(GetLongerRange, BothRangesEmpty) {
  std::vector<int> vec1{};
  std::vector<int> vec2{};
  const auto &[first, last] = utils::get_longer_range(vec1.begin(), vec1.end(),
                                                      vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec1.begin());
  EXPECT_EQ(last, vec1.end());
}

///////////////////////////////////////////////////////////////////////////////

/**
 * MultiIterator tests.
 */

TEST(MultiIterator, DefaultConstructor) {
  // std::vector has random access iterator category, std::list has
  // bidirectional iterator category, so the common type is bidirectional
  // iterator category
  utils::MultiIterator<std::vector<int>::iterator, std::list<int>::iterator>
      multi_iterator;

  using multi_iterator_type = decltype(multi_iterator);

  ::testing::StaticAssertTypeEq<multi_iterator_type::iterator_category,
                                std::bidirectional_iterator_tag>();
  ::testing::StaticAssertTypeEq<multi_iterator_type::value_type,
                                std::tuple<int, int>>();
  ::testing::StaticAssertTypeEq<multi_iterator_type::difference_type,
                                std::ptrdiff_t>();
  ::testing::StaticAssertTypeEq<multi_iterator_type::pointer,
                                std::tuple<int *, int *>>();
  ::testing::StaticAssertTypeEq<multi_iterator_type::reference,
                                utils::pointer_tuple<int, int>>();
}

TEST(MultiIterator, ConstructsFromMultipleIterators) {
  std::vector vec1{1, 2, 3};
  std::vector vec2{4, 5, 6};
  utils::MultiIterator it(vec1.begin(), vec2.begin());
  auto [a, b] = *it;
  EXPECT_EQ(a, 1);
  EXPECT_EQ(b, 4);
}

TEST(MultiIterator, AdvancesIterators) {
  std::vector vec1{1, 2, 3};
  std::vector vec2{4, 5, 6};
  utils::MultiIterator it(vec1.begin(), vec2.begin());
  ++it;
  auto [a, b] = *it;
  EXPECT_EQ(a, 2);
  EXPECT_EQ(b, 5);
}

TEST(MultiIterator, ComparesEquality) {
  std::vector vec1{1, 2, 3};
  std::vector vec2{4, 5, 6};
  utils::MultiIterator it1(vec1.begin(), vec2.begin());
  utils::MultiIterator it2(vec1.begin(), vec2.begin());
  EXPECT_TRUE(it1 == it2);
}

TEST(MultiIterator, ComparesInequality) {
  std::vector vec1{1, 2, 3};
  std::vector vec2{4, 5, 6};
  utils::MultiIterator it1(vec1.begin(), vec2.begin());
  utils::MultiIterator it2(vec1.begin() + 1, vec2.begin());
  // please see documentation for operator!=
  EXPECT_FALSE(it1 != it2);
}

TEST(MultiIterator, ComputesDifference) {
  std::vector vec1{1, 2, 3};
  std::vector vec2{4, 5, 6};
  utils::MultiIterator it1(vec1.begin(), vec2.begin());
  utils::MultiIterator it2(vec1.begin() + 2, vec2.begin() + 2);
  EXPECT_EQ(it2 - it1, 2);
}

TEST(MultiIterator, HandlesEmptyIterators) {
  std::vector<int> vec1;
  std::vector<int> vec2;
  utils::MultiIterator it(vec1.begin(), vec2.begin());
  EXPECT_TRUE(it == utils::MultiIterator(vec1.end(), vec2.end()));
}

TEST(MultiIterator, Sort) {
  // [!multi_iterator_sort_start]
  std::vector vec1{1, 2, 2, 1, 5, 6, 7, 8, 9, 10};
  std::vector<std::string> vec2{"a", "b", "c", "d"};
  utils::MultiIterator begin{vec1.begin(), vec2.begin()};
  utils::MultiIterator end{vec1.end(), vec2.end()};
  std::sort(begin, end, [](const auto &lhs, const auto &rhs) {
    if (utils::get<0>(lhs) < utils::get<0>(rhs)) {
      return true;
    }
    if (utils::get<0>(lhs) == utils::get<0>(rhs)) {
      return utils::get<1>(lhs) < utils::get<1>(rhs);
    }
    return false;
  });
  // [!multi_iterator_sort_end]
  std::vector<std::pair<int, std::string>> expected{
      {1, "a"}, {1, "d"}, {2, "b"}, {2, "c"}};

  for (auto it = begin; it != end; ++it) {
    const auto [a, b] = *it;
    EXPECT_EQ(std::make_pair(a, b), expected.front());
    expected.erase(expected.begin());
  }
}
