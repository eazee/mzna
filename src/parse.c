#include "include/mzna.h"

char nextch(FILE* infile, int* row, int* col) {
    char c;
    c = fgetc(infile);
    if(c == '\n') {
        (*row)++;
        (*col) = 0;
    } else {
        (*col)++;
    }
    return c;
}

char peek(FILE *infile) {
    char c;
    c = fgetc(infile);
    ungetc(c, infile);
    return c;
}

int parse(FILE* infile) {
    int row = 1, col = 0;
    char c;

    while(1) {
        c = nextch(infile, &row, &col);
        if(c == EOF) break;

        // FOR NOW just ignore newlines
        if(c == '\n') continue;

        // Comments
        if(c == '#') {
            do {
                c = nextch(infile, &row, &col);
                if(c == EOF) break;
            } while (c != '\n');
            printf("JUST FOUND A COMMENT\n");
            continue;
        }

        // Idents
        if(isalnum(c)) {
            // store the whole thing
            // loop
        }

        // Catch all else as error
        fprintf(stderr, "[%sParser Error%s] Unexpected '%c' at Row %d, Col %d\n", TRM_RED_BOLD, TRM_RESET, c, row, col);
        return 1;
    }
    return 1;
}