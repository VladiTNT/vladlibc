#include "file.h"
#include <stdio.h>
#include <stdlib.h>

long file_size(FILE* f) {
    fseek(f, 0L, SEEK_END);
    long size = ftell(f);
    fseek(f, 0L, SEEK_SET);
    return size;
}

char* file_load(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) return NULL;

    long size = file_size(f);

    char* buffer = malloc(size + 1);
    if (!buffer) return NULL;

    fread(buffer, sizeof(char), size, f);
    buffer[size] = '\0';

    fclose(f);

    return buffer;
}

void file_write(const char* path, const char* buffer, size_t buff_len) {
    FILE* f = fopen(path, "w");
    if (!f) return;

    fwrite(buffer, sizeof(char), buff_len, f);

    fclose(f);
}