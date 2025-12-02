/*
* Author: Urpagin
* Date: 2025-12-01
* Description: mempass, a simple utility to memorize a secret.
* License: Copyright (C) 2025 Urpagin (GPL v2)
*/

#include "str.h"
#include <stdio.h>


// Prompts the user for an input.
str get_usr_input(char *prompt) {
    char buf[32];
    str s = str_new();
    printf("%s", prompt);
    for (;;) {
        char *r = fgets(buf, sizeof(buf), stdin);
        printf("Lap\n");
        str_append(&s, buf);
        if (!r) {
            break;
        }
    }
    printf("\n");
    return s;
}

int main(int argc, char *argv[]) {

    str u = get_usr_input("Prompt: ");
    str_print(&u);

    return 0;
}

