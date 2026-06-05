#define _GNU_SOURCE
/**
 * @file aoc_value.c
 * @brief Implementation of tagged value resource-management helpers.
 *
 * This unit provides:
 * - Resource cleanup for tagged value instances that may own heap memory.
 *
 * Ownership contract implemented here:
 * - Numeric values own no heap memory.
 * - String values may own as.str when tag is AOC_VALUE_STR.
 */
#include "aoc_value.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Release any owned storage held by an AocValue.
 *
 * If the value currently holds a string payload, its pointer is freed.
 * The value is then reset to a safe numeric default state.
 *
 * @param v Pointer to value to clean up; may be null.
 */
void aoc_value_free(AocValue *v) {
  if (v == NULL) {
    return;
  }

  if (v->tag == AOC_VALUE_STR) {
    free(v->as.str);
  }

  v->tag = AOC_VALUE_I64;
  v->as.i64 = 0;
}

/**
 * @brief Make a heap-allocated C string representation of an AocValue.
 *
 * The caller is responsible for freeing the returned string.
 * Returns null if val is null or the tag is unrecognized.
 *
 * @param val The AocValue to convert; may be null.
 * @return Heap-allocated string; caller must free. Null on unrecognized tag.
 */
char *aocValueToString(const AocValue *val) {
  char *s;
  switch (val->tag) {
    case AOC_VALUE_I64: 
      asprintf(&s, "%ld", val->as.i64);
      break;
    
    case AOC_VALUE_U64: 
      asprintf(&s, "%lu", val->as.u64);
      break;

    case AOC_VALUE_STR:
      asprintf(&s, "%s", val->as.str);
      break;
  }
  return s;
}
