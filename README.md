# FlowshopSLS

## Description
This project is a heuristic optimization implementation for the Flowshop scheduling problem using an Iterative Improvement algorithms.
> [!Note]
> This is a university project for the course of Heuristic Optimization. The instructions for the project can be found in the file `implementation_1_2025.pdf`, in the `doc`directory.

---

## Repository structure

- `src`: Contains the source code of the project.
- `include`: Contains the header files of the project and the documentation for the classes is there.
- `doc`: Contains the instructions for the project and the report.
- `results`: Contains the results of the tests.
- `instances`: Contains the instances and the best known solutions for the instances.
- `bin`: Contains the executable files of the project.
- `obj`: Contains the object files of the project. (created by `make`)

The `src` and `include` directories are organized in subdirectories. You can usually find the source code related to a header file in the same subdirectory but in the `src` directory.
For example, the header file `include/core/instance.hpp` is related to the source file `src/core/instance.cpp`.
The subdirectories are:
- `config`: Contains the class responsible for the configuration of the solvers.
- `core`: Contains the core classes of the project.
- `initialization`: Contains the class responsible for the initialization of the solution.
- `neighbourhoods`: Contains the iterator classes for the neighbourhoods.
- `utils`: Contains the utility classes of the project.
---
# How to run

## Running the project
> [!Important]
> The two building methods are equivalent, use whatever you prefer.
> Please note that the rng is different depending on the compiler used. For example, the same seed may produce different results when using `cmake` or `make` (although a seed is not used in the testing phase).

### Using Make
If you have `make` installed. You can run the following command in the root of the project:

```shell
make
```

#### For the iterative improvement algorithm
```shell
./bin/pfsp --ii --instance_name --first|--best --transpose|--exchange|--insert --srz|--random-init
```

#### For the Variable Neighborhood Descent algorithm
```shell
./bin/pfsp --vnd --instance_name --tei|--tie
```
Where --tei represents a neighborhood order of transpose -> exchange -> insert and --tie represents a neighborhood order of transpose -> insert -> exchange.

#### For Tabu Search
```shell
./bin/pfsp --tabu --instance_name <tenure> <alpha> <max-generations> <max-stuck>
```

#### For the Memetic Algorithm
```shell
./bin/pfsp --memetic --instance_name <population-size> <mutation-rate> --none|--ii|--vnd|--tabu
```
Where `--none` means that the memetic algorithm will not use any local search, 
`--ii` means that the memetic algorithm will use the iterative improvement algorithm, 
`--vnd` means that the memetic algorithm will use the variable neighborhood descent algorithm and 
`--tabu` means that the memetic algorithm will use the tabu search algorithm.

---

### Using CMake
If you have `cmake` (at least version 3.26) installed, you can run the following commands in the root of the project:

```shell
cmake -B build
cmake --build build
```
Running the algorithms is the same as with `make`, but you will need to run the executable from the `build` directory:
```shell
./build/Debug/pfsp ...
```

---

# Testing the project
To run the algorithms multiple times and gather statistics, you can use the `runII`, `runVND`, `runTS` or `runMemetic` scripts. These scripts can be found in the `src` directory.
They will both run each version of the algorithm 10 times and gather statistics about the results. 
The results will be saved in a file called `resultsII.csv`, `resultsVND.csv`, `resultsTabu.csv` or `resultsMemetic.csv` respectively in the `results` directory.

> [!Caution]
> The proposed scripts expect the `pfsp` executable to be in the `bin` directory.
