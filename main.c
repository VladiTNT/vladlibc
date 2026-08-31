#include <stdio.h>
#include "lib/strv.h"

int main(void) {
    struct strv s1 = strv_new_from_literal("Many nerds code in C\n");
    struct strv s2 = strv_clone(s1);

    printf("%.*s", s1.len, s1.data);
    printf("%.*s", s2.len, s2.data);

    printf("%d %d\n", s1.data, s2.data);

    return 0;
}