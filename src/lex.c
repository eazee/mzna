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

int lex(FILE* infile, TokenStream* ts) {
    int row = 1, col = 0;
    char c;

    while(1) {
        c = nextch(infile, &row, &col);
        if(c == EOF) break;

        // FOR NOW just ignore newlines
        if(c == '\n') continue;

        // Ignore whitespace
        if(c == ' ') continue;

        // Comments
        if(c == '#') {
            do {
                c = nextch(infile, &row, &col);
                if(c == EOF) break;
            } while (c != '\n');
            continue;
        }

        // Colon (:)
        if(c == ':') {
            TokenStream_add(ts, row, col, ":", COLON);
            continue;
        }

        // Assignment operator (->) OR minus sign
        if(c == '-') {
            if(peek(infile) == '>') {
                TokenStream_add(ts, row, col, "->", ASSOP);
                nextch(infile, &row, &col);
                continue;
            } else {
                TokenStream_add(ts, row, col, "-", MINUSOP);
                continue;
            }
        }

        // Integer literals
        if(isdigit(c) || (c == '.' && isdigit(peek(infile)))) {
            size_t strsize = INIT_DIGIT_BUFFER;
            char*  numstr  = malloc(strsize);
            int    i       = 0;
            int    srow    = row;
            int    scol    = col;

            do {
                numstr[i] = c;
                c = nextch(infile, &row, &col);
                i++;
                if(i > strsize) {
                    strsize += INRC_DIGIT_BUFFER;
                    numstr = realloc(numstr, strsize);
                }
            } while(isdigit(c) || c == '.');
            ungetc(c, infile);
            numstr[i] = '\0';
            TokenStream_add(ts, row, col, numstr, NUMBER);
            free(numstr);
            continue;
        }

        // Idents and keywords
        if(isalpha(c)) {
            size_t strsize  = INIT_IDENT_BUFFER;
            char*  identstr = malloc(strsize);
            int    i        = 0;
            int    srow     = row;
            int    scol     = col;

            do {
                identstr[i] = c;
                c = nextch(infile, &row, &col);
                i++;
                if(i > strsize) {
                    strsize += INCR_IDENT_BUFFER;
                    identstr = realloc(identstr, strsize);
                }
            } while(isalnum(c));
            ungetc(c, infile);
            identstr[i] = '\0';
            if(strcmp(identstr, "in") == 0) {
                TokenStream_add(ts, srow, scol, identstr, IN);
            } else if(strcmp(identstr, "program") == 0) {
                TokenStream_add(ts, srow, scol, identstr, PROGRAM);
            } else {
                TokenStream_add(ts, srow, scol, identstr, IDENT);
            }
            free(identstr);
            continue;
        }

        // String literals
        if(c == '"') {
            int   strsize = INIT_STRLIT_BUFFER;
            char* litstr  = malloc(strsize);
            int   i       = 0;
            int   srow    = row;
            int   scol    = col;
            c             = nextch(infile, &row, &col);

            while(c != '"') {
                if(c == EOF) {
                    fprintf(stderr, "[%sParser Error%s] Unexpected end of file. Expected end of string literal at Row %d, Col %d\n",
                        TRM_RED_BOLD, TRM_RESET, row, col);
                    return 1;
                }
                litstr[i] = c;
                c = nextch(infile, &row, &col);
                i++;
                if(i > strsize) {
                    strsize += INCR_STRLIT_BUFFER;
                    litstr = realloc(litstr, strsize);
                }
            }
            litstr[i] = '\0';
            TokenStream_add(ts, srow, scol, litstr, STRING);
            free(litstr);
            continue;
        }

        // Catch all else as error
        fprintf(stderr, "[%sParser Error%s] Unexpected '%c' at Row %d, Col %d\n", TRM_RED_BOLD, TRM_RESET, c, row, col);
        return 1;
    }
    return 1;
}