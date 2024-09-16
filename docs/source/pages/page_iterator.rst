.. _page_iterator:

Iterator
========

The **iterator** header file contains template functions for working with iterators.

.. doxygenfile:: iterator.hpp
    :project: libutils

Usage
-----

The following examples demonstrates how to use the **iterator** header file:

- ``advance<std::size_t N = 1>``

.. literalinclude:: ../../../tests/test.iterator.cpp
    :language: cpp
    :start-after: advance_start
    :end-before: advance_end
    :dedent: 2
    :append:
        std::cout << "*it1: " << *it1 << '\n'
                  << "*it2: " << *it2 << std::endl;

Output:

.. code-block:: none

    *it1: 2
    *it2: 2

- ``distance_difference``

.. literalinclude:: ../../../tests/test.iterator.cpp
    :language: cpp
    :start-after: distance_difference_start
    :end-before: distance_difference_end
    :dedent: 2
    :append:
        std::cout << "result: " << result << std::endl;

Output:

.. code-block:: none

    result: -1

- ``get_longer_range``

.. literalinclude:: ../../../tests/test.iterator.cpp
    :language: cpp
    :start-after: get_longer_range_start
    :end-before: get_longer_range_end
    :dedent: 2
    :append:
        std::cout << "partial_sum: ";
        std::partial_sum(first, last, std::ostream_iterator<int>(std::cout, " "));

Output:

.. code-block:: none

    partial_sum: 1 3 6 10 15 21

- ``MulitIterator``

.. literalinclude:: ../../../tests/test.iterator.cpp
    :language: cpp
    :start-after: multi_iterator_sort_start
    :end-before: multi_iterator_sort_end
    :dedent: 2
    :append:
        for (auto it{begin}; it != end; ++it) {
            std::cout << *it << " ";
        }

Output:

.. code-block:: none

    [1, a] [1, d] [2, b] [2, c]
