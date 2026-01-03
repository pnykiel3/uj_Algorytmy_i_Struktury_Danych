# 📚 Algorithms & Data Structures Portfolio

[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)
[![University](https://img.shields.io/badge/University-Jagiellonian%20University-red.svg)](https://uj.edu.pl)

A comprehensive collection of classic algorithms and data structures implemented in C++ during Algorithms and Data Structures coursework at Jagiellonian University.

---

## 🎯 Overview

This repository demonstrates practical implementations of fundamental computer science concepts, including efficient data structures, graph algorithms, and computational problem-solving techniques. All implementations include comprehensive testing and performance analysis.

---

## 📋 Table of Contents

- [Data Structures](#-data-structures)
- [Graph Algorithms](#-graph-algorithms)
- [Algorithmic Techniques](#-algorithmic-techniques)
- [Project Structure](#-project-structure)
- [Technologies](#-technologies)

---

## 🗂️ Data Structures

### Linear Data Structures
- **Stack** - Array-based stack implementation with template support
  - Custom implementation used in RPN calculator
  - *Location: `Zestaw07/mystack.h`*

- **Queue** - Circular queue implementation with dynamic sizing
  - *Location: `Zestaw08/myqueue.h`*

- **Priority Queue** - Both array-based and binary heap implementations
  - Array-based version: `Zestaw09/mypriorityqueue.h`
  - Binary heap version: `2_Zestaw3/priorityQueueBinary.h`
  - Performance comparison included

### Hash-Based Structures
- **Hash Table with Open Addressing** - Efficient key-value storage
  - *Location: `2_Zestaw2/openhash.h`*
  
- **Hashed Set** - Set implementation using hash tables
  - *Location: `2_Zestaw2/setHashed.h`*

### Set Implementations
- **Simple Array-Based Set** - Basic set with linear search
  - *Location: `2_Zestaw1/setsimple.h`*
  
- **Linked List Set** - Set implementation using linked lists
  - *Location: `2_Zestaw1/setlinked.h`*

- **Dictionary** - Key-value pair storage
  - *Location: `2_Zestaw1/dictionarysimple.h`*

### Tree Structures
- **Binary Search Tree (BST)** - Classic BST with find_min/find_max operations
  - *Location: `Zestaw09/binarysearchtree.h`, `Zestaw11/binarysearchtree.h`*

- **Random Binary Tree** - Randomized tree structure for balanced insertion
  - *Location: `Zestaw10/notrandombinarytree.h`*

### Graph Representations
- **Adjacency Matrix Graph** - ADT graph with template-based capacity
  - *Location: `2_Zestaw4/ADTgraph.h`*

- **Neighbor List Graph** - Efficient neighbor representation
  - *Location: `2_Zestaw5/C/NEIGHBORgraph.h`*

---

## 🌐 Graph Algorithmss

### Shortest Path Algorithms
- **Floyd-Warshall Algorithm** - All-pairs shortest path
  - Computes shortest distances between all vertex pairs
  - Includes path reconstruction using predecessor matrix
  - *Location: `2_Zestaw8/floydWarshall.h`*

### Graph Traversal & Analysis
- **Graph ADT Operations**
  - Vertex and edge manipulation
  - Adjacency checking
  - Neighbor retrieval
  - Weighted edge support
  - *Location: `2_Zestaw4/`, `2_Zestaw5/`*

---

## 🧮 Algorithmic Techniques

### Computational Applications
- **Reverse Polish Notation (RPN) Calculator**
  - Expression evaluation using custom stack implementation
  - Includes comprehensive test suite with assertions
  - *Location: `Zestaw07/rpn.cpp`*

### Performance Analysis
- **Empirical Algorithm Analysis**
  - Time complexity measurements for various data structures
  - Comparison of different implementations (e.g., array vs. linked list sets)
  - Performance data and plots included
  - *Locations: `2_Zestaw1/`, `2_Zestaw2/`, `2_Zestaw3/`*

---

## 📁 Project Structure

```
uj_Algorytmy_i_Struktury_Danych/
│
├── Zestaw03/          # Arraylist implementation
├── Zestaw04/          # Single linked list implementation
├── Zestaw05/          # Double linked list implementation
├── Zestaw06/          # Double ended queue implementation
├── Zestaw07/          # Stack implementation & RPN calculator
├── Zestaw08/          # Queue implementation
├── Zestaw09/          # Priority Queue & BST
├── Zestaw10/          # Random Binary Tree
├── Zestaw11/          # Advanced BST operations
│
├── 2_Zestaw1/         # Set implementations (array, linked list, dictionary)
├── 2_Zestaw2/         # Hash table implementations
├── 2_Zestaw3/         # Priority queue with binary heap
├── 2_Zestaw4/         # Graph ADT (adjacency matrix)
├── 2_Zestaw5/         # Graph implementations (neighbor list)
├── 2_Zestaw6/         # Graph analysis
├── 2_Zestaw7/         # Advanced graph algorithms
└── 2_Zestaw8/         # Floyd-Warshall algorithm
```

---

## 🛠️ Technologies

- **Language**: C++14/17
- **Build System**: Make, CMake
- **Development**: CLion IDE, VS Code
- **Testing**: Custom test suites with assertions

---

## 🚀 Getting Started

Most projects include a Makefile with standard targets:

```bash
# Compile the project
make

# Run tests
make run

# Clean build artifacts
make clean

# Create archive
make tar
```

For specific instructions, refer to the README.md file in each subdirectory.

---

## 📊 Performance Highlights

- Implemented and compared multiple data structure variants (e.g., different set implementations)
- Conducted empirical performance analysis with data visualization
- Optimized algorithms based on theoretical complexity analysis

---

## 📫 Contact

**Paweł Nykiel**
p.nykiel@icloud.com
If you're interested in discussing algorithms, data structures, or potential opportunities, feel free to reach out!

---

*This repository represents coursework completed at Jagiellonian University's Computer Science program, demonstrating practical application of theoretical computer science concepts.*
