# University Course Prerequisite Management Using Topological Sorting

## Course

**CSA03 – Data Structures – Slot D**

## Project Description

This project presents a graph-based solution for managing university course prerequisites using Topological Sorting. Each course is represented as a vertex in a directed graph, while a prerequisite relationship is represented as a directed edge.

The proposed system generates a valid course-taking order based on prerequisite dependencies. It also detects cycles in the prerequisite graph. If a cycle exists, a valid course sequence cannot be generated because the courses involved depend on one another.

## Problem Statement

Universities contain several courses with prerequisite relationships. Manually determining a valid order in which students should complete these courses can become difficult when the number of courses and dependencies increases.

The problem is formulated using a Directed Acyclic Graph (DAG), where:

* Vertex → University course
* Directed edge → Prerequisite dependency
* Topological ordering → Valid course-taking sequence

If the prerequisite graph contains a cycle, no valid topological ordering exists.

## Objectives

* Represent university courses using a directed graph.
* Represent prerequisite relationships using directed edges.
* Apply Topological Sorting to generate a valid course sequence.
* Detect cycles in the prerequisite graph.
* Demonstrate the practical application of graph data structures.

## Concepts Used

* Graphs
* Directed Graphs
* Adjacency Matrix / Adjacency List
* In-degree
* Queue
* Topological Sorting
* Cycle Detection
* Time Complexity Analysis

## Algorithm

1. Create a directed graph containing all courses.
2. Add an edge from each prerequisite course to its dependent course.
3. Calculate the in-degree of every course.
4. Insert all courses with in-degree 0 into a queue.
5. Remove a course from the queue and add it to the topological ordering.
6. Reduce the in-degree of its adjacent courses.
7. Add newly available zero in-degree courses to the queue.
8. Continue until the queue becomes empty.
9. If all courses are processed, the ordering is valid.
10. If some courses remain unprocessed, the graph contains a cycle.

## Complexity

For a graph containing `V` courses and `E` prerequisite relationships:

**Time Complexity:** O(V + E)

**Space Complexity:** O(V + E)

## Implementation Language

* C

## Environment / Tools

* C Compiler
* Visual Studio Code / Code::Blocks / GCC
* Git
* GitHub

## Test Cases

### Test Case 1 – Valid Prerequisite Graph

A prerequisite graph without cycles should produce a valid course-taking order.

**Expected Result:**
A valid topological ordering is generated.

### Test Case 2 – Graph Containing a Cycle

A prerequisite graph containing circular dependencies should not produce a valid ordering.

**Expected Result:**
The program identifies the cycle and reports that a valid course sequence cannot be generated.

### Test Case 3 – Course With Multiple Prerequisites

A course may depend on multiple prerequisite courses.

**Expected Result:**
The dependent course appears only after all its prerequisites have been processed.

## Results

The implementation successfully represents the prerequisite system as a directed graph and applies Topological Sorting to generate a valid course-taking sequence. The system also detects cyclic dependencies and prevents invalid course sequences.

## SDG Relevance

The project supports **SDG 4 – Quality Education** by providing a structured approach to course planning and prerequisite management. A systematic course sequence can help students understand academic dependencies and plan their learning progression more effectively.

## Limitations

* The current implementation uses a fixed set of courses.
* Course information is entered manually.
* It does not maintain a permanent database.
* It does not provide a graphical user interface.

## Future Improvements

* Add a graphical user interface.
* Store course information using a database.
* Allow dynamic addition and deletion of courses.
* Provide semester-wise course planning.
* Add prerequisite validation for individual students.
* Develop a web-based version.

## Authors

**D. Saketh – 192525018**

**Course:** CSA03 – Data Structures
**Department:** Computer Science and Engineering

