# Algorithm Benchmarks

A collection of algorithm implementations, experiments, stress tests, and benchmarks.

The goal of this repository is to explore how algorithms behave in practice, not just in theory. Most experiments compare custom implementations against highly optimized standard library implementations while measuring runtime under different conditions.

## Current Experiments

### Sorting Algorithms

* Quicksort (First Element Pivot) vs `std::sort`

  * Custom implementation of Quicksort
  * Stress-tested against `std::sort`
  * Benchmarked with different compiler optimization levels (`-O2`, `-O3`)
  * Future plans:

    * Randomized Pivot Quicksort
    * Median-of-Three Quicksort
    * Merge Sort
    * Heap Sort
    * Performance on sorted, reverse-sorted, and duplicate-heavy inputs

## Repository Structure

```text
.
├── quicksort_vs_std_sort/
│   ├── README.md
│   ├── quicksort_first_element.cpp
│   ├── test_generator.cpp
│
└── clock.cpp
```

## Notes

* All benchmarks are performed on the same generated input wherever possible.
* Results are intended for learning and exploration rather than rigorous scientific benchmarking.
* Every implementation is stress-tested against a trusted reference implementation before benchmarking.

## Utilities

### `clock.cpp`

Contains examples and references for timing code using the C++ `chrono` library.
