#ifndef _parse_h
#define _parse_h

#define INIT_IDENT_BUFFER  12
#define INCR_IDENT_BUFFER  12
#define INIT_STRLIT_BUFFER 32
#define INCR_STRLIT_BUFFER 32
#define INIT_DIGIT_BUFFER  6
#define INRC_DIGIT_BUFFER  6

#define TOKEN_STREAM_BUFFER 128
#define TOKEN_STREAM_INCREM 64

typedef enum { IDENT, IN, PROGRAM, STRING, NUMBER, ASSOP, COLON,
    ADDOP, MINUSOP, MULTOP, DIVOP  } token_type_t;
typedef struct {
    int row;
    int col;
    char* value;
    token_type_t type;
} Token;
typedef struct {
    size_t max;
    size_t size;
    Token* stream;
} TokenStream;

/* parse.c */
int parse(FILE* infile, TokenStream* ts);

/* token.c */
void TokenStream_init(TokenStream* ts);
void TokenStream_add(TokenStream* ts, int row, int col, char* value, token_type_t toktype);
void TokenStream_destroy(TokenStream* ts);

#endif