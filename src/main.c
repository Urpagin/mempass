/*
 * Author: Urpagin
 * Date: 2025-12-01
 * Description: mempass, a simple utility to memorize a secret.
 * License: Copyright (C) 2025 Urpagin (GPL v2)
 */

#include "str.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// Get password securely
str get_pass() {
    // Disable ECHO
    set_echo(STDIN_FILENO, 0);

    str pass = str_from_stdin("Secret: ");

    // Revert back to normal.
    set_echo(STDIN_FILENO, 1);

    return pass;
}

// Shreds a memory zone up to and including `size`
// bytes, `passes` times over using random data
// from /dev/random.
// Returns 0 on success, -1 on error.
int shred(uint8_t *p, const size_t size, const size_t passes) {
    int fd = open("/dev/random", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open /dev/random");
        return fd;
    }

    const size_t RND_SIZE = 64;
    uint8_t rnd[RND_SIZE];

    for (size_t pass = 0; pass < passes; ++pass) {
        // Where we are in the p.
        uint8_t idx = 0;
        ssize_t r;
        int halt = 0;
        while((r = read(fd, rnd, RND_SIZE)) > 0 && !halt) {
            
            for (size_t i = 0; i < RND_SIZE; ++i) {
                if (idx > size) {
                    // Data fully shredded.
                    halt = 1;
                    break;
                }
                // Shred one byte at a time.
                *(p + idx)  = rnd[i];
                ++idx;
            }
        }


        if (r == -1) {
            perror("Error reading random data");
            return -1;
        }
        // This should never happen.
        if (r == 0) {
            perror("EOF reached on /dev/random???");
            return -1;
        }

    }


    return 0;

}

int main(int argc, char *argv[]) {

    str s = str_new(10);
    str_append(&s, "Hello, World!");

    str_print(&s);
    shred((uint8_t*)s.buf, s.cap, 1000000);
    str_print(&s);


    // set_echo(STDIN_FILENO, 1);
    // str u = str_from_stdin("after 1: ");
    //
    // set_echo(STDIN_FILENO, 0);
    // str i = str_from_stdin("after 0: ");
    // printf("\n");
    //
    // set_echo(STDIN_FILENO, 1);
    //
    // str_print(&i);

    //
    // set_echo(STDIN_FILENO, 1);
    // str j = str_from_stdin("after 1 again: ");
    //
    // str u = get_usr_input("Prompt: ");
    //str_print(&u);

    return 0;
}
