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

int string_not_terminated(char c) {
    switch(c) {
        case('"'):
            return 0;
        case(EOF):
            return -1;
        default:
            return 1;
    }
}

int lex(FILE* infile, token_stream_t* ts) {
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
            token_stream_add(ts, row, col, ":", COLON);
            continue;
        }

        // Assignment operator (->) OR minus sign
        if(c == '-') {
            if(peek(infile) == '>') {
                token_stream_add(ts, row, col, "->", ASSOP);
                nextch(infile, &row, &col);
                continue;
            } else {
                token_stream_add(ts, row, col, "-", MINUSOP);
                continue;
            }
        }

        // Parameter operator (<-) OR less than sign (<) OR less than or equal sign (<=)
        if(c == '<') {
            if(peek(infile) == '-') {
                token_stream_add(ts, row, col, "<-", PARAMOP);
                nextch(infile, &row, &col);
                continue;
            } else if(peek(infile) == '=') {
                token_stream_add(ts, row, col, "<=", LESSTHANOREQ);
                nextch(infile, &row, &col);
                continue;
            } else {
                token_stream_add(ts, row, col, "<", LESSTHAN);
                continue;
            }
        }

        // Greater than (>) OR greater than or equal (>=)
        if(c == '>') {
            if(peek(infile) == '=') {
                token_stream_add(ts, row, col, ">=", GREATERTHANOREQ);
                nextch(infile, &row, &col);
                continue;
            } else {
                token_stream_add(ts, row, col, ">", GREATERTHAN);
                continue;
            }
        }

        // Equality comparison operator (=?)
        if(c == '=') {
            if(peek(infile) == '?') {
                token_stream_add(ts, row, col, "=?", COMPOP);
                nextch(infile, &row, &col);
                continue;
            }
        }

        // Comma (,)
        if(c == ',') {
            token_stream_add(ts, row, col, ",", COMMA);
            continue;
        }

        // plus (+) OR plus assignment op (+->)
        if(c == '+') {
            if(fgetc(infile) == '-' && fgetc(infile) == '>') {
                token_stream_add(ts, row, col, "+->", ADDASSOP);
                col += 2;
                continue;
            } else {
                ungetc('>', infile);
                ungetc('-', infile);
                token_stream_add(ts, row, col, "+", ADDOP);
                continue;
            }
        }
        // divide (/)
        if(c == '/') {
            token_stream_add(ts, row, col, "/", DIVOP);
            continue;
        }
        // multiply (*)
        if(c == '*') {
            token_stream_add(ts, row, col, "*", MULTOP);
            continue;
        }

        // Number literals
        if(isdigit(c) || (c == '.' && isdigit(peek(infile)))) {
            size_t strsize = INIT_DIGIT_BUFFER;
            char*  numstr  = malloc(strsize);
            int    i       = 0;
            int    srow    = row;
            int    scol    = col;
            char   testc;

            while(1) {
                numstr[i] = c;
                i++;
                if(i > strsize) {
                    strsize += INCR_DIGIT_BUFFER;
                    numstr = realloc(numstr, strsize);
                }

                testc = peek(infile);
                if(isdigit(testc) || testc == '.') {
                    c = nextch(infile, &row, &col);
                } else {
                    break;
                }
            }

            numstr[i] = '\0';
            token_stream_add(ts, srow, scol, numstr, NUMBER);
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
            char   test_c;

            while(1) {
                identstr[i] = c;
                test_c = peek(infile);
                
                i++;
                if(i > strsize) {
                    strsize += INCR_IDENT_BUFFER;
                    identstr = realloc(identstr, strsize);
                }

                if(isalnum(test_c) || test_c == '_') {
                    c = nextch(infile, &row, &col);
                } else {
                    break;
                }
            }

            identstr[i] = '\0';
            if(strcmp(identstr, "in") == 0) {
                token_stream_add(ts, srow, scol, identstr, IN);
            } else if(strcmp(identstr, "program") == 0) {
                token_stream_add(ts, srow, scol, identstr, PROGRAM);
            } else {
                token_stream_add(ts, srow, scol, identstr, IDENT);
            }
            free(identstr);
            continue;
        }

        // String literals
        if(c == '"') {
            int   term;
            int   srow = row, scol = col;
            char  testc  = peek(infile);
            int   len    = 0;
            int   size   = INIT_STRLIT_BUFFER;
            char* strlit = malloc(size);

            while((term = string_not_terminated(testc)) == 1) {
                c = nextch(infile, &row, &col);
                strlit[len] = c;
                testc = peek(infile);
                len++;
                if(len >= size) {
                    size += INCR_STRLIT_BUFFER;
                    strlit = realloc(strlit, size);
                }
            }

            if(term == -1) {
                fprintf(stderr, "[%sParser Error%s] Unexpected end of file. Expecting termination of string literal at Row %d, Col %d\n",
                    TRM_RED_BOLD, TRM_RESET, row, col);
                return 1;
            }

            strlit[len] = '\0';
            token_stream_add(ts, srow, scol, strlit, STRING);
            free(strlit);
            nextch(infile, &row, &col);
            continue;
        }

        // Catch all else as error
        fprintf(stderr, "[%sParser Error%s] Unexpected '%c' at Row %d, Col %d\n", TRM_RED_BOLD, TRM_RESET, c, row, col);
        return 1;
    }
    return 1;
}