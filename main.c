#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib/file.h"
#include "lib/json.h"

void json_skip_spaces(char** data) {
    while (**data == ' ' || **data == '\n' || **data == '\t') {
        (*data)++;
    }
}

char* json_read_string(char** data) {
    if (**data != '"') return NULL;
    (*data)++;

    const char* start = *data;
    while (**data != '"' && **data != '\0') {
        (*data)++;
    }

    int string_len = *data - start;
    char* result = malloc(string_len + 1);
    strncpy(result, start, string_len);
    result[string_len] = '\0';

    if (**data == '"') (*data)++;
    return result;
};

double json_read_number(char** data) {
    char* end;
    double num = strtod(*data, &end);
    *data = end;
    return num;
}

bool json_read_bool(char** data) {
    if (!strncmp(*data, "true", 4)) {
        *data += 4;
        return true;
    } else if (!strncmp(*data, "false", 5)) {
        *data += 5;
        return false;
    }
    return false;
}

void json_read_null(char** data) {
    if (!strncmp(*data, "null", 4)) {
        (*data) += 4;
    }
}

enum json_type json_get_type(char c) {
    if (c == '{') {
        return TYPE_OBJECT;
    } else if (c == '[') {
        return TYPE_ARRAY;
    } else if (c == '"') {
        return TYPE_STRING;
    } else if (c >= '0' && c <= '9') {
        return TYPE_NUMBER;
    } else if (c == 't' || c == 'f') {
        return TYPE_BOOL;
    } else if (c == 'n') {
        return TYPE_NULL;
    }
}

int main(void) {
    char* data = file_load("./test.json");

    return 0;
}

