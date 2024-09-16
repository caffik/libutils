.. _page_utility:

Utility
====

The **utility** header file provides a set of general purpose utilities to
simplify common programming tasks. Some of the functions are written
to operate during compile-time, while others are written to operate
during run-time.

.. doxygenfile:: utility.hpp
    :project: libutils

Usage
------

The following examples demonstrates how to use the **utility** header file:

- ``get_reference``

.. literalinclude:: ../../../tests/test.utility.cpp
    :language: cpp
    :start-after: get_reference_start
    :end-before: get_reference_end
    :dedent: 4:
    :append:
        int &ref{value};
        std::cout << std::is_same_v<decltype(utils::get_reference(ptr)), int&>  << ",  "
                        << std::is_same_v<decltype(utils::get_reference(ref)), int&> << ", "
                        << std::is_same_v<decltype(utils::get_reference(value)), int&>
                        << std::endl;

Output:

.. code-block:: none

    1, 1, 1

- ``constexpr_for``

.. code-block:: cpp

    // this is rather naive example but it demonstrates how to use the constexpr_for
    template <std::size_t N>
    struct fibonacci : std::integral_constant<std::size_t,
        fibonacci<N-1>::value + fibonacci<N-2>::value> { };

    template <>
    struct fibonacci<0> : std::integral_constant<std::size_t, 0> {};

    template <>
    struct fibonacci<1> : std::integral_constant<std::size_t, 1> {};

    template <>
    struct fibonacci<2> : std::integral_constant<std::size_t, 1> {};

    int main() {
        constexpr std::size_t n{10};
        std::array<std::size_t, n> fib{};
        utils::constexpr_for<0, n, 1>([&fib](auto i) {
            fib[i] = fibonacci<i>::value;
        });

        std::cout << fib[99] << std::endl;
    }

Output:

.. code-block:: none

    3405478146
