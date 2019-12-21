#include "include/parse.h"
#include <stdlib.h>

int program(token_stream_t* ts, ast_node_t* node) {
    
}

int parse(token_stream_t* ts) {
    ast_node_t* root_node = (ast_node_t*) malloc(sizeof(ast_node_t));
    ast_node_init(root_node, ROOT, NOREL);

    program(ts, root_node);

    ast_node_destroy(root_node);
    return 0;
}