/*
 * Author: Urpagin
 * Date: 2025-12-01
 * Description: crypto.h, functions related to hashing, memory and security.
 * License: Copyright (C) 2025 Urpagin (GPL v2)
 * File: crypto.h
 */

#pragma once

#include "str.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// Shreds a memory zone up to and including `size`
// bytes, `passes` times over using random data
// from /dev/random.
// Returns 0 on success, -1 on error.
// if size == 0, or passes == 0, returns 0 not performing anything.
static int shred(void *data, const size_t size, const size_t passes) {

    // I know it's useless because of the forloop (passes), but who cares!
    // No one's ever going to read this, anyway.
    if (size == 0 || passes == 0 || !data) {
        return 0;
    }

    // To middle-finger the compiler from possibly
    // optimizing away our pretty logic.
    volatile uint8_t *p = (volatile uint8_t *)data;

    int fd = open("/dev/random", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open /dev/random");
        return -1;
    }

    const size_t RND_SIZE = 64;
    uint8_t rnd[RND_SIZE];

    for (size_t pass = 0; pass < passes; ++pass) {
        // Where we are in the p.
        size_t idx = 0;
        ssize_t r;
        while (idx < size && (r = read(fd, rnd, RND_SIZE)) > 0) {
            // Loop on r, because read() can return any 1 <= r <= RND_SIZE
            for (size_t i = 0; i < (size_t)r; ++i) {
                // Shred one byte at a time.
                p[idx++] = rnd[i];
            }
        }

        if (r == -1) {
            perror("Error reading random data");
            close(fd);
            return -1;
        }
        // This should never happen.
        if (r == 0) {
            perror("EOF reached on /dev/random???");
            close(fd);
            return -1;
        }
    }

    close(fd);
    return 0;
}

// Shreds the pointer a hundred times and frees it.
// size is the size of the allocated memory.
static inline int obliterate_str(str *s) {
    if (!s->cap || !s->len) {
        free(s->buf);
        return 0;
    }

    int ret = shred(s->buf, s->cap, 100);
    free(s->buf);
    return ret;
}
