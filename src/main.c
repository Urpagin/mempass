/*
 * Author: Urpagin
 * Date: 2025-12-01
 * Description: mempass, a simple utility to memorize a secret.
 * License: Copyright (C) 2025 Urpagin (GPL v2)
 */

// For getline()
#define _POSIX_C_SOURCE 200809L


#include "crypto.h"
#include "str.h"
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// TODO: (THICC) all that is below:

/*
 * Usage:
 * ./mempass (interactive, asks for one secret and then it's test time.)
 *
 * ./mempass [--generate|-g] (prompts for one or more secrets and also add a
 * label) (JSON or custom format)
 * TODO: requires ncurses?
 *
 * ./mempass [FILE_PATH] (then screen selector for which secret would the user
 * like to train on)
 *
 * ./mempass [FILE_PATH] [--random|-r] (prompts the user with a random label for
 * them to train on)
 *
 * ./mempass [FILE_PATH] [--label|-l] (directly enters training mode.)
 *
 */

// No program args passed in. Pure interactive.
void start_interactive() {
    printf("Inside start_interactive()\n");

    // I. Get a single secret.
    hstr secret = get_pass();

    printf("secret data: %s", secret->buf);

    printf("%s\n", hashed.digest);

    printf("\n");

    // II. Typing out phase.
}

// Dispatches which function to call based on the program arguments.
// Does the argument parsing.
// argparse code credit: getopt(3) section EXAMPLE, getopt_long()
// (I don't really understand this.)
void dispatch(int argc, char **argv) {
    int c;
    int digit_optind = 0;

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"add", required_argument, 0, 0},
            {"append", no_argument, 0, 0},
            {"delete", required_argument, 0, 0},
            {"verbose", no_argument, 0, 0},
            {"create", required_argument, 0, 'c'},
            {"file", required_argument, 0, 0},
            {0, 0, 0, 0},
        };

        c = getopt_long(argc, argv, "abc:d012", long_options, &option_index);

        if (c == -1) {
            start_interactive();
            break;
        }

        switch (c) {
        case 0:
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;
        case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind)
                printf("digits occur in two different argv-elements.\n");
            digit_optind = this_option_optind;
            printf("option %c\n", c);
            break;

        case 'a':
            printf("option a\n");
            break;

        case 'b':
            printf("option b\n");
            break;

        case 'c':
            printf("option c with value '%s'\n", optarg);
            break;

        case 'd':
            printf("option d with value '%s'\n", optarg);
            break;

        case '?':
            break;

        default:
            printf("?? getopt returned char code 0%o ??\n", c);
        }
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    // Parses the arguments and dispatches to the right program
    // behaviour.
    dispatch(argc, argv);
    return 0;
}
