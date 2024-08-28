.. _page_type_traits:

Type_traits
===========

The **type_traits** header file contains metaprogramming tools for compile-time type introspection. The header
provides a set of templates that can be used to query properties of types.

* **has_push_back**

.. doxygengroup:: has_push_back_struct
    :project: libutils
    :content-only:

* **has_insert**

.. doxygengroup:: has_insert_struct
    :project: libutils
    :content-only:

* **remove_cvref**

.. doxygengroup:: remove_cvref_alias
    :project: libutils
    :content-only:

Usage
-----

The following examples demonstrates how to use the **type_traits** header file:

- ``has_push_back``

.. code-block:: cpp

    std::cout << std::boolalpha
              << "utils::has_push_back_v<int>: "
              << utils::has_push_back_v<int> << '\n'
              << "utils::has_push_back_v<std::vector<int>>: "
              << utils::has_push_back_v<std::vector<int>> << std::endl;

Output:

.. code-block:: none

    utils::has_push_back_v<int>: false
    utils::has_push_back_v<std::vector<int>>: true

- ``has_insert``

.. code-block:: cpp

    std::cout << std::boolalpha
              << "utils::has_insert_v<int>: "
              << utils::has_insert_v<int> << '\n'
              << "utils::has_insert_v<std::vector<int>>: "
              << utils::has_insert_v<std::vector<int>> << std::endl;

Output:

.. code-block:: none

    utils::has_insert_v<int>: false
    utils::has_insert_v<std::vector<int>>: true

- ``remove_cvref``

.. code-block:: cpp

    std::cout << std::boolalpha
              << "std::is_same_v<utils::remove_cvref_t<const int&>, int>: "
              << std::is_same_v<utils::remove_cvref_t<const int&>, int> << '\n'
              << "std::is_same_v<utils::remove_cvref_t<volatile int&>, int>: "
              << std::is_same_v<utils::remove_cvref_t<volatile int&>, int> << std::endl;

Output:

.. code-block:: none

    std::is_same_v<utils::remove_cvref_t<const int&>, int>: true
    std::is_same_v<utils::remove_cvref_t<volatile int&>, int>: true
