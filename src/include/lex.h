#ifndef _lex_h
#define _lex_h

#define INIT_IDENT_BUFFER  12
#define INCR_IDENT_BUFFER  12
#define INIT_STRLIT_BUFFER 32
#define INCR_STRLIT_BUFFER 32
#define INIT_DIGIT_BUFFER  6
#define INCR_DIGIT_BUFFER  6

#define TOKEN_STREAM_BUFFER 128
#define TOKEN_STREAM_INCREM 64

#include <stdio.h>      // FILE, fgetc, ungetc, fprintf, size_t

typedef enum { IDENT, STRING, NUMBER, ASSOP, PARAMOP,
    COLON, ADDOP, MINUSOP, MULTOP, DIVOP, GREATERTHAN, GREATERTHANOREQ,
    LESSTHAN, LESSTHANOREQ, COMPOP, COMMA, TYPE, ADDASSOP, MINUSASSOP,
    DIVASSOP, MULTASSOP, NEWLINE } token_type_t;
typedef struct {
    int row;
    int col;
    char* value;
    token_type_t type;
} token_t;
typedef struct {
    size_t max;
    size_t size;
    token_t* stream;
} token_stream_t;

/* lex.c */
int lex(FILE* infile, token_stream_t* ts);

/* token.c */
void token_stream_init(token_stream_t* ts);
void token_stream_add(token_stream_t* ts, int row, int col, char* value, token_type_t toktype);
void token_stream_destroy(token_stream_t* ts);

#endif /* _lex_h */