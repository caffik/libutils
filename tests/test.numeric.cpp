#include <gtest/gtest.h>
#include <libutils/numeric.hpp>
#include <limits>
#include <vector>

/**
 * product function tests.
 */

TEST(Product, ComputesProductOfNonEmptyRange) {
  //! [product_start]
  const std::vector vec{1, 2, 3, 4};
  const auto result{utils::product(vec.begin(), vec.end(), 1)};
  //! [product_end]
  EXPECT_EQ(result, 24);
}

TEST(Product, ComputesProductWithInitialValue) {
  const std::vector vec{1, 2, 3, 4};
  const auto result{utils::product(vec.begin(), vec.end(), 2)};
  EXPECT_EQ(result, 48);
}

TEST(Product, ComputesProductOfEmptyRange) {
  const std::vector<int> vec{};
  const auto result{utils::product(vec.begin(), vec.end(), 1)};
  EXPECT_EQ(result, 1);
}

TEST(Product, ComputesProductOfSingleElementRange) {
  const std::vector vec{5};
  const auto result{utils::product(vec.begin(), vec.end(), 1)};
  EXPECT_EQ(result, 5);
}

TEST(Product, ComputesProductOfRangeWithZero) {
  const std::vector vec{1, 2, 0, 4};
  const auto result{utils::product(vec.begin(), vec.end(), 1)};
  EXPECT_EQ(result, 0);
}

/**
 * mean function tests.
 */

TEST(MeanFunction, NonEmptyRange) {
  //! [mean_start]
  const std::vector vec{1, 2, 3, 4, 5};
  const auto result{utils::mean(vec.begin(), vec.end())};
  //! [mean_end]
  EXPECT_EQ(result, 3);
}

TEST(MeanFunction, EmptyRange) {
  const std::vector<int> vec{};
  EXPECT_EQ(utils::mean(vec.begin(), vec.end()), 0);
}

TEST(MeanFunction, SingleElementRange) {
  const std::vector vec{42};
  EXPECT_EQ(utils::mean(vec.begin(), vec.end()), 42);
}

TEST(MeanFunction, NonZeroInitialValue) {
  const std::vector vec{1, 2, 3, 4, 5};
  EXPECT_EQ(utils::mean(vec.begin(), vec.end()), 3);
}

TEST(MeanFunction, FloatingPointRange) {
  const std::vector vec{1.0, 2.0, 3.0, 4.0, 5.0};
  EXPECT_DOUBLE_EQ(utils::mean(vec.begin(), vec.end()), 3.0);
}

TEST(MeanFunction, LargeNumbers) {
  std::vector<long> vec{1000000000, 2000000000, 3000000000, 4000000000,
                        5000000000};
  EXPECT_EQ(utils::mean(vec.begin(), vec.end()), 3000000000);
}

TEST(MeanFunction, NegativeNumbers) {
  const std::vector vec{-1, -2, -3, -4, -5};
  EXPECT_EQ(utils::mean(vec.begin(), vec.end()), -3);
}

/**
 * mean function tests with type.
 */

TEST(MeanFunctionWithType, NonEmptyRange) {
  const std::vector vec{1, 2, 3, 4, 5};
  EXPECT_EQ(utils::mean<int>(vec.begin(), vec.end()), 3);
}

TEST(MeanFunctionWithType, EmptyRange) {
  const std::vector<int> vec{};
  EXPECT_EQ(utils::mean<int>(vec.begin(), vec.end()), 0);
}

TEST(MeanFunctionWithType, SingleElementRange) {
  const std::vector vec{42};
  EXPECT_EQ(utils::mean<int>(vec.begin(), vec.end()), 42);
}

TEST(MeanFunctionWithType, FloatingPointRange) {
  const std::vector vec{1.0, 2.0, 3.0, 4.0, 5.0};
  EXPECT_DOUBLE_EQ(utils::mean<double>(vec.begin(), vec.end()), 3.0);
}

TEST(MeanFunctionWithType, LargeNumbers) {
  //! [mean_type_start]
  constexpr auto int32_max{std::numeric_limits<std::int32_t>::max()};
  const std::vector<std::int32_t> vec(3, int32_max);
  const auto result{utils::mean<std::int64_t>(vec.begin(), vec.end())};
  //! [mean_type_end]
  EXPECT_EQ(result, int32_max);
}

TEST(MeanFunctionWithType, NegativeNumbers) {
  std::vector vec{-1, -2, -3, -4, -5};
  EXPECT_EQ(utils::mean<int>(vec.begin(), vec.end()), -3);
}