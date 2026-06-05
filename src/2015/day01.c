/**
 * @file day01.c
 * @brief AoC 2015 Day 1 — Not Quite Lisp: implementation.
 *
 * Puzzle input is a single line of '(' and ')' characters.
 * Part 1 finds the final floor Santa ends up on.
 * Part 2 finds the position of the first character that causes Santa
 * to enter the basement (floor -1).
 *
 * Both functions return a heap-allocated AocValue. Caller must
 * aoc_value_free() then free() the returned pointer.
 */
#include "day01.h"
#include <stdio.h>
#include <stdlib.h>

#include "../common/aoc_value.h"

// TODO: Implement parsing and solving

/**
 * @brief Solve 2015 day 1 part 1.
 *
 * @param input_file Open file handle for the puzzle input. Must not be null.
 * @return Heap-allocated AocValue (AOC_VALUE_I64) containing the answer.
 */
AocValue *y2015d01p1(FILE *input_file) {
    if (input_file == NULL) {
        fprintf(stderr, "input file handle was null.\n");
    }
    AocValue *val = malloc(sizeof(AocValue));
    val->as.i64 = 1;
    val->tag = AOC_VALUE_I64;
    return val;
}

/**
 * @brief Solve 2015 day 1 part 2.
 *
 * @param input_file Open file handle for the puzzle input. Must not be null.
 * @return Heap-allocated AocValue (AOC_VALUE_I64) containing the answer.
 */
AocValue *y2015d01p2(FILE *input_file) {
    if (input_file == NULL) {
        fprintf(stderr, "input file handle was null.\n");
    }
    AocValue *val = malloc(sizeof(AocValue));
    val->as.i64 = 2;
    val->tag = AOC_VALUE_I64;
    return val;
}
