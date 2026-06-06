/**
 * @file day03.c
 * @brief AoC 2015 Day 3 — Perfectly Spherical Houses in a Vacuum: implementation.
 *
 * Puzzle input is a string of characters: '^' (north), 'v' (south),
 * '<' (west), '>' (east).
 * Part 1: Santa follows the directions and delivers presents to houses.
 *         Count unique houses visited.
 * Part 2: Santa and Robot-Santa alternate following the same directions.
 *         Count unique houses visited by either.
 */
#include "day03.h"
#include "../common/hash_set.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/aoc_value.h"

typedef struct {
  int x;
  int y;
} Point;

void modPoint(Point *p, const char *c) {
  switch (*c) {
    case '^': {
      p->y -= 1;
      break;
    }
    case 'v': {
      p->y += 1;
      break;
    }
    case '<': {
      p->x -= 1;
      break;
    }
    case '>': {
      p->x += 1;
      break;
    }
  }
} 

uint64_t key_create(int x, int y) {
  return ((uint64_t)(uint32_t)x << 32) | (uint32_t)y;
}

/**
 * @brief Solve 2015 day 3 part 1.
 *
 * @param raw Null-terminated puzzle input string. Must not be null.
 * @return Heap-allocated AocValue (AOC_VALUE_I64) containing the count of
 *         unique houses that receive at least one present.
 */
AocValue *y2015d03p1(const char *raw) {
    AocValue *val = malloc(sizeof(AocValue));
    // Start at house (0, 0) and count unique positions visited.
    // For each character: '^' -> y++, 'v' -> y--, '<' -> x--, '>' -> x++
    Point p = { .x = 0, .y = 0};
    HashSet *set = set_create(2000);
    set_insert(set, key_create(p.x, p.y));
    size_t count = 1;
    char *cur = (char *)raw;
    for(; *cur != '\0'; cur++) {
      modPoint(&p, cur);
      uint64_t key = key_create(p.x, p.y);
      if (set_insert(set, key)) {
        count++;
      }
    }
    set_free(set);
    set = NULL;

    val->as.i64 = count;
    val->tag = AOC_VALUE_I64;
    return val;
}

/**
 * @brief Solve 2015 day 3 part 2.
 *
 * @param raw Null-terminated puzzle input string. Must not be null.
 * @return Heap-allocated AocValue (AOC_VALUE_I64) containing the count of
 *         unique houses visited by Santa and Robot-Santa combined.
 */
AocValue *y2015d03p2(const char *raw) {
    AocValue *val = malloc(sizeof(AocValue));
    Point santa = { .x = 0, .y = 0};
    Point robo  = { .x = 0, .y = 0};
    HashSet *set = set_create(2000);
    set_insert(set, key_create(0,0));
    size_t count = 1;
    bool roboTurn = false;
    char *cur = (char *)raw;
    for (; *cur != '\0'; cur++) {
      uint64_t key;
      if (roboTurn) {
        modPoint(&robo, cur);
        key = key_create(robo.x, robo.y);
      } else {
        modPoint(&santa, cur);
        key = key_create(santa.x, santa.y);
      }
      if (set_insert(set, key)) {
        count++;
      }
      roboTurn = !roboTurn;
    }
    set_free(set);
    val->as.i64 = count;
    val->tag = AOC_VALUE_I64;
    return val;
}
