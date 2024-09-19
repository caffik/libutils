.. _page_tuple.rst:

Tuple
=====

The header file **tuple** provides utilities for
manipulating tuples, including moving, copying, and swapping elements
between tuples. It also allows applying functions to corresponding
elements of multiple tuples. Additionally, it offers a class for managing
tuples of pointers.

.. doxygenfile:: tuple.hpp
    :project: libutils

Usage
------

The following examples demonstrate how to use the **tuple** header file:

- ``move_tuple_elements``

.. literalinclude:: ../../../tests/test.tuple.cpp
    :language: cpp
    :start-after: move_tuple_elements_start
    :end-before: move_tuple_elements_end
    :dedent: 4
    :append:
        utils::move_tuple_elements(from, to);
        for (const auto & e : vec2) {
            std::cout << e << " ";
        }

Output:

.. code-block:: none

    1 2 3 4 5

- ``swap_tuple_elements``

.. literalinclude:: ../../../tests/test.tuple.cpp
    :language: cpp
    :start-after: swap_tuple_elements_start
    :end-before: swap_tuple_elements_end
    :dedent: 4
    :append:
        utils::swap_tuple_elements(tuple1, tuple2);
        for (const auto & e : vec1) {
            std::cout << e << " ";
        }

Output:

.. code-block:: none

    6 7 8 9 10 11 12

- ``copy_tuple_elements``

.. literalinclude:: ../../../tests/test.tuple.cpp
    :language: cpp
    :start-after: copy_tuple_elements_start
    :end-before: copy_tuple_elements_end
    :dedent: 4
    :append:
        utils::copy_tuple_elements(from, to);
        for (const auto & e : vec2) {
            std::cout << e << " ";
        }

Output:

.. code-block:: none

    1 2 3 4 5

- ``constexpr_for_tuples``

.. literalinclude:: ../../../tests/test.tuple.cpp
    :language: cpp
    :start-after: constexpr_for_tuples_start
    :end-before: constexpr_for_tuples_end
    :dedent: 4
    :append:
        for (const auto & e : results) {
            std::cout << e << " ";
        }

Output:

.. code-block:: none

   4, 6, 195

- ``PointerTuple``

Please see the test file ``test.tuple.cpp`` for an example of how to use
the ``PointerTuple`` class.
