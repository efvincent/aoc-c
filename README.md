# Advent of Code - C23 Learning Project

A self-contained C23 project for solving Advent of Code puzzles, designed as a learning exercise.

## Quick Start

```bash
make              # Build the dispatcher executable
make test         # Run tests
make clean        # Remove artifacts

./build/aoc 2024 1      # Run 2024 day 1, both parts
./build/aoc 2024 1 1    # Run 2024 day 1, part 1 only
./build/aoc 2024 1 2    # Run 2024 day 1, part 2 only
```

## Documentation

- [**Project Layout**](docs/project-layout.md) — Directory structure and file organization
- [**Building & Running**](docs/building.md) — Build system, compilation, execution
- [**Contributing**](docs/contributing.md) — How to add new puzzles and utilities
- [**C23 Reference**](docs/c23-reference.md) — Language features and stdlib highlights

## Project Overview

**Single executable dispatcher** — One `aoc` binary interprets command-line arguments to run specific puzzles.

**Modular utilities** — Common functionality (containers, pathfinding, math) organized in `src/common/` by category.

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
│   ├── main.c                  # CLI dispatcher (write this)
│   ├── common/                 # Shared utilities
│   │   ├── containers.h/c      # Dynamic arrays, stacks, queues
│   │   ├── pathfinding.h/c     # Graph algorithms
│   │   └── math_utils.h/c      # Math helpers
│   └── YYYY/
│       └── dayDD.c/h           # Puzzle solution (parsing + parts)
├── data/
│   └── YYYY/
│       └── dayDD.txt           # Input files
├── tests/
│   └── YYYY/
│       └── dayDD_test.c        # Unit tests
├── docs/                       # Documentation
├── Makefile                    # Build configuration
└── README.md                   # This file
```

For more details on project structure, see [Project Layout](docs/project-layout.md).
