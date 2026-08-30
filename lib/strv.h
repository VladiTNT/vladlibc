#ifndef STRV_H
#define STRV_H

#include <stdlib.h>

/* These are error codes for the strv struct. */
enum strv_err {
    NO_ERROR,
    ALLOC_ERROR,
    STRING_DESTORYED_ERROR,
};

/* Returns a string literal description of the provided error code. */
const char* strv_err_desc(enum strv_err err);

/* This is a header for a heap allocated string.
You shouldn't modify the fields on your own. */
struct strv {
    size_t len;
    size_t cap;
    char* data;
    enum strv_err err;
};

/* Makes a new heap allocated string with cap capacity. */
struct strv strv_new_with_cap(size_t cap);

/* Makes a heap allocated string from the provided C string literal. */
struct strv strv_new_from_literal(const char* string);

/* Deallocates a string. */
void strv_destroy(struct strv* s);

#endif