# FlowshopSLS

## Description
This project is a heuristic optimization implementation for the Flowshop scheduling problem using an Iterative Improvement algorithms.
> [!Note]
> This is a university project for the course of Heuristic Optimization. The instructions for the project can be found in the file `implementation_1_2025.pdf`, in the `doc`directory.

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

---

### Using CMake
If you have `cmake` (at least version 3.26) installed, you can run the following commands in the root of the project:

```shell
cmake -B build
cmake --build build
```
#### For the iterative improvement algorithm
```shell
./build/Debug/pfsp --ii --instance_name --first|--best --transpose|--exchange|--insert --srz|--random-init
```

#### For the Variable Neighborhood Descent algorithm
```shell
./build/Debug/pfsp --vnd --instance_name --tei|--tie
```
Where --tei represents a neighborhood order of transpose -> exchange -> insert and --tie represents a neighborhood order of transpose -> insert -> exchange.

---