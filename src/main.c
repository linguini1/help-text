#include "helptext.h"
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The size of 1 byte in bytes (lol) */
#define BYTE_SIZE 1

/* The output file to write to, if provided. */
char *outfile = NULL;

/* The input file to read from, if provided. */
char *infile = NULL;

/* The default name of the `#define` macro */
char *macro_name = "HELP_TEXT";

/* The size of each line of text in implicit C string concatenation. */
size_t line_width = 80;

int main(int argc, char **argv) {

    int c;
    while ((c = getopt(argc, argv, ":i:o:n:w:h")) != -1) {
        switch (c) {
        case 'h':
            puts(HELP_TEXT);
            exit(EXIT_SUCCESS);
            break;
        case 'o':
            outfile = optarg;
            break;
        case 'i':
            infile = optarg;
            break;
        case 'n':
            macro_name = optarg;
            break;
        case 'l':
            line_width = strtoul(optarg, NULL, 10);
            break;
        case '?':
            fprintf(stderr, "Unknown option -%c\n", optopt);
            exit(EXIT_FAILURE);
            break;
        }
    }

    /* Validate macro name is a valid C symbol. */

    if (macro_name[0] != '_' && !isalpha(macro_name[0])) {
        fprintf(stderr, "Macro name `%s` does not start with a letter or underscore, and is not a valid C symbol.\n",
                macro_name);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < strlen(macro_name); i++) {

        char c = macro_name[i];

        if (!(isalnum(c) || c == '_')) {
            fprintf(stderr,
                    "Macro name `%s` is not a valid C symbol name consisting of only alphanumeric characters and "
                    "underscores.\n",
                    macro_name);
            exit(EXIT_FAILURE);
        }
    }

    /* Select input stream */

    FILE *in = stdin;
    if (infile != NULL) {
        in = fopen(infile, "r");
        if (in == NULL) {
            fprintf(stderr, "Could not open file '%s' for reading with error: %s\n", infile, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    /* Select output stream */

    FILE *out = stdout;
    if (outfile != NULL) {
        out = fopen(outfile, "w");
        if (out == NULL) {
            fprintf(stderr, "Could not open file '%s' for writing with error: %s\n", outfile, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    /* Remove some freedom from the line width limit because of opening and closing quotes, a space and `\` continuation
     * character.
     */
    line_width -= 4;

    /* Process the input text into a macro define. */

    fprintf(out, "#define %s \\\n", macro_name); // Macro name

    size_t column = 0; // Starts at column 0
    while (!feof(in)) {

        /* Add opening quotation marks */

        if (column == 0) {
            fputc('"', out);
        }

        /* Get next character from input */

        char c = fgetc(in);
        if (c == EOF) break;

        /* Check if character needs to be escaped and if there is less than 2 columns of room remaining. If so, the
         * character needs to be placed on the next line to preserve the desired line width. */
        if ((c == '\n' || c == '\t' || c == '\r' || c == '"') && (line_width - column < 2)) {
            fprintf(out, "\" \\\n");
            column = 0; // New line started
            continue;   // Go to next iteration
        }

        /* Write character to output file, handling characters that need escaping. */

        switch (c) {
        case '\n':
            fprintf(out, "\\n");
            column += 2;
            break;
        case '\r':
            fprintf(out, "\\r");
            column += 2;
            break;
        case '\t':
            fprintf(out, "\\t");
            column += 2;
            break;
        case '"':
            fprintf(out, "\\\"");
            column += 2;
            break;
        default:
            fputc(c, out);
            column++; // We've advanced a column now
            break;
        }

        /* If we've hit the line width limit, end the string and move on */

        if (column == line_width) {
            fprintf(out, "\" \\\n");
            column = 0; // New line started
        }
    }

    /* EOF has been reached, end the macro if it didn't happen to be finished already. */

    if (column != 0) {
        fprintf(out, "\"\n");
    }

    return EXIT_SUCCESS;
}
