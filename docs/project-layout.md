# Project Layout

## Directory Structure

```
src/
  main.c              # CLI dispatcher — parses arguments and routes to puzzle
  common/
    containers.h      # Dynamic arrays, stacks, queues
    containers.c
    pathfinding.h     # Graph algorithms: BFS, DFS, A*, etc.
    pathfinding.c
    math_utils.h      # Math utilities: GCD, modular arithmetic, etc.
    math_utils.c
  2024/
    day01.c           # Puzzle solution for 2024 day 1
    day01.h           # Exports: day_2024_01_part1(), day_2024_01_part2()
    day02.c
    day02.h
  2025/
    day01.c
    day01.h

data/
  2024/
    day01.txt         # Input file (from Advent of Code)
    day02.txt
  2025/
    day01.txt

tests/
  2024/
    day01_test.c      # Unit tests for 2024 day 1
  2025/
    day01_test.c

docs/                 # Documentation
  project-layout.md   # This file
  building.md         # Build system
  contributing.md     # Adding puzzles and utilities
  c23-reference.md    # C23 language and stdlib reference

Makefile              # Build configuration
.instructions.md      # Copilot workflow rules
.gitignore            # Exclude build artifacts
README.md             # Project overview and quick start
```

## Source Organization

### Main Dispatcher (`src/main.c`)
Parses command-line arguments and routes to puzzle functions.

**You write this file.** It should:
- Parse `year`, `day`, and optional `part` arguments
- Load the input file from `data/YYYY/dayDD.txt`
- Call the appropriate function from the puzzle solution
- Handle errors gracefully

Example usage:
```c
aoc 2024 1          // Run 2024 day 1, both parts
aoc 2024 1 1        // Run 2024 day 1, part 1 only
aoc 2024 1 2        // Run 2024 day 1, part 2 only
```

### Common Utilities (`src/common/`)
Shared code organized by category:

- **containers.h/c** — Data structures (dynamic arrays, linked lists, stacks, queues, hash tables)
- **pathfinding.h/c** — Graph algorithms (BFS, DFS, A*, Dijkstra)
- **math_utils.h/c** — Math helpers (GCD, LCM, modular arithmetic, prime factorization)

Each category is a separate header/source pair. This keeps utilities modular and easy to maintain.

### Puzzle Solutions (`src/YYYY/dayDD.c/h`)
One file per puzzle containing:
1. **Parsing logic** — Read and structure input data
2. **Part 1 implementation** — Solve the first part
3. **Part 2 implementation** — Solve the second part

Each puzzle exports two functions:
```c
// In src/2024/day01.h
void day_2024_01_part1(FILE *input_file);
void day_2024_01_part2(FILE *input_file);
```

Parsing and solving are in the same file because they're tightly coupled in AoC puzzles.

### Input Data (`data/YYYY/`)
Raw input files from Advent of Code, organized by year and day.

File names follow the pattern: `dayDD.txt` (e.g., `day01.txt`, `day25.txt`).

### Tests (`tests/YYYY/`)
Unit tests for each puzzle, organized by year.

Test files can test individual functions or integration.

## Building

See [Building](building.md) for compilation details and targets.

## Adding a New Puzzle

See [Contributing](contributing.md) for step-by-step instructions.
