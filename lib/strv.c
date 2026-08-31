#include "strv.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

void strv_new_cap(struct strv* s, size_t cap) {
    if (s->cap >= cap) {
        return;
    }

    s->data = realloc(s->data, cap);
    if (s->data == NULL) {
        s->err = ALLOC_ERROR;
        return;
    }

    s->cap = cap;

    return;
}

void strv_increase_cap(struct strv* s, size_t cap) {
    strv_new_cap(s, s->cap + cap);
}

size_t strv_available(struct strv s) {
    return s.cap - s.len;
}

void strv_append(struct strv* s1, struct strv* s2) {
    size_t available_in_s1 = strv_available(*s1);

    if (available_in_s1 < s2->len) {
        strv_increase_cap(s1, s2->len * 2);
        if (s1->err) {
            return;
        }
    }

    memcpy(s1->data + s1->len, s2->data, s2->len);

    s1->len += s2->len;

    return;
}

void strv_append_literal(struct strv* s, const char* buff) {
    size_t buff_len = strlen(buff);
    size_t available_in_s = strv_available(*s);

    if (available_in_s > buff_len) {
        strv_increase_cap(s, buff_len * 2);
        if (s->err) {
            return;
        }
    }

    memcpy(s->data + s->len, buff, buff_len);

    s->len += buff_len;

    return;
}

bool strv_equal(struct strv* s1, struct strv* s2) {
    if (s1->len != s2->len) {
        return false;
    }

    for (size_t i = 0; i < s1->len; i++) {
        if (*(s1->data+i) != *(s2->data+i)) {
            return false;
        }
    }

    return true;
}

void strv_write_literal(struct strv* s, const char* buff) {
    size_t buff_len = strlen(buff);

    if (s->cap < buff_len) {
        strv_increase_cap(s, buff_len * 2);
        if (s->err) {
            return;
        }
    }

    memcpy(s->data, buff, buff_len);

    s->len = buff_len;

    return;
}

void strv_write(struct strv* s1, struct strv* s2) {
    if (s1->cap < s2->len) {
        strv_increase_cap(s1, s2->len * 2);
        if (s1->err) {
            return;
        }
    }   

    memcpy(s1->data, s2->data, s2->len);

    s1->len = s2->len;

    return;
}

struct strv strv_clone(struct strv s) {
    struct strv new_s = strv_new_with_cap(s.cap);
    if (new_s.err) {
        return new_s;
    }

    memcpy(new_s.data, s.data, s.len);

    new_s.len = s.len;

    return new_s;
}

bool strv_contains_char(struct strv s, char c) {
    for (size_t i = 0; i < s.len; i++) {
        if (*(s.data + i) == c) {
            return true;
        }
    }
    return false;
}

bool strv_contains(struct strv s1, struct strv s2) {
    for (size_t i = 0; i < s1.len; i++) {
        /* If a byte of s1 is equal to the first byte of s2 */
        if (*(s1.data + i) == *(s2.data)) {
            bool found_flag = true;
            /* We compare the next bytes. */
            for (size_t j = 1; j < s2.len; j++) {
                /* If one isn't equal, we break and set the flag */
                if (*(s1.data + i + j) != *(s2.data + j)) {
                    found_flag = false;
                    break;
                }
            }

            if (found_flag) {
                return true;
            }
        }
    }
    return false;
}

bool strv_contains_literal(struct strv s, const char* buff) {
    size_t buff_len = strlen(buff);

    for (size_t i = 0; i < s.len; i++) {
        if (*(s.data + i) == *(buff)) {
            bool found_flag = true;
            for (size_t j = 1; j < buff_len; j++) {
                if (*(s.data + i + j) != *(buff + j)) {
                    found_flag = false;
                    break;
                }
            }

            if (found_flag) {
                return true;
            }
        }
    }

    return false;
}

struct strv* strv_split(struct strv s, char sep, int* n) {
    if (!s.data || !n) return NULL;

    /* Allocate memory for delimiters */
    size_t* seps = malloc(sizeof(size_t) * (s.len + 2));
    if (!seps) return NULL;

    int seps_count = 0;
    seps[seps_count++] = (size_t)-1;

    for (size_t i = 0; i < s.len; i++) {
        if (s.data[i] == sep) {
            seps[seps_count++] = i;
        }
    }
    seps[seps_count++] = s.len;

    /* Count valid substrings */
    *n = 0;
    for (size_t i = 1; i < seps_count; i++) {
        if (seps[i] - seps[i-1] > 1) {
            (*n)++;
        }
    }

    if (*n == 0) {
        free(seps);
        return NULL;
    }

    struct strv* result_strings = malloc(sizeof(*result_strings) * (*n));
    if (!result_strings) {
        free(seps);
        return NULL;
    }
    int curr_string = 0;

    for (size_t i = 1; i < seps_count; i++) {
        size_t sub_string_len = seps[i] - seps[i-1] - 1;
        if (sub_string_len > 0) {
            struct strv temp_string = strv_new_with_cap(sub_string_len);
            
            memcpy(temp_string.data, s.data + seps[i-1] + 1, sub_string_len);
            temp_string.len = sub_string_len;

            result_strings[curr_string++] = temp_string;
        }
    }

    free(seps);
    return result_strings;
}