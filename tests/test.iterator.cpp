#include <gtest/gtest.h>
#include <libutils/iterator.hpp>
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
  const auto result{utils::distanceDifference(vec1.begin(), vec1.end(),
                                              vec2.begin(), vec2.end())};
  EXPECT_EQ(result, 0);
}

TEST(DistanceDifference, FirstRangeLonger) {
  const std::vector vec1{1, 2, 3, 4, 5, 6};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto result{utils::distanceDifference(vec1.begin(), vec1.end(),
                                              vec2.begin(), vec2.end())};
  EXPECT_EQ(result, 1);
}

TEST(DistanceDifference, SecondRangeLonger) {
  //! [distance_difference_start]
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector vec2{1, 2, 3, 4, 5, 6};
  const auto result{utils::distanceDifference(vec1.begin(), vec1.end(),
                                              vec2.begin(), vec2.end())};
  //! [distance_difference_end]
  EXPECT_EQ(result, -1);
}

TEST(DistanceDifference, EmptyFirstRange) {
  const std::vector<int> vec1{};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto result{utils::distanceDifference(vec1.begin(), vec1.end(),
                                              vec2.begin(), vec2.end())};
  EXPECT_EQ(result, -5);
}

TEST(DistanceDifference, EmptySecondRange) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector<int> vec2{};
  const auto result{utils::distanceDifference(vec1.begin(), vec1.end(),
                                              vec2.begin(), vec2.end())};
  EXPECT_EQ(result, 5);
}

TEST(DistanceDifference, BothRangesEmpty) {
  const std::vector<int> vec1{};
  const std::vector<int> vec2{};
  const auto result{utils::distanceDifference(vec1.begin(), vec1.end(),
                                              vec2.begin(), vec2.end())};
  EXPECT_EQ(result, 0);
}

/**
 * GetLongerRange tests.
 */

TEST(GetLongerRange, IdenticalRanges) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto &[first, last] =
      utils::getLongerRange(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec1.begin());
  EXPECT_EQ(last, vec1.end());
}

TEST(GetLongerRange, FirstRangeLonger) {
  //! [get_longer_range_start]
  const std::vector vec1{1, 2, 3, 4, 5, 6};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto &[first, last] =
      utils::getLongerRange(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
  //! [get_longer_range_end]
  EXPECT_EQ(first, vec1.begin());
  EXPECT_EQ(last, vec1.end());
}

TEST(GetLongerRange, SecondRangeLonger) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector vec2{1, 2, 3, 4, 5, 6};
  const auto &[first, last] =
      utils::getLongerRange(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec2.begin());
  EXPECT_EQ(last, vec2.end());
}

TEST(GetLongerRange, EmptyFirstRange) {
  const std::vector<int> vec1{};
  const std::vector vec2{1, 2, 3, 4, 5};
  const auto &[first, last] =
      utils::getLongerRange(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec2.begin());
  EXPECT_EQ(last, vec2.end());
}

TEST(GetLongerRange, EmptySecondRange) {
  const std::vector vec1{1, 2, 3, 4, 5};
  const std::vector<int> vec2{};
  const auto &[first, last] =
      utils::getLongerRange(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec1.begin());
  EXPECT_EQ(last, vec1.end());
}

TEST(GetLongerRange, BothRangesEmpty) {
  std::vector<int> vec1{};
  std::vector<int> vec2{};
  const auto &[first, last] =
      utils::getLongerRange(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
  EXPECT_EQ(first, vec1.begin());
  EXPECT_EQ(last, vec1.end());
}