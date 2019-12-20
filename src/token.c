#include "include/lex.h"
#include <string.h>         // strcpy
#include <stdlib.h>         // malloc, realloc, free

void token_stream_init(token_stream_t* ts) {
    ts->max = TOKEN_STREAM_BUFFER;
    ts->size = 0;
    ts->stream = (token_t*) malloc(ts->max*sizeof(token_t));
}

void token_stream_add(token_stream_t* ts, int row, int col, char* value, token_type_t toktype) {
    if(ts->size >= ts->max) {
        ts->max += TOKEN_STREAM_INCREM;
        ts->stream = (token_t*) realloc(ts->stream, ts->max * sizeof(token_t));
    }
    ts->stream[ts->size].row = row;
    ts->stream[ts->size].col = col;
    ts->stream[ts->size].type = toktype;
    ts->stream[ts->size].value = (char*) malloc(strlen(value) + 1);
    strcpy(ts->stream[ts->size].value, value);
    ts->size++;
}

void token_stream_destroy(token_stream_t* ts) {
    for(int i = 0; i < ts->size; i++) {
        free(ts->stream[i].value);
    }
    free(ts->stream);
}