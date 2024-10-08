.. _page_algorithm:

Algorithm
=========

The **algorithm** header file contains template functions that operate on ranges of elements. Range is defined as
``[first, last)`` where ``last`` refers to the element *past* the last element to inspect or modify.

.. doxygenfile:: algorithm.hpp
    :project: libutils

Usage
-----

The following examples demonstrates how to use the **algorithm** header file:

- ``argmax``

.. literalinclude:: ../../../tests/test.algorithm.cpp
    :language: cpp
    :start-after: argmax_start
    :end-before: argmax_end
    :dedent: 4
    :append:
        std::cout << "result: " << result << std::endl;

Output:

.. code-block:: none

    result: 4

- ``argmax_conditional``

.. literalinclude:: ../../../tests/test.algorithm.cpp
    :language: cpp
    :start-after: argmax_conditional_start
    :end-before: argmax_conditional_end
    :dedent: 4
    :append:
        std::cout << std::boolalpha
                  << "result.first: " << result.first
                  << ", result.second: " << result.second std::endl;

Output:

.. code-block:: none

    result.first: true, result.second: 3

- ``copy_range_n_times``

.. literalinclude:: ../../../tests/test.algorithm.cpp
    :language: cpp
    :start-after: copy_range_n_times_start
    :end-before: copy_range_n_times_end
    :dedent: 4
    :append:
        std::cout << desination: ";
        for (const auto& elem : result) {
            std::cout << elem << " ";
        }

Output:

.. code-block:: none

    destination: 1 2 3 1 2 3 1 2 3

- ``max_element_conditional``

.. literalinclude:: ../../../tests/test.algorithm.cpp
    :language: cpp
    :start-after: max_element_conditional_start
    :end-before: max_element_conditional_end
    :dedent: 4
    :append:
        std::cout << "result: " << result << std::endl;

Output:

.. code-block:: none

    result: 7

- ``mismatch_from_end``

.. literalinclude:: ../../../tests/test.algorithm.cpp
    :language: cpp
    :start-after: mismatch_from_end_start
    :end-before: mismatch_from_end_end
    :dedent: 4
    :append:
        std::cout << "*mis_first: " << *mis_first
                  << ", *mis_second: " << *mis_second << std::endl;

Output:

.. code-block:: none

    *mis_first: 3, *mis_second: 3

- ``reorder_elements_by_indices``

.. literalinclude:: ../../../tests/test.algorithm.cpp
    :language: cpp
    :start-after: reorder_elements_by_indices_start
    :end-before: reorder_elements_by_indices_end
    :dedent: 4
    :append:
        std::cout << "elements: ";
        for (const auto& e : elements) {
            std::cout << e << " ";
        }

Output:

.. code-block:: none

    elements: 40 30 20 10