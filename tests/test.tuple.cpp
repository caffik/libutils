#include <gtest/gtest.h>
#include <libutils/tuple.hpp>
#include <list>

/*
 * MoveTuplesArgs tests.
 */

TEST(moveTupleElements, MoveReferences) {
  // [!move_tuple_elements_start]
  std::vector vec1{1, 2, 3, 4, 5};
  auto from{std::forward_as_tuple(vec1)};
  std::vector vec2{6, 7, 8, 9, 10, 11, 12};
  auto to{std::forward_as_tuple(vec2)};
  // [!move_tuple_elements_start]
  const auto expected{reinterpret_cast<long long>(vec1.data())};

  utils::move_tuple_elements(from, to);
  const auto result{reinterpret_cast<long long>(std::get<0>(to).data())};
  EXPECT_EQ(result, expected);
}

TEST(moveTupleElements, MovePointers) {
  std::vector vec1{1, 2, 3, 4, 5};
  auto from{std::make_tuple(&vec1)};
  std::vector vec2{1, 2, 3, 4, 5, 6, 7};
  auto to{std::make_tuple(&vec2)};

  const auto expected{reinterpret_cast<long long>(vec1.data())};

  utils::move_tuple_elements(from, to);
  const auto result{reinterpret_cast<long long>(std::get<0>(to)->data())};
  EXPECT_EQ(result, expected);
}

TEST(moveTupleElements, MovePointersValues) {
  std::vector vec1{1, 2, 3, 4, 5};
  auto from{std::forward_as_tuple(vec1)};
  std::vector vec2{1, 2, 3, 4, 5, 6, 7};
  auto to{std::make_tuple(&vec2)};

  const auto expected{reinterpret_cast<long long>(vec1.data())};

  utils::move_tuple_elements(from, to);
  const auto result{reinterpret_cast<long long>(std::get<0>(to)->data())};
  EXPECT_EQ(result, expected);
}

/*
 * SwapTuplesArgs tests.
 */

TEST(SwapTupleElements, SwapsElementsOfSameType) {
  std::tuple tuple1(1, 2.0, 'a'); // <int, double, char>
  std::tuple tuple2(3, 4.0, 'b'); // <int, double, char>
  utils::swap_tuple_elements(tuple1, tuple2);
  EXPECT_EQ(std::get<0>(tuple1), 3);
  EXPECT_EQ(std::get<1>(tuple1), 4.0);
  EXPECT_EQ(std::get<2>(tuple1), 'b');
  EXPECT_EQ(std::get<0>(tuple2), 1);
  EXPECT_EQ(std::get<1>(tuple2), 2.0);
  EXPECT_EQ(std::get<2>(tuple2), 'a');
}

TEST(SwapTupleElements, SwapsElementsWithDifferentSizes) {
  std::tuple tuple1(1, 2.0);      // <int, double>
  std::tuple tuple2(3, 4.0, 'b'); // <int, double, char>
  utils::swap_tuple_elements(tuple1, tuple2);
  EXPECT_EQ(std::get<0>(tuple1), 3);
  EXPECT_EQ(std::get<1>(tuple1), 4.0);
  EXPECT_EQ(std::get<0>(tuple2), 1);
  EXPECT_EQ(std::get<1>(tuple2), 2.0);
  EXPECT_EQ(std::get<2>(tuple2), 'b');
}

TEST(SwapTupleElements, SwapReferences) {
  // [!swap_tuple_elements_start]
  std::vector vec1{1, 2, 3, 4, 5};
  auto tuple1{std::forward_as_tuple(vec1)};
  std::vector vec2{6, 7, 8, 9, 10, 11, 12};
  auto tuple2{std::forward_as_tuple(vec2)};
  // [!swap_tuple_elements_end]

  const auto expected{reinterpret_cast<long long>(vec1.data())};
  utils::move_tuple_elements(tuple1, tuple2);
  const auto result{reinterpret_cast<long long>(std::get<0>(tuple2).data())};
  EXPECT_EQ(result, expected);
}

TEST(SwapTupleElements, SwapPointers) {
  std::vector vec1{1, 2, 3, 4, 5};
  auto tuple1{std::make_tuple(&vec1)};
  std::vector vec2{1, 2, 3, 4, 5, 6, 7};
  auto tuple2{std::make_tuple(&vec2)};

  const auto expected{reinterpret_cast<long long>(vec1.data())};
  utils::move_tuple_elements(tuple1, tuple2);
  const auto result{reinterpret_cast<long long>(std::get<0>(tuple2)->data())};
  EXPECT_EQ(result, expected);
}

/*
 * CopyTuplesArgs tests.
 */

TEST(copyTupleElements, CopyReferences) {
  // [!copy_tuple_elements_start]
  std::vector vec1{1, 2, 3, 4, 5};
  auto from{std::forward_as_tuple(vec1)};
  std::vector vec2{6, 7, 8, 9, 10, 11, 12};
  auto to{std::forward_as_tuple(vec2)};
  // [!copy_tuple_elements_end]

  const auto expected{reinterpret_cast<long long>(vec1.data())};
  utils::copy_tuple_elements(from, to);
  const auto result{reinterpret_cast<long long>(std::get<0>(to).data())};
  EXPECT_NE(result, expected);
  EXPECT_EQ(std::get<0>(from), std::get<0>(to));
}

TEST(copyTupleElements, CopyPointers) {
  std::vector vec1{1, 2, 3, 4, 5};
  auto from{std::make_tuple(&vec1)};
  std::vector vec2{1, 2, 3, 4, 5, 6, 7};
  auto to{std::make_tuple(&vec2)};

  const auto expected{reinterpret_cast<long long>(vec1.data())};
  utils::copy_tuple_elements(from, to);
  const auto result{reinterpret_cast<long long>(std::get<0>(to)->data())};
  EXPECT_NE(result, expected);
  EXPECT_EQ(*std::get<0>(from), *std::get<0>(to));
}

/*
 * ConstexprForTuples tests.
 */

TEST(ConstexprForTuples, AppliesFunctionToElementsOfSameType) {
  std::tuple tuple1(1, 2.0, 'a');
  std::tuple tuple2(3, 4.0, 'b');
  std::vector<int> results;
  utils::constexpr_for_tuples([&](auto a, auto b) { results.push_back(a + b); },
                              tuple1, tuple2);
  EXPECT_EQ(results[0], 4);
  EXPECT_EQ(results[1], 6.0);
  EXPECT_EQ(results[2], 'a' + 'b');
}

TEST(ConstexprForTuples, AppliesFunctionToElementsOfDifferentTypes) {
  // [!constexpr_for_tuples_start]
  std::tuple tuple1(1, 2.0, 'a');
  std::tuple tuple2(3L, 4.0f, 'b');
  std::vector<int> results;
  utils::constexpr_for_tuples([&](auto a, auto b) { results.push_back(a + b); },
                              tuple1, tuple2);
  // [!constexpr_for_tuples_end]
  EXPECT_EQ(results[0], 4);
  EXPECT_EQ(results[1], 6.0);
  EXPECT_EQ(results[2], 'a' + 'b');
}

TEST(ConstexprForTuples, AppliesFunctionToElementsWithDifferentSizes) {
  std::tuple tuple1(1, 2.0);
  std::tuple tuple2(3, 4.0, 'b');
  std::vector<int> results;
  utils::constexpr_for_tuples([&](auto a, auto b) { results.push_back(a + b); },
                              tuple1, tuple2);
  EXPECT_EQ(results[0], 4);
  EXPECT_EQ(results[1], 6.0);
}

/*
 * pointer_tuple tests.
 */

class PointerTupleTest : public ::testing::Test {
protected:
  std::string a{"Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                "Phasellus consectetur rhoncus lorem id aliquam. Donec maximus "
                "felis in turpis maximus, et pretium mi pretium. Vivamus sit "
                "amet risus fringilla, interdum nisi non, dignissim nulla."};
  std::vector<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list<int> c{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  utils::pointer_tuple<std::string, std::vector<int>, std::list<int>> ptr_tuple{
      &a, &b, &c};
};

TEST_F(PointerTupleTest, StructuredBinding) {
  auto &[a, b, c] = ptr_tuple;
  EXPECT_EQ(&a, &utils::get<0>(ptr_tuple));
  EXPECT_EQ(&b, &utils::get<1>(ptr_tuple));
  EXPECT_EQ(&c, &utils::get<2>(ptr_tuple));
}

TEST_F(PointerTupleTest, CopyAssignmentCopiesValues) {
  std::string x{
      "Quisque urna dolor, feugiat vitae aliquam eget, fringilla a ipsum. Duis "
      "tempor facilisis pharetra. Suspendisse potenti. Ut et mi lorem."};
  std::vector y{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  std::list z{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

  utils::pointer_tuple other{&x, &y, &z};
  ptr_tuple = other;
  auto &[a, b, c] = ptr_tuple;

  EXPECT_EQ(a, x); EXPECT_NE(&a, &x);
  EXPECT_EQ(b, y); EXPECT_NE(&b, &y);
  EXPECT_EQ(c, z); EXPECT_NE(&c, &z);
}

TEST_F(PointerTupleTest, MoveAssignmentMovesValues) {
  std::string x{
      "Quisque urna dolor, feugiat vitae aliquam eget, fringilla a ipsum. Duis "
      "tempor facilisis pharetra. Suspendisse potenti. Ut et mi lorem."};
  std::vector y{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  std::list z{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

  auto x_data{reinterpret_cast<long long>(x.data())};
  auto y_data{reinterpret_cast<long long>(y.data())};
  auto z_data{&z.front()};
  utils::pointer_tuple other{&x, &y, &z};
  ptr_tuple = std::move(other);
  auto &[a, b, c] = ptr_tuple;

  EXPECT_EQ(reinterpret_cast<long long>(a.data()), x_data);
  EXPECT_EQ(reinterpret_cast<long long>(b.data()), y_data);
  EXPECT_EQ(&c.front(), z_data);
}

TEST_F(PointerTupleTest, Swap) {
  std::string x{
      "Quisque urna dolor, feugiat vitae aliquam eget, fringilla a ipsum. Duis "
      "tempor facilisis pharetra. Suspendisse potenti. Ut et mi lorem."};
  std::vector y{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  std::list z{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  utils::pointer_tuple other{&x, &y, &z};

  auto x_data{reinterpret_cast<long long>(x.data())};
  auto y_data{reinterpret_cast<long long>(y.data())};
  auto z_data{&z.front()};

  utils::swap(ptr_tuple, other);
  auto &[a, b, c] = ptr_tuple;

  EXPECT_EQ(reinterpret_cast<long long>(a.data()), x_data);
  EXPECT_EQ(reinterpret_cast<long long>(b.data()), y_data);
  EXPECT_EQ(&c.front(), z_data);
}


TEST_F(PointerTupleTest, ImplicitTupleConversion) {
  std::tuple<std::string, std::vector<int>, std::list<int>> tuple{ptr_tuple};
  auto &[a, b, c] = tuple;

  EXPECT_TRUE(a == utils::get<0>(ptr_tuple));
  EXPECT_TRUE(b == utils::get<1>(ptr_tuple));
  EXPECT_TRUE(c == utils::get<2>(ptr_tuple));
}


TEST(PointerTupleTemporary, Get) {
  std::string a{"Lorem ipsum dolor sit amet"};
  double d{3.14};
  char c{'a'};
  EXPECT_EQ(&a, &utils::get<0>(utils::pointer_tuple{&a, &d, &c}));
  EXPECT_EQ(&d, &utils::get<1>(utils::pointer_tuple{&a, &d, &c}));
  EXPECT_EQ(&c, &utils::get<2>(utils::pointer_tuple{&a, &d, &c}));
}

TEST(PointerTuple, OutputOperator) {
  std::string a{"Lorem ipsum dolor sit amet"};
  double d{3.14};
  char c{'a'};
  utils::pointer_tuple ptr_tuple{&a, &d, &c};
  std::stringstream ss;
  ss << ptr_tuple;
  EXPECT_EQ(ss.str(), "[Lorem ipsum dolor sit amet, 3.14, a]");
  ss.clear(); ss.str("");
  ss << utils::pointer_tuple{&a, &d, &c};
  EXPECT_EQ(ss.str(), "[Lorem ipsum dolor sit amet, 3.14, a]");
}
