#include <gtest/gtest.h>
#include <libutils/utility.hpp>

TEST(GetReference, ReturnsReferenceForValue) {
  int value{42};
  int &ref{utils::get_reference(value)};
  EXPECT_EQ(&ref, &value);
}

TEST(GetReference, ReturnsReferenceForPointer) {
  //! [get_reference_start]
  int value{42};
  int *ptr{&value};
  //! [get_reference_end]
  int &ref{utils::get_reference(ptr)};
  EXPECT_EQ(&ref, &value);
}

TEST(GetReference, HandlesConstValue) {
  const int value{42};
  const int &ref{utils::get_reference(value)};
  EXPECT_EQ(&ref, &value);
}

TEST(GetReference, HandlesConstPointer) {
  const int value{42};
  const int *ptr{&value};
  const int &ref{utils::get_reference(ptr)};
  EXPECT_EQ(&ref, &value);
}

TEST(GetReference, HandlesNullPointer) {
  int *ptr = nullptr;
  EXPECT_THROW(utils::get_reference(ptr), std::bad_function_call);
}
