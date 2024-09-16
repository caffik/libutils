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
 * ArgmaxConditional tests.
 */

TEST(ArgmaxConditional, FindsIndexOfMaxElementWithPredicate) {
    //! [argmax_conditional_start]
    const std::vector v1{1, 3, 5, 7, 9};
    const std::vector v2{0, 1, 0, 1, 0};
    const auto result{utils::argmax_conditional(v1.begin(), v1.end(), v2.begin(), [](const int x) { return x == 1; })};
    //! [argmax_conditional_end]
    EXPECT_EQ(result, std::make_pair(true, static_cast<std::size_t>(3)));
}

TEST(ArgmaxConditional, NoElementSatisfiesPredicate) {
    const std::vector v1{1, 3, 5, 7, 9};
    const std::vector v2{0, 0, 0, 0, 0};
    const auto result{utils::argmax_conditional(v1.begin(), v1.end(), v2.begin(), [](const int x) { return x == 1; })};
    EXPECT_EQ(result, std::make_pair(false, static_cast<std::size_t>(5)));
}

TEST(ArgmaxConditional, EmptyRange) {
    const std::vector<int> v1{};
    const std::vector<int> v2{};
    const auto result{utils::argmax_conditional(v1.begin(), v1.end(), v2.begin(), [](const int x) { return x == 1; })};
    EXPECT_EQ(result, std::make_pair(false, static_cast<std::size_t>(0)));
}

TEST(ArgmaxConditional, SingleElementSatisfiesPredicate) {
    const std::vector v1{1};
    const std::vector v2{1};
    const auto result{utils::argmax_conditional(v1.begin(), v1.end(), v2.begin(), [](const int x) { return x == 1; })};
    EXPECT_EQ(result, std::make_pair(true, static_cast<std::size_t>(0)));
}

TEST(ArgmaxConditional, MultipleElementsSatisfyPredicate) {
    const std::vector v1{1, 3, 5, 7, 9};
    const std::vector v2{1, 1, 1, 1, 1};
    const auto result{utils::argmax_conditional(v1.begin(), v1.end(), v2.begin(), [](const int x) { return x == 1; })};
    EXPECT_EQ(result, std::make_pair(true, static_cast<std::size_t>(4)));
}

/**
 * CopyRangeNTimes tests.
 */

TEST(CopyRangeNTimes, CopiesRangeMultipleTimes) {
    //! [copy_range_n_times_start]
    const std::vector source{1, 2, 3};
    std::vector<int> destination(9);
    const auto result{utils::copy_range_n_times(source.begin(), source.end(), destination.begin(), 3)};
    //! [copy_range_n_times_end]
    const std::vector expected{1, 2, 3, 1, 2, 3, 1, 2, 3};
    EXPECT_EQ(destination, expected);
    EXPECT_EQ(result, destination.end());
}

TEST(CopyRangeNTimes, CopiesRangeOnce) {
    const std::vector source{1, 2, 3};
    std::vector<int> destination(3);
    const auto result{utils::copy_range_n_times(source.begin(), source.end(), destination.begin(), 1)};
    const std::vector expected{1, 2, 3};
    EXPECT_EQ(destination, expected);
    EXPECT_EQ(result, destination.end());
}

TEST(CopyRangeNTimes, HandlesEmptySourceRange) {
    const std::vector<int> source{};
    std::vector<int> destination(0);
    const auto result{utils::copy_range_n_times(source.begin(), source.end(), destination.begin(), 3)};
    const std::vector<int> expected{};
    EXPECT_EQ(destination, expected);
    EXPECT_EQ(result, destination.end());
}

/**
 * MaxElementConditional tests.
 */

TEST(MaxElementConditional, FindsMaxElementWithPredicate) {
    //! [max_element_conditional_start]
    const std::vector v1{1, 3, 5, 7, 9};
    const std::vector v2{0, 1, 0, 1, 0};
    const auto result{
            utils::max_element_conditional(v1.begin(), v1.end(), v2.begin(), [](const int x) { return x == 1; })};
    //! [max_element_conditional_end]
    EXPECT_EQ(*result, 7);
}

TEST(MaxElementConditional, NoElementSatisfiesPredicate) {
    const std::vector v1{1, 3, 5, 7, 9};
    const std::vector v2{0, 0, 0, 0, 0};
    const auto result{
            utils::max_element_conditional(v1.begin(), v1.end(), v2.begin(), [](const int x) { return x == 1; })};
    EXPECT_EQ(result, v1.end());
}

TEST(MaxElementConditional, EmptyRange) {
    const std::vector<int> v1{};
    const std::vector<int> v2{};
    const auto result{
            utils::max_element_conditional(v1.begin(), v1.end(), v2.begin(), [](const int x) { return x == 1; })};
    EXPECT_EQ(result, v1.end());
}

TEST(MaxElementConditional, SingleElementSatisfiesPredicate) {
    const std::vector v1{1};
    const std::vector v2{1};
    const auto result{
            utils::max_element_conditional(v1.begin(), v1.end(), v2.begin(), [](const int x) { return x == 1; })};
    EXPECT_EQ(*result, 1);
}

/**
 * MismatchFromEnd tests.
 */

TEST(MismatchFromEnd, IdenticalRanges) {
    const std::vector vec1{1, 2, 3, 4, 5};
    const std::vector vec2{1, 2, 3, 4, 5};
    const auto &[mis_first, mis_second] = utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.begin());
    EXPECT_EQ(mis_second, vec2.begin());
}

TEST(MismatchFromEnd, DifferentRanges) {
    const std::vector vec1{1, 2, 3, 4, 5};
    const std::vector vec2{1, 2, 3, 4, 6};
    const auto &[mis_first, mis_second] = utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.end());
    EXPECT_EQ(mis_second, vec2.end());
}

TEST(MismatchFromEnd, FirstRangeShorter) {
    //! [mismatch_from_end_start]
    const std::vector vec1{3, 4, 5};
    const std::vector vec2{1, 2, 3, 4, 5};
    const auto &[mis_first, mis_second] = utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    //! [mismatch_from_end_end]
    EXPECT_EQ(mis_first, vec1.begin());
    EXPECT_EQ(mis_second, vec2.begin() + 2);
}

TEST(MismatchFromEnd, SecondRangeShorter) {
    const std::vector vec1{1, 2, 3, 4, 5};
    const std::vector vec2{3, 4, 5};
    const auto &[mis_first, mis_second] = utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.begin() + 2);
    EXPECT_EQ(mis_second, vec2.begin());
}

TEST(MismatchFromEnd, EmptyFirstRange) {
    const std::vector<int> vec1{};
    const std::vector vec2{1, 2, 3, 4, 5};
    const auto &[mis_first, mis_second] = utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.end());
    EXPECT_EQ(mis_second, vec2.end());
}

TEST(MismatchFromEnd, BothRangesEmpty) {
    std::vector<int> vec1{};
    std::vector<int> vec2{};
    const auto &[mis_first, mis_second] = utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end());
    EXPECT_EQ(mis_first, vec1.end());
    EXPECT_EQ(mis_second, vec2.end());
}

/*
 * ReorderElementsByIndices tests.
 */

TEST(ReorderElementsByIndices, ReordersCorrectly) {
    //! [reorder_elements_by_indices_start]
    std::vector elements{10, 20, 30, 40};
    std::vector indices{3, 2, 1, 0};
    utils::reorder_elements_by_indices(elements.begin(), elements.end(), indices.begin());
    //! [reorder_elements_by_indices_end]
    EXPECT_EQ(elements, (std::vector{40, 30, 20, 10}));
}

TEST(ReorderElementsByIndices, NoReorderingNeeded) {
    std::vector elements{10, 20, 30, 40};
    std::vector indices{0, 1, 2, 3};
    utils::reorder_elements_by_indices(elements.begin(), elements.end(), indices.begin());
    EXPECT_EQ(elements, (std::vector{10, 20, 30, 40}));
}

TEST(ReorderElementsByIndices, SingleElement) {
    std::vector elements = {10};
    std::vector indices = {0};
    utils::reorder_elements_by_indices(elements.begin(), elements.end(), indices.begin());
    EXPECT_EQ(elements, (std::vector{10}));
}

TEST(ReorderElementsByIndices, EmptyRange) {
    std::vector<int> elements = {};
    std::vector<int> indices = {};
    utils::reorder_elements_by_indices(elements.begin(), elements.end(), indices.begin());
    EXPECT_EQ(elements, (std::vector<int>{}));
}
