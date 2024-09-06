#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <type_traits>

namespace utils {
 /** @defgroup has_push_back_struct HasPushBack
  * @{
 */

 /**
  * @brief Trait to check if a type has a push_back method.
  *
  * This primary template inherits from std::false_type, indicating that the type
  * T does not have a push_back method.
  *
  * @tparam T The type to check.
  * @tparam Ignored A parameter to enable SFINAE, defaults to void.
  */
 template<typename T, typename = void>
 struct has_push_back : std::false_type {
 };

 /**
  * @brief Specialization of has_push_back for types that have a push_back
  * method.
  *
  * This specialization inherits from std::true_type, indicating that the type T
  * has a push_back method.
  *
  * @tparam T The type to check.
  */
 template<typename T>
 struct has_push_back<T, std::void_t<decltype(std::declval<T>().push_back({}))> >
   : std::true_type {
 };

 /**
  * @brief Helper variable template to check if a type has a push_back method.
  *
  * This variable template is a convenient way to check if a type T has a
  * push_back method. It is equivalent to has_push_back<T>::value.
  *
  * @tparam T The type to check.
  */
 template<typename T>
 inline constexpr bool has_push_back_v = has_push_back<T>::value;

 /** @} */ // end of has_push_back_struct

 /** @defgroup has_insert_struct HasInsert
  * @{
 */
 /**
  * @brief Trait to check if a type has an insert method.
  *
  * This primary template inherits from std::false_type, indicating that the type
  * T does not have an insert method.
  *
  * @tparam T The type to check.
  * @tparam Ignored A parameter to enable SFINAE, defaults to void.
  */
 template<typename T, typename = void>
 struct has_insert : std::false_type {
 };

 /**
  * @brief Specialization of has_insert for types that have an insert method.
  *
  * This specialization inherits from std::true_type, indicating that the type T
  * has an insert method.
  *
  * @tparam T The type to check.
  */
 template<typename T>
 struct has_insert<T, std::void_t<decltype(std::declval<T>().insert({}, {}))> >
   : std::true_type {
 };

 /**
  * @brief Helper variable template to check if a type has an insert method.
  *
  * This variable template is a convenient way to check if a type T has an
  * insert method. It is equivalent to has_insert<T>::value.
  *
  * @tparam T The type to check.
  */
 template<typename T>
 inline constexpr bool has_insert_v = has_insert<T>::value;

 /** @} */ // end of has_insert_struct

 /** @defgroup remove_cvref_alias RemoveCVRef
  * @{
 */
 /**
  * @brief Alias template to remove const, volatile, and reference qualifiers from a type.
  *
  * This alias template removes const, volatile, and reference qualifiers from the type T.
  *
  * @tparam T The type to remove qualifiers from.
  */
 template<typename T>
 using remove_cvref = std::remove_cv<std::remove_reference_t<T> >;

 /**
  * @brief Alias template to remove const, volatile, and reference qualifiers from a type.
  *
  * This alias template removes const, volatile, and reference qualifiers from the type T.
  * It is equivalent to remove_cvref<T>::type.
  *
  * @tparam T The type to remove qualifiers from.
  */
 template<typename T>
 using remove_cvref_t = typename remove_cvref<T>::type;
 /** @} */ // end of remove_cvref_alias

 /** @defgroup invoke_or_return InvokeOrReturn
  * @{
 */
 /**
  * @brief Invokes a series of functions on a copy of the given argument and returns the modified copy.
  *
  * This function template takes an argument by reference, creates a copy of it, and then invokes
  * each of the provided functions on the copy. The modified copy is then returned.
  *
  * @tparam T The type of the argument.
  * @tparam Funcs The types of the functions to be invoked.
  * @tparam N The number of functions to be invoked (deduced automatically).
  * @param arg The argument to be copied and modified.
  * @param funcs The functions to be invoked on the copied argument.
  * @return The modified copy of the argument.
  *
  * @note The signature of the functions must be equivalent to void(T &a).
  *
  */
 template<typename T, typename... Funcs, std::size_t N = sizeof...(Funcs)>
 std::enable_if_t<N != 0, T> invoke_or_return(T &arg, Funcs&&... funcs) {
  T arg_cp{arg};
  (std::invoke(funcs, arg_cp), ...);
  return arg_cp;
 }

 /**
  * @brief Returns the argument as is when no functions are provided.
  *
  * This function template takes an argument by reference and returns it without any modifications
  * if no functions are provided.
  *
  * @tparam T The type of the argument.
  * @tparam Funcs The types of the functions (not used in this specialization).
  * @tparam N The number of functions (deduced automatically, should be zero).
  * @param arg The argument to be returned as is.
  * @param funcs The functions (not used in this specialization).
  * @return The original argument.
  */
 template<typename T, typename... Funcs, std::size_t N = sizeof...(Funcs)>
 std::enable_if_t<N == 0, T &> invoke_or_return(T &arg, Funcs&&... funcs) {
  return arg;
 }

 /** @} */ // end of invoke_or_return
} // namespace utils

#endif // TYPE_TRAITS_HPP
