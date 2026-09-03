#ifndef STRV_H
#define STRV_H

#include <stdlib.h>
#include <stdbool.h>

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

/* Sets the capacity of the string. */
void strv_new_cap(struct strv* s, size_t cap);

/* Increases the capacity of s by cap bytes. */
void strv_increase_cap(struct strv* s, size_t cap);

/* Returns the available space that the string has. */
size_t strv_available(struct strv s);

/* Appends the contents of s2 to s1. */
void strv_append(struct strv* s1, struct strv s2);

/* Appends the string literal to s. */
void strv_append_literal(struct strv* s, const char* buff);

/* Returns true if the provided strings are equal. */
bool strv_equal(struct strv s1, struct strv s2);

/* Replaces the contents of s with the provided literal. */
void strv_write_literal(struct strv* s, const char* buff);

/* Replaces the contents of s1 with those of s2. */
void strv_write(struct strv* s1, struct strv s2);

/* Makes a copy s. */
struct strv strv_clone(struct strv s);

/* Returns true if c is present in s. */
bool strv_contains_char(struct strv s, char c);

/* Returns true if s2 is present in s1. */
bool strv_contains(struct strv s1, struct strv s2);

/* Returns true if the literal stored in buff is present in s. */
bool strv_contains_literal(struct strv s, const char* buff);

/*
Splits s into it's substrings based on the given separator.
It returns a pointer to the first substring and it stores the amount of substrings into n.
If the function fails it will return NULL.
You will have to manually free the memory of the result strings.
*/
struct strv* strv_split(struct strv s, char sep, int* n);

#endif