# FlowshopSLS

## Description
This project is a heuristic optimization implementation for the Flowshop scheduling problem using an Iterative Improvement algorithms.
> [!Note]
> This is a university project for the course of Heuristic Optimization. The instructions for the project can be found in the file `implementation_1_2025.pdf`, in the `doc`directory.

---
# How to run

> [!Important]
> Please note that the rng is different depending on the compiler used. For example, the same seed may produce different results when using `cmake` or `make` (although a seed is not used in the testing phase).

## If you have CMake installed
If you have `cmake` (at least version 3.26) installed, you can run the following commands in the root of the project:

```shell
cmake -B build
cmake --build build
./build/Debug/pfsp-ii <pivoting_rule> <neighborhood_structure> <initialization_method>
```

## If you don't have CMake installed
If you don't have `cmake` installed, you should have `make` installed. You can run the following commands in the root of the project:

```shell
make
./bin/pfsp-ii <pivoting_rule> <neighborhood_structure> <initialization_method>
```

---

## Implemented algorithms
The algorithms differ in the way they
- Generate the initial solution
  1. Random initial solution
  2. Simplified RZ heuristic
- Explore the neighborhood
  1. Transpose
  2. Exchange
  3. Insert
- Choose a candidate solution in the neighborhood
  1. Best improvement
  2. First improvement

---