# Advent of Code - C23 Learning Project

A self-contained C23 project for solving Advent of Code puzzles, designed as a learning exercise.

## Quick Start

```bash
make              # Build the dispatcher executable
make debug        # Build with debug symbols
make test         # Build and run tests (currently requires a single test main)
make clean        # Remove artifacts

./build/aoc 2015 1 1    # Run 2015 day 1, part 1
./build/aoc 2015 1 2    # Run 2015 day 1, part 2
./build/aoc 2015 3 1    # Run 2015 day 3, part 1
```

## Documentation

- [**Project Layout**](docs/project-layout.md) — Directory structure and file organization
- [**Building & Running**](docs/building.md) — Build system, compilation, execution
- [**Contributing**](docs/contributing.md) — How to add new puzzles and utilities
- [**C23 Reference**](docs/c23-reference.md) — Language features and stdlib highlights

## Project Overview

**Single executable dispatcher** — One `aoc` binary interprets command-line arguments to run specific puzzles.

**Modular utilities** — Shared helpers live in `src/common/` (currently `aoc_io`, `aoc_value`, `bitset`, and `hash_set`).

**Per-year, per-day solutions** — Each puzzle lives in `src/YYYY/dayDD.c` with its header.

**C23 standard only** — No external libraries; uses GCC's C23 support with standard C library.

## Requirements

- **GCC** with C23 support (`gcc -std=c23`)
- **Standard C library** (no external dependencies)
- **GNU Make** for building

## Repository Structure

```
aoc/
├── src/
│   ├── main.c                  # CLI dispatcher
│   ├── common/
│   │   ├── aoc_io.h/c          # Input slurp helper
│   │   ├── aoc_value.h/c       # Tagged-union answer value type
│   │   ├── bitset.h            # Header-only packed bitset helpers
│   │   └── hash_set.h/c        # Open-addressed uint64 hash set
│   └── 2015/
│       ├── day01.c/h           # 2015 day 1
│       └── day03.c/h           # 2015 day 3
├── data/
│   └── 2015/
│       ├── day01.txt           # Input file
│       ├── day02.txt           # Input file
│       └── day03.txt           # Input file
├── tests/
│   └── 2015/
│       ├── day01_test.c        # Unit tests
│       └── day03_test.c        # Unit tests
├── docs/                       # Documentation
├── Makefile                    # Build configuration
└── README.md                   # This file
```

For more details on project structure, see [Project Layout](docs/project-layout.md).
