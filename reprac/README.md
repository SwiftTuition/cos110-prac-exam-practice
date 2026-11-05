# COS 110 Re-Practical Exam: Menu and Binary practice questions

Practice questions based on the published scenario for the COS 110 Re-Practical Exam (6 November 2026):
Section A is the restaurant `Menu`, `Item` and exception classes; Section B is `Binary`, `Node<T>` and `BinaryStrings`.
They are not the real exam questions. The published UML is partial, so on the day, read the given headers first.
The headers show which functions are `virtual` and `const`.

The folder layout, the makefile, `-Wall -Werror` and valgrind follow the earlier practicals. The re-practical paper
does not describe them, so check the instructions on the day.

## Work in the browser or on your own computer

The steps in the [main README](../README.md) apply here too: open a codespace for this repository (it has `g++`,
`make` and `valgrind`), or clone it and use WSL Ubuntu or the lab computers. Then go to a question's folder in
`reprac/` and build it. For example:

```bash
cd reprac/questions/A_1/A1-01_exception_classes/A_1
make A_1
```

## How each question works

- `QUESTION.md` says what to write. `HINTS.md` (where there is one) gives hints.
- Write your code only in the file the question names, for example `A_1.cpp`.
- `make` compiles with `g++ -std=c++98 -Wall -Werror` and runs the program under `valgrind`. Compare the output with
  the `ExpectedOutput` block at the bottom of `main.cpp`. Check that valgrind says `All heap blocks were freed` and
  `ERROR SUMMARY: 0 errors`.
- You may change `main.cpp` to test more cases. Do not change the other given files.
- Try the question before you look in `solutions/`. Each solution folder has the model answer and an explanation.
  Other correct answers exist.

The PDFs in `pdf/` hold every question, and every model answer with its explanation.

## Questions

| Section | Topic | Question |
|---|---|---|
| A_1 | Exceptions | [`A1-01_exception_classes`](questions/A_1/A1-01_exception_classes/QUESTION.md) |
| A_1 | Exceptions | [`A1-02_menu_find_first`](questions/A_1/A1-02_menu_find_first/QUESTION.md) |
| A_1 | Exceptions | [`A1-03_menu_find_last`](questions/A_1/A1-03_menu_find_last/QUESTION.md) |
| A_1 | Exceptions | [`A1-04_menu_average_price`](questions/A_1/A1-04_menu_average_price/QUESTION.md) |
| A_1 | Exceptions | [`A1-05_menu_number_above`](questions/A_1/A1-05_menu_number_above/QUESTION.md) |
| A_1 | Exceptions | [`A1-06_menu_number_below`](questions/A_1/A1-06_menu_number_below/QUESTION.md) |
| A_1 | Exceptions | [`A1-07_menu_number_equal`](questions/A_1/A1-07_menu_number_equal/QUESTION.md) |
| A_1 | Exceptions | [`A1-08_menu_print_summary_catch_order`](questions/A_1/A1-08_menu_print_summary_catch_order/QUESTION.md) |
| A_2 | Operator overloading | [`A2-01_item_stream_insertion`](questions/A_2/A2-01_item_stream_insertion/QUESTION.md) |
| A_2 | Operator overloading | [`A2-02_menu_stream_insertion`](questions/A_2/A2-02_menu_stream_insertion/QUESTION.md) |
| A_2 | Operator overloading | [`A2-03_exception_stream_insertion`](questions/A_2/A2-03_exception_stream_insertion/QUESTION.md) |
| A_2 | Operator overloading | [`A2-04_menu_operator_plus`](questions/A_2/A2-04_menu_operator_plus/QUESTION.md) |
| A_2 | Operator overloading | [`A2-05_menu_subscript_reference`](questions/A_2/A2-05_menu_subscript_reference/QUESTION.md) |
| A_2 | Operator overloading | [`A2-06_item_equal_less`](questions/A_2/A2-06_item_equal_less/QUESTION.md) |
| A_2 | Operator overloading | [`A2-07_menu_plus_equals_grows`](questions/A_2/A2-07_menu_plus_equals_grows/QUESTION.md) |
| A_2 | Operator overloading | [`A2-08_menu_minus_removes`](questions/A_2/A2-08_menu_minus_removes/QUESTION.md) |
| A_3 | Assignment operator | [`A3-01_item_assignment`](questions/A_3/A3-01_item_assignment/QUESTION.md) |
| A_3 | Assignment operator | [`A3-02_menu_assignment`](questions/A_3/A3-02_menu_assignment/QUESTION.md) |
| A_3 | Assignment operator | [`A3-03_menu_copy_constructor`](questions/A_3/A3-03_menu_copy_constructor/QUESTION.md) |
| A_3 | Assignment operator | [`A3-04_menu_assignment_keep_size`](questions/A_3/A3-04_menu_assignment_keep_size/QUESTION.md) |
| A_3 | Assignment operator | [`A3-05_binary_assignment`](questions/A_3/A3-05_binary_assignment/QUESTION.md) |
| B_1 | Recursion | [`B1-01_toDecimal`](questions/B_1/B1-01_toDecimal/QUESTION.md) |
| B_1 | Recursion | [`B1-02_countOnes`](questions/B_1/B1-02_countOnes/QUESTION.md) |
| B_1 | Recursion | [`B1-03_isPalindrome`](questions/B_1/B1-03_isPalindrome/QUESTION.md) |
| B_1 | Recursion | [`B1-04_countNegative`](questions/B_1/B1-04_countNegative/QUESTION.md) |
| B_1 | Recursion | [`B1-05_calculatePos_recursive`](questions/B_1/B1-05_calculatePos_recursive/QUESTION.md) |
| B_1 | Recursion | [`B1-06_printReverse`](questions/B_1/B1-06_printReverse/QUESTION.md) |
| B_1 | Recursion | [`B1-07_setBits`](questions/B_1/B1-07_setBits/QUESTION.md) |
| B_2 | Linked lists | [`B2-01_append`](questions/B_2/B2-01_append/QUESTION.md) |
| B_2 | Linked lists | [`B2-02_insertAt`](questions/B_2/B2-02_insertAt/QUESTION.md) |
| B_2 | Linked lists | [`B2-03_removeAt`](questions/B_2/B2-03_removeAt/QUESTION.md) |
| B_2 | Linked lists | [`B2-04_remove_equal`](questions/B_2/B2-04_remove_equal/QUESTION.md) |
| B_2 | Linked lists | [`B2-05_reverse`](questions/B_2/B2-05_reverse/QUESTION.md) |
| B_2 | Linked lists | [`B2-06_sort_by_value`](questions/B_2/B2-06_sort_by_value/QUESTION.md) |
| B_2 | Linked lists | [`B2-07_calculatePos`](questions/B_2/B2-07_calculatePos/QUESTION.md) |
| B_2 | Linked lists | [`B2-08_copy_constructor`](questions/B_2/B2-08_copy_constructor/QUESTION.md) |
| B_3 | Template specialisation | [`B3-01_printValue_binary`](questions/B_3/B3-01_printValue_binary/QUESTION.md) |
| B_3 | Template specialisation | [`B3-02_largest_binary`](questions/B_3/B3-02_largest_binary/QUESTION.md) |
| B_3 | Template specialisation | [`B3-03_isEqual_binary`](questions/B_3/B3-03_isEqual_binary/QUESTION.md) |
| B_3 | Template specialisation | [`B3-04_addition_binary_throws`](questions/B_3/B3-04_addition_binary_throws/QUESTION.md) |
| B_3 | Template specialisation | [`B3-05_Node_toInt_binary`](questions/B_3/B3-05_Node_toInt_binary/QUESTION.md) |
| B_3 | Template specialisation | [`B3-06_countTrue_binary_inline`](questions/B_3/B3-06_countTrue_binary_inline/QUESTION.md) |

Prepared by Swift Tuition. Compiled and checked with g++ 13 (C++98) and valgrind.
