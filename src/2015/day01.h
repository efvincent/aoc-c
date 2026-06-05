/**
 * @file day01.h
 * @brief AoC 2015 Day 1 — Not Quite Lisp.
 *
 * Function declarations for both parts of the 2015 day 1 puzzle.
 * Each function reads from the provided file handle and returns a
 * heap-allocated AocValue. The caller is responsible for calling
 * aoc_value_free() on the value and then free() on the pointer.
 */
#ifndef DAY_2015_01_H
#define DAY_2015_01_H

#include <stdio.h>
#include "../common/aoc_value.h"

/**
 * @brief Solve 2015 day 1 part 1.
 *
 * @param input_file Open file handle for the puzzle input. Must not be null.
 * @return Heap-allocated AocValue containing the answer.
 *         Caller must aoc_value_free() then free() the returned pointer.
 */
AocValue *y2015d01p1(FILE *input_file);

/**
 * @brief Solve 2015 day 1 part 2.
 *
 * @param input_file Open file handle for the puzzle input. Must not be null.
 * @return Heap-allocated AocValue containing the answer.
 *         Caller must aoc_value_free() then free() the returned pointer.
 */
AocValue *y2015d01p2(FILE *input_file);

#endif
