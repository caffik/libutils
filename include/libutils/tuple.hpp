#ifndef TUPLE_HPP
#define TUPLE_HPP

#include "utility.hpp"
#include <sstream>
#include <tuple>

namespace utils {
/**
 * @brief Moves elements from one tuple to another.
 *
 * This function template moves elements from the `from` tuple to the `to`
 * tuple. It uses compile-time recursion to iterate over the elements of the
 * tuples.
 *
 * @note The function moves first `min(sizeof...(Fs), sizeof...(Ts))` elements.
 * @remark If at least one of the corresponding elements are not move
 * assignable, the function will not compile.
 *
 * @tparam I The current index in the tuple (default is 0).
 * @tparam Fs The types of the elements in the `from` tuple.
 * @tparam Ts The types of the elements in the `to` tuple.
 * @param from The source tuple from which elements are moved.
 * @param to The destination tuple to which elements are moved.
 */
template <std::size_t I = 0, typename... Fs, typename... Ts>
void move_tuple_elements(std::tuple<Fs...> &from, std::tuple<Ts...> &to) {
  get_reference(std::get<I>(to)) = std::move(get_reference(std::get<I>(from)));
  if constexpr (I + 1 < std::min(sizeof...(Ts), sizeof...(Fs))) {
    move_tuple_elements<I + 1>(from, to);
  }
}

/**
 * @brief Swaps elements between two tuples.
 *
 * This function template swaps elements between the `tuple1` and `tuple2`
 * tuples. It uses compile-time recursion to iterate over the elements of the
 * tuples.
 *
 * @note The function swaps first `min(sizeof...(Ts), sizeof...(Us))` elements.
 * @remark If at least one of the corresponding elements are not swappable, the
 * function will not compile.
 *
 * @tparam I The current index in the tuple (default is 0).
 * @tparam Ts The types of the elements in the `tuple1`.
 * @tparam Us The types of the elements in the `tuple2`.
 * @param tuple1 The first tuple whose elements are to be swapped.
 * @param tuple2 The second tuple whose elements are to be swapped.
 */
template <std::size_t I = 0, typename... Ts, typename... Us>
void swap_tuple_elements(std::tuple<Ts...> &tuple1, std::tuple<Us...> &tuple2) {
  std::swap(get_reference(std::get<I>(tuple1)),
            get_reference(std::get<I>(tuple2)));
  if constexpr (I + 1 < std::min(sizeof...(Ts), sizeof...(Us))) {
    swap_tuple_elements<I + 1>(tuple1, tuple2);
  }
}

/**
 * @brief Copies elements from one tuple to another.
 *
 * This function template copies elements from the `from` tuple to the `to`
 * tuple. It uses compile-time recursion to iterate over the elements of the
 * tuples.
 *
 * @note The function copies the first `min(sizeof...(Fs), sizeof...(Ts))`
 * elements.
 * @remark If at least one of the corresponding elements is not copy assignable,
 * the function will not compile.
 *
 * @tparam I The current index in the tuple (default is 0).
 * @tparam Fs The types of the elements in the `from` tuple.
 * @tparam Ts The types of the elements in the `to` tuple.
 * @param from The source tuple from which elements are copied.
 * @param to The destination tuple to which elements are copied.
 */
template <std::size_t I = 0, typename... Fs, typename... Ts>
void copy_tuple_elements(const std::tuple<Fs...> &from, std::tuple<Ts...> &to) {
  get_reference(std::get<I>(to)) = get_reference(std::get<I>(from));
  if constexpr (I + 1 < std::min(sizeof...(Fs), sizeof...(Ts))) {
    copy_tuple_elements<I + 1>(from, to);
  }
}

/**
 * @brief Applies a function to corresponding elements of multiple tuples.
 *
 * This function template applies the given function `f` to the corresponding
 * elements of the provided tuples. It uses compile-time recursion to iterate
 * over the elements of the tuples.
 *
 * @tparam F The type of the function to apply.
 * @tparam Tuples The types of the tuples.
 * @param f The function to apply to the elements of the tuples.
 * @param tuples The tuples whose elements are to be processed.
 */
template <typename F, typename... Tuples>
constexpr void constexpr_for_tuples(F &&f, Tuples &&...tuples) {
  constexpr std::size_t N = std::min(std::initializer_list<std::size_t>{
      std::tuple_size_v<std::decay_t<Tuples>>...});

  constexpr_for<static_cast<std::size_t>(0), N, 1>(
      [&](auto i) { f(std::get<i>(tuples)...); });
}

////////////////////////// PointerTuple ///////////////////////////////////////

/**
 * @brief A class that holds a tuple of pointers to elements.
 *
 * This class template holds a tuple of pointers to objects of type `Ts...`.
 * Move and copy operators are applied to the objects pointed by the pointers
 * but not to the tuple itself. That is: the addresses of the pointers remain
 * the same after operations. Thought class manages the pointers, `get` function
 * and structured bindings return references.
 *
 * @tparam Ts The types of the elements.
 */
template <typename... Ts> class pointer_tuple {
public:
  // Constructors and assignment operators
  pointer_tuple() = delete;

  /**
   * @brief Copy constructor.
   *
   * This constructor creates a new pointer_tuple object as a copy of an
   * existing pointer_tuple object. It performs a kind of shallow copy. That is:
   * the pointers are not the references, but they point to the same objects.
   *
   * @param other The pointer_tuple object to copy from.
   */
  pointer_tuple(const pointer_tuple &other) = default;

  /**
   * @brief Move constructor.
   *
   * This constructor creates a new pointer_tuple object by moving the contents
   * of an existing pointer_tuple object.
   *
   * @param other The pointer_tuple object to move from.
   */
  pointer_tuple(pointer_tuple &&other) = default;
  ~pointer_tuple() = default;

  /**
   * @brief Constructs a pointer_tuple object with the given pointers of
   * elements.
   *
   * @param pointers The elements to be stored in the tuple.
   */
  explicit pointer_tuple(Ts *...pointers) : tuple_of_pointers_{pointers...} {}

  /**
   * @brief Copy assignment operator.
   *
   * Copies the objects pointed to by the pointers from the other pointer_tuple
   * object to the objects pointed to by the pointers in this object.
   *
   * @param other The pointer_tuple object to copy from.
   * @return A reference to this object.
   */
  pointer_tuple &operator=(const pointer_tuple &other) {
    copy_tuple_elements(other.tuple_of_pointers_, this->tuple_of_pointers_);
    return *this;
  }

  /**
   * @brief Move assignment operator.
   *
   * Moves the objects pointed to by the pointers from the other pointer_tuple
   * object to the objects pointed to by the pointers in this object.
   *
   * @param other The pointer_tuple object to move from.
   * @return A reference to this object.
   */
  pointer_tuple &operator=(pointer_tuple &&other) noexcept {
    move_tuple_elements(other.tuple_of_pointers_, this->tuple_of_pointers_);
    return *this;
  };

  /**
   * @brief Assignment operator for pointer_tuple.
   *
   * This operator assigns the values from a given std::tuple to the elements
   * pointed to by the pointers in the pointer_tuple.
   *
   * @param values A std::tuple containing the values to be assigned.
   * @return A reference to the modified pointer_tuple.
   */
  pointer_tuple &operator=(const std::tuple<Ts...> &values) {
    copy_tuple_elements(values, tuple_of_pointers_);
    return *this;
  }

  /**
   * @brief Returns a reference to the N-th element in the tuple of pointers.
   *
   * This function template returns a reference to the N-th element in the tuple
   * of pointers.
   *
   * @tparam N The index of the element to return.
   * @tparam InputIt The types of the elements in the pointer_tuple.
   * @param ptr_tuple The reference to pointer_tuple object whose element is to
   * be returned.
   * @return A reference to the N-th element in the tuple of pointers.
   */
  template <std::size_t N, typename... InputIt>
  friend std::tuple_element_t<N, pointer_tuple<InputIt...>>
  get(pointer_tuple<InputIt...> &ptr_tuple);

  /**
   * @brief Returns a reference to the N-th element in the tuple of pointers.
   *
   * This function template returns a reference to the N-th element in the tuple
   * of pointers.
   *
   * @tparam N The index of the element to return.
   * @tparam InputIt The types of the elements in the pointer_tuple.
   * @param ptr_tuple The rvalue pointer_tuple object whose element is to be
   * returned.
   * @return A reference to the N-th element in the tuple of pointers.
   */
  template <std::size_t N, typename... InputIt>
  friend std::tuple_element_t<N, pointer_tuple<InputIt...>>
  get(pointer_tuple<InputIt...> &&ptr_tuple);

  template <std::size_t N, typename... InputIt>
  friend std::tuple_element_t<N, pointer_tuple<InputIt...>>
  get(const pointer_tuple<InputIt...> &ptr_tuple);

  /**
   * @brief Converts the pointer_tuple to a std::tuple.
   *
   * This operator converts the pointer_tuple object to a std::tuple containing
   * references to the elements pointed to by the pointers in the tuple.
   *
   * @return A std::tuple containing references to the elements.
   */
  operator std::tuple<Ts...>() const {
    return std::apply([](auto &&...args) { return std::tuple(*args...); },
                      tuple_of_pointers_);
  }

  /**
   * @brief Swaps the data between this pointer_tuple and another.
   *
   * This function swaps the elements between the tuple of pointers in this
   * pointer_tuple object and the tuple of pointers in the provided
   * pointer_tuple object.
   *
   * @param o The pointer_tuple object to swap data with.
   */
  void swapData(pointer_tuple &o) {
    swap_tuple_elements(tuple_of_pointers_, o.tuple_of_pointers_);
  }

  /**
   * @brief Macro to define comparison operators for pointer_tuple.
   *
   * This macro defines a friend function for the specified comparison operator
   * to compare two pointer_tuple objects.
   *
   * @param op The comparison operator to define (e.g., ==, !=, <, >, <=, >=).
   */
#define COMPARE_OPERATOR(op)                                                   \
  friend bool operator op(const pointer_tuple &lhs,                            \
                          const pointer_tuple &rhs) {                          \
    bool result{true};                                                         \
    constexpr_for_tuples(                                                      \
        [&result](const auto &lhs_ptr, const auto &rhs_ptr) {                  \
          result &= (*lhs_ptr op * rhs_ptr);                                   \
        },                                                                     \
        lhs.tuple_of_pointers_, rhs.tuple_of_pointers_);                       \
    return result;                                                             \
  }

  COMPARE_OPERATOR(==)
  COMPARE_OPERATOR(!=)
  COMPARE_OPERATOR(<)
  COMPARE_OPERATOR(>)
  COMPARE_OPERATOR(<=)
  COMPARE_OPERATOR(>=)
#undef COMPARE_OPERATOR

private:
  std::tuple<Ts *...> tuple_of_pointers_{};
};

/**
 * @brief Macro to define swap functions for pointer_tuple.
 *
 * This macro defines a template function to swap the data between two
 * pointer_tuple objects with different reference qualifiers.
 *
 * @param lhs_ref The reference qualifier for the left-hand side pointer_tuple.
 * @param rhs_ref The reference qualifier for the right-hand side pointer_tuple.
 */
#define SWAP_REFERENCES(lhs_ref, rhs_ref)                                      \
  template <typename... Ts>                                                    \
  void swap(pointer_tuple<Ts...> lhs_ref lhs,                                  \
            pointer_tuple<Ts...> rhs_ref rhs) noexcept {                       \
    lhs.swapData(rhs);                                                         \
  }

SWAP_REFERENCES(&, &)
SWAP_REFERENCES(&&, &)
SWAP_REFERENCES(&, &&)
SWAP_REFERENCES(&&, &&)
#undef SWAP_REFERENCES

/**
 * @brief Returns a reference to the N-th element in the tuple of pointers.
 *
 * This function template returns a reference to the N-th element in the tuple
 * of pointers.
 *
 * @tparam N The index of the element to return.
 * @tparam InputIt The types of the elements in the pointer_tuple.
 * @param ptr_tuple The reference to pointer_tuple object whose element is to
 * be returned.
 * @return A reference to the N-th element in the tuple of pointers.
 */
template <std::size_t N, typename... InputIt>
std::tuple_element_t<N, pointer_tuple<InputIt...>>
get(pointer_tuple<InputIt...> &ptr_tuple) {
  return *std::get<N>(ptr_tuple.tuple_of_pointers_);
}

/**
 * @brief Returns a reference to the N-th element in the tuple of pointers.
 *
 * This function template returns a reference to the N-th element in the tuple
 * of pointers.
 *
 * @tparam N The index of the element to return.
 * @tparam InputIt The types of the elements in the pointer_tuple.
 * @param ptr_tuple The rvalue pointer_tuple object whose element is to be
 * returned.
 * @return A reference to the N-th element in the tuple of pointers.
 */
template <std::size_t N, typename... InputIt>
std::tuple_element_t<N, pointer_tuple<InputIt...>>
get(pointer_tuple<InputIt...> &&ptr_tuple) {
  return *std::get<N>(ptr_tuple.tuple_of_pointers_);
}

/**
 * @brief Returns a reference to the N-th element in the tuple of pointers.
 *
 * This function template returns a reference to the N-th element in the tuple
 * of pointers. It is a const version of the get function.
 *
 * @tparam N The index of the element to return.
 * @tparam Ts The types of the elements in the pointer_tuple.
 * @param ptr_tuple The const reference to a pointer_tuple object whose element
 * is to return.
 * @return A reference to the N-th element in the tuple of pointers.
 */
template <std::size_t N, typename... Ts>
std::tuple_element_t<N, pointer_tuple<Ts...>>
get(const pointer_tuple<Ts...> &ptr_tuple) {
  return *std::get<N>(ptr_tuple.tuple_of_pointers_);
}

/**
 * @brief Returns a reference to the N-th element in the tuple.
 *
 * @param tuple The const reference to the std::tuple object whose element is to
 * be returned.
 */
template <std::size_t N, typename... Ts>
decltype(auto) get(const std::tuple<Ts...> &tuple) {
  return std::get<N>(tuple);
}

/**
 * @brief Returns a reference to the N-th element in the tuple.
 *
 * @param tuple The rvalue reference to the std::tuple object whose element is
 * to be returned.
 */
template <std::size_t N, typename... Ts>
decltype(auto) get(std::tuple<Ts...> &&tuple) {
  return std::get<N>(std::move(tuple));
}

} // namespace utils

/*
 * Implementation of structured bindings for pointer_tuple.
 */

namespace std {
template <typename... Ts> struct tuple_size<utils::pointer_tuple<Ts...>> {
  static constexpr int value = sizeof...(Ts);
};

template <size_t I, typename... Ts>
struct tuple_element<I, utils::pointer_tuple<Ts...>> {
  using type = std::add_lvalue_reference_t<
      std::remove_pointer_t<std::tuple_element_t<I, std::tuple<Ts *...>>>>;
};

} // namespace std

namespace utils {

/**
 * @brief Overload of the stream insertion operator for reference pointer_tuple.
 *
 * This function template overloads the stream insertion operator (<<) for
 * pointer_tuple objects. It formats the elements pointed to by the pointers
 * in the tuple and inserts them into the output stream.
 *
 * @tparam CharT The character type of the output stream.
 * @tparam Traits The traits type of the output stream.
 * @tparam Ts The types of the elements in the pointer_tuple.
 * @param os The output stream to which the formatted string is inserted.
 * @param ptr_tuple The pointer_tuple object whose elements are to be formatted
 * and inserted into the output stream.
 * @return A reference to the output stream.
 */
template <typename CharT, typename Traits, typename... Ts,
          std::enable_if_t<(sizeof...(Ts) > 0), bool> = true>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> &os,
           pointer_tuple<Ts...> &ptr_tuple) {
  auto j{sizeof...(Ts)};
  std::basic_stringstream<CharT, Traits> ss;
  ss << "[";
  utils::constexpr_for<0, sizeof...(Ts), 1>([&ss, &ptr_tuple, &j](auto i) {
    ss << utils::get<i>(ptr_tuple) << (--j ? ", " : "");
  });
  ss << "]";
  os << ss.str();
  return os;
}

/**
 * @brief Overload of the stream insertion operator for rvalue pointer_tuple.
 */
template <typename CharT, typename Traits, typename... Ts,
          std::enable_if_t<(sizeof...(Ts) > 0), bool> = true>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> &os,
           pointer_tuple<Ts...> &&ptr_tuple) {
  auto j{sizeof...(Ts)};
  std::basic_stringstream<CharT, Traits> ss;
  ss << "[";
  utils::constexpr_for<0, sizeof...(Ts), 1>([&ss, &ptr_tuple, &j](auto i) {
    ss << utils::get<i>(ptr_tuple) << (--j ? ", " : "");
  });
  ss << "]";
  os << ss.str();
  return os;
}

} // namespace utils

#endif // TUPLE_HPP
