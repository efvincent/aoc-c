/**
 * @file aoc_io.c
 * @brief Shared file I/O helpers for Advent of Code inputs.
 */

#include <stdio.h>
#include <stdlib.h>

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
char *slurp_file(FILE *handle, size_t *outSize) {
  if (fseek(handle, 0, SEEK_END) == -1) {
    return NULL;
  };
  size_t fsize = ftell(handle);
  rewind(handle);

  char *buffer = malloc(fsize + 1);
  if (!buffer) {
    return NULL;;
  }

  size_t readSize = fread(buffer, 1, fsize, handle);
  if (readSize < fsize) {
    free(buffer);
    return NULL;
  }
  buffer[readSize] = '\0';

  if (outSize) {
    *outSize = readSize;
  }

  return buffer;
}