/*
* Author: Urpagin
* Date: 2025-12-01
* Description: A small header-only dynamic string implementation.
* License: Copyright (C) 2025 Urpagin (GPL v2)
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A custom String.
typedef struct String {
    size_t cap;
    size_t len;
    char* buf;
} str;


// Instantiates a new String with 
static inline str str_new(void) {
    // "compound literal" syntax.
    return (str){0, 0, NULL};
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
        s->buf = (char*)p;
        //s->cap += growth;
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

    fwrite(s->buf, 1, s->len, stdout);
    fwrite("\n", 1, 2, stdout);
}

// Returns whether a str contains a substring.
static inline bool str_contains(const str *s, const char *p) {
    // loop str
    for (size_t i = 0; i < s->len; ++i) {
        // if first char of pattern in str.
        if (s->buf[i] == p[0]) {
            // loop pattern
            bool is_matching = false;
            for (size_t j = 0; j < strlen(p); ++j) {
                if (s->buf[l])

                if ()
            }
        }
    }
}

static inline void str_debug(const str *s) {
    printf("String: {capacity: %ld; length: %ld}\n", s->cap, s->len);
}


