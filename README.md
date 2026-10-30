# COS 110 Practical Exam: HRMS practice questions

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/SwiftTuition/cos110-prac-exam-practice)

Practice questions based on the **published** HRMS scenario for the COS 110 Practical Exam (31 October 2026).
They are not the real exam questions. The real exam's complete UML may differ, so on the day, read the given headers first.

Each question asks you to write **one function** in **one file**, like the mock prac. The other files are given.

## Option 1: work in the browser (nothing to install)

1. Sign in to GitHub.
2. Open this link: **[Create a codespace for this repository](https://codespaces.new/SwiftTuition/cos110-prac-exam-practice)**, then click **Create codespace**.
3. Wait a minute or two. A VS Code editor opens in the browser, with a terminal at the bottom. It already has `g++`, `make` and `valgrind`.
4. In the terminal, go to a question's folder and build it. For example:

```bash
cd questions/A_1/A1-01_setidnum_length_gender/A_1
make A_1
```

(Use the real folder name from the table below. The `make` target is the section name, as in the mock prac.)

Your GitHub account includes free Codespaces hours each month. When you finish, stop the codespace at [github.com/codespaces](https://github.com/codespaces) (the **...** menu next to it, then **Stop codespace**). To come back later, open the same page and click your codespace.

## Option 2: work on your own computer

Clone or download this repository (green **Code** button, then **Download ZIP**). You need `g++`, `make` and `valgrind`, for example in WSL Ubuntu or on the lab computers.

## How each question works

- `QUESTION.md` says what to write. `HINTS.md` (where there is one) gives hints, from gentle to specific.
- Write your code only in the file the question names, for example `A_1.cpp`.
- `make` compiles with `g++ -std=c++98 -Wall -Werror` and runs your program under `valgrind`. Compare the output with the `ExpectedOutput` block at the bottom of `main.cpp`, and check that valgrind says `All heap blocks were freed` and `ERROR SUMMARY: 0 errors`.
- You may change `main.cpp` to test more cases. Do not change the other given files.
- Try the question before you look in `solutions/`. Other correct answers exist.

The PDFs in `pdf/` hold every question and every model solution.

## Questions

| Section | Topic | Question |
|---|---|---|
| A_1 | Exceptions | [`A1-01_setidnum_length_gender`](questions/A_1/A1-01_setidnum_length_gender/QUESTION.md) |
| A_1 | Exceptions | [`A1-02_setidnum_full_validation`](questions/A_1/A1-02_setidnum_full_validation/QUESTION.md) |
| A_1 | Exceptions | [`A1-03_setidnum_age`](questions/A_1/A1-03_setidnum_age/QUESTION.md) |
| A_1 | Exceptions | [`A1-04_extract_int_from_string`](questions/A_1/A1-04_extract_int_from_string/QUESTION.md) |
| A_1 | Exceptions | [`A1-05_team_subscript_throws`](questions/A_1/A1-05_team_subscript_throws/QUESTION.md) |
| A_1 | Exceptions | [`A1-06_department_subscript_throws`](questions/A_1/A1-06_department_subscript_throws/QUESTION.md) |
| A_1 | Exceptions | [`A1-07_team_addmember_throws`](questions/A_1/A1-07_team_addmember_throws/QUESTION.md) |
| A_1 | Exceptions | [`A1-08_team_assignids_catches`](questions/A_1/A1-08_team_assignids_catches/QUESTION.md) |
| A_1 | Exceptions | [`A1-09_exception_hierarchy_catch_order`](questions/A_1/A1-09_exception_hierarchy_catch_order/QUESTION.md) |
| A_1 | Exceptions | [`A1-10_team_hire_cleanup_on_throw`](questions/A_1/A1-10_team_hire_cleanup_on_throw/QUESTION.md) |
| A_2 | Operator overloading | [`A2-01_employee_stream_insertion`](questions/A_2/A2-01_employee_stream_insertion/QUESTION.md) |
| A_2 | Operator overloading | [`A2-02_team_stream_insertion`](questions/A_2/A2-02_team_stream_insertion/QUESTION.md) |
| A_2 | Operator overloading | [`A2-03_department_stream_insertion`](questions/A_2/A2-03_department_stream_insertion/QUESTION.md) |
| A_2 | Operator overloading | [`A2-04_list_template_stream_insertion`](questions/A_2/A2-04_list_template_stream_insertion/QUESTION.md) |
| A_2 | Operator overloading | [`A2-05_team_subscript_const`](questions/A_2/A2-05_team_subscript_const/QUESTION.md) |
| A_2 | Operator overloading | [`A2-06_department_subscript_reference`](questions/A_2/A2-06_department_subscript_reference/QUESTION.md) |
| A_2 | Operator overloading | [`A2-07_employee_equality`](questions/A_2/A2-07_employee_equality/QUESTION.md) |
| A_2 | Operator overloading | [`A2-08_department_compare_cost`](questions/A_2/A2-08_department_compare_cost/QUESTION.md) |
| A_2 | Operator overloading | [`A2-09_team_plus_equals_grow`](questions/A_2/A2-09_team_plus_equals_grow/QUESTION.md) |
| A_2 | Operator overloading | [`A2-10_team_plus_merge`](questions/A_2/A2-10_team_plus_merge/QUESTION.md) |
| A_2 | Operator overloading | [`A2-11_employee_increment_birthday`](questions/A_2/A2-11_employee_increment_birthday/QUESTION.md) |
| A_2 | Operator overloading | [`A2-12_team_call_operator_find`](questions/A_2/A2-12_team_call_operator_find/QUESTION.md) |
| A_3 | Assignment operator | [`A3-01_employee_assignment`](questions/A_3/A3-01_employee_assignment/QUESTION.md) |
| A_3 | Assignment operator | [`A3-02_team_assignment`](questions/A_3/A3-02_team_assignment/QUESTION.md) |
| A_3 | Assignment operator | [`A3-03_team_assignment_compact`](questions/A_3/A3-03_team_assignment_compact/QUESTION.md) |
| A_3 | Assignment operator | [`A3-04_department_assignment`](questions/A_3/A3-04_department_assignment/QUESTION.md) |
| A_3 | Assignment operator | [`A3-05_sales_assignment`](questions/A_3/A3-05_sales_assignment/QUESTION.md) |
| A_3 | Assignment operator | [`A3-06_list_assignment`](questions/A_3/A3-06_list_assignment/QUESTION.md) |
| A_3 | Assignment operator | [`A3-07_team_copy_constructor`](questions/A_3/A3-07_team_copy_constructor/QUESTION.md) |
| B_1 | Recursion | [`B1-01_extract_int_recursive`](questions/B_1/B1-01_extract_int_recursive/QUESTION.md) |
| B_1 | Recursion | [`B1-02_is_all_digits`](questions/B_1/B1-02_is_all_digits/QUESTION.md) |
| B_1 | Recursion | [`B1-03_count_members`](questions/B_1/B1-03_count_members/QUESTION.md) |
| B_1 | Recursion | [`B1-04_total_employees`](questions/B_1/B1-04_total_employees/QUESTION.md) |
| B_1 | Recursion | [`B1-05_count_nodes`](questions/B_1/B1-05_count_nodes/QUESTION.md) |
| B_1 | Recursion | [`B1-06_print_reverse`](questions/B_1/B1-06_print_reverse/QUESTION.md) |
| B_1 | Recursion | [`B1-07_list_contains`](questions/B_1/B1-07_list_contains/QUESTION.md) |
| B_1 | Recursion | [`B1-08_company_total_cost`](questions/B_1/B1-08_company_total_cost/QUESTION.md) |
| B_1 | Recursion | [`B1-09_id_checksum`](questions/B_1/B1-09_id_checksum/QUESTION.md) |
| B_1 | Recursion | [`B1-10_oldest_member`](questions/B_1/B1-10_oldest_member/QUESTION.md) |
| B_2 | Linked lists | [`B2-01_append`](questions/B_2/B2-01_append/QUESTION.md) |
| B_2 | Linked lists | [`B2-02_insertAt`](questions/B_2/B2-02_insertAt/QUESTION.md) |
| B_2 | Linked lists | [`B2-03_remove_value`](questions/B_2/B2-03_remove_value/QUESTION.md) |
| B_2 | Linked lists | [`B2-04_removeAt`](questions/B_2/B2-04_removeAt/QUESTION.md) |
| B_2 | Linked lists | [`B2-05_reverse`](questions/B_2/B2-05_reverse/QUESTION.md) |
| B_2 | Linked lists | [`B2-06_sort`](questions/B_2/B2-06_sort/QUESTION.md) |
| B_2 | Linked lists | [`B2-07_indexOf`](questions/B_2/B2-07_indexOf/QUESTION.md) |
| B_2 | Linked lists | [`B2-08_operator_index`](questions/B_2/B2-08_operator_index/QUESTION.md) |
| B_2 | Linked lists | [`B2-09_clear`](questions/B_2/B2-09_clear/QUESTION.md) |
| B_2 | Linked lists | [`B2-10_company_removeDepartment`](questions/B_2/B2-10_company_removeDepartment/QUESTION.md) |
| B_2 | Linked lists | [`B2-11_copy_constructor`](questions/B_2/B2-11_copy_constructor/QUESTION.md) |
| B_3 | Template specialization | [`B3-01_printItem_department`](questions/B_3/B3-01_printItem_department/QUESTION.md) |
| B_3 | Template specialization | [`B3-02_largest_employee`](questions/B_3/B3-02_largest_employee/QUESTION.md) |
| B_3 | Template specialization | [`B3-03_isEqual_department`](questions/B_3/B3-03_isEqual_department/QUESTION.md) |
| B_3 | Template specialization | [`B3-04_List_printAll_department`](questions/B_3/B3-04_List_printAll_department/QUESTION.md) |
| B_3 | Template specialization | [`B3-05_List_clear_department`](questions/B_3/B3-05_List_clear_department/QUESTION.md) |
| B_3 | Template specialization | [`B3-06_totalCost_department`](questions/B_3/B3-06_totalCost_department/QUESTION.md) |
| B_3 | Template specialization | [`B3-07_addition_employee_throws`](questions/B_3/B3-07_addition_employee_throws/QUESTION.md) |

Prepared by Swift Tuition. Compiled and checked with g++ 13 (C++98) and valgrind.
