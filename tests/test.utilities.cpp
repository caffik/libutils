#include <gtest/gtest.h>
#include <libutils/utilities.hpp>

TEST(Utilities, copy) {
  std::vector vec1{1, 2};
  std::vector<int> vec2(8);

  utils::copy(vec1.begin(), vec1.end(), vec2.begin(), 4);
  std::vector expected{1, 2, 1, 2, 1, 2, 1, 2};
  ASSERT_TRUE(vec2 == expected);
}

TEST(Utilities, mismatch_from_end) {
  std::vector vec1{1, 2, 3, 4, 5, 6, 7};
  std::vector vec2{8, 5, 6, 7};

  auto number_of_same_elems_from_end{3};
  auto expected = std::make_pair(std::prev(vec1.end(), number_of_same_elems_from_end),
                                 std::prev(vec2.end(), number_of_same_elems_from_end));

  ASSERT_TRUE(utils::mismatch_from_end(vec1.begin(), vec1.end(), vec2.end())
              == expected);                           
}

TEST(Utilities, distanceBetween) {
  std::vector vec{1,2,3,4,5,6,7};
  using difference_type = std::vector<int>::difference_type;  
  std::vector<difference_type> expected{3, 2, 1};
  
  auto distanceBetween{utils::distanceBetween(vec.begin(), 
                                                      std::next(vec.begin(), 3),
                                                      std::next(vec.begin(), 5),
                                                      std::prev(vec.end(), 1))};
  ASSERT_TRUE(distanceBetween == expected);
}

TEST(Utilities, distanceDifference) {
  std::vector vec1{1, 2, 3, 4, 5, 6, 7};
  std::vector vec2{5, 6, 1};

  auto expected{4};
  ASSERT_TRUE(utils::distanceDifference(vec1.begin(), vec1.end(),
                                                vec2.begin(), vec2.end())
              == expected);
}

TEST(Utilities, getLongerRange) {
  std::vector vec1{1, 2, 3, 4, 5, 6, 7};
  std::vector vec2{8, 5, 6, 7};

  auto expected{std::make_pair(vec1.begin(), vec1.end())};

  ASSERT_TRUE(utils::getLongerRange(vec1.begin(), vec1.end(), 
                                            vec2.begin(), vec2.end())
              == expected);
}
