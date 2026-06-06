#include "hash_set.h"

/**
 * @file hash_set.c
 * @brief Implementation of the uint64_t open-addressed hash set.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bitset.h"

/**
 * @brief Mix a 64-bit key into a well-distributed hash value.
 *
 * The table masks the result with capacity - 1, so good bit diffusion across
 * the full word helps avoid clustering.
 *
 * @param x Key to hash.
 * @return Mixed 64-bit hash value.
 */
static uint64_t hash(uint64_t x) {
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9ULL;
  x ^= x >> 27; 
  x *= 0x94d049bb133111ebULL;
  x ^= x >> 31;
  return x;
}

/** @copydoc set_create */
HashSet *set_create(size_t capacity) {
  // force power of 2 capacity for fast modulo via bitwise AND
  size_t cap = 1;
  while (cap < capacity) {
    cap <<= 1;
  }

  HashSet *set = malloc(sizeof(HashSet));
  if (set == NULL) {
    return NULL;
  }

  set->capacity = cap;
  set->count = 0;
  set->keys = malloc(cap * sizeof(uint64_t));
  if (set->keys == NULL) {
    free(set);
    return NULL;
  }

  size_t words = bitset_word_count(cap);
  set->occupied = calloc(words, sizeof(uint64_t));
  if (set->occupied == NULL) {
    free(set->keys);
    free(set);
    return NULL;
  }

  return set;
}

/**
 * @brief Rebuild the table at double capacity.
 *
 * Existing keys are reinserted into a fresh table so their probe sequences are
 * recomputed against the new mask.
 *
 * @param set Set to resize in place.
 */
static void set_resize(HashSet *set) {
  // capture state of set
  size_t oldCap = set->capacity;
  uint64_t *oldKeys = set->keys;
  uint64_t *oldOccupied = set->occupied;

  // double capacity, allocate space for keys and occupied flags
  set->capacity *= 2;
  set->count = 0;
  set->keys     = malloc(set->capacity * sizeof(uint64_t));
  set->occupied = calloc(bitset_word_count(set->capacity), sizeof(uint64_t));

  // restore old keys where occupied
  set->count = 0;   // Reset count, re-insert will increment it
  for (size_t i = 0; i < oldCap; i++) {
    if (bitset_test(oldOccupied, i)) {
      set_insert(set, oldKeys[i]);
    }  
  }

  free(oldOccupied);
  free(oldKeys);
}

/** @copydoc set_insert */
bool set_insert(HashSet *set, uint64_t key) {
  // grow the set if we're beyond half full
  if (set->count >= set->capacity / 2) {
    set_resize(set);
  } 

  // determine the index to be used for the key
  uint64_t idx = hash(key) & (set->capacity - 1);
  
  // probe for unoccupied slot, leaving idx at the first empty slot
  while (bitset_test(set->occupied, idx)) {
    if (set->keys[idx] == key) {
      return false;
    }
    idx = (idx + 1) & (set->capacity - 1);
  }

  set->keys[idx] = key;
  bitset_set(set->occupied, idx);
  set->count++;
  return true;
}

/** @copydoc set_free */
void set_free(HashSet *set) {
  free(set->keys);
  free(set->occupied);
  free(set);
}