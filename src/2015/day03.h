/**
 * @file day03.h
 * @brief AoC 2015 Day 3 — Perfectly Spherical Houses in a Vacuum.
 *
 * Function declarations for both parts of the 2015 day 3 puzzle.
 * Each function parses a null-terminated movement string and returns a
 * heap-allocated AocValue. The caller is responsible for calling
 * aoc_value_free() on the value and then free() on the pointer.
 */
#ifndef DAY_2015_03_H
#define DAY_2015_03_H

#include "../common/aoc_value.h"

/**
 * @brief Solve 2015 day 3 part 1.
 *
 * Santa follows directions (^=north, v=south, <=west, >=east) and delivers
 * presents to houses. Count the number of unique houses that receive at least
 * one present.
 *
 * @param raw Null-terminated puzzle input string (direction characters). Must not be null.
 * @return Heap-allocated AocValue containing the count of houses visited.
 *         Caller must aoc_value_free() then free() the returned pointer.
 */
AocValue *y2015d03p1(const char *raw);

/**
 * @brief Solve 2015 day 3 part 2.
 *
 * Santa and Robot-Santa alternate following directions. Count the number of
 * unique houses that receive at least one present from either Santa or Robot-Santa.
 *
 * @param raw Null-terminated puzzle input string (direction characters). Must not be null.
 * @return Heap-allocated AocValue containing the count of houses visited.
 *         Caller must aoc_value_free() then free() the returned pointer.
 */
AocValue *y2015d03p2(const char *raw);

#endif
