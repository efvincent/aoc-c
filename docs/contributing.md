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
src/2024/day01.h
src/2024/day01.c
```

### 3. Write the Header

Define the two exported functions:

```c
// src/2024/day01.h
#ifndef DAY_2024_01_H
#define DAY_2024_01_H

#include <stdio.h>

void day_2024_01_part1(FILE *input_file);
void day_2024_01_part2(FILE *input_file);

#endif
```

Function names follow the pattern: `day_YYYY_DD_partN`

### 4. Write the Solution

Implement parsing and solving in the source file:

```c
// src/2024/day01.c
#include "day01.h"
#include <stdio.h>
#include <stdlib.h>

void day_2024_01_part1(FILE *input_file) {
    // Parse input
    // Compute answer
    // Print result
}

void day_2024_01_part2(FILE *input_file) {
    // Similar structure
}
```

**Tips:**
- Read input using `fopen()`, `fgets()`, or `fscanf()`
- Use standard C library functions (no external libraries)
- Print results to stdout clearly (e.g., "Part 1: 12345")
- Manage memory carefully (use `free()` for `malloc()`)

### 5. Update the Dispatcher

Add the puzzle to `src/main.c` so it can be invoked:

```c
// In main.c (pseudocode)
if (year == 2024 && day == 1) {
    FILE *f = fopen("data/2024/day01.txt", "r");
    if (!f) { perror("Error"); return 1; }
    
    if (part == 0 || part == 1) {
        day_2024_01_part1(f);
    }
    if (part == 0 || part == 2) {
        rewind(f);
        day_2024_01_part2(f);
    }
    fclose(f);
}
```

### 6. Build and Test

```bash
make
./build/aoc 2024 1
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
