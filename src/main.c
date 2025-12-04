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

// TODO: (THICC) all that is below:

/*
* Usage:
* ./mempass (interactive, asks for one secret and then it's test time.)
*
* ./mempass [--generate|-g] (prompts for one or more secrets and also add a label) (JSON or custom format)
* TODO: requires ncurses?
*
* ./mempass [FILE_PATH] (then screen selector for which secret would the user like to train on)
*
* ./mempass [FILE_PATH] [--random|-r] (prompts the user with a random label for them to train on)
*
* ./mempass [FILE_PATH] [--label|-l] (directly enters training mode.)
*
*/

int main(int argc, char *argv[]) {

    str s = get_pass();
    str_print(&s);
    obliterate_str(&s);

    return 0;
}
