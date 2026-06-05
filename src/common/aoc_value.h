/**
 * @file aoc_value.h
 * @brief Tagged-union value type for Advent of Code puzzle answers.
 *
 * This header defines a compact runtime-typed value container that allows
 * puzzle parts to return heterogeneous answer types through one interface.
 *
 * Ownership policy:
 * - Numeric variants own no heap memory.
 * - String variant owns the pointer stored in as.str when dynamically allocated.
 * - aoc_value_free releases owned string storage for string-tagged values.
 */

#ifndef AOC_VALUE_H
#define AOC_VALUE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Runtime discriminator for the active member of AocValue.as.
 *
 * The value of this tag determines which member of AocValue.as is valid.
 */
typedef enum : char {
  /** @brief Signed 64-bit integer answer (`as.i64`). */
  AOC_VALUE_I64,

  /** @brief Unsigned 64-bit integer answer (`as.u64`). */
  AOC_VALUE_U64,

  /** @brief NUL-terminated C string answer stored in as.str. */
  AOC_VALUE_STR
} AocValueTag;

/**
 * @brief Tagged union representing one Advent of Code answer value.
 *
 * Read only the union member selected by tag:
 * - AOC_VALUE_I64 -> as.i64
 * - AOC_VALUE_U64 -> as.u64
 * - AOC_VALUE_STR -> as.str
 *
 * Invariant:
 * - tag must always match the currently active union member.
 */
typedef struct {
  AocValueTag tag;
  union {
    int64_t i64;
    uint64_t u64;
    /**
     * @brief Owned C string answer when tag is AOC_VALUE_STR.
     *
     * Expected to be heap-allocated when ownership is transferred to this value.
     * aoc_value_free releases this pointer for string-tagged values.
     */
    char *str;
  } as;
} AocValue;

/**
 * @brief Release owned resources held by an AocValue.
 *
 * Frees any heap memory owned by the value payload, then resets the value
 * to a safe numeric default. This function does NOT free the AocValue struct
 * itself -- the caller is responsible for freeing the struct if it was
 * heap-allocated.
 *
 * Behavior:
 * - If v is null, no action is taken.
 * - If v->tag is AOC_VALUE_STR, v->as.str is freed (if non-null).
 * - The value is reset to a safe numeric default by the implementation.
 *
 * @param v Pointer to value to clean up; may be null.
 */
void aoc_value_free(AocValue *v);

/**
 * @brief Make a heap-allocated C string representation of an AocValue.
 *
 * The caller is responsible for freeing the returned string.
 * Returns null if val is null or the tag is unrecognized.
 * Passing the return value to printf with %%s without a null check
 * is undefined behavior -- guard against null before use.
 *
 * @param val The AocValue to convert; may be null.
 * @return Heap-allocated string; caller must free. Null on unrecognized tag.
 */
char *aocValueToString(const AocValue *val);

#endif
