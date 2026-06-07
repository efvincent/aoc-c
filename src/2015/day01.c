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
#include <stdlib.h>

#include "../common/aoc_value.h"

// TODO: Implement parsing and solving

/**
 * @brief Solve 2015 day 1 part 1.
 *
 * @param raw Null-terminated puzzle input string. Must not be null.
 * @return Heap-allocated AocValue (AOC_VALUE_I64) containing the answer.
 */
AocValue *y2015d01p1(const char *raw) {
  char *cur = (char *)raw;
  int floor = 0;
  for (; *cur != '\0'; cur++) {
    switch (*cur) {
      case '(': {
        floor += 1;
        break;
      }
      case ')': {
        floor -= 1;
        break;
      }
      default:
        unreachable();
    }
  }
  AocValue *val = malloc(sizeof(AocValue));
  val->as.i64 = floor;
  val->tag = AOC_VALUE_I64;
  return val;
}

/**
 * @brief Solve 2015 day 1 part 2.
 *
 * @param raw Null-terminated puzzle input string. Must not be null.
 * @return Heap-allocated AocValue (AOC_VALUE_I64) containing the answer.
 */
AocValue *y2015d01p2(const char *raw) {
  char *cur = (char *)raw;
  int floor = 0;
  int steps = 0;
  for (; *cur != '\0'; cur++) {
    steps += 1;
    switch (*cur) {
      case '(': {
        floor += 1;
        break;
      }
      case ')':
        floor -= 1;
        if (floor < 0) {
          goto done;               
        } 
        break;
    }
  }
  done:
  AocValue *val = malloc(sizeof(AocValue));
  val->as.i64 = steps;
  val->tag = AOC_VALUE_I64;
  return val;
}
