#ifndef AOC_IO_H
#define AOC_IO_H

/**
 * @file aoc_io.h
 * @brief Shared file I/O helpers for Advent of Code inputs.
 */

#include <stdio.h>

/**
 * @brief Read an entire file stream into a newly allocated buffer.
 *
 * The returned buffer is null-terminated for convenient string processing.
 * The caller owns the buffer and must free() it.
 *
 * @param handle Open file handle positioned anywhere in the stream.
 * @param outSize Optional output pointer for the number of bytes read,
 *        excluding the trailing null terminator.
 * @return Newly allocated null-terminated buffer on success, or null on
 *         allocation failure.
 */
char *slurp_file(FILE *handle, size_t *outSize);

#endif