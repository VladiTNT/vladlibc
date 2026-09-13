#ifndef JSON_H
#define JSON_H

#include <stdlib.h>
#include <string.h>

enum json_type {
    TYPE_OBJECT,
    TYPE_ARRAY,
    TYPE_NUMBER,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_NULL,
};

struct json_value {
    enum json_type type;
    void* value;
};

struct json_object {
    char** keys;
    struct json_value* values;
    int count;
};

struct json_array {
    struct json_value* values;
    int count;
};

struct json_value* json_unmarshal(const char** data);

#endif