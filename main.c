#include <stdio.h>
#include "lib/strv.h"

int main(void) {
    struct strv s = strv_new_from_literal("Vlad is cool!");
    
    int count;
    struct strv* ss = strv_split(s, ' ', &count);

    for (int i = 0; i < count; i++) {
        printf("%.*s\n", ss[i].len, ss[i].data);
    }

    return 0;
}