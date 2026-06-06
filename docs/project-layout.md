# Project Layout

## Directory Structure

```
src/
  main.c              # CLI dispatcher — parses arguments and routes to puzzle
  common/
    aoc_io.h / aoc_io.c        # Read entire input streams into strings
    aoc_value.h / aoc_value.c  # Tagged-union answer value type (AocValue)
    bitset.h                   # Header-only packed bitset helpers
    hash_set.h / hash_set.c    # Open-addressed uint64_t hash set
  2015/
    day01.c           # Puzzle solution for 2015 day 1
    day01.h           # Exports: y2015d01p1(), y2015d01p2()
    day03.c           # Puzzle solution for 2015 day 3
    day03.h           # Exports: y2015d03p1(), y2015d03p2()

data/
  2015/
    day01.txt
    day02.txt
    day03.txt

tests/
  2015/
    day01_test.c      # Unit tests for 2015 day 1
    day03_test.c      # Unit tests for 2015 day 3

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

Supported invocations:
```bash
aoc <year> <day> <part>   # run a specific part and print the answer
aoc <year> <day>          # validate year/day arguments
aoc <year>                # validate year argument
```

The dispatcher:
- Opens `data/YYYY/dayDD.txt` for the requested puzzle
- Reads the entire file into a null-terminated string using `slurp_file()`
- Calls `yYYYYdDDpN(raw)` with the input string and prints the returned `AocValue`
- Frees the input buffer and calls `aoc_value_free()` and `free()` to clean up

### Common Utilities (`src/common/`)
Shared code organized by category. Currently contains:

- **aoc_io.h/c** — Input loading helper (`slurp_file`)
- **aoc_value.h/c** — Tagged-union answer type (`AocValue`) and helpers
- **bitset.h** — Header-only packed bitset helpers
- **hash_set.h/c** — Open-addressed set for `uint64_t` keys

As puzzles grow, additional modules can be added as separate headers/sources,
or as header-only helpers when the API is small and inlinable.

### Puzzle Solutions (`src/YYYY/dayDD.c/h`)
One file per puzzle containing:
1. **Parsing logic** — Read and structure input data
2. **Part 1 implementation** — Solve the first part
3. **Part 2 implementation** — Solve the second part

Each puzzle exports two functions:
```c
// In src/2015/day01.h
AocValue *y2015d01p1(const char *raw);
AocValue *y2015d01p2(const char *raw);
```

The naming convention is `yYYYYdDDpN` (year, day, part). Functions return a
heap-allocated `AocValue`; the caller must call `aoc_value_free(val)` and
then `free(val)`.

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
