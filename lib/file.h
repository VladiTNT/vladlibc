#ifndef FILE_H
#define FILE_H

#include <stdio.h>

/* Returns the size of a file in bytes. */
long file_size(FILE* f);

/* Reads a whole file in heap memory and returns a pointer to the data. */
char* file_load(const char* path);

#endif