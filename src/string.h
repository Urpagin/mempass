/*
* Author: Urpagin
* Date: 2025-12-01
* Description: A small header-only string.
* License: Copyright (C) 2025 Urpagin (GPL v2)
*/

#include <stddef.h>


// A custom String.
typedef struct String {
    size_t capacity;
    size_t len;
    char* buf;
} str;


// Instantiates a new String with 
str str_new() {
    // "compound literal" syntax.
    return (str){0, 0, NULL};
}

// Appends a buffer to a str.
str append_buf(str *s, char[] buf, size_t size) {

}

