#include "json.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct json_value* json_unmarshal(const char** data);