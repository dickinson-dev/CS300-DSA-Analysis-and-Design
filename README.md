# CS 300: Data Structures and Algorithms

This repository contains selected coursework and portfolio artifacts from SNHU's CS 300 course. The projects explore how data structures affect program organization, runtime, memory use, and maintainability.

## Portfolio Artifacts

- [Project One: Runtime and Memory Analysis](Project-One/Project-One-Dickinson.docx) — Pseudocode and analysis comparing vector, hash table, and binary search tree approaches to storing and working with course information.
- [Project Two: Course Planner](Project-Two/ProjectTwo.cpp) — A C++ course planner that loads course data into a binary search tree, prints courses in alphanumeric order, and searches for a course.
- [Project Two Input Data](Project-Two/CS-300-ABCU_Advising_Program_Input.csv) — Sample course data used by the program.

## Reflection

### What problem were you solving?

The projects focused on building a course planner that reads course information, stores courses and prerequisites, prints courses in alphanumeric order, and looks up individual courses. Project One examined how different data structures could support these tasks and how their runtime and memory requirements compare.

### How did you approach the problem, and why are data structures important?

I broke the problem into smaller operations: loading and validating the input file, storing course records, checking prerequisites, searching for courses, and displaying results. I compared vectors, hash tables, and binary search trees to see how the structure choice affects those operations. Data structures matter because they shape how information is organized and how efficiently a program can retrieve, update, and present it.

### How did you overcome roadblocks?

I worked through the program in stages and used pseudocode to clarify the logic before implementation. When handling input validation and prerequisites, I considered cases such as missing course data, duplicate course numbers, and prerequisites that don't appear in the file. Breaking the work into smaller functions and checking the assumptions at each stage helped me identify problems and improve the implementation.

### How has this work changed your approach to software design and development?

I now consider a program's data and operations before choosing how to store information. Comparing multiple data structures helped me see that a working solution is only part of the design; the choice should also fit the expected searches, ordering, and validation requirements.

### How has your approach to maintainable, readable, and adaptable programs evolved?

I put more emphasis on clear function responsibilities, meaningful names, input validation, and separating file parsing from searching and display. These choices make the code easier to follow and help future changes stay localized. I also consider edge cases early so the program can handle imperfect input more reliably.
