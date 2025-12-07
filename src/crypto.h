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
#include <openssl/sha.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

// Used to hold securely a secret.
// The secret and a salt are hashed to produce hash.
// Uses the Sha512 hashing algorithm to produce a 64 bit digest.
//
// The hashed string should have been: "<secret>$<salt>".
typedef struct S512HashedString {
    uint8_t digest[SHA512_DIGEST_LENGTH];
    char *salt;
} hstr;

// Generates n ASCII characters from /dev/urandom (except sep).
static str rng_generate(size_t n, char sep) {
    int fd;
    if ((fd = open("/dev/urandom", O_RDONLY)) == -1) {
        perror("Failed to open /dev/urandom");
        fprintf(stderr, "Cannot generate salt; exitting...\n");
        exit(EXIT_FAILURE);
    }

    uint8_t byte;
    size_t total = 0;
    // +1 because i don't even know if the null terminator is included or not
    // :shrug:
    str salt = str_new(n + 1);
    while (total < n) {
        ssize_t r = read(fd, &byte, 1);

        if (r <= 0) {
            perror("Failed to read /dev/urandom");
            fprintf(stderr, "Cannot generate salt; exitting...\n");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // printable ASCII chars
        static const uint8_t ASCII_BEGIN = 33;
        static const uint8_t ASCII_END = 126;

        // only visible ASCII chars (33..=126)
        char current_char = byte % ASCII_END; // 0..126
        if (current_char < ASCII_BEGIN)
            current_char += ASCII_BEGIN;

        if (current_char == sep)
            continue;

        str_append_buf(&salt, &current_char, 1);
        total++;
    }

    close(fd);

    // Add a null-terminator to salt? idontknow
    return salt;
}

// Hashes a str using the Sha512 hashing algorithm.
// DO NOT FORGET TO OBLITERATE THE SECRET.
static hstr hstr_new(str *secret) {
    hstr hashed;

    // Salt the secret
    str salt = rng_generate(10, '$');
    hashed.salt = salt.buf;
    str_append(secret, "$");
    str_append_buf(secret, salt.buf, salt.len);

    // TODO: inspect if this cast is legal
    const unsigned char *data = (unsigned char *)secret->buf;
    unsigned char digest[SHA512_DIGEST_LENGTH];
    SHA512(data, secret->len, hashed.digest);
    // 'digest' now contains the raw 64-byte binary hash.

    return hashed;
}

// Compares the hash of a str with a hstr.
// DO NOT FORGET TO OBLITERATE THE SECRET.
//
// RETURN VALUES:
// 0 if a != b
// 1 if a == b
static int hstr_is_equal_str(str **a, hstr *b) { return 0; }
