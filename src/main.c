/**
 * @file main.c
 * @brief CLI entry point and argument validation for the AoC dispatcher.
 *
 * This module currently validates year/day command-line arguments and prints
 * the parsed values. It is the entry point for eventually dispatching to
 * year/day puzzle implementations.
 */
#include <stdio.h>
#include <stdlib.h>

/** @brief Maximum supported puzzle year. */
const int MAX_YEAR=2025;

/** @brief Minimum supported puzzle year. */
const int MIN_YEAR=2015;

/** @brief Minimum valid Advent of Code day number. */
const int MIN_DAY=1;

/** @brief Maximum valid Advent of Code day number. */
const int MAX_DAY=25;

/**
 * @brief Parse and validate a year argument.
 *
 * The function converts the input string using atoi and checks that the
 * resulting value is in the inclusive range [MIN_YEAR, MAX_YEAR].
 *
 * @param s Input year string from argv.
 * @return Parsed year on success.
 * @return -1 if conversion fails to a non-zero integer.
 * @return -2 if the parsed year is outside the allowed range.
 */
int parseYear(const char *s) {
  int y = atoi(s);
  if (y == 0) {
    fprintf(stderr, "Invalid year: %s\n", s);
    return -1;
  }
  if (y < MIN_YEAR || y > MAX_YEAR) {
    fprintf(stderr, "Year invalid or out of range (%d-%d): %s\n", MIN_YEAR, MAX_YEAR, s);
    return -2;
  }
  return y;
}

/**
 * @brief Parse and validate a day argument.
 *
 * The function converts the input string using atoi and checks that the
 * resulting value is in the inclusive range [MIN_DAY, MAX_DAY].
 *
 * @param s Input day string from argv.
 * @return Parsed day on success.
 * @return -1 if conversion fails to a non-zero integer.
 * @return -2 if the parsed day is outside the allowed range.
 */
int parseDay(const char *s) {
  int d = atoi(s);
  if (d == 0) {
    fprintf(stderr, "Invalid day: %s\n", s);
    return -1;
  }
  if (d < MIN_DAY || d > MAX_DAY) {
    fprintf(stderr, "Day invalid or out of range (%d-%d): %s\n", MIN_DAY, MAX_DAY, s);
    return -2;
  }
  return d;
}

/**
 * @brief Program entry point.
 *
 * Supported argument forms at present:
 * - no args: prints a message
 * - year only: validates and prints year
 * - year + day: validates and prints year/day
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on handled success paths.
 * @return Negative value on validation or usage errors.
 */
int main(int argc, char **argv) {
  printf("Hello, world!\nargc: %d, program name is %s\n", argc, argv[0]);
  switch (argc) {
    case 1:
      printf("No arguments passed.\n");
      break;
    case 2: {
      int y = parseYear(argv[1]);
      if (y < MIN_YEAR) {
        return -1;
      }
      printf("Year: %d\n", y);
      break;
    }
    case 3: {
      int y = parseYear(argv[1]);
      int d = parseDay(argv[2]);
      if (y < MIN_YEAR || d < MIN_DAY) {
        return -2;
      }
      printf("Year %d, Day: %d\n", y, d);
      break;    
    }
    default:
      fprintf(stderr, "Got the wrong number of arguments\n");
      return -3;
  }
  return 0;
}
