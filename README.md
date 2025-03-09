# FlowshopSLS

## Description
This project is a heuristic optimization implementation for the Flowshop scheduling problem using an Iterative Improvement algorithms.
> [!Note]
> This is a university project for the course of Heuristic Optimization. The instructions for the project can be found in the file `implementation_1_2025.pdf`, in the `doc`directory.

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
