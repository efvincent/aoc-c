# Contributing: Adding Puzzles and Utilities

## Adding a New Puzzle

### 1. Download Input Data

From Advent of Code, download the input for your puzzle and save it:

```
data/2024/day01.txt
```

### 2. Create Puzzle Files

Create header and source files:

```
src/2015/day01.h
src/2015/day01.c
```

### 3. Write the Header

Define the two exported functions:

```c
// src/2015/day01.h
#ifndef DAY_2015_01_H
#define DAY_2015_01_H

#include <stdio.h>
#include "../common/aoc_value.h"

AocValue *y2015d01p1(FILE *input_file);
AocValue *y2015d01p2(FILE *input_file);

#endif
```

Function names follow the pattern: `yYYYYdDDpN` (year, day zero-padded, part).

### 4. Write the Solution

Implement parsing and solving in the source file:

```c
// src/2015/day01.c
#define _GNU_SOURCE
#include "day01.h"
#include "../common/aoc_value.h"
#include <stdio.h>
#include <stdlib.h>

AocValue *y2015d01p1(FILE *input_file) {
    AocValue *val = malloc(sizeof(AocValue));
    // Parse input_file and compute answer
    val->tag = AOC_VALUE_I64;
    val->as.i64 = 0;  // replace with real answer
    return val;
}

AocValue *y2015d01p2(FILE *input_file) {
    // Similar structure
    AocValue *val = malloc(sizeof(AocValue));
    val->tag = AOC_VALUE_I64;
    val->as.i64 = 0;
    return val;
}
```

**Tips:**
- Read input using `fgets()`, `fscanf()`, or character-by-character with `fgetc()`
- Use only the C standard library (no external libraries)
- Return answer as an `AocValue`; the dispatcher prints and frees it
- Manage memory carefully: every `malloc` needs a matching `free`

### 5. Update the Dispatcher

Add the puzzle to the year/day switch in `src/main.c`:

```c
// Inside runPuzzle(), in the case 2015: block:
case 1: {
    switch (part) {
        case 1: val = y2015d01p1(file); break;
        case 2: val = y2015d01p2(file); break;
        default: return;
    }
    // ... print, free (already handled by dispatcher)
}
```

Also include the new header at the top of `main.c`:
```c
#include "2015/day01.h"
```

### 6. Build and Test

```bash
make debug
./build/aoc 2015 1 1
```

### 7. Add Tests (Optional)

Create a test file:

```c
// tests/2024/day01_test.c
#include <stdio.h>
#include "../../src/2024/day01.h"

int main() {
    // Test functions
    return 0;
}
```

Run tests with `make test`.

## Adding Common Utilities

### When to Add a Utility

Add a new utility module when:
- You need data structures (e.g., dynamic arrays, hash tables)
- You need algorithms (e.g., pathfinding, sorting)
- Multiple puzzles can reuse the code

### 1. Choose a Category

Existing categories:
- **containers** — Dynamic arrays, linked lists, stacks, queues, hash tables
- **pathfinding** — BFS, DFS, A*, Dijkstra
- **math_utils** — GCD, LCM, modular arithmetic, primes

### 2. Write the Header

```c
// src/common/containers.h
#ifndef COMMON_CONTAINERS_H
#define COMMON_CONTAINERS_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntVector;

IntVector *int_vector_create(size_t initial_capacity);
void int_vector_push(IntVector *v, int value);
int int_vector_pop(IntVector *v);
void int_vector_free(IntVector *v);

#endif
```

### 3. Implement in the Source File

```c
// src/common/containers.c
#include "containers.h"
#include <stdlib.h>
#include <string.h>

IntVector *int_vector_create(size_t initial_capacity) {
    IntVector *v = malloc(sizeof(IntVector));
    v->data = malloc(initial_capacity * sizeof(int));
    v->size = 0;
    v->capacity = initial_capacity;
    return v;
}

// ... implement other functions
```

**Tips:**
- Use clear naming conventions (e.g., `type_action`)
- Document functions with comments
- Handle allocation failures
- Provide cleanup functions (e.g., `_free()`)

### 4. Use in Puzzles

Include the header in your puzzle solution:

```c
// src/2024/day01.c
#include "../common/containers.h"

void day_2024_01_part1(FILE *input_file) {
    IntVector *nums = int_vector_create(100);
    // ... use vector
    int_vector_free(nums);
}
```

The Makefile automatically compiles `src/common/containers.c` together with your puzzle.

### 5. Test It

Write a test to verify the utility works:

```c
// tests/2024/containers_test.c
#include "../../src/common/containers.h"

int main() {
    IntVector *v = int_vector_create(10);
    int_vector_push(v, 42);
    // ... test assertions
    int_vector_free(v);
    return 0;
}
```

## Guidelines

### Memory Management
- Use `malloc()` and `free()` carefully
- Always check allocation results
- Free resources before returning/exiting

### Error Handling
- Check file operations succeed
- Handle edge cases (empty input, invalid data)
- Use `perror()` for system errors

### Code Style
- Use clear variable names
- Add comments for non-obvious logic
- Keep functions focused and reasonably sized
- Follow the existing code style in the project

### Testing
- Write tests for utilities
- Test edge cases and error conditions
- Use `assert.h` for quick sanity checks if helpful

## Resources

- [Project Layout](project-layout.md) — Directory structure
- [Building](building.md) — Compilation and running
- [C23 Reference](c23-reference.md) — Language features and stdlib
