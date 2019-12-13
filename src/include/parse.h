#ifndef _parse_h
#define _parse_h

typedef enum { IDENT } token_type_t;
typedef struct {
    int row;
    int col;
    char* value;
    token_type_t type;
} Token;

int parse(FILE* infile);

#endif