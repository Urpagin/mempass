/*
 * Author: Urpagin
 * Date: 2025-12-01
 * Description: mempass, a simple utility to memorize a secret.
 * License: Copyright (C) 2025 Urpagin (GPL v2)
 */

#include "str.h"

int main(int argc, char *argv[]) {
    str u = str_from_stdin("Usr: ");

  // str u = get_usr_input("Prompt: ");
  str_print(&u);

  return 0;
}
