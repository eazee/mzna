#include "include/parse.h"
#include <stdlib.h>

int check_type(parse_stream_t* ps, int lookahead, token_type_t type_check) {
    int index = ps->i + lookahead;
    if(index < ps->t->size)
        return (ps->t->stream[index].type == type_check) ? 1 : 0;
    return 0;
}

int has_space(parse_stream_t* ps) {
    if(ps->i < ps->t->size)
        return 1;
    return 0;
}

int block(parse_stream_t* ps, ast_node_t* node) {}

int function(parse_stream_t* ps, ast_node_t* node) {
    ast_node_t* func_node = ast_node_new(FUNCTION, BODY);
    ast_node_add_child(node, func_node);
    ast_node_assign_string(func_node, ps->t->stream[ps->i].value);
}

// program := (assignment | function)*
int program(parse_stream_t* ps, ast_node_t* node) {
    // check if function declaration
    if(check_type(ps, 0, IDENT) && (check_type(ps, 1, PARAMOP) || (check_type(ps, 1, TYPE) && check_type(ps, 2, PARAMOP)))) {
        function(ps, node);
    }
    return 0;
}

int parse(token_stream_t* ts, ast_node_t* root_node) {
    parse_stream_t ps = {0, ts};
    int status = program(&ps, root_node);   // 0 = success, anything else is fail
    return status;
}