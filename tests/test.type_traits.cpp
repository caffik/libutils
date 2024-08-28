#include <gtest/gtest.h>
#include <libutils/type_traits.hpp>
#include <list>
#include <vector>

/**
 * HasPushBack tests.
 */

TEST(HasPushBack, VectorHasPushBack) {
  EXPECT_TRUE(utils::has_push_back_v<std::vector<int>>);
}

TEST(HasPushBack, ListHasPushBack) {
  EXPECT_TRUE(utils::has_push_back_v<std::list<int>>);
}

TEST(HasPushBack, IntDoesNotHavePushBack) {
  EXPECT_FALSE(utils::has_push_back_v<int>);
}

TEST(HasPushBack, CustomTypeWithPushBack) {
  struct Custom {
    void push_back(int) {}
  };
  EXPECT_TRUE(utils::has_push_back_v<Custom>);
}

TEST(HasPushBack, CustomTypeWithoutPushBack) {
  struct Custom {};
  EXPECT_FALSE(utils::has_push_back_v<Custom>);
}

/**
 * HasInsert tests.
 */

TEST(HasInsert, VectorHasInsert) {
  EXPECT_TRUE(utils::has_insert_v<std::vector<int>>);
}

TEST(HasInsert, ListHasInsert) {
  EXPECT_TRUE(utils::has_insert_v<std::list<int>>);
}

TEST(HasInsert, IntDoesNotHaveInsert) {
  EXPECT_FALSE(utils::has_insert_v<int>);
}

TEST(HasInsert, CustomTypeWithInsert) {
  struct Custom {
    void insert(int, int) {}
  };
  EXPECT_TRUE(utils::has_insert_v<Custom>);
}

TEST(HasInsert, CustomTypeWithoutInsert) {
  struct Custom {};
  EXPECT_FALSE(utils::has_insert_v<Custom>);
}

/**
 * RemoveCVRef tests.
 */

TEST(RemoveCVRef, RemoveConst) {
  EXPECT_TRUE((std::is_same_v<utils::remove_cvref_t<const int>, int>));
}

TEST(RemoveCVRef, RemoveVolatile) {
  EXPECT_TRUE((std::is_same_v<utils::remove_cvref_t<volatile int>, int>));
}

TEST(RemoveCVRef, RemoveReference) {
  EXPECT_TRUE((std::is_same_v<utils::remove_cvref_t<int&>, int>));
}

TEST(RemoveCVRef, RemoveConstVolatile) {
  EXPECT_TRUE((std::is_same_v<utils::remove_cvref_t<const volatile int>, int>));
}

TEST(RemoveCVRef, RemoveConstReference) {
  EXPECT_TRUE((std::is_same_v<utils::remove_cvref_t<const int&>, int>));
}

TEST(RemoveCVRef, RemoveVolatileReference) {
  EXPECT_TRUE((std::is_same_v<utils::remove_cvref_t<volatile int&>, int>));
}

TEST(RemoveCVRef, RemoveConstVolatileReference) {
  EXPECT_TRUE((std::is_same_v<utils::remove_cvref_t<const volatile int&>, int>));
}
