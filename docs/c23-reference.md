# C23 Features & Standard Library Reference

A quick reference for C23 features and standard library functions useful for this project.

## C23 Highlights

### Designated Initializers
```c
struct point { int x; int y; };
struct point p = { .x = 10, .y = 20 };
```

### `_Bool` and `<stdbool.h>`
```c
#include <stdbool.h>
bool flag = true;
```

### Type-Generic Programming
```c
#define abs(x) _Generic((x), \
    int: abs, \
    long: labs, \
    long long: llabs \
)(x)
```

### `typeof`
```c
int x = 42;
typeof(x) y = x;  // y is int
```

## Useful Standard Library Headers

- `<stdio.h>` — I/O (printf, scanf, file operations)
- `<stdlib.h>` — Memory (malloc, free), utilities
- `<string.h>` — String operations (strlen, strcpy, strcmp)
- `<ctype.h>` — Character classification (isdigit, isalpha)
- `<limits.h>` — Integer limits (INT_MAX, INT_MIN)
- `<math.h>` — Math functions (requires `-lm` linking)
- `<time.h>` — Time and performance measurement
- `<assert.h>` — Assertions for debugging

## Common Patterns

### Dynamic Arrays
```c
#include <stdlib.h>

int *arr = malloc(n * sizeof(int));
if (!arr) { /* handle error */ }
// use arr
free(arr);
```

### String Parsing
```c
#include <string.h>

char *token = strtok(str, ",");
while (token) {
    // process token
    token = strtok(NULL, ",");
}
```

## Notes

Add any additional patterns, gotchas, or learning notes here as you work through puzzles.
