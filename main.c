#include <stdio.h>
#include "lib/strv.h"

int main(void) {
    struct strv s = strv_new_from_literal("Hello, world!\n");

    printf("%.*s", s.len, s.data);

    strv_destroy(&s);

    printf("Error: %s\n", strv_err_desc(s.err));

    return 0;
}