#include "include/mzna.h"

void TokenStream_init(TokenStream* ts) {
    ts->max = TOKEN_STREAM_BUFFER;
    ts->size = 0;
    ts->stream = (Token*) malloc(ts->max*sizeof(Token));
}

void TokenStream_add(TokenStream* ts, int row, int col, char* value, token_type_t toktype) {
    if(ts->size >= ts->max) {
        ts->max += TOKEN_STREAM_INCREM;
        ts->stream = (Token*) realloc(ts->stream, ts->max * sizeof(Token));
    }
    ts->stream[ts->size].row = row;
    ts->stream[ts->size].col = col;
    ts->stream[ts->size].type = toktype;
    ts->stream[ts->size].value = (char*) malloc(strlen(value) + 1);
    strcpy(ts->stream[ts->size].value, value);
    ts->size++;
}

void TokenStream_destroy(TokenStream* ts) {
    for(int i = 0; i < ts->size; i++) {
        free(ts->stream[i].value);
    }
    free(ts->stream);
}