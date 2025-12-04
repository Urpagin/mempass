/*
 * Author: Urpagin
 * Date: 2025-12-01
 * Description: A small header-only dynamic string implementation.
 * License: Copyright (C) 2025 Urpagin (GPL v2)
 * File: str.h
 */

#pragma once

// For getline()
#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

// A custom String.
typedef struct String {
    size_t cap;
    size_t len;
    char *buf;
} str;

// Instantiates a new String with
// capacity is the initial capacity allocated.
static inline str str_new(size_t capacity) {
    if (!capacity) {
        // "compound literal" syntax.
        return (str){0, 0, NULL};
    }

    return (str){capacity, 0, (char *)malloc(capacity)};
}

// Appends a buffer to a str.
static inline void str_append_buf(str *s, const char buf[], const size_t size) {
    if (s->cap < (s->len + size)) {
        size_t growth = (s->cap + size) * 1.5;
        void *p = realloc(s->buf, growth);
        if (!p) {
            perror("Failed to reallocate");
            exit(1);
        }
        s->buf = (char *)p;
        // s->cap += growth;
        s->cap = growth;
    }

    // +1: null byte
    memcpy((s->buf + s->len), buf, size);
    s->len += size;
}

// Appends a char* to a str.
static inline void str_append(str *s, const char *buf) {
    str_append_buf(s, buf, strlen(buf));
}

// Clears the str and deallocates it.
// Effectively rendering it the same as the return value of str_new().
static inline void str_clear(str *s) {
    free(s->buf);
    s->cap = 0;
    s->len = 0;
}

// Prints a str.
// Adds a newline.
static inline void str_print(const str *s) {
    if (!s->len)
        return;

    fwrite(s->buf, sizeof(char), s->len, stdout);
    printf("\n");
}

// Prints the `prompt` argument to stdout without any newline.
// Reads stdin using getline().
// Returns a str.
static inline str str_from_stdin(const char *prompt) {
    size_t init_cap = 32;

    str s = str_new(init_cap);

    printf("%s", prompt);

    ssize_t read = getline(&s.buf, &init_cap, stdin);
    if (read == -1) {
        perror("Failed to read user input");
        return s;
    }

    s.cap = init_cap;
    s.len = read;

    return s;
}

static inline void str_debug(const str *s) {
    printf("String: {capacity: %ld; length: %ld}\n", s->cap, s->len);
}

// Sets the ECHO bit of the terminal file fd to:
// OFF if state == 0
// ON otherwise.
// TODO: return int, 0 success -1 error.
//
// TODO: After pressing [ENTER] after getting the user input,
// TODO: it echoes the full text at the end. Altough the ECHO works WHILE the
// user it typing.
static inline void set_echo(const int fd, int state) {
    struct termios t;
    // Gets the existing termios config for the fd.
    tcgetattr(fd, &t);

    // ON
    if (state)
        t.c_lflag |= ECHO;
    // OFF
    else
        t.c_lflag &= ~ECHO;

    // Apply the changes
    tcsetattr(fd, TCSANOW, &t);
}



// Removes the last \10 (\n) if there is one
// and replaces it with a null terminator.
//
// If the string's len is 0, no-op.
static inline void trim_last(str *s) {
    if (!s->len) return ;

    // Last char
    const size_t last_idx = s->len - 1;

    if (s->buf[last_idx] == '\n') {
        s->buf[last_idx] = '\0';
    }
}


// Get password securely
// Trims any newlines.
static inline str get_pass(void) {
    // Disable ECHO
    set_echo(STDIN_FILENO, 0);

    str pass = str_from_stdin("Secret: ");

    trim_last(&pass);

    // Revert back to normal.
    set_echo(STDIN_FILENO, 1);


    return pass;
}
