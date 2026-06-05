# Building & Running

## Build System

This project uses **GNU Make** with a simple, self-discovering build system.

The Makefile automatically finds all `.c` files in `src/` and compiles them together into a single executable.

## Build Targets

```bash
make                # Default: build the aoc executable
make clean          # Remove all build artifacts
make rebuild        # Clean and build
make test           # Compile and run tests
make debug          # Build with debug symbols (-g) and no optimization (-O0)
```

## Build Configuration

**Compiler:** GCC  
**Standard:** C23  
**Flags:** `-std=c23 -Wall -Wextra -O2`  
**Debug Flags:** `-std=c23 -Wall -Wextra -g -O0`

## Output Locations

```
build/
  aoc               # Main executable
  tests_runner      # Test executable (if tests exist)
  2015/             # Object files mirroring src layout
  common/
```

## Running Puzzles

After building, run the dispatcher:

```bash
./build/aoc 2015 1 1    # Run 2015 day 1, part 1
./build/aoc 2015 1 2    # Run 2015 day 1, part 2
./build/aoc 2024 1 1    # Run 2024 day 1, part 1 (once implemented)
```

## Running Tests

```bash
make test           # Compile tests and run
```

Tests are autodiscovered from `tests/YYYY/` and compiled into a single test executable.

## Compilation Details

### Source Discovery

The Makefile uses `find` to recursively discover all `.c` files:
- **Source files:** `find src -type f -name '*.c'` — all `.c` files under `src/`
- **Test files:** `find tests -type f -name '*.c'` — all `.c` files under `tests/`

Adding a new `.c` file anywhere under `src/` or `tests/` is sufficient; no Makefile edits needed.

### Object Files

Object files are stored in `build/` to keep the source tree clean.

### Linking

All `.o` files are linked together with the C standard library into a single executable.

## Troubleshooting

**"No such file or directory"** when running puzzles:
- Ensure input data exists at `data/YYYY/dayDD.txt`
- Your `main.c` dispatcher must construct the correct path

**Compilation errors with includes:**
- Ensure headers use relative includes: `#include "common/containers.h"` or similar
- The Makefile doesn't add special `-I` flags; adjust as needed if includes fail

**Missing symbols at link time:**
- Ensure `.c` files are in `src/` or `src/YYYY/` — the Makefile discovers them automatically
- Check that function definitions match declarations in `.h` files

## Customizing the Build

Edit `Makefile` to:
- Change optimization flags (`-O2`, `-O0`, `-Os`)
- Add warning flags (e.g., `-Werror` to treat warnings as errors)
- Add include directories with `-I` if needed
- Link additional libraries (if you add external dependencies)

For most learning purposes, the defaults are fine.
