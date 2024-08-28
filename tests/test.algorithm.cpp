#include <gtest/gtest.h>
#include <vector>

#include <libutils/algorithm.hpp>

/**
 * Argmax tests.
 */

TEST(Argmax, FindsIndexOfMaxElement) {
    //! [argmax_start]
    const std::vector v{1, 3, 5, 7, 9};
    const auto result{utils::argmax(v.begin(), v.end())};
    //! [argmax_end]
    EXPECT_EQ(result, 4);
}

TEST(Argmax, SingleElement) {
    const std::vector v{42};
    const auto result{utils::argmax(v.begin(), v.end())};
    EXPECT_EQ(result, 0);
}

TEST(Argmax, EmptyRange) {
    const std::vector<int> v{};
    const auto result{utils::argmax(v.begin(), v.end())};
    EXPECT_EQ(result, 0);
}

TEST(Argmax, AllElementsEqual) {
    const std::vector v{5, 5, 5, 5, 5};
    const auto result{utils::argmax(v.begin(), v.end())};
    EXPECT_EQ(result, 0);
}

TEST(Argmax, NegativeNumbers) {
    const std::vector v{-1, -3, -5, -7, -9};
    const auto result{utils::argmax(v.begin(), v.end())};
    EXPECT_EQ(result, 0);
}

/**
 * CopyRangeNTimes tests.
 */

TEST(CopyRangeNTimes, CopiesRangeMultipleTimes) {
    //! [copy_range_n_times_start]
    const std::vector source{1, 2, 3};
    std::vector<int> destination(9);
    const auto result{utils::copy_range_n_times(source.begin(), source.end(),
                                                destination.begin(), 3)};
    //! [copy_range_n_times_end]
    const std::vector expected{1, 2, 3, 1, 2, 3, 1, 2, 3};
    EXPECT_EQ(destination, expected);
    EXPECT_EQ(result, destination.end());
}

TEST(CopyRangeNTimes, CopiesRangeOnce) {
    const std::vector source{1, 2, 3};
    std::vector<int> destination(3);
    const auto result{utils::copy_range_n_times(source.begin(), source.end(),
                                                destination.begin(), 1)};
    const std::vector expected{1, 2, 3};
    EXPECT_EQ(destination, expected);
    EXPECT_EQ(result, destination.end());
}

TEST(CopyRangeNTimes, HandlesEmptySourceRange) {
    const std::vector<int> source{};
    std::vector<int> destination(0);
    const auto result{utils::copy_range_n_times(source.begin(), source.end(),
                                                destination.begin(), 3)};
    const std::vector<int> expected{};
    EXPECT_EQ(destination, expected);
    EXPECT_EQ(result, destination.end());
}

/**
 * MismatchFromEnd tests.
 */

TEST(MismatchFromEnd, IdenticalRanges) {
    const std::vector vec1{1, 2, 3, 4, 5};
    const std::vector vec2{1, 2, 3, 4, 5};
    const auto &[mis_first, mis_second] =
        utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.begin());
    EXPECT_EQ(mis_second, vec2.begin());
}

TEST(MismatchFromEnd, DifferentRanges) {
    const std::vector vec1{1, 2, 3, 4, 5};
    const std::vector vec2{1, 2, 3, 4, 6};
    const auto &[mis_first, mis_second] =
        utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.end());
    EXPECT_EQ(mis_second, vec2.end());
}

TEST(MismatchFromEnd, FirstRangeShorter) {
    //! [mismatch_from_end_start]
    const std::vector vec1{3, 4, 5};
    const std::vector vec2{1, 2, 3, 4, 5};
    const auto &[mis_first, mis_second] =
        utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    //! [mismatch_from_end_end]
    EXPECT_EQ(mis_first, vec1.begin());
    EXPECT_EQ(mis_second, vec2.begin() + 2);
}

TEST(MismatchFromEnd, SecondRangeShorter) {
    const std::vector vec1{1, 2, 3, 4, 5};
    const std::vector vec2{3, 4, 5};
    const auto &[mis_first, mis_second] =
        utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.begin() + 2);
    EXPECT_EQ(mis_second, vec2.begin());
}

TEST(MismatchFromEnd, EmptyFirstRange) {
    const std::vector<int> vec1{};
    const std::vector vec2{1, 2, 3, 4, 5};
    const auto &[mis_first, mis_second] =
        utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.end());
    EXPECT_EQ(mis_second, vec2.end());
}

TEST(MismatchFromEnd, BothRangesEmpty) {
    std::vector<int> vec1{};
    std::vector<int> vec2{};
    const auto &[mis_first, mis_second] =
        utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.end());
    EXPECT_EQ(mis_second, vec2.end());
}
