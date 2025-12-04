/*
 * Author: Urpagin
 * Date: 2025-12-01
 * Description: mempass, a simple utility to memorize a secret.
 * License: Copyright (C) 2025 Urpagin (GPL v2)
 */

#include "str.h"
#include <unistd.h>


int main(int argc, char *argv[]) {

    set_echo(STDIN_FILENO, 1);
    str u = str_from_stdin("after 1: ");

    set_echo(STDIN_FILENO, 0);
    str i = str_from_stdin("after 0: ");

    //
    // set_echo(STDIN_FILENO, 1);
    // str j = str_from_stdin("after 1 again: ");
    //
    // str u = get_usr_input("Prompt: ");
    str_print(&u);

    return 0;
}
