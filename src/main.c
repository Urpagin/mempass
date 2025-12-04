/*
 * Author: Urpagin
 * Date: 2025-12-01
 * Description: mempass, a simple utility to memorize a secret.
 * License: Copyright (C) 2025 Urpagin (GPL v2)
 */

#include "crypto.h"
#include "str.h"
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    str s = get_pass();
    str_print(&s);
    obliterate_str(&s);

    return 0;
}
