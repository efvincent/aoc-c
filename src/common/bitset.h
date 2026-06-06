#ifndef BITSET_H
#define BITSET_H

/**
 * @file bitset.h
 * @brief Header-only helpers for packed occupancy bitsets.
 *
 * The helpers in this file treat a uint64_t array as a dense bitset where
 * each slot index maps to one bit position.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Map a slot index to its containing 64-bit word index.
 *
 * @param slot Logical slot index.
 * @return Index into the backing uint64_t word array.
 */
static inline size_t bitset_word_index(size_t slot) {
  return slot >> 6;   // slot / 64
}

/**
 * @brief Build a one-bit mask for a slot within its 64-bit word.
 *
 * @param slot Logical slot index.
 * @return Mask with exactly one bit set for the slot position.
 */
static inline uint64_t bitset_mask(size_t slot) {
  return 1ULL << (slot & 63);   // slot % 64
}

/**
 * @brief Test whether a slot bit is currently set.
 *
 * @param bits Backing bitset words.
 * @param slot Logical slot index.
 * @return true when the slot bit is set, false otherwise.
 */
static inline bool bitset_test(const uint64_t *bits, size_t slot) {
  return (bits[bitset_word_index(slot)] & bitset_mask(slot)) != 0;
}

/**
 * @brief Mark a slot as set in the bitset.
 *
 * @param bits Backing bitset words.
 * @param slot Logical slot index.
 */
static inline void bitset_set(uint64_t *bits, size_t slot) {
  bits[bitset_word_index(slot)] |= bitset_mask(slot);
}

/**
 * @brief Clear a slot bit in the bitset.
 *
 * @param bits Backing bitset words.
 * @param slot Logical slot index.
 */
static inline void bitset_clear(uint64_t *bits, size_t slot) {
  bits[bitset_word_index(slot)] &= ~bitset_mask(slot);
}

/**
 * @brief Compute how many 64-bit words are needed for a slot count.
 *
 * @param capacity Number of logical slots represented by the bitset.
 * @return Number of uint64_t words required to store all slot bits.
 */
static inline size_t bitset_word_count(size_t capacity) {
  return (capacity + 63) / 64;
}

#endif