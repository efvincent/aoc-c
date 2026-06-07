
#ifndef HASH_SET_H
#define HASH_SET_H

/**
 * @file hash_set.h
 * @brief Open-addressed hash set for 64-bit unsigned integer keys.
 *
 * The set uses linear probing with a power-of-two capacity. Keys are stored
 * directly in the table, while a parallel occupancy array distinguishes empty
 * slots from populated ones.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HashSet HashSet;

/**
 * @brief Allocate a hash set with at least the requested capacity.
 *
 * The implementation rounds capacity up to the next power of two so it can use
 * bit masking instead of modulo during probing.
 *
 * @param capacity Minimum desired slot count before rounding.
 * @return Newly allocated set, or null if allocation fails.
 */
HashSet *set_create(size_t capacity);

/**
 * @brief Insert a key if it is not already present.
 *
 * The set resizes automatically when the load factor reaches one half.
 *
 * @param set Set to modify.
 * @param key Key to insert.
 * @return true if the key was newly inserted, or false if it already existed.
 */
bool set_insert(HashSet *set, uint64_t key);

/**
 * @brief Release all storage owned by a hash set.
 *
 * @param set Set to free; behavior is implementation-defined if null.
 */
void set_free(HashSet *set);

#endif