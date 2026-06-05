#define _GNU_SOURCE
/**
 * @file main.c
 * @brief CLI dispatcher entry point for Advent of Code puzzle execution.
 *
 * Parses and validates year, day, and part arguments, opens the corresponding
 * input data file, and routes execution to the appropriate puzzle function.
 * Puzzle answers are printed to stdout.
 *
 * Usage:
 * @code
 *   aoc <year> <day> <part>    # run a specific part
 *   aoc <year> <day>           # validate year/day (puzzle not yet dispatched)
 *   aoc <year>                 # validate year only
 * @endcode
 */
#include "common/aoc_value.h"
#include "common/aoc_io.h"
#include "2015/day01.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

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
 * @brief Parse and validate a part argument.
 *
 * Valid values are 1 and 2 only.
 *
 * @param s Input part string from argv.
 * @return 1 or 2 on success.
 * @return -1 if the value is not 1 or 2.
 */
int parsePart(const char *s) {
  int p = atoi(s);
  if (p == 0 || (p != 1 && p != 2)) {
    fprintf(stderr, "Invalid part, must be 1 or 2: %s\n", s);
    return -1;
  }
  return p;
}

/**
 * @brief Open the input data file for a given year and day.
 *
 * Constructs the path `data/<year>/day<DD>.txt` and opens it for reading.
 * The caller is responsible for calling fclose() on a non-null return value.
 *
 * @param day  Puzzle day (1–25).
 * @param year Puzzle year (e.g. 2015).
 * @return Open FILE handle on success, or null if path formatting fails or
 *         the file cannot be opened.
 */
FILE *getData(const int day, const int year) {
  char *fn;
  if (asprintf(&fn, "data/%d/day%02d.txt", year, day) < 0) {
    return NULL;
  }
  FILE *file = fopen(fn, "r");
  free(fn);
  return file;
}


/**
 * @brief Dispatch execution to the appropriate puzzle function.
 *
* Looks up the puzzle for the given year, day, and part, opens and slurps its
* input file, invokes the solution function, prints the result, and frees the
* answer resources.
 *
 * On error (file not found, unimplemented puzzle), a message is printed and
 * the function returns without printing an answer.
 *
 * @param day  Puzzle day (1–25).
 * @param year Puzzle year (e.g. 2015).
 * @param part Puzzle part (1 or 2).
 */
void runPuzzle(const int day, const int year, const int part) {
  AocValue *val = NULL;
  switch (year) {
    case 2015: {

      FILE *file = getData(day, year);
      if (file == NULL) {
        fprintf(stderr, "Could not open data file for year %d day %d.\n", year, day);
        return;
      }

      char *raw = slurp_file(file, NULL);
      if (raw == NULL) {
        fprintf(stderr, "Could not read data from data file for year %d day %d.\n", year, day);
        fclose(file);
        return;
      }
      
      switch (day) {
        case 1: {
          switch (part) {
            case 1: 
              val = y2015d01p1(raw);
              break;
            case 2: 
              val = y2015d01p2(raw);
              break;
            default:
              unreachable();
              return;
          }
          free(raw);
          fclose(file);
          char *ans = aocValueToString(val);
          if (ans == NULL) {
            fprintf(stderr, "failed to format answer for year %d day %d part %d.\n", year, day, part);
          } else {
            printf("Year %d day %d part %d answer: %s\n", year, day, part, ans);
            free(ans);
          }
          aoc_value_free(val);
          free(val);
          break;
        }
        default:
          free(raw);
          fclose(file);
          fprintf(stderr, "Year %d, day %d not yet implemented.\n", year, day);
          return;
      }
      break;
    }
    default:
      fprintf(stderr, "Year %d day %d not yet implemented.\n", year, day);
      return;
  }
}

/**
 * @brief Program entry point.
 *
 * Accepted argument forms:
 * - no args: prints a usage reminder
 * - `<year>`: validates year only
 * - `<year> <day>`: validates year and day
 * - `<year> <day> <part>`: runs the puzzle and prints the answer
 *
 * @param argc Argument count (1–4 supported).
 * @param argv Argument vector.
 * @return 0 on success.
 * @return -1 if year or day argument is invalid (1 or 2 args).
 * @return -2 if any argument is invalid (3 args).
 * @return -3 if argument count is unsupported.
 */
int main(int argc, char **argv) {
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
    case 4:{
      int y = parseYear(argv[1]);
      int d = parseDay(argv[2]);
      int p = parsePart(argv[3]);
      if (y < MIN_YEAR || d < MIN_DAY || p < 0) {
        return -2;
      }
      runPuzzle(d, y, p);
      break;
    }
    default:
      fprintf(stderr, "Got the wrong number of arguments\n");
      return -3;
  }
  return 0;
}
