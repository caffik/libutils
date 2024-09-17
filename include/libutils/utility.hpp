#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <functional>

namespace utils {
/**
 * @brief Returns a reference to the value or dereferenced pointer.
 *
 * This function template takes a forwarding reference to a value or pointer.
 * If the argument is a pointer, it returns a reference to the value pointed to
 * by the pointer. Otherwise, it returns the value itself.
 *
 * @tparam T The type of the argument, deduced automatically.
 * @param t The value or pointer to be processed.
 * @return A reference to the value or dereferenced pointer.
 * @throws std::bad_function_call if the pointer is null.
 */
template <typename T> T &get_reference(T &t) { return t; }
template <typename T> T &get_reference(T *t) {
  if (!t)
    throw std::bad_function_call();
  return *t;
}

/**
 * @brief Executes a function in a compile-time loop.
 *
 * This function template executes a given function in a compile-time loop
 * from Start to End with a step of Inc. The function is called with the current
 * index wrapped in an integral constant.
 *
 * @tparam Start The starting index of the loop.
 * @tparam End The ending index of the loop.
 * @tparam I The increment step for each iteration.
 * @tparam F The type of the function to be called.
 * @param f The function to be called with the current index.
 */
template <auto Start, auto End, auto I, typename F>
constexpr void constexpr_for(F &&f) {
  if constexpr (Start < End) {
    // Call the function with the current index: Start.
    f(std::integral_constant<decltype(Start), Start>());
    constexpr_for<Start + I, End, I>(f);
  }
}

} // namespace utils

#endif // UTILITY_HPP
