.. _page_numeric:

Numeric
=======

The **numeric** header file contains template functions that perform numeric operations on ranges of elements.

.. doxygenfile:: numeric.hpp
    :project: libutils

Usage
-----

The following examples demonstrates how to use the **numeric** header file:

- ``product``

.. literalinclude:: ../../../tests/test.numeric.cpp
    :language: cpp
    :start-after: product_start
    :end-before: product_end
    :dedent: 2
    :append:
        std::cout << "result: " << result << std::endl;

Output:

.. code-block:: none

    result: 24

- ``mean``

.. literalinclude:: ../../../tests/test.numeric.cpp
    :language: cpp
    :start-after: mean_start
    :end-before: mean_end
    :dedent: 2
    :append:
        std::cout << "result: " << result << std::endl;

Output:

.. code-block:: none

    result: 3

- ``mean [with type]``

.. literalinclude:: ../../../tests/test.numeric.cpp
    :language: cpp
    :start-after: mean_type_start
    :end-before: mean_type_end
    :dedent: 2
    :append:
        std::cout << std::boolalpha
                  << "result == int32_max: " << (result == int32_max) << std::endl;

Output:

.. code-block:: none

    result == int32_max: true
