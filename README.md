# Data Structures and Algorithms in C

A comprehensive collection of fundamental data structures and algorithms implemented entirely from scratch in standard C.

This repository serves as a practical reference and a technical portfolio piece demonstrating proficiency in manual memory management, complex pointer manipulation, and algorithmic efficiency (Big O).

## Repository Structure

The project is modularized into 11 distinct categories, each containing the implementation source files and test drivers:

1. **[01-sorting](./01-sorting)**: Bubble, Insertion, Selection, and Quick Sort.
2. **[02-binary-search](./02-binary-search)**: Iterative and recursive array searching.
3. **[03-linked-list](./03-linked-list)**: Singly linked list with dummy head node.
4. **[04-stack](./04-stack)**: LIFO structure implemented via linked list.
5. **[05-queue](./05-queue)**: FIFO structure with efficient $O(1)$ operations.
6. **[06-doubly-linked-list](./06-doubly-linked-list)**: Two-way pointer navigation and management.
7. **[07-priority-queue](./07-priority-queue)**: Node-based priority queue implementation.
8. **[08-binary-search-tree](./08-binary-search-tree)**: Hierarchical data management, recursive/iterative traversals, and complex node deletion.
9. **[09-avl-tree](./09-avl-tree)**: Self-balancing BST with automatic Left/Right and Double rotations.
10. **[10-heap](./10-heap)**: Array-based Min/Max Binary Heap and Heap Sort.
11. **[11-graph](./11-graph)**: Directed graph utilizing Adjacency Lists, including Depth-First (DFT) and Breadth-First Traversal (BFT).

## Compilation and Execution

All programs are written in standard C and can be compiled using `gcc`. Each directory contains its own standalone `.c` file with a `main()` driver function for testing.

To compile and run a specific data structure (e.g., the AVL Tree):

```bash
# Navigate to the specific directory
cd 09-avl-tree

# Compile the source code
gcc avl-tree-with-operations.c -o avl_tree

# Execute the compiled binary
./avl_tree
```
