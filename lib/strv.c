#include "strv.h"
#include <stdlib.h>
#include <string.h>

const char* strv_err_desc(enum strv_err err) {
    switch (err) {
    case NO_ERROR:
        return "There is no error, string is fine";
    case ALLOC_ERROR:
        return "Failed to allocate memory for string";
    case STRING_DESTORYED_ERROR:
        return "String has been deallocated";
    default:
        return "Unknown error code";
    }
}

struct strv strv_new_with_cap(size_t cap) {
    struct strv s;

    s.len = 0;
    s.cap = cap;

    s.data = malloc(cap);
    if (s.data == NULL) {
        s.err = ALLOC_ERROR;
        return s;
    }

    s.err = NO_ERROR;
    return s;
}

struct strv strv_new_from_literal(const char* string) {
    size_t string_len = strlen(string);

    struct strv s = strv_new_with_cap(2 * string_len);
    if (s.err != NO_ERROR) {
        return s;
    }

    s.len = string_len;

    memcpy(s.data, string, string_len);

    return s;
}

void strv_destroy(struct strv* s) {
    if (s->err == STRING_DESTORYED_ERROR) {
        return;
    }

    free(s->data);

    s->len = 0;
    s->cap = 0;
    s->data = NULL;
    s->err = STRING_DESTORYED_ERROR;
}
